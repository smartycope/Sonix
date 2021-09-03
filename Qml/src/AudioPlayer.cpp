#include "AudioPlayer.hpp"

#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QByteArray>
#include <QDebug>
#include <qaudiooutput.h>
#include "Global.hpp"
#include "sonic.h"


int AudioPlayer::_samplerate = 44100;
int AudioPlayer::_channels = 2;

double AudioPlayer::_speed = 1.0;
int   AudioPlayer::linVolume = 99;
float AudioPlayer::_pitch = 1.0f;
float AudioPlayer::_rate = 1.0f;
bool  AudioPlayer::_emulateChordPitch = 0;
bool  AudioPlayer::_enableNonlinearSpeedup = 0;
bool  AudioPlayer::_highQuality = 0;
float AudioPlayer::_speedIncrement = 0.25f;
float AudioPlayer::_volumeIncrement = 5;
int   AudioPlayer::_skipSeconds = 15;

ulong AudioPlayer::bytesRead = 0;
const int AudioPlayer::updateMS = 5;


const std::string AudioPlayer::printQAudioError(QAudio::Error err){
    switch(err){
        case QAudio::NoError:
            return std::string("NoError");
            break;
        case QAudio::OpenError:
            return std::string("OpenError");
            break;
        case QAudio::IOError:
            return std::string("IOError");
            break;
        case QAudio::UnderrunError:
            return std::string("UnderrunError");
            break;
        case QAudio::FatalError:
            return std::string("FatalError");
            break;
        default:
            return std::string("PROBLEM");
    }
}

const std::string AudioPlayer::printQAudioState(QAudio::State state){
    switch(state){
        case QAudio::IdleState:
            return std::string("Idle");
            break;
        case QAudio::StoppedState:
            return std::string("Stopped");
            break;
        case QAudio::SuspendedState:
            return std::string("Suspended");
            break;
        case QAudio::ActiveState:
            return std::string("Active");
            break;
        case QAudio::InterruptedState:
            return std::string("Interrupted");
            break;
        default:
            return std::string("PROBLEM");
    }
}

void AudioPlayer::setVolume(int to){
    linVolume = to;
    logVolume = QAudio::convertVolume(qreal(to) / qreal(100.0), QAudio::LogarithmicVolumeScale, QAudio::LinearVolumeScale);
    audioOut->setVolume(logVolume);
}

int AudioPlayer::getVolume(){
    return linVolume;
}


AudioPlayer::AudioPlayer(Book* book): callbackTimer(new QTimer(this)){
    //* These are book-independant. Set these even if no filepath was provided
    linVolume = Global::args->get<int>("--volume");
    _speed = Global::args->get<float>("--speed");
    _rate = Global::args->get<float>("--rate");
    _pitch = Global::args->get<float>("--pitch");
    _emulateChordPitch = Global::args->get<bool>("--emulateChordPitch");
    _enableNonlinearSpeedup = Global::args->get<bool>("--enableNonlinearSpeedup");
    _highQuality = Global::args->get<bool>("--increaseQuality");
    _samplerate = Global::args->get<int>("--samplerate");
    _channels = Global::args->get<int>("--channels");

    const QAudioDeviceInfo deviceInfo = QAudioDeviceInfo::defaultOutputDevice();
    QAudioFormat format;
    format.setSampleRate(_samplerate);
    format.setChannelCount(_channels);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    if (!deviceInfo.isFormatSupported(format)) {
        if (Global::verbose)
            Global::log("Default audio format not supported - trying to use nearest");
        format = deviceInfo.nearestFormat(format);
    }

    audioOut.reset(new QAudioOutput(deviceInfo, format));
    pipe.reset(new QFile);

    setVolume(linVolume);

    sStream = sonicCreateStream(_samplerate, _channels);
    assert(sStream);
    sonicSetSpeed(sStream, _speed);
    sonicSetPitch(sStream, _pitch);
    sonicSetRate(sStream, _rate);
    // sonicSetVolume(sStream, getVolume();
    sonicSetChordPitch(sStream, _emulateChordPitch);
    sonicSetQuality(sStream, _highQuality);

    if (book)
        pipe->open(book->open(), QIODevice::ReadOnly);

    io = audioOut->start();

    if (not book)
        audioOut->stop();

    // Alright, so let me expalin.
    // audioOut is a QScopedPointer, which cannot implicitly cast to a QObject*, so I need to
    // dereference the QScopedPointer, then re-reference it as a QAudioOutput*, which can be
    // cast to a QObject*.
    // connect(&(*audioOut), &QAudioOutput::stateChanged, this, &AudioPlayer::audioStateChanged);
    connect(&(*audioOut), SIGNAL(stateChanged(QAudio::State)), this, SLOT(audioStateChanged(QAudio::State)));


    connect(callbackTimer, &QTimer::timeout, this, &AudioPlayer::workhorseFunc);

    if (book)
        callbackTimer->start(updateMS);
}

AudioPlayer::~AudioPlayer(){
    callbackTimer->stop();
    sonicDestroyStream(sStream);
}

