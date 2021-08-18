#ifndef AUDIOOUTPUT_H
#define AUDIOOUTPUT_H

// #include <math.h>

// #include <QIODevice>
#include <QObject>
#include <QAudioOutput>
#include <QTimer>
#include <QScopedPointer>
#include <QFile>

#include "Book.hpp"
#include "sonic.h"
#include "cope.hpp"

class AudioPlayer: public QObject{
    Q_OBJECT

public:
    AudioPlayer(Book* book = nullptr);
    ~AudioPlayer();

    static int samplerate;
    static int channels;

    static double speed;
    static int   linVolume;
    static float pitch;
    static float rate;
    static bool  emulateChordPitch;
    static bool  enableNonlinearSpeedup;
    static bool  highQuality;
    static float speedIncrement;
    static float volumeIncrement;
    static int   skipSeconds;

    static ulong bytesRead;
    static const int updateMS;

    int getVolume();
    void updateBook(Book* book);

public slots:
    void togglePause(bool dummyparam = false);
    void setVolume(int to);
    void setSpeed(double to);
    void setPitch(float to);
    void setRate(float to);
    void setEmulateChordPitch(bool to);
    void setHighQuality(bool to);
    void setEnableNonlinearSpeedup(bool to);

    void skip(int amount);
    void jump(int chapters);
    void incrementSpeed();
    void incrementVolume();
    void decrementSpeed();
    void decrementVolume();
    void skipForward();
    void skipBackward();
    void jumpForward();
    void jumpBackward();

private:
    QScopedPointer<QAudioOutput> audioOut;
    QScopedPointer<QFile> pipe;
    sonicStream sStream;
    QTimer* callbackTimer;

    qreal logVolume;

    void flushStream();
    void finished();
    void audioStateChanged(QAudio::State state);
    const static std::string printQAudioError(QAudio::Error err);
    const static std::string printQAudioState(QAudio::State state);
};

#endif // AUDIOOUTPUT_H
