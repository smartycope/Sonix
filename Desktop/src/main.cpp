#include "PlayerWindow.h"

#include <QApplication>
#include "defs.h"


int main(int argc, char **argv){
    QApplication a(argc, argv);
    PlayerWindow w;
    w.show();
    return a.exec();
}


/*

-sample_fmt[:stream_specifier] sample_fmt (output,per-stream)
Set the audio sample format. Use -sample_fmts to get a list of supported sample formats.

name   depth
u8        8
s16      16
s32      32
flt      32
dbl      64
u8p       8
s16p     16
s32p     32
fltp     32
dblp     64
s64      64
s64p     64


To add an embedded cover/thumbnail:
ffmpeg -i in.mp4 -i IMAGE -map 0 -map 1 -c copy -c:v:1 png -disposition:v:1 attached_pic out.mp4

*/























//TODO
//* IMPORTANT:
// Note that in a real application, you will probably want to call read()
// in a separate thread because it is NOT realtime safe. That means it does
// not run in constant time because it might be allocating memory, calling
// system functions, or doing other things that can take an
// unpredictably long amount of time.
//
// The danger is that if read() takes too long, then audioCallback() might not
// finish quickly enough, and there will be a "dropout" or pop in the audio
// that comes out your speakers.
//
// If you want to guard against dropouts, you should either decode the entire file into
// memory or decode it on-the-fly in a separate thread. To implement the latter, you would:
//   - Set up a secondary thread and read() a few seconds of audio into a ringbuffer
//   - When the callback runs, you want to fetch audio from that ringbuffer.
//   - Have the secondary thread keep read()ing and ensuring the ringbuffer is full.
//
// Ross Bencina has a great introduction to realtime programming and goes into
// more detail here:
// http://www.rossbencina.com/code/real-time-audio-programming-101-time-waits-for-nothing





















#if 0





#include <qlocale.h>
extern "C"{
#include <mp4v2/mp4v2.h>
}

#include <bits/stdint-uintn.h>
#include <stdlib.h>
#include <stdio.h>
#include "portaudio.h"
#include <string>
#include <filesystem>
#include <sstream>
#include <faad.h>

#include <fstream>
// #include <string

#define TEST_FILE "/home/marvin/Media/Audiobooks/Dragons Egg-Cheela, Book 1.m4b"
#define FRAMES_PER_BUFFER paFramesPerBufferUnspecified
#define debug(var) printf("%s = %s\n", #var, var);
#define die(msg) printf(msg), exit(0);


