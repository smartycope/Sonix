#include "AudioPlayer.hpp"

// #include <QAudioDeviceInfo>
// #include <QAudioOutput>
#include <QByteArray>
#include "Global.hpp"


// Initializing the static members
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

const int AudioPlayer::updateMS = 5;


// These are all static
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
    // This *shouldn't* be nessicary, but if I don't do it here, other bad things happen elsewhere
    assert(book);
    b = book;

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

    // Set up the format we're using (pcm, 8 bit, unsigned)
    const QAudioDeviceInfo deviceInfo = QAudioDeviceInfo::defaultOutputDevice();
    QAudioFormat format;
    format.setSampleRate(_samplerate);
    format.setChannelCount(_channels);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    // Make sure that format is actually supported (It better be...)
    if (!deviceInfo.isFormatSupported(format)) {
        if (Global::verbose)
            Global::log("Default audio format not supported - trying to use nearest");
        format = deviceInfo.nearestFormat(format);
    }

    // Initialize audioOut
    audioOut.reset(new QAudioOutput(deviceInfo, format));

    setVolume(linVolume);

    // Set up sonic
    sStream = sonicCreateStream(_samplerate, _channels);
    assert(sStream);
    sonicSetSpeed(sStream, _speed);
    sonicSetPitch(sStream, _pitch);
    sonicSetRate(sStream, _rate);
    // sonicSetVolume(sStream, getVolume();
    sonicSetChordPitch(sStream, _emulateChordPitch);
    sonicSetQuality(sStream, _highQuality);

    b->open();

    // This starts the audio playback
    io = audioOut->start();

    // Maybe I should change this?...
    if (not b)
        audioOut->stop();

    // Alright, so let me expalin.
    // audioOut is a QScopedPointer, which cannot implicitly cast to a QObject*, so I need to
    // dereference the QScopedPointer, then re-reference it as a QAudioOutput*, which can be
    // cast to a QObject*.
    // connect(&(*audioOut), &QAudioOutput::stateChanged, this, &AudioPlayer::audioStateChanged);
    connect(&(*audioOut), SIGNAL(stateChanged(QAudio::State)), this, SLOT(audioStateChanged(QAudio::State)));

    // Check for new data every so often (workhorseFunc doesn't do anything if we don't need more data)
    connect(callbackTimer, &QTimer::timeout, this, &AudioPlayer::workhorseFunc);

    if (b)
        callbackTimer->start(updateMS);
}

AudioPlayer::~AudioPlayer(){
    callbackTimer->stop();
    sonicDestroyStream(sStream);
}

// Essentially what's happening here, is we're manually reading pipe (the QFile where ffmpeg is stuffing data
// in another thread), giving that data to sonic, and then reading data from sonic.
// However, samples into sonic != samples out of sonic (unless speed is at 1x), because we're speeding up the audio,
// and some of those samples are no longer needed. So what this is doing is just reading from the file and passing
// through sonic in a while loop, until we have enough samples. This is WAY easier (and faster) than trying to
// calculate the pitch and calculate the equation given in sonic.h. (Which is kinda sad, that's a cool equation)
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
            int readp = b->ffmpegFile.read(pipeBuffer.data(), audioOut->periodSize() - reads);

            //* Remember, sonic takes the count in samples, not bytes
            assert(sonicWriteCharToStream(sStream, pipeBuffer.data(), readp / _channels));
            reads += sonicReadCharFromStream(sStream, sonicBuffer.data() + reads, (audioOut->periodSize() - reads) / _channels) * _channels;
        } while(reads < audioOut->periodSize());
        io->write(sonicBuffer.data(), audioOut->periodSize());
        --chunks;
    }
}

void AudioPlayer::updateBook(Book* book){
    assert(book);
    b = book;

    b->open();
    callbackTimer->start(updateMS);
    audioOut->resume();
}

ulong AudioPlayer::pos(){
    return (b->ffmpegFile.pos() / _channels) / _samplerate;
}

void AudioPlayer::finished(){ }

void AudioPlayer::togglePause(bool dummyparam){
    if (audioOut->state() == QAudio::SuspendedState or audioOut->state() == QAudio::StoppedState) {
        audioOut->resume();
    } else if (audioOut->state() == QAudio::ActiveState) {
        audioOut->suspend();
    } else if (audioOut->state() == QAudio::IdleState) { }
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
    todo("enableNonlinearSpeedup");
}

void AudioPlayer::flushStream(){
    todo("Flush audio player");
}

// amount is in samples
void AudioPlayer::skip(int amount){
    b->ffmpegFile.skip(amount);
}

void AudioPlayer::jump(Chapter to){
    b->ffmpegFile.seek(to.startTime * _channels * _samplerate);
}

void AudioPlayer::updateSpeed(){
    setSpeed(Global::getUIProperty("speedControl", "value").toDouble() / 100.0);
}

void AudioPlayer::updateChapter(){
    todo("updateChapter");
}

void AudioPlayer::incrementSpeed(){
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
    skip(_skipSeconds);
}

void AudioPlayer::skipBackward(){
    skip(-_skipSeconds);
}

void AudioPlayer::jumpForward(){
    int currentChapter = b->getCurrentChapter(pos()).num;
    if (currentChapter < b->chapters().size())
        jump(b->chapters()[currentChapter + 1]);
}

void AudioPlayer::jumpBackward(){
    int currentChapter = b->getCurrentChapter(pos()).num;
    if (currentChapter > 0)
        jump(b->chapters()[currentChapter - 1]);
}
