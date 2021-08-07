#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QMainWindow>

#include "Book.h"
#include "sndfile.h"
#include "sonic.h"
#include "portaudio.h"
#include "cope.h"
#include <cassert>
#include <iostream>
#include <string>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui{ class PlayerWindow; }
QT_END_NAMESPACE


#define SKIP_SECONDS 20
#define SKIP_SAMPLES (book->samplerate * SKIP_SECONDS)
#define SPEED_INCREMENT .25f
#define VOLUME_INCREMENT 2.0f

#define FRAMES_PER_BUFFER paFramesPerBufferUnspecified

//* Optimally, this would be (sizeof(float) * book->frames * book->channels), but
//      the Raspberry Pi I'm using doesn't have enough ram for that.
#define SONIC_BUFFER_SIZE 524288
#define UNSPECIFIED_COVER_PATH "/home/marvin/hello/C/SAP/Desktop/assets/defaultBookCover.png"

#define TEST_PATH "/home/marvin/Media/Audiobooks/Snapshot.wav"


class PlayerWindow: public QMainWindow{
    Q_OBJECT

public:
    PlayerWindow(QWidget* parent = nullptr);
    ~PlayerWindow();

    Book* book = nullptr;

    void setBook(Book* book);

    bool  getPaused()                 { return paused; };
    float getSpeed()                  { return speed; };
    float getPitch()                  { return pitch; };
    float getRate()                   { return rate; };
    float getVolume()                 { return volume; };
    bool  getEmulateChordPitch()      { return emulateChordPitch; };
    int   getQuality()                { return quality; };
    bool  getEnableNonlinearSpeedup() { return enableNonlinearSpeedup; };

    // Only Public because we need access to it from the audio callback
    sonicStream sStream;
    int sonicPosition;
    int outputPosition;
    float* sonicBuffer;

public slots:
    bool togglePaused(); // Returns what the new current paused value is
    void skip(int amount);
    void jump(int chapters);
    void skipForward();
    void skipBackward();
    void jumpForward();
    void jumpBackward();
    void flushStream();
    void finished(); // Called when we've finished the audiobook
    void error_check(PaError err);
    void incrementSpeed();
    void decrementSpeed();
    void incrementVolume();
    void decrementVolume();

    void setPaused(bool to);
    void setSpeed(double to);
    void setPitch(float to);
    void setRate(float to);
    void setVolume(int percentage);
    void setEmulateChordPitch(bool to);
    void setQuality(int to);
    void setEnableNonlinearSpeedup(bool to);

    void open();

private:
    Ui::PlayerWindow *ui;

    PaStream* paStream = nullptr;
    PaError error;
    PaStreamParameters paStreamParams;

    bool paused;
    float speed;
    float pitch;
    float rate;
    float volume;
    bool emulateChordPitch;
    int quality;
    bool enableNonlinearSpeedup; // not currently implemented

    void updateSonic();
    void updatePortaudio();
    void updateUI();
    void updateAll();

    bool sonicInitalized = false;
    bool portaudioInitalized = false;
    bool uiInitalized = false;

};


int audioCallback(const void* input, void* output,
                      const unsigned long samplesNeeded,
                      const PaStreamCallbackTimeInfo* paTimeInfo,
                      PaStreamCallbackFlags statusFlags,
                      void* self);

#endif // PLAYERWINDOW_H
