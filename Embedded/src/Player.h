#pragma once

#include "Book.h"
#include "sndfile.h"
#include "sonic.h"
#include "portaudio.h"
#include "cope.h"
#include <cassert>

#define SKIP_SECONDS 20
#define SKIP_SAMPLES (book->samplerate * SKIP_SECONDS)
#define SPEED_INCREMENT .25f
#define VOLUME_INCREMENT 2.0f

#define FRAMES_PER_BUFFER paFramesPerBufferUnspecified

//* Optimally, this would be (sizeof(float) * book->frames * book->channels), but
//  The Raspberry Pi I'm using doesn't have enough ram for that.
#define SONIC_BUFFER_SIZE 524288


class Player{
public:
    Book* book;

    Player(Book* book);
    ~Player();

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
    void setSpeed(float to);
    void setPitch(float to);
    void setRate(float to);
    void setVolume(float to);
    void setEmulateChordPitch(bool to);
    void setQuality(int to);
    void setEnableNonlinearSpeedup(bool to);

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


private:
    PaStream* paStream;
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
};



int audioCallback(const void* input, void* output,
                      const unsigned long samplesNeeded,
                      const PaStreamCallbackTimeInfo* paTimeInfo,
                      PaStreamCallbackFlags statusFlags,
                      void* player);