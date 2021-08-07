#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QtCore/qglobal.h>
#include <string>
#include <QIODevice>
#include <QDataStream>
#include <qqml.h>
// #include "Book.h"
#include "cope.cpp"
#include "sndfile.h"
#include "sonic.h"
#include <QAudioOutput>
#include <QAudio>
#include <QFile>
#include <QBuffer>

#define SONIC_UPDATE_MS 20
#define QAUDIO_BUFFER_SIZE 1024
#define SAMPLE_SIZE 32
#define bookpath "/home/rebecca/Downloads/art_of_war_librivox_64kb_mp3/art_of_war_01-02_sun_tzu_64kb.wav"


class Player: public QObject{
    Q_OBJECT

public:
    QString author;
    QString title;
//    QImage cover;
    double position;
    bool book_finished;
    SNDFILE* file;
    SF_INFO fileInfo;
    QFile* sourceFile;


    bool _playing;

//    Player(QString bookpath):
    explicit Player(QObject *parent = nullptr):
        QObject(parent),
        // file(),
        _playing(true),
        book_finished(false),
        audioBuffer(nullptr),
        audioOut(nullptr),
        outputPosition(0),
        filePosition(0),
        sonicPosition(0),
        speed(1.0),
        pitch(1.0),
        rate(1.0),
        volume(1.0),
        emulateChordPitch(1),
        quality(1){
            init();
        };

    //* Getters
    bool playing(){ return _playing; }

    //* Setters
    void setPlaying(bool set){ _playing = set; }

    ~Player();

private:
    void init();

    std::string printQAudioError(QAudio::Error err);
    std::string printQAudioState(QAudio::State state);

    sonicStream sStream;
    QBuffer* audioBuffer;
    unsigned char* sonicBuffer;
    QAudioOutput* audioOut; // class member.
    QIODevice* audioOutDevice;
    QByteArray* transportBuffer;


    int outputPosition;
    int sonicPosition;
    int filePosition;

    float speed;
    float pitch;
    float rate;
    float volume;
    int emulateChordPitch;
    int quality;

    const unsigned int samplesNeeded = 64;


public slots:
    //* Button Functions
    void togglePause();
    void skipForward();
    void skipBackward();
    void jumpForward();
    void jumpBackward();
    void pauseChanged(bool set);

    //* QAudio slots
    void audioStateChanged(QAudio::State state);
    void updateSonic();


};

#endif // PLAYER_H