typedef struct {
    // SNDFILE* sndFile;
    // SF_INFO sfInfo;
    MP4SampleId filePosition;
    int sonicPosition;
    int outputPosition;
    unsigned long samplerate;
    unsigned char channels;
    char* filepath;
    uint32_t numSamples;
    uint32_t timescale;
    MP4TrackId trackID;
    MP4FileHandle mp4File;
    NeAACDecHandle aacDecoder;

    // float* sonicBuffer;
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
    OurData* data = (OurData*)userData; /// Cast our data to be usable
    uint8_t* out = (uint8_t*)output;
    uint32_t currentSamples = 0, samplesRead = 0;
    // uint8_t _transportBuffer[4096*4];
    // uint8_t* transportBuffer = (uint8_t*)transportBuffer;
    // uint8_t* transportBuffer = (uint8_t*)malloc(4096);

    uint8_t* mp4ToNeaac = NULL;
    uint8_t* neaacToPortaudio = (uint8_t*)malloc(samplesNeeded * 2);

    // MP4SampleId sampleID;
    // MP4Duration time;
    // unsigned long long time;
    // uint64_t msectime;
    // uint32_t samplesNeeded = (uint32_t)_samplesNeeded;

    // uint64_t sectime, mintime, hrtime;

    // // Loop until decoding finished
    // do {
    //     //
    //     // Put next frame in buffer
    //     //

    //     // Decode the frame in buffer


    // if ((hInfo.error == 0) && (hInfo.samples > 0))
    // {
    //     //
    //     // do what you need to do with the decoded samples
    //     //
    // } else if (hInfo.error != 0) die("frame decoding error");
    // } while (more data available);




    // for (; data->filePosition <= samplesNeeded; data->filePosition++) {
    while (currentSamples < samplesNeeded){
        if (!MP4ReadSample(data->mp4File, data->trackID, data->filePosition, &mp4ToNeaac, &samplesRead)) { printf("Sample reading failed\n"); exit(1); }
        // MP4GetTrackType(data->mp4File, data->trackID);
        NeAACDecFrameInfo frameInfo;
        out = reinterpret_cast<uint8_t*>(NeAACDecDecode(data->aacDecoder, &frameInfo, mp4ToNeaac, samplesRead));
        data->filePosition += 1;
        // for (int i = currentSamples; i <= samplesRead + currentSamples; i++){
        //     out[i] = transportBuffer[i];
        // }

        currentSamples += samplesRead;
        // time = MP4GetSampleTime(data->mp4File, data->currentTrackID, sampleID);
        // debug(currentSamples);
        // debug(samplesRead);


        // printf("sampleId %6d, size %5u duration %8lu", // time %8" "lu" " %02lu:%02lu:%02lu.%03lu %c\n",
        //         data->currentTrackID,  MP4GetSampleSize(data->mp4File, data->currentTrackID, sampleID),
        //         MP4GetSampleDuration(data->mp4File, data->currentTrackID, sampleID));
        //         // time, hrtime, mintime, sectime, msectime,
        //         // MP4GetSampleSync(data->mp4File, data->currentTrackID, sampleID) == 1 ? 'S' : ' ' );
    }
    // for (int i = currentSamples; i <= currentSamples; i++){
    //     out[i] = neaacToPortaudio[i];
    // }

    // debug(data->filePosition);

    free(mp4ToNeaac);

    return paContinue;
}

int main( int argc, char** argv ){
    // MP4TrackId trackId = MP4_INVALID_TRACK_ID;
    // MP4SampleId sampleId = MP4_INVALID_SAMPLE_ID;
    // MP4LogLevel verbosity = MP4_LOG_ERROR;

    PaStream *stream;
    PaError error;
    PaStreamParameters outputParameters;

    //* Construct the Struct
    OurData* data = (OurData*)malloc(sizeof(OurData));
    data->mp4File = MP4Read(TEST_FILE); if (!data->mp4File) exit(1);
    data->aacDecoder = NeAACDecOpen();
    data->filePosition = 1;
    data->sonicPosition = 0;
    data->outputPosition = 0;
    // data->filepath = TEST_FILE;
    data->trackID = MP4FindTrackId(data->mp4File, 0);
    data->numSamples = MP4GetTrackNumberOfSamples(data->mp4File, data->trackID);
    data->timescale = MP4GetTrackTimeScale(data->mp4File, data->trackID);
    data->channels = MP4GetTrackAudioChannels(data->mp4File, data->trackID);
    // data->channels = 2;
    data->samplerate = data->timescale;


    // auto aacCfg = NeAACDecGetCurrentConfiguration(data->aacDecoder);
	// aacCfg->outputFormat = FAAD_FMT_16BIT;	/* force 16 bit audio */
	// aacCfg->downMatrix = 0;			/* NOT 5.1 -> stereo */
	// aacCfg->dontUpSampleImplicitSBR = 0;		/* upsample, please! */
	// NeAACDecSetConfiguration(data->aacDecoder, aacCfg);

    uint8_t* rawConfig = NULL;
    uint32_t rawConfigSize = 0;
    MP4GetTrackESConfiguration(data->mp4File, data->trackID, &rawConfig, &rawConfigSize);

    // char err = NeAACDecInit2(data->aacDecoder, rawConfig, rawConfigSize, &data->samplerate, &data->channels);
    char err = NeAACDecInit(data->aacDecoder, NULL, 0, &data->samplerate, &data->channels);
    if (err != 0) die("failed to initalize the library");

    printf("tracks: %d\n", MP4GetNumberOfTracks(data->mp4File));
    printf("track %d, samples %d, timescale %d\n", data->trackID, data->numSamples, data->timescale);
    printf("Channels: %d\n", MP4GetTrackAudioChannels(data->mp4File, data->trackID));
    // debug(MP4GetTrackType(data->mp4File, data->trackID));
    // debug(MP4_OD_TRACK_TYPE);
    // debug(MP4_SCENE_TRACK_TYPE);
    // debug(MP4_AUDIO_TRACK_TYPE);
    // debug(MP4_VIDEO_TRACK_TYPE);
    // debug(MP4_HINT_TRACK_TYPE);
    // debug(MP4_CNTL_TRACK_TYPE);
    // debug(MP4_TEXT_TRACK_TYPE);
    // debug(MP4_CLOCK_TRACK_TYPE);
    // debug(MP4_MPEG7_TRACK_TYPE);
    // debug(MP4_OCI_TRACK_TYPE);
    // debug(MP4_IPMP_TRACK_TYPE);
    // debug(MP4_MPEGJ_TRACK_TYPE);

    //* Initialize PortAudio
    error_check(Pa_Initialize());

    // Set the output parameters
    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.channelCount = data->channels;
    outputParameters.sampleFormat = paInt8;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    error_check(Pa_OpenStream(&stream, NULL, &outputParameters, data->samplerate, FRAMES_PER_BUFFER, paClipOff, audioCallback, data));
    error_check(Pa_StartStream(stream));

    while(1);

    //* Shut everything down and clean up
    error_check(Pa_StopStream(stream));
    error_check(Pa_Terminate());

    MP4Close(data->mp4File);
    NeAACDecClose(data->aacDecoder);
    free(data);
    return(0);
}





#endif






/*


#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <audiodecoder/audiodecoder.h> // libaudiodecoder
#include <portaudio.h>                 // PortAudio
#include <unistd.h>



// All audio will be handled as stereo.
const int NUM_CHANNELS = 2;

// Declaration for audio callback called by PortAudio.
int audioCallback(const void *input, void *output,
                  unsigned long frameCount,
                  const PaStreamCallbackTimeInfo* timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* userData);


int main (int argc, char * const argv[]) {

    // Initialize an AudioDecoder object and open demo.mp3
    std::string filename = "demo.mp3";
    AudioDecoder* pAudioDecoder = new AudioDecoder(filename);

    if (pAudioDecoder->open() != AUDIODECODER_OK)
    {
        std::cerr << "Failed to open " << filename << std::endl;
        return 1;
    }

    // Initialize the PortAudio library.
    if (Pa_Initialize() != paNoError) {
        std::cerr << "Failed to initialize PortAudio." << std::endl;
        return 1;
    };

    PaStream* pStream = NULL;

    // Open the PortAudio stream (opens the soundcard device).
    if (Pa_OpenDefaultStream(&pStream,
                  0, // No input channels
                  2, // 2 output channel
                  paFloat32, // Sample format (see PaSampleFormat)
                  44100, // Sample Rate
                  paFramesPerBufferUnspecified,  // Frames per buffer
                  &audioCallback,
                  static_cast<void*>(pAudioDecoder)) != paNoError)
    {
        std::cerr << "Failed to open the default PortAudio stream." << std::endl;
        return 1;
    }

    // Start the audio stream. PortAudio will then start calling our callback function
    // every time the soundcard needs audio.
    // Note that this is non-blocking by default!
    if (Pa_StartStream(pStream) != paNoError)
    {
        std::cerr << "Failed to start the PortAudio stream." << std::endl;
        return 1;
    }

    // So here's where control would normally go back to your program, probably
    // your GUI thread. The audio will be decoded and played back in a separate thread
    // (managed by PortAudio) via the callback function we've defined below.
    // Since we have no GUI to in this example, we're just going to sleep here
    // for a while.
#ifdef _WIN32
	Sleep(20000);
#else
    sleep(20);
#endif

    // Shutdown:
    // First, stop the PortAudio stream (closes the soundcard device).
    if (Pa_StopStream(pStream) != paNoError)
    {
        std::cerr << "Failed to stop the PortAudio stream." << std::endl;
        return 1;
    }

    // Tell the PortAudio library that we're all done with it.
    if (Pa_Terminate() != paNoError)
    {
        std::cerr << "Failed to terminate PortAudio." << std::endl;
        return 1;
    }

    // Close the AudioDecoder object and free it.
    delete pAudioDecoder;

    return 0;
}

// This is the function that gets called when we need to generate sound!
// In this example, we're going to decode some audio using libaudiodecoder
// and fill the "output" buffer with that. In other words, we're going to
// decode demo.mp3 and send that audio to the soundcard. Easy!
int audioCallback(const void *input, void *output,
                  unsigned long frameCount,
                  const PaStreamCallbackTimeInfo* timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* userData){
    AudioDecoder* pAudioDecoder = static_cast<AudioDecoder*>(userData);

    // Play it safe when debugging and coding, protect your ears by clearing
    // the output buffer.
    memset(output, 0, frameCount * NUM_CHANNELS * sizeof(float));

    // Decode the number of samples that PortAudio said it needs to send to the
    // soundcard. This is where we're grabbing audio from demo.mp3!
    int samplesRead = pAudioDecoder->read(frameCount * NUM_CHANNELS, static_cast<SAMPLE*>(output));

    // IMPORTANT:
    // Note that in a real application, you will probably want to call read()
    // in a separate thread because it is NOT realtime safe. That means it does
    // not run in constant time because it might be allocating memory, calling
    // system functions, or doing other things that can take an
    // unpredictably long amount of time.
    //
    // The danger is that if read() takes too long, then audioCallback() might not
    // finish quickly enough, and there will be a "dropout" or pop in the audio
    // that comes out your speakers.
    //
    // If you want to guard against dropouts, you should either decode the entire file into
    // memory or decode it on-the-fly in a separate thread. To implement the latter, you would:
    //   - Set up a secondary thread and read() a few seconds of audio into a ringbuffer
    //   - When the callback runs, you want to fetch audio from that ringbuffer.
    //   - Have the secondary thread keep read()ing and ensuring the ringbuffer is full.
    //
    // Ross Bencina has a great introduction to realtime programming and goes into
    // more detail here:
    // http://www.rossbencina.com/code/real-time-audio-programming-101-time-waits-for-nothing

    return paContinue;
}


*/

























