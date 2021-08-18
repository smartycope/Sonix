#include "AudioPlayer.hpp"

#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QByteArray>
#include <QDebug>
#include "defs.h"
extern bool verbose;
// #include <qmath.h>
// #include <qendian.h>

int AudioPlayer::samplerate = 44100;
int AudioPlayer::channels = 2;

double AudioPlayer::speed = 1.0;
int   AudioPlayer::linVolume = 99;
float AudioPlayer::pitch = 1.0f;
float AudioPlayer::rate = 1.0f;
bool  AudioPlayer::emulateChordPitch = 0;
bool  AudioPlayer::enableNonlinearSpeedup = 0;
bool  AudioPlayer::highQuality = 0;
float AudioPlayer::speedIncrement = 0.25f;
float AudioPlayer::volumeIncrement = 5;
int   AudioPlayer::skipSeconds = 15;

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
    const QAudioDeviceInfo deviceInfo = QAudioDeviceInfo::defaultOutputDevice();
    QAudioFormat format;
    format.setSampleRate(samplerate);
    format.setChannelCount(channels);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    if (!deviceInfo.isFormatSupported(format)) {
        if (verbose)
            qWarning() << "Default format not supported - trying to use nearest";
        format = deviceInfo.nearestFormat(format);
    }

    audioOut.reset(new QAudioOutput(deviceInfo, format));
    pipe.reset(new QFile);

    setVolume(linVolume);

    sStream = sonicCreateStream(samplerate, channels);
    sonicSetSpeed(sStream, speed);
    sonicSetPitch(sStream, pitch);
    sonicSetRate(sStream, rate);
    // sonicSetVolume(sStream, getVolume();
    sonicSetChordPitch(sStream, emulateChordPitch);
    sonicSetQuality(sStream, highQuality);

    if (book)
        pipe->open(book->open(), QIODevice::ReadOnly);

    auto io = audioOut->start();

    if (not book)
        audioOut->stop();

    // connect(&audioOut, SIGNAL(stateChanged(QAudio::State)), this, SLOT(audioStateChanged(QAudio::State)));

    //* This is the main callback function. This does all the heavy lifting
    connect(callbackTimer, &QTimer::timeout, [this, io] {
        if (audioOut->state() == QAudio::StoppedState)
            return;

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
                assert(sonicWriteCharToStream(sStream, pipeBuffer.data(), readp / channels));
                reads += sonicReadCharFromStream(sStream, sonicBuffer.data() + reads, (audioOut->periodSize() - reads) / channels) * channels;
            } while(reads < audioOut->periodSize());
            io->write(sonicBuffer.data(), audioOut->periodSize());
            --chunks;
        }
    });

    if (book)
        callbackTimer->start(updateMS);
}

void AudioPlayer::updateBook(Book* book){
    assert(book);

    pipe->open(book->open(), QIODevice::ReadOnly);
    callbackTimer->start(updateMS);
    audioOut->resume();
}

AudioPlayer::~AudioPlayer(){
    callbackTimer->stop();
    sonicDestroyStream(sStream);
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
    if (verbose){
        _debugs(printQAudioError(audioOut->error()).c_str());
        _debugs(printQAudioState(state).c_str());
    }

    switch(state) {
        case QAudio::IdleState:
            if (verbose)
                _debugs("eof reached!");
            finished();
            break;
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

void AudioPlayer::setSpeed(double to){
    speed = to;
    sonicSetSpeed(sStream, to);
}

void AudioPlayer::setPitch(float to){
    pitch = to;
    sonicSetPitch(sStream, to);
}

void AudioPlayer::setRate(float to){
    rate = to;
    sonicSetRate(sStream, to);
}

void AudioPlayer::setEmulateChordPitch(bool to){
    emulateChordPitch = to;
    sonicSetChordPitch(sStream, to);
}

void AudioPlayer::setHighQuality(bool to){
    highQuality = to;
    sonicSetQuality(sStream, to);
}

void AudioPlayer::setEnableNonlinearSpeedup(bool to){
    enableNonlinearSpeedup = to;
    if (verbose)
        todo("enableNonlinearSpeedup");
}

void AudioPlayer::flushStream(){
    if (verbose)
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

void AudioPlayer::incrementSpeed(){
    setSpeed(speed + speedIncrement);
}

void AudioPlayer::incrementVolume(){
    setVolume(getVolume() + volumeIncrement);
}

void AudioPlayer::decrementSpeed(){
    setSpeed(speed - speedIncrement);
}

void AudioPlayer::decrementVolume(){
    setVolume(getVolume() - volumeIncrement);
}

void AudioPlayer::skipForward(){
    skip(skipSeconds);
}

void AudioPlayer::skipBackward(){
    skip(-skipSeconds);
}

void AudioPlayer::jumpForward(){
    jump(1);
}

void AudioPlayer::jumpBackward(){
    jump(-1);
}
