#include "Player.h"
#include <QDebug>
#include <QtCore/qglobal.h>
#include <iostream>
#include <QByteArray>
//#include "cope.cpp"


std::string Player::printQAudioError(QAudio::Error err){
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

std::string Player::printQAudioState(QAudio::State state){
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

void Player::jumpBackward(){
    note(jumpBackward called!)
}

void Player::jumpForward(){
    note(jumpForward called!)
}

void Player::skipForward(){
    note(skipForward called!)
}

void Player::skipBackward(){
    note(skipBackward called!)
}

void Player::togglePause(){
    // note(togglePause called!)

    // _playing = not _playing;
    pauseChanged(not _playing);
}

void Player::pauseChanged(bool set){
    // note()
    _playing = set;
    _debug(_playing)
    if (_playing)
        audioOut->resume();
    else
        audioOut->suspend();

}

Player::~Player(){
    sonicDestroyStream(sStream);
    delete audioOut;
    delete audioBuffer;
}

void Player::audioStateChanged(QAudio::State state){
    debugs(printQAudioError(audioOut->error()).c_str());
    debugs(printQAudioState(state).c_str());
    switch(state) {
        case QAudio::IdleState:
            // Finished playing (no more data)
            if (book_finished)
                audioOut->stop();
            else{
                if (audioOutDevice and audioOut->error()){
                    debugs(color("resetting audio...", COLOR_RESET).c_str())
                    audioOutDevice->reset();
                    audioOutDevice = audioOut->start();
                }
            }

            // updateSonic();
            // sourceFile.close();
            // TODO consider closing the file here
            break;

        case QAudio::StoppedState: break;
        case QAudio::SuspendedState: break;
        case QAudio::ActiveState: break;
        case QAudio::InterruptedState: break;

        default:
            debugs("Something has gone horribly wrong");
            quit(99);
            break;
    }
}


void Player::updateSonic(){
    // audioBuffer << sourceFile;

    // char transportBuffer[audioOut->periodSize()];

    int timeout = 1000;

    // sourceFile.open(QIODevice::ReadOnly);
    // sourceFile.seek(filePosition);
    // _debug(sourceFile.waitForReadyRead(timeout))
    // audioBuffer->setData();
    int actuallyRead = sourceFile->read(transportBuffer, audioOut->periodSize());
    // filePosition += actuallyRead;
    // sourceFile.close();
    // _debug(sourceFile.waitForBytesWritten(timeout))
    // int actuallyWritten = audioOutDevice->write(transportBuffer, actuallyRead);
    qint64 actuallyWritten;
    // audioOutDevice->waitForReadyWrite()


    // if(audioOutDevice->isOpen() && audioOut->state() != QAudio::StoppedState)
    actuallyWritten = audioOutDevice->write(transportBuffer, audioOut->periodSize());




    _debug(actuallyRead, 3)
    _debug(actuallyWritten, 3)
    _debug(audioOutDevice->waitForBytesWritten(timeout));
    _debug(audioOut->periodSize());
    // _debug(audioOut->bytesFree())
    // _debug(audioOut->bufferSize())
    // _debug(audioOut->elapsedUSecs())
    // _debug(audioOut->processedUSecs())
    _debug(audioOut->elapsedUSecs() - audioOut->processedUSecs())

    // _debug(printQAudioState(audioOut->state()).c_str())
    // _debug(printQAudioError(audioOut->error()).c_str())
    // _debug(audioOutDevice->bytesAvailable())
    // _debug(audioOutDevice->atEnd())
    // _debug(audioOutDevice->bytesToWrite())
    // _debug(audioOutDevice->canReadLine())
    // _debug(audioOutDevice->errorString().toStdString().c_str())
    // _debug(audioOutDevice->isOpen())
    // _debug(audioOutDevice->isReadable())
    // _debug(audioOutDevice->isSequential())
    // _debug(audioOutDevice->isTextModeEnabled())
    // _debug(audioOutDevice->isTransactionStarted())
    // _debug(audioOutDevice->isWritable())
    _debug(audioOutDevice->pos())
    // _debug(audioOutDevice->readChannelCount())
    // _debug(audioOutDevice->size())






    /*
    int currentSamples, samplesRead;
    unsigned char transportBuffer[2048];

    while((outputPosition + (samplesNeeded * fileInfo.channels) + 1) > sonicPosition){
        // seek to our current file position
        sf_seek(file, filePosition, SEEK_SET);

        // are we going to read past the end of the file?
        if (samplesNeeded > (fileInfo.frames - filePosition)){
            // if we are, only read to the end of the file
            currentSamples = fileInfo.frames - filePosition;
            // and then loop to the beginning of the file
            //TODO Change this eventually
            // data->filePosition = 0;
            // return paAbort;
        }
        else{
            // otherwise, we'll just fill up the rest of the output buffer
            currentSamples = samplesNeeded;
            // and increment the file position
            filePosition += currentSamples;
        }

        sf_read_raw(file, transportBuffer, currentSamples);
        sonicWriteUnsignedCharToStream(sStream, transportBuffer, currentSamples);

        do{
            samplesRead = sonicReadUnsignedCharFromStream(sStream, sonicBuffer + sonicPosition, currentSamples);
            sonicPosition += samplesRead * fileInfo.channels;

        //* While there's still stuff to be read
        } while (samplesRead > 0);

    //* Just keep calling it until we have enough
    }

    // int prevPos = outputPosition;
    // for(int i = 0; i < samplesNeeded * fileInfo.channels; i++){
    //    audioBuffer->setData([i] = data->sonicBuffer[data->outputPosition];
    // audioBuffer->close();
    //*  audioBuffer->setData((char*)sonicBuffer + outputPosition, samplesNeeded * fileInfo.channels);
    // audioBuffer->open(QBuffer::ReadWrite);





    //*  read frames
    // int len = m_bytearray.length() - mPos;
    // int bytesWritten = mPosEnd - mPos;

    // if(len>=audio->periodSize()){
    //     m_audiodevice->write(m_bytearray.data()+mPos, bytesWritten);
    // }
    // else{

    //     w_data.replace(0,qAbs(len),m_bytearray.data()+mPos);
    //     w_data.replace(qAbs(len),audio->periodSize()-abs(len),m_bytearray.data());
    //    m_audiodevice->write(w_data.data(),audio->periodSize());
    // }

    // if(audioBuffer->isOpen() && audioOut->state() != QAudio::StoppedState) {
        note(made it here!)
        qint64 bytesOfAudioWrittenToDevice = audioBuffer->write((char*)sonicBuffer + outputPosition, audioOut->periodSize());
        // audio_bytesRemainingToRead -= bytesOfAudioWrittenToDevice;
        qDebug() << "Wrote" << bytesOfAudioWrittenToDevice << "bytes of audio to output device.";// Remaining bytes to read:" << audio_bytesRemainingToRead;
        qDebug() << "Free bytes in audio output:" << audioOut->bytesFree();
    // }

    //* write frames
        // qint32* buffer;
        // int frameSize, byteCount=0;
        // DWORD tdFrames, fdFrames;
        // float fvalue = 0;
        // qint32 q32value;

        // frameSize = 40 * mBlockSize; //40 mics
        // buffer = new int[frameSize];
        // int periodBytes = audio->periodSize();
        // int freeBytes = audio->bytesFree();
        // int chunks = qMin(periodBytes/mBlockSize,freeBytes/mBlockSize);

        // CcmStartInput();

        // while(chunks){
        //     CcmReadFrames(buffer,NULL,frameSize,0,&tdFrames,&fdFrames,NULL,CCM_WAIT);
        //     if(tdFrames==0){
        //         break;
        //     }
        //     int diffBytes = periodBytes - byteCount;

        //     if(diffBytes>=(int)sizeof(q32value)*mBlockSize){
        //         for(int x=0;x<mBlockSize;x++){
        //             q32value = (quint32)buffer[x]/256;
        //            *mstream << (qint32)fvalue;
        //             byteCount+=sizeof(q32value);
        //         }
        //     }
        //     else{
        //         for(int x=0;x<(diffBytes/(int)sizeof(q32value));x++){
        //             q32value = (quint32)buffer[x]/256;
        //             *mstream << (qint32) fvalue;
        //             byteCount+=sizeof(q32value);
        //         }
        //     }
        //     --chunks;
        // }
        // CcmStopInput();
        // mPosEnd = mPos + byteCount;
        // write_frames();
        // mPos += byteCount;
        // if(mPos >= m_bytearray.length()){
        //       mPos = 0;
        //       mstream->device()->seek(0); //change mstream pointer back to bytearray start
        // }






    // QDataStream intoAudioBuffer(sonicBuffer);
    // intoAudioBuffer << sonicBuffer + outputPosition;
    outputPosition += samplesNeeded * fileInfo.channels;
    //    ++outputPosition
    // }

    */
}


void Player::init(){
    // connect(this, SIGNAL(onPauseChanged()), SLOT(_onPauseChanged()));
    // connect(this, SIGNAL(onBookChanged()), SLOT(_onBookChanged()));
    // for(int i = 10; i; --i)
        // note()

    audioBuffer = new QBuffer();

    file = sf_open(bookpath, SFM_READ, &fileInfo);

    sonicBuffer = (unsigned char*)malloc(sizeof(unsigned char) * fileInfo.frames);

    sStream = sonicCreateStream(fileInfo.samplerate, fileInfo.channels);
    sonicSetSpeed(sStream, speed);
    sonicSetPitch(sStream, pitch);
    sonicSetRate(sStream, rate);
    sonicSetVolume(sStream, volume);
    sonicSetChordPitch(sStream, emulateChordPitch);
    sonicSetQuality(sStream, quality);

    // // _filepath.open(QIODevice::ReadOnly);

    QAudioFormat format;
    format.setSampleRate(fileInfo.samplerate);
    format.setChannelCount(fileInfo.channels);
    _debug(fileInfo.samplerate)
    _debug(fileInfo.channels)
    _debug(fileInfo.frames)
    _debug(fileInfo.format)
    _debug(fileInfo.sections)
    _debug(fileInfo.seekable)

    // format.setSampleSize(SAMPLE_SIZE);
    // format.setCodec("audio/pcm");
    // format.setByteOrder(QAudioFormat::LittleEndian);
    // format.setSampleType(QAudioFormat::Float);

    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    // debugf("channels: %d, samplerate: %d, frames: %ld, format: %d\n", fileInfo.channels, fileInfo.channels, fileInfo.frames, fileInfo.format);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Audio backend can't support that audio file format";
        quit(1);
    }

    audioOut = new QAudioOutput(format, this);
    audioOut->setNotifyInterval(SONIC_UPDATE_MS);
    // audioOut->setBufferSize(QAUDIO_BUFFER_SIZE);
    connect(audioOut, SIGNAL(stateChanged(QAudio::State)), this, SLOT(audioStateChanged(QAudio::State)));
    connect(audioOut, SIGNAL(notify()), this, SLOT(updateSonic()));
    // audioOutDevice = audioOut->start();
    // audioOutDevice->open(QIODevice::ReadWrite);
    // audioOut->start(audioBuffer);
    // audioBuffer->open(QBuffer::ReadWrite);


    // audioOutDevice = new QIODevice();
    // audioOutDevice->open(QIODevice::ReadWrite);

    sourceFile = new QFile(bookpath);
    // sourceFile.setFileName(bookpath);
    sourceFile->open(QIODevice::ReadOnly);

    // transportBuffer = new QByteArray();
    audioBuffer = new QBuffer()

    // audioBuffer->open(QBuffer::ReadWrite);

    // QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    // if (!info.isFormatSupported(format)) {
    //     qWarning() << "Raw audio format not supported by backend, cannot play audio.";
    //     return;
    // }

    // audio = new QAudioOutput(format, this);
    // connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
    // updateSonic();
    audioOutDevice = audioOut->start();
    updateSonic();




    note();



}
