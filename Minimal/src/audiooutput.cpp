#include "audiooutput.h"

#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QDebug>
#include <qmath.h>
#include <qendian.h>



const int AudioPlayer::samplerate = 44100;
const int AudioPlayer::channels = 2;

float AudioPlayer::speed = 3.0f;
float AudioPlayer::pitch = 1.0f;
float AudioPlayer::rate = 1.0f;
int   AudioPlayer::emulateChordPitch = 0;
int   AudioPlayer::quality = 0;
int   AudioPlayer::enableNonlinearSpeedup = 0;

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

AudioPlayer::AudioPlayer(FILE* pipeFile): callbackTimer(new QTimer(this)){
    const QAudioDeviceInfo deviceInfo = QAudioDeviceInfo::defaultOutputDevice();
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    if (!deviceInfo.isFormatSupported(format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        format = deviceInfo.nearestFormat(format);
    }

    sStream = sonicCreateStream(samplerate, channels);
    sonicSetSpeed(sStream, speed);
    sonicSetPitch(sStream, pitch);
    sonicSetRate(sStream, rate);
    // sonicSetVolume(sStream, getVolume();
    sonicSetChordPitch(sStream, emulateChordPitch);
    sonicSetQuality(sStream, quality);

    // pipe.reset(new QFile("/home/marvin/hello/test.wav"));
    pipe.reset(new QFile);
    audioOut.reset(new QAudioOutput(deviceInfo, format));
    pipe->open(pipeFile, QIODevice::ReadOnly);

    qreal initialVolume = QAudio::convertVolume(audioOut->volume(),
                                                QAudio::LinearVolumeScale,
                                                QAudio::LogarithmicVolumeScale);
    volume = qRound(initialVolume * 100);

    auto io = audioOut->start();

    // connect(this, SIGNAL(stateChanged(QAudio::State)), this, SLOT(AudioPlayer::audioStateChanged(QAudio::State)));
    // connect(&QAudioOutput::stateChanged, audioStateChanged);

    connect(callbackTimer, &QTimer::timeout, [this, io] {
        if (audioOut->state() == QAudio::StoppedState)
            return;

        QByteArray pipeBuffer(32768, 0);
        QByteArray sonicBuffer(32768, 0);
        int chunks = audioOut->bytesFree() / audioOut->periodSize();
        while (chunks) {
            int reads = 0;
            do{
                int readp = pipe->read(pipeBuffer.data(), audioOut->periodSize() - reads);

                //* Remember, sonic takes the count in samples, not bytes
                assert(sonicWriteCharToStream(sStream, pipeBuffer.data(), readp / channels));
                reads += sonicReadCharFromStream(sStream, sonicBuffer.data() + reads, audioOut->periodSize() - reads) * channels;
            } while(reads < audioOut->periodSize());
            io->write(sonicBuffer.data(), reads);
            --chunks;
        }
    });

    callbackTimer->start(UPDATE_MS);
}

AudioPlayer::~AudioPlayer(){
    callbackTimer->stop();
    sonicDestroyStream(sStream);
}

void AudioPlayer::setVolume(int value){
    qreal linearVolume = QAudio::convertVolume(value / qreal(100),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);

    volume = linearVolume;
}

void AudioPlayer::togglePause(){
    if (audioOut->state() == QAudio::SuspendedState || audioOut->state() == QAudio::StoppedState) {
        audioOut->resume();
    } else if (audioOut->state() == QAudio::ActiveState) {
        audioOut->suspend();
    } else if (audioOut->state() == QAudio::IdleState) {
        // no-op
    }
}

void AudioPlayer::audioStateChanged(QAudio::State state){
    _debugs(printQAudioError(audioOut->error()).c_str());
    _debugs(printQAudioState(state).c_str());
    switch(state) {
        case QAudio::IdleState:
            // Finished playing (no more data)
            _debug("eof reached!");
            // if (book_finished)
            //     audioOut->stop();
            // else{
            //     if (audioOutDevice and audioOut->error()){
            //         _debugs(color("resetting audio...", COLOR_RESET).c_str())
            //         audioOutDevice->reset();
            //         audioOutDevice = audioOut->start();
            //     }
            // }

            // updateSonic();
            // sourceFile.close();
            // TODO consider closing the file here
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