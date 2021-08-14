#ifndef AUDIOOUTPUT_H
#define AUDIOOUTPUT_H

#include <math.h>

#include <QAudioOutput>
#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include <QTimer>
#include <QScopedPointer>
#include <QFile>

#include "sonic.h"

#define _debug(var)  printf("%s = %d\n", #var, var);
#define _debugs(str) printf("%s\n", str);

#define UPDATE_MS 20

#define SKIP_SECONDS 20
#define SKIP_SAMPLES (samplerate * SKIP_SECONDS)


class AudioPlayer: public QObject{
    Q_OBJECT

public:
    AudioPlayer(FILE* pipeFile);
    ~AudioPlayer();

public slots:
    void togglePause();
    void setVolume(int);

private:
    QScopedPointer<QAudioOutput> audioOut;
    QScopedPointer<QFile> pipe;
    sonicStream sStream;

    QTimer* callbackTimer;
    qreal volume;

    const static int samplerate;
    const static int channels;

    static float speed;
    static float pitch;
    static float rate;
    static int emulateChordPitch;
    static int quality;
    static int enableNonlinearSpeedup;

    const static std::string printQAudioError(QAudio::Error err);
    const static std::string printQAudioState(QAudio::State state);

    void audioStateChanged(QAudio::State state);
};

/*
void skip(OurData* data, int amount){
    if (data->outputPosition + (amount * CHANNELS) < 0)
        data->outputPosition = 0;
    else if (data->outputPosition + (amount * CHANNELS) > data->frames)
        data->outputPosition = data->frames;
    else
        data->outputPosition += amount * CHANNELS;

    data->filePosition = (int)(data->outputPosition / CHANNELS);
    flushStream(data);
}
*/

#endif // AUDIOOUTPUT_H
