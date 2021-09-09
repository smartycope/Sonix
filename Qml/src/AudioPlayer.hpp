#ifndef AUDIOOUTPUT_H
#define AUDIOOUTPUT_H

#include <QObject>
#include <QAudioOutput>
#include <QTimer>
#include <QScopedPointer>
#include <QFile>
// #include <qqml.h>
// #include <qobjectdefs.h>

#include "Book.hpp"
#include "sonic.h"
#include "cope.hpp"

class AudioPlayer: public QObject{
    Q_OBJECT
    Q_PROPERTY(int    samplerate             READ samplerate             WRITE setSamplerate             NOTIFY samplerateChanged)
    Q_PROPERTY(int    channels               READ channels               WRITE setChannels               NOTIFY channelsChanged)
    Q_PROPERTY(double speed                  READ speed                  WRITE setSpeed                  NOTIFY speedChanged)
    Q_PROPERTY(float  pitch                  READ pitch                  WRITE setPitch                  NOTIFY pitchChanged)
    Q_PROPERTY(float  rate                   READ rate                   WRITE setRate                   NOTIFY rateChanged)
    Q_PROPERTY(bool   emulateChordPitch      READ emulateChordPitch      WRITE setEmulateChordPitch      NOTIFY emulateChordPitchChanged)
    Q_PROPERTY(bool   enableNonlinearSpeedup READ enableNonlinearSpeedup WRITE setEnableNonlinearSpeedup NOTIFY enableNonlinearSpeedupChanged)
    Q_PROPERTY(bool   highQuality            READ highQuality            WRITE setHighQuality            NOTIFY highQualityChanged)
    Q_PROPERTY(float  speedIncrement         READ speedIncrement         WRITE setSpeedIncrement         NOTIFY speedIncrementChanged)
    Q_PROPERTY(float  volumeIncrement        READ volumeIncrement        WRITE setVolumeIncrement        NOTIFY volumeIncrementChanged)
    Q_PROPERTY(int    skipSeconds            READ skipSeconds            WRITE setSkipSeconds            NOTIFY skipSecondsChanged)
    QML_ELEMENT

  public:
    // The constructor used to be able to take a nullptr, and just use updateBook()
    // to choose a book at a different point, but I CANNOT get that to work. Instead,
    // you just have to initialize the player whenever you get the book.
    AudioPlayer(Book* book);
    ~AudioPlayer();

    static double _speed;
    static int    _samplerate;
    static int    _channels;

    static int   linVolume;
    static const int updateMS;

    // In seconds
    ulong pos();

  public slots:
    int    samplerate()             { return _samplerate; }
    int    channels()               { return _channels; }
    double speed()                  { return _speed; }
    float  pitch()                  { return _pitch; }
    float  rate()                   { return _rate; }
    bool   emulateChordPitch()      { return _emulateChordPitch; }
    bool   enableNonlinearSpeedup() { return _enableNonlinearSpeedup; }
    bool   highQuality()            { return _highQuality; }
    float  speedIncrement()         { return _speedIncrement; }
    float  volumeIncrement()        { return _volumeIncrement; }
    int    skipSeconds()            { return _skipSeconds; }

    void updateBook(Book* book);
    int  getVolume();

    void setSamplerate(int to)        { _samplerate = to; }
    void setChannels(int to)          { _channels = to; }
    void setSpeedIncrement(float to)  { _speedIncrement = to; }
    void setVolumeIncrement(float to) { _volumeIncrement = to; }
    void setSkipSeconds(int to)       { _skipSeconds = to; }
    void togglePause(bool dummyparam = false);
    void setSpeed(double to);
    void setPitch(float to);
    void setRate(float to);
    void setEmulateChordPitch(bool to);
    void setHighQuality(bool to);
    void setEnableNonlinearSpeedup(bool to);
    void setVolume(int to);

    // amount is in samples
    void skip(int amount);
    void jump(Chapter to);
    void updateChapter();
    void updateSpeed();
    void incrementSpeed();
    void incrementVolume();
    void decrementSpeed();
    void decrementVolume();
    void skipForward();
    void skipBackward();
    void jumpForward();
    void jumpBackward();

  private slots:
    void audioStateChanged(QAudio::State state);

  signals:
    void samplerateChanged();
    void channelsChanged();
    void speedChanged();
    void pitchChanged();
    void rateChanged();
    void emulateChordPitchChanged();
    void enableNonlinearSpeedupChanged();
    void highQualityChanged();
    void speedIncrementChanged();
    void volumeIncrementChanged();
    void skipSecondsChanged();

  private:
    static float  _pitch;
    static float  _rate;
    static bool   _emulateChordPitch;
    static bool   _enableNonlinearSpeedup;
    static bool   _highQuality;
    static float  _speedIncrement;
    static float  _volumeIncrement;
    static int    _skipSeconds;

    QScopedPointer<QAudioOutput> audioOut;
    // pipe isn't nessicarily a "pipe", it's just whatever file ffmpeg is putting stuff, and we're reading from
    // QScopedPointer<QFile> pipe;
    sonicStream sStream;
    QTimer* callbackTimer;
    QIODevice* io;

    qreal logVolume;

    // The only reason we keep this around is to access it's chapters
    Book* b;

    void flushStream();
    void finished();
    const static std::string printQAudioError(QAudio::Error err);
    const static std::string printQAudioState(QAudio::State state);

    //* This is the main callback function. This does all the heavy lifting
    void workhorseFunc();
};

#endif // AUDIOOUTPUT_H