//* This is the main callback function. This does all the heavy lifting
void AudioPlayer::workhorseFunc(){
    if (audioOut->state() == QAudio::StoppedState)
        return;

    // Don't ask me where 32768 came from, it was part of the example when I copied it here, and I'm afraid to touch it
    QByteArray pipeBuffer(32768, 0);
    QByteArray sonicBuffer(32768, 0);
    int chunks = audioOut->bytesFree() / audioOut->periodSize();
    while (chunks) {
        // reads and readp are in bytes
        int reads = 0;
        do{
            int readp = pipe->read(pipeBuffer.data(), audioOut->periodSize() - reads);
            AudioPlayer::bytesRead += readp;

            //* Remember, sonic takes the count in samples, not bytes
            assert(sonicWriteCharToStream(sStream, pipeBuffer.data(), readp / _channels));
            reads += sonicReadCharFromStream(sStream, sonicBuffer.data() + reads, (audioOut->periodSize() - reads) / _channels) * _channels;
        } while(reads < audioOut->periodSize());
        // _debug(reads)
        io->write(sonicBuffer.data(), audioOut->periodSize());
        --chunks;
    }
}

void AudioPlayer::updateBook(Book* book){
    assert(book);

    pipe.reset(new QFile);
    pipe->open(book->open(), QIODevice::ReadOnly);
    callbackTimer->start(updateMS);
    audioOut->resume();
}

void AudioPlayer::finished(){
    pass
}

void AudioPlayer::togglePause(bool dummyparam){
    if (audioOut->state() == QAudio::SuspendedState or audioOut->state() == QAudio::StoppedState) {
        audioOut->resume();
    } else if (audioOut->state() == QAudio::ActiveState) {
        audioOut->suspend();
    } else if (audioOut->state() == QAudio::IdleState) {
        pass
    }
}

void AudioPlayer::audioStateChanged(QAudio::State state){
    if (Global::verbose){
        _debugs(printQAudioError(audioOut->error()).c_str());
        _debugs(printQAudioState(state).c_str());
    }

    switch(state) {
        case QAudio::IdleState:
        case QAudio::StoppedState: break;
        case QAudio::SuspendedState: break;
        case QAudio::ActiveState: break;
        case QAudio::InterruptedState: break;
        default:
            _debugs("Something has gone horribly wrong");
            exit(99);
            break;
    }
}

void AudioPlayer::setSamplerate(int to){
    _samplerate = to;
}

void AudioPlayer::setChannels(int to){
    _channels = to;
}

void AudioPlayer::setSpeedIncrement(float to){
    _speedIncrement = to;
}

void AudioPlayer::setVolumeIncrement(float to){
    _volumeIncrement = to;
}

void AudioPlayer::setSkipSeconds(int to){
    _skipSeconds = to;
}

void AudioPlayer::setSpeed(double to){
    _speed = to;
    sonicSetSpeed(sStream, to);
}

void AudioPlayer::setPitch(float to){
    _pitch = to;
    sonicSetPitch(sStream, to);
}

void AudioPlayer::setRate(float to){
    _rate = to;
    sonicSetRate(sStream, to);
}

void AudioPlayer::setEmulateChordPitch(bool to){
    _emulateChordPitch = to;
    sonicSetChordPitch(sStream, to);
}

void AudioPlayer::setHighQuality(bool to){
    _highQuality = to;
    sonicSetQuality(sStream, to);
}

void AudioPlayer::setEnableNonlinearSpeedup(bool to){
    _enableNonlinearSpeedup = to;
    if (Global::verbose)
        todo("enableNonlinearSpeedup");
}

void AudioPlayer::flushStream(){
    if (Global::verbose)
        todo("Flush audio player");
}

void AudioPlayer::skip(int amount){
    todo("skip");
    // if (outputPosition + (amount * CHANNELS) < 0)
    //     outputPosition = 0;
    // else if (outputPosition + (amount * CHANNELS) > book->frames)
    //     outputPosition = book->frames;
    // else
    //     outputPosition += amount * CHANNELS;

    // // book->pos = (int)(outputPosition / CHANNELS);
    // book->sampleProvider.pos += amount;
    // flushStream();
}

void AudioPlayer::jump(int chapters){
    todo("jump");
}

void AudioPlayer::updateSpeed(){
    setSpeed(Global::getUIProperty("speedControl", "value").toDouble() / 100.0);
}

void AudioPlayer::updateChapter(){
    noteCall();
}

void AudioPlayer::incrementSpeed(){
    notecall()
    setSpeed(_speed + _speedIncrement);
}

void AudioPlayer::incrementVolume(){
    setVolume(getVolume() + _volumeIncrement);
}

void AudioPlayer::decrementSpeed(){
    setSpeed(_speed - _speedIncrement);
}

void AudioPlayer::decrementVolume(){
    setVolume(getVolume() - _volumeIncrement);
}

void AudioPlayer::skipForward(){
    notecall()
    skip(_skipSeconds);
}

void AudioPlayer::skipBackward(){
    notecall()
    skip(-_skipSeconds);
}

void AudioPlayer::jumpForward(){
    notecall()
    jump(1);
}

void AudioPlayer::jumpBackward(){
    notecall()
    jump(-1);
}
