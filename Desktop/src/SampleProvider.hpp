#include "defs.h"
#include <iterator>
#include <qobjectdefs.h>
#ifdef USE_SNDFILE
    #include "sndfile.h"
#endif
#ifdef USE_SERVER
    #include "httplib.h"
#endif
#include <string>
#include <vector>
// #include <deque>
#include <queue>
#include <nlohmann/json.hpp>
#include "sonic.h"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sstream>
#include "cope.hpp"
#include <sys/wait.h>
#include "src/defs.h"
// #include "cope.cpp"
#include <cstdio>

// for convenience
using json = nlohmann::json;
using namespace std;

#ifdef USE_SERVER
    using namespace httplib;
#endif

//* How many samples to request at once (in seconds, fix later)
#define SAMPLE_REQUEST_SIZE 1
//* How big we let the vector get before dropping samples
// Note: This is not hard and fast. The actual max size is going to be
// MAX_BUFFER_SIZE + (SAMPLE_REQUEST_SIZE * SAMPLERATE) - 1
#define MAX_BUFFER_SIZE 2097152
//* How many played samples to keep around in case we skip back a couple times
#define KEEP_BACKUP_SAMPLES MAX_BUFFER_SIZE / 4


// SampleProvider: Gets samples however I've decided to get them (I've tried and at partially implemented at least 5)
// and provides *sped up* them to other places in the program their nessicary via an uniform interface.
// NOTE: No samples enter the queue unsped up (if nessicary)

class SampleProvider{
public:
    bool eof;

    SampleProvider();
    SampleProvider(string filepath, float start = 0.0);

    void updateFile(string filepath, float start = 0.0);
    vector<SampleType> getSamples(unsigned long toRead);

    void flush();
    void skip(int sec);
    // Jump to a specified time, in seconds from the beginning
    void jump(int sec);

public slots:
    unsigned long requestSamples(char authcode[4] = nullptr);

private:
    #ifdef USE_SNDFILE
        SNDFILE* file;
    #endif

    #ifdef USE_SERVER
        Client client;
    #endif

    #ifdef USE_FFMPEG
        FILE* pipe;
        string filepath;
    #endif

    // queue<SampleType> sampleBuffer;
    vector<SampleType> sampleBuffer = {};

    long timePos;  //* In seconds
    // Reverse so we can easily drop samples by calling resize()
    reverse_iterator<std::vector<SampleType>::iterator> pos;
};