#if 0
char* ProgName;
char* Mp4PathName;
char* Mp4FileName;

// forward declaration
void ExtractTrack( MP4FileHandle mp4File, MP4TrackId trackId,
                   bool sampleMode, MP4SampleId sampleId, char* dstFileName = NULL );

extern "C" int main( int argc, char** argv ){
    // const char* const usageString = "[-l] [-t <track-id>] [-s <sample-id>] [-v [<level>]] <file-name>";
    bool doList = false;
    bool doSamples = false;
    MP4TrackId trackId = MP4_INVALID_TRACK_ID;
    MP4SampleId sampleId = MP4_INVALID_SAMPLE_ID;
    char* dstFileName = NULL;
    MP4LogLevel verbosity = MP4_LOG_ERROR;

    // /* begin processing command line */
    // ProgName = argv[0];
    // while ( true ) {
    //     int c = -1;
    //     int option_index = 0;
    //     static const prog::Option long_options[] = {
    //         { "list",    prog::Option::NO_ARG,       0, 'l' },
    //         { "track",   prog::Option::REQUIRED_ARG, 0, 't' },
    //         { "sample",  prog::Option::OPTIONAL_ARG, 0, 's' },
    //         { "verbose", prog::Option::OPTIONAL_ARG, 0, 'v' },
    //         { "version", prog::Option::NO_ARG,       0, 'V' },
    //         { NULL, prog::Option::NO_ARG, 0, 0 }
    //     };

    //     c = prog::getOptionSingle( argc, argv, "lt:s::v::V", long_options, &option_index );

    //     if ( c == -1 )
    //         break;

    //     switch ( c ) {
    //         case 'l':
    //             doList = true;
    //             break;
    //         case 's':
    //             doSamples = true;
    //             if ( prog::optarg ) {
    //                 if ( sscanf( prog::optarg, "%u", &sampleId ) != 1 ) {
    //                     fprintf( stderr,
    //                              "%s: bad sample-id specified: %s\n",
    //                              ProgName, prog::optarg );
    //                 }
    //             }
    //             break;
    //         case 't':
    //             if ( sscanf( prog::optarg, "%u", &trackId ) != 1 ) {
    //                 fprintf( stderr,
    //                          "%s: bad track-id specified: %s\n",
    //                          ProgName, prog::optarg );
    //                 exit( 1 );
    //             }
    //             break;
    //         case 'v':
    //             verbosity = MP4_LOG_VERBOSE1;
    //             if ( prog::optarg ) {
    //                 uint32_t level;
    //                 if ( sscanf( prog::optarg, "%u", &level ) == 1 ) {
    //                     if ( level >= 2 ) {
    //                         verbosity = MP4_LOG_VERBOSE2;
    //                     }
    //                     if ( level >= 3 ) {
    //                         verbosity = MP4_LOG_VERBOSE3;
    //                     }
    //                     if ( level >= 4 ) {
    //                         verbosity = MP4_LOG_VERBOSE4;
    //                     }
    //                 }
    //             }
    //             break;
    //         case '?':
    //             fprintf( stderr, "usage: %s %s\n", ProgName, usageString );
    //             exit( 0 );
    //         case 'V':
    //             fprintf( stderr, "%s - %s\n", ProgName, MP4V2_PROJECT_name_formal );
    //             exit( 0 );
    //         default:
    //             fprintf( stderr, "%s: unknown option specified, ignoring: %c\n",
    //                      ProgName, c );
    //     }
    // }

    // /* check that we have at least one non-option argument */
    // if ( ( argc - prog::optind ) < 1 ) {
    //     fprintf( stderr, "usage: %s %s\n", ProgName, usageString );
    //     exit( 1 );
    // }

    // MP4LogSetLevel(verbosity);
    // if ( verbosity ) {
    //     fprintf( stderr, "%s version %s\n", ProgName, MP4V2_PROJECT_version );
    // }

    // /* point to the specified file names
    // Mp4PathName = argv[prog::optind++];

    // /* get dest file name for a single track */
    // if ( trackId && ( argc - prog::optind ) > 0 ) {
    //     dstFileName = argv[prog::optind++];
    // }

    // char* lastSlash = strrchr( Mp4PathName, '/' );
    // if ( lastSlash ) {
    //     Mp4FileName = lastSlash + 1;
    // }
    // else {
    //     Mp4FileName = Mp4PathName;
    // }

    //  warn about extraneous non-option arguments
    // if ( prog::optind < argc ) {
    //     fprintf( stderr, "%s: unknown options specified, ignoring: ", ProgName );
    //     while ( prog::optind < argc ) {
    //         fprintf( stderr, "%s ", argv[prog::optind++] );
    //     }
    //     fprintf( stderr, "\n" );
    // }

    // end processing of command line

    MP4FileHandle mp4File = MP4Read(TEST_FILE);

    if (!mp4File) exit(1);

    // MP4Info(mp4File);

    if (trackId == 0 ) {
        uint32_t numTracks = MP4GetNumberOfTracks( mp4File );

        for ( uint32_t i = 0; i < numTracks; i++ ) {
            trackId = MP4FindTrackId( mp4File, i );
            ExtractTrack( mp4File, trackId, doSamples, sampleId );
        }
    }
    else {
        ExtractTrack( mp4File, trackId, doSamples, sampleId, dstFileName );
    }

    MP4Close( mp4File );

    return( 0 );
}

void ExtractTrack( MP4FileHandle mp4File, MP4TrackId trackId,
                   bool sampleMode, MP4SampleId sampleId, char* dstFileName ){
    static std::string outName;

    if( !sampleMode ) {
        if( !dstFileName ) {
            std::stringstream ss;
            ss << Mp4FileName << ".t" << trackId;
            outName = ss.str();
        } else {
            outName = dstFileName;
        }

        // if( out.open( outName.c_str(), File::MODE_CREATE )) {
        //     fprintf( stderr, "%s: can't open %s\n", ProgName, outName.c_str());//, sys::getLastErrorStr() );
        //     return;
        // }
    }

    MP4SampleId numSamples;

    if ( sampleMode && sampleId != MP4_INVALID_SAMPLE_ID ) {
        numSamples = sampleId;
    }
    else {
        sampleId = 1;
        numSamples = MP4GetTrackNumberOfSamples( mp4File, trackId );
    }

    for ( ; sampleId <= numSamples; sampleId++ ) {
        // signals to ReadSample() that it should malloc a buffer for us
        uint8_t* pSample = NULL;
        uint32_t sampleSize = 0;

        if( !MP4ReadSample( mp4File, trackId, sampleId, &pSample, &sampleSize )) {
            fprintf( stderr, "%s: read sample %u for %s failed\n", ProgName, sampleId, outName.c_str() );
            break;
        }

        if ( sampleMode ) {
            std::stringstream ss;
            ss << Mp4FileName << ".t" << trackId << ".s" << sampleId;
            outName = ss.str();

            // if( out.open( outName.c_str(), File::MODE_CREATE )) {
                fprintf( stderr, "%s: can't open %s\n", ProgName, outName.c_str()); //, sys::getLastErrorStr() );
                break;
            }
        }

        File::Size nout;
        if( out.write( pSample, sampleSize, nout )) {
            fprintf( stderr, "%s: write to %s failed\n", ProgName, outName.c_str()); //, sys::getLastErrorStr() );
            break;
        }

        free( pSample );

        if( sampleMode )
            out.close();
    }

    out.close();
}



#endif











#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portaudio.h"

// #include <libavcodec/avcodec.h>

#include <libavutil/frame.h>
#include <libavutil/mem.h>
// #include <libavformat/avformat.h>


#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096

#define FRAMES_PER_BUFFER paFramesPerBufferUnspecified
#define debug(var) printf("%s = %d\n", #var, var);

#include <stdio.h>
#include <stdlib.h>

// extern "C" {
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
// }


// Callback function for audio output
int audioCallback(const void* input,
                  void* output,
                  const unsigned long samplesNeeded,
                  const PaStreamCallbackTimeInfo* paTimeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* userData){
    OurData* data = (OurData*)userData; /// Cast our data to be usable
    char* out = (char*)output;
    int currentSamples, samplesRead;
    // float transportBuffer[2048];

    AVPacket* pkt;
    int position = 0;
    while (samplesNeeded >= position){
        av_read_frame(data->formatCtx, pkt);
        for (int k = 0; k >= pkt->size; k++){
            position += 1;
            out[position] = pkt->data;
        }
    }
}



    // decode data
    // double* _data;

    // int size;
    // samplesRead = decode_audio_file(data->filepath, data->samplerate, samplesNeeded, &out, data) != 0;
    // free(_data);

/*
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
*/
    // return paContinue;
// }


#include <stdio.h>
#include <stdlib.h>

#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include "libavutil/mathematics.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include <ao/ao.h>


#define die(msg) printf(msg); exit(1);
#define false 0
#define true 1

int main(int argc, char **argv){

    const char* input_filename=argv[1];

    //avcodec_register_all();
    av_register_all();
    //av_ini

    AVFormatContext* container = avformat_alloc_context();
    if(avformat_open_input(&container,input_filename,NULL,NULL)<0){
        die("Could not open file");
    }


    AVDictionary* metadata = container->metadata;

    if(avformat_find_stream_info(container, &metadata)<0){
        die("Could not find file info");
    }

    // av_dump_format(container,0,input_filename,false);


    int stream_id=-1;
    int i;
    for(i=0;i<container->nb_streams;i++){
        if(container->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO){
            stream_id=i;
            break;
        }
    }
    if(stream_id==-1){
        die("Could not find Audio Stream");
    }

    AVCodecContext* ctx = container->streams[stream_id]->codec;
    AVCodec* codec = avcodec_find_decoder(ctx->codec_id);

    if(codec==NULL){
        die("cannot find codec!");
    }

    if(avcodec_open2(ctx,codec, &metadata)<0){
        die("Codec cannot be found");
    }

    //// ctx=avcodec_alloc_context3(codec);

    PaStream *stream;
    PaError error;
    PaStreamParameters outputParameters;



    //* Construct the Struct
    OurData *data = (OurData *)malloc(sizeof(OurData));
    data->filePosition = 0;
    data->sonicPosition = 0;
    data->outputPosition = 0;
    // data->sfInfo.format = 0;
    data->channels = 2;
    data->samplerate = 22050;
    data->filepath = argv[1];
    data->formatCtx = container;
    data->codecCtx = ctx;
    data->codec = codec;
    //* Open the file
    // data->sndFile = sf_open(inFileName, SFM_READ, &data->sfInfo);

    // get format from audio file
    // data->format = avformat_alloc_context();
    // if (avformat_open_input(&data->format, data->filepath, NULL, NULL) != 0) {
    //     fprintf(stderr, "Could not open file\n");
    //     return -1;
    // }
    // if (avformat_find_stream_info(data->format, NULL) < 0) {
    //     fprintf(stderr, "Could not retrieve stream info from file'\n");
    //     return -1;
    // }

    //* Initialize PortAudio
    error_check(Pa_Initialize());

    // Set the output parameters
    outputParameters.device = Pa_GetDefaultOutputDevice(); // use the default device
    outputParameters.channelCount = data->channels; // use the same number of channels as our sound file
    outputParameters.sampleFormat = paInt8; // 32bit int format
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL; // no api specific data

    error_check(Pa_OpenStream(&stream, NULL, &outputParameters, data->samplerate, FRAMES_PER_BUFFER, paClipOff, audioCallback, data));
    error_check(Pa_StartStream(stream));

    while(1);

    //* Shut everything down and clean up
    error_check(Pa_StopStream(stream));
    error_check(Pa_Terminate());
    free(data);


    // //initialize AO lib
    // ao_initialize();

    // int driver=ao_default_driver_id();

    // ao_sample_format sformat;
    // enum AVSampleFormat sfmt=ctx->sample_fmt;
    // if(sfmt==AV_SAMPLE_FMT_U8){
    //     printf("U8\n");

    //     sformat.bits=8;
    // }else if(sfmt==AV_SAMPLE_FMT_S16){
    //     printf("S16\n");
    //     sformat.bits=16;
    // }else if(sfmt==AV_SAMPLE_FMT_S32){
    //     printf("S32\n");
    //     sformat.bits=32;
    // }

    // sformat.channels=ctx->channels;
    // sformat.rate=ctx->sample_rate;
    // sformat.byte_format=AO_FMT_NATIVE;
    // sformat.matrix=0;


}

/*
long decode_audio_file(const char* path, const int sample_rate, long samplesToRead, float** _data, OurData* data) {
    // Find the index of the first audio stream
    int stream_index =- 1;
    for (int i=0; i<data->format->nb_streams; i++) {
        if (data->format->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
            stream_index = i;
            break;
        }
    }
    if (stream_index == -1) {
        fprintf(stderr, "Could not retrieve audio stream from file '%s'\n", path);
        exit(-1);
    }
    AVStream* stream = data->format->streams[stream_index];

    // find & open codec
    AVCodecContext* codec = stream->codec;
    if (avcodec_open2(codec, avcodec_find_decoder(codec->codec_id), NULL) < 0) {
        fprintf(stderr, "Failed to open decoder for stream #%u in file '%s'\n", stream_index, path);
        exit(-1);
    }

    // // prepare resampler
    struct SwrContext* swr = swr_alloc();
    av_opt_set_int(swr, "in_channel_count",  codec->channels, 0);
    av_opt_set_int(swr, "out_channel_count", 1, 0);
    av_opt_set_int(swr, "in_channel_layout",  codec->channel_layout, 0);
    av_opt_set_int(swr, "out_channel_layout", AV_CH_LAYOUT_MONO, 0);
    av_opt_set_int(swr, "in_sample_rate", codec->sample_rate, 0);
    av_opt_set_int(swr, "out_sample_rate", sample_rate, 0);
    av_opt_set_sample_fmt(swr, "in_sample_fmt",  codec->sample_fmt, 0);
    av_opt_set_sample_fmt(swr, "out_sample_fmt", AV_SAMPLE_FMT_DBL,  0);
    swr_init(swr);
    if (!swr_is_initialized(swr)) {
        fprintf(stderr, "Resampler has not been properly initialized\n");
        return -1;
    }

    // prepare to read _data
    AVPacket packet;
    av_init_packet(&packet);
    AVFrame* frame = av_frame_alloc();
	if (!frame) {
		fprintf(stderr, "Error allocating the frame\n");
		exit(-1);
	}

    // iterate through frames
    *_data = NULL;
    int* size = 0;
    while (av_read_frame(data->format, &packet) >= 0) {
        // decode one frame
        int gotFrame;
        if (avcodec_decode_audio4(codec, frame, &gotFrame, &packet) < 0) {
            break;
        }
        if (!gotFrame) {
            continue;
        }
        // // resample frames
        double* buffer;
        av_samples_alloc((uint8_t**) &buffer, NULL, 1, frame->nb_samples, AV_SAMPLE_FMT_DBL, 0);
        int frame_count = swr_convert(swr, (uint8_t**) &buffer, frame->nb_samples, (const uint8_t**) frame->data, frame->nb_samples);
        // append resampled frames to _data
        *_data = (float*) realloc(*_data, (*size + frame->nb_samples) * sizeof(float));
        memcpy(*_data + *size, buffer, frame_count * sizeof(float));
        *size += frame_count;
    }

    // clean up
    av_frame_free(&frame);
    swr_free(&swr);
    avcodec_close(codec);


    // success
    return *size;

}

int main(int argc, char const *argv[]) {
    // check parameters
    if (argc < 2) {
        fprintf(stderr, "Please provide the path to an audio file as first command-line argument.\n");
        return -1;
    }

    // initialize all muxers, demuxers and protocols for libavformat
    // (does nothing if called twice during the course of one program execution)
    av_register_all();

    PaStream *stream;
    PaError error;
    PaStreamParameters outputParameters;



    //* Construct the Struct
    OurData *data = (OurData *)malloc(sizeof(OurData));
    data->filePosition = 0;
    data->sonicPosition = 0;
    data->outputPosition = 0;
    // data->sfInfo.format = 0;
    data->channels = 2;
    data->samplerate = 22050;
    data->filepath = argv[1];
    //* Open the file
    // data->sndFile = sf_open(inFileName, SFM_READ, &data->sfInfo);

    // get format from audio file
    data->format = avformat_alloc_context();
    if (avformat_open_input(&data->format, data->filepath, NULL, NULL) != 0) {
        fprintf(stderr, "Could not open file\n");
        return -1;
    }
    if (avformat_find_stream_info(data->format, NULL) < 0) {
        fprintf(stderr, "Could not retrieve stream info from file'\n");
        return -1;
    }

    //* Initialize PortAudio
    error_check(Pa_Initialize());

    // Set the output parameters
    outputParameters.device = Pa_GetDefaultOutputDevice(); // use the default device
    outputParameters.channelCount = data->channels; // use the same number of channels as our sound file
    outputParameters.sampleFormat = paFloat32; // 32bit int format
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL; // no api specific data

    error_check(Pa_OpenStream(&stream, NULL, &outputParameters, data->samplerate, FRAMES_PER_BUFFER, paClipOff, audioCallback, data));
    error_check(Pa_StartStream(stream));

    //* Shut everything down and clean up
    error_check(Pa_StopStream(stream));
    error_check(Pa_Terminate());
    free(data);
    avformat_free_context(data->format);






    // // sum data
    // double sum = 0.0;
    // for (int i=0; i<size; ++i) {
    //     sum += _data[i];
    // }

    // // display result and exit cleanly
    // printf("sum is %f", sum);

    return 0;
}
*/
#endif