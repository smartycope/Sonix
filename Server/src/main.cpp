#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "sndfile.h"
#include "sonic.h"
#include "portaudio.h"
#include "httplib.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sonic.h"
#include "wave.h"
// #include <sonic>
// #include <wave>

#define BUFFER_SIZE 2048
#define debug(var) printf("%s = %d\n", #var, var);

#define SKIP_SECONDS 20
#define SKIP_SAMPLES (data->sfInfo.samplerate * SKIP_SECONDS)

sonicStream stream;
httplib::Server svr;
waveFile inFile;
int sampleRate, numChannels;


void get(const httplib::Request& request, httplib::Response& response) {
    // std::cout << "GET called with: " << request.get_header_value("/") << '\n';
    std::cout << "GET called with: \n"
              << "Headers: " << request.get_header_value("/") << '\n'
              << "Body: " << request.body << '\n'
            //   << "Files: " << request.files << '\n'
              << "Path: " << request.path << '\n'
              << "Target: " << request.target << '\n';

    int samplesRead, samplesWritten;
    short inBuffer[BUFFER_SIZE];
    unsigned char outBuffer[BUFFER_SIZE];
    // std::string buffer;

    // do {
    samplesRead = readFromWaveFile(inFile, inBuffer, BUFFER_SIZE / numChannels);
    if (samplesRead == 0) {
        sonicFlushStream(stream);
    } else {
        sonicWriteShortToStream(stream, inBuffer, samplesRead);
    }
    // do {
    samplesWritten = sonicReadUnsignedCharFromStream(stream, outBuffer, BUFFER_SIZE / numChannels);
    if (samplesWritten > 0) {
        response.set_content(std::string(reinterpret_cast<const char*>(outBuffer), samplesWritten), "text/plain"); // "audio/wave"
        // writeToWaveFile(outFile, outBuffer, samplesWritten);
    }
        // } while (samplesWritten > 0);
    // } while (samplesRead > 0);
}

void post(const httplib::Request& request, httplib::Response& response){
    std::cout << "POST called with: \n"
              << "Headers: " << request.get_header_value("/") << '\n'
              << "Body: " << request.body << '\n'
            //   << "Files: " << request.files << '\n'
              << "Path: " << request.path << '\n'
              << "Target: " << request.target << '\n';
}

void options(const httplib::Request& request, httplib::Response& response){
    std::cout << "OPTIONS called with: \n"
              << "Headers: " << request.get_header_value("/") << '\n'
              << "Body: " << request.body << '\n'
            //   << "Files: " << request.files << '\n'
              << "Path: " << request.path << '\n'
              << "Target: " << request.target << '\n';
}



void initSonic(char* inFileName, float speed,
                     float pitch, float rate, float volume, int outputSampleRate,
                     int emulateChordPitch, int quality,
                     int enableNonlinearSpeedup) {
    // waveFile inFile;
    // sonicStream stream;

    inFile = openInputWaveFile(inFileName, &sampleRate, &numChannels);
    if (outputSampleRate != 0) {
        sampleRate = outputSampleRate;
    }
    if (inFile == NULL) {
        fprintf(stderr, "Unable to read wave file %s\n", inFileName);
        exit(1);
    }

    stream = sonicCreateStream(sampleRate, numChannels);
    sonicSetSpeed(stream, speed);
    sonicSetPitch(stream, pitch);
    sonicSetRate(stream, rate);
    sonicSetVolume(stream, volume);
    sonicSetChordPitch(stream, emulateChordPitch);
    sonicSetQuality(stream, quality);
}

void closeStream(){
    sonicDestroyStream(stream);
    closeWaveFile(inFile);
}

static void usage() {
    fprintf(
      stderr,
      "Usage: sonic [OPTION]... infile outfile\n"
      "    -c         -- Modify pitch by emulating vocal chords vibrating\n"
      "                  faster or slower.\n"
      "    -n         -- Enable nonlinear speedup\n"
      "    -o         -- Override the sample rate of the output.  -o 44200\n"
      "                  on an input file at 22100 KHz will paly twice as fast\n"
      "                  and have twice the pitch.\n"
      "    -p pitch   -- Set pitch scaling factor.  1.3 means 30%% higher.\n"
      "    -q         -- Disable speed-up heuristics.  May increase quality.\n"
      "    -r rate    -- Set playback rate.  2.0 means 2X faster, and 2X "
      "pitch.\n"
      "    -s speed   -- Set speed up factor.  2.0 means 2X faster.\n"
    #ifdef SONIC_SPECTROGRAM
      "    -S width height -- Write a spectrogram in outfile in PGM format.\n"
    #endif  /* SONIC_SPECTROGRAM */
      "    -v volume  -- Scale volume by a constant factor.\n");
    exit(1);
}

int main(int argc, char** argv) {
    char* inFileName;
    float speed = 1.0f;
    float pitch = 1.0f;
    float rate = 1.0f;
    float volume = 1.0f;
    int outputSampleRate = 0;    /* Means use the input file sample rate. */
    int emulateChordPitch = 0;
    int quality = 0;
    int xArg = 1;
    int enableNonlinearSpeedup = 0;
/*
    while (xArg < argc && *(argv[xArg]) == '-') {
        if (!strcmp(argv[xArg], "-c")) {
            emulateChordPitch = 1;
            printf("Scaling pitch linearly.\n");
        } else if (!strcmp(argv[xArg], "-n")) {
            enableNonlinearSpeedup = 1;
            printf("Enabling nonlinear speedup.\n");
        } else if (!strcmp(argv[xArg], "-o")) {
            xArg++;
            if (xArg < argc) {
                outputSampleRate = atoi(argv[xArg]);
                printf("Setting output sample rate to %d\n", outputSampleRate);
            }
        } else if (!strcmp(argv[xArg], "-p")) {
            xArg++;
            if (xArg < argc) {
                pitch = atof(argv[xArg]);
                printf("Setting pitch to %0.2fX\n", pitch);
            }
        } else if (!strcmp(argv[xArg], "-q")) {
            quality = 1;
            printf("Disabling speed-up heuristics\n");
        } else if (!strcmp(argv[xArg], "-r")) {
            xArg++;
            if (xArg < argc) {
                rate = atof(argv[xArg]);
                if (rate == 0.0f) {
                    usage();
                }
                printf("Setting rate to %0.2fX\n", rate);
            }
        } else if (!strcmp(argv[xArg], "-s")) {
            xArg++;
            if (xArg < argc) {
                speed = atof(argv[xArg]);
                printf("Setting speed to %0.2fX\n", speed);
            }
        } else if (!strcmp(argv[xArg], "-v")) {
            xArg++;
            if (xArg < argc) {
                volume = atof(argv[xArg]);
                printf("Setting volume to %0.2f\n", volume);
            }
        }
        xArg++;
    }
    if (argc - xArg != 2) {
        // usage();
    }
*/

    svr.Get("/", get);
    svr.Post("/", post);
    svr.Options("/", options);

    // inFileName = argv[xArg];
    inFileName = (char*)"/home/marvin/Media/Audiobooks/Snapshot.wav";

    initSonic(inFileName, speed, pitch, rate, volume, outputSampleRate, emulateChordPitch, quality, enableNonlinearSpeedup);

    std::cout << "Starting Server\n";
    svr.listen("localhost", 8080);
    svr.stop();
    closeStream();
    return 0;
}
