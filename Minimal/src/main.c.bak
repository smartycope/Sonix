#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "sndfile.h"
#include "sonic.h"
#include "portaudio.h"


WINDOW* win;
int oldcur;

#define FRAMES_PER_BUFFER paFramesPerBufferUnspecified
#define debug(var) printf("%s = %d\n", #var, var);

#define SKIP_SECONDS 20
#define SKIP_SAMPLES (data->sfInfo.samplerate * SKIP_SECONDS)

sonicStream sStream;

/* Data structure to pass to callback includes the sound file, info about
the sound file, and a position cursor (where we are in the sound file) */
typedef struct {
    SNDFILE* sndFile;
    SF_INFO sfInfo;
    int filePosition;
    int sonicPosition;
    int outputPosition;
    float* sonicBuffer;
}OurData;

void error_check(PaError err) {
    if(err != paNoError){
        error_check(Pa_Terminate());

        printf("An error occured with portaudio\n");
        fprintf( stderr, "Error number: %d\n", err );
        printf("Error : %s\n", Pa_GetErrorText(err));

        exit(1);
    }
}

// Callback function for audio output
int audioCallback(const void* input,
                  void* output,
                  const unsigned long samplesNeeded,
                  const PaStreamCallbackTimeInfo* paTimeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* userData){
    OurData *data = (OurData *)userData; /// Cast our data to be usable
    float* out = (float*)output;
    int currentSamples, samplesRead;
    float transportBuffer[2048];

    do{
        // seek to our current file position
        sf_seek(data->sndFile, data->filePosition, SEEK_SET);

        // are we going to read past the end of the file?
        if (samplesNeeded > (data->sfInfo.frames - data->filePosition)){
            // if we are, only read to the end of the file
            currentSamples = data->sfInfo.frames - data->filePosition;
            // and then loop to the beginning of the file
            //TODO Change this eventually
            // data->filePosition = 0;
            // return paAbort;
        }
        else{
            // otherwise, we'll just fill up the rest of the output buffer
            currentSamples = samplesNeeded;
            // and increment the file position
            data->filePosition += currentSamples;
        }

        sf_readf_float(data->sndFile, transportBuffer, currentSamples);
        sonicWriteFloatToStream(sStream, transportBuffer, currentSamples);

        do{
            samplesRead = sonicReadFloatFromStream(sStream, data->sonicBuffer + data->sonicPosition, currentSamples);
            data->sonicPosition += samplesRead * data->sfInfo.channels;

        //* While there's still stuff to be read
        } while (samplesRead > 0);

    //* Just keep calling it until we have enough
    } while ((data->outputPosition + (samplesNeeded * data->sfInfo.channels) + 1) > data->sonicPosition);

    int prevPos = data->outputPosition;
    for(int i = 0; i < samplesNeeded * data->sfInfo.channels; i++){
        out[i] = data->sonicBuffer[data->outputPosition];
        ++data->outputPosition;
    }

    return paContinue;
}

// Print the usage.
static void usage() {
    fprintf(
      stderr,
      "Usage: sonic [OPTION]... infile\n"
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
      "    -v volume  -- Scale volume by a constant factor.\n");
    exit(1);
}


void flushStream(OurData* data){
    data->sonicPosition = data->outputPosition;
}

void skip(OurData* data, int amount){
    if (data->outputPosition + (amount * data->sfInfo.channels) < 0)
        data->outputPosition = 0;
    else if (data->outputPosition + (amount * data->sfInfo.channels) > data->sfInfo.frames)
        data->outputPosition = data->sfInfo.frames;
    else
        data->outputPosition += amount * data->sfInfo.channels;

    data->filePosition = (int)(data->outputPosition / data->sfInfo.channels);
    flushStream(data);
}

void mainLoop(OurData* data, PaStream* stream){
    char c = 0, paused = 0;

    while(c != 'q'){
        c = getchar();
        if (c == ' '){
            if (paused)
                error_check(Pa_StartStream(stream));
            else
                error_check(Pa_StopStream(stream));

            paused = !paused;
        }
        else if (c == ',' || c == '<'){
            skip(data, -SKIP_SAMPLES);
        }
        else if (c == '.' || c == '>'){
            skip(data, SKIP_SAMPLES);
        }
        else if (c == 's'){
            double spd;
            scanf("%lf", &spd);
            sonicSetSpeed(sStream, (float)spd);
            // printf("Enter a speed:\n");
        }
    }

}

int main(int argc, char** argv) {
    char* inFileName;
    float speed = 1.0f;
    float pitch = 1.0f;
    float rate = 1.0f;
    float volume = 1.0f;
    int outputSampleRate = 0;    // Means use the input file sample rate.
    int emulateChordPitch = 0;
    int quality = 0;
    int xArg = 1;
    int enableNonlinearSpeedup = 0;
    int numRows = 0, numCols = 0;
    PaStream *stream;
    PaError error;
    PaStreamParameters outputParameters;

    //* Parse args
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
    if (argc - xArg != 1) {
        usage();
    }
    inFileName = argv[xArg];

    //* Construct the Struct
    OurData *data = (OurData *)malloc(sizeof(OurData));
    data->filePosition = 0;
    data->sonicPosition = 0;
    data->outputPosition = 0;
    data->sfInfo.format = 0;
    //* Open the file
    data->sndFile = sf_open(inFileName, SFM_READ, &data->sfInfo);
    data->sonicBuffer = (float*)malloc(sizeof(float) * data->sfInfo.frames);

    if (!data->sndFile){
        printf("error opening file\n");
        return 1;
    }

    if (outputSampleRate != 0)
        data->sfInfo.samplerate = outputSampleRate;

    //* Initialize PortAudio
    error_check(Pa_Initialize());

    // Set the output parameters
    outputParameters.device = Pa_GetDefaultOutputDevice(); // use the default device
    outputParameters.channelCount = data->sfInfo.channels; // use the same number of channels as our sound file
    outputParameters.sampleFormat = paFloat32; // 32bit int format
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL; // no api specific data

    //* Initialize Sonic
    sStream = sonicCreateStream(data->sfInfo.samplerate, data->sfInfo.channels);
    sonicSetSpeed(sStream, speed);
    sonicSetPitch(sStream, pitch);
    sonicSetRate(sStream, rate);
    sonicSetVolume(sStream, volume);
    sonicSetChordPitch(sStream, emulateChordPitch);
    sonicSetQuality(sStream, quality);

    error_check(Pa_OpenStream(&stream, NULL, &outputParameters, data->sfInfo.samplerate, FRAMES_PER_BUFFER, paClipOff, audioCallback, data));
    error_check(Pa_StartStream(stream));

    printf("Welcome to SuperSonic Audiobook Player! Press q to quit, </> to skip back/forward, space to pause, and s to change the speed.\n");
    mainLoop(data, &stream);

    //* Shut everything down and clean up
    error_check(Pa_StopStream(stream));
    error_check(Pa_Terminate());
    sonicDestroyStream(sStream);
    free(data->sonicBuffer);
    free(data);
    return 0;
}