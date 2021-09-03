#include "SampleProvider.hpp"


#define defaultJSON "{ \"album\":                  \"[Album]\",           \
                       \"albumartist\":            \"[Album Artist]\",    \
                       \"artist\":                 \"[Artist]\",          \
                       \"description\":            \"[No Description]\",  \
                       \"compilation\":            false,                 \
                       \"composer\":               \"[Composer]\",        \
                       \"discnumber\":             -1,                    \
                       \"genre\":                  \"Audiobook\",         \
                       \"totaldiscs\":             -1,                    \
                       \"totaltracks\":            -1,                    \
                       \"tracknumber\":            -1,                    \
                       \"title\":                  \"[Title]\",           \
                       \"year\":                   0,                     \
                       \"isrc\":                   \"[isrc]\",            \
                       \"bitrate\":                -1,                    \
                       \"length\":                 -1,                    \
                       \"channels\":               -1,                    \
                       \"bitspersample\":          -1,                    \
                       \"samplerate\":             -1,                    \
                       \"positionseconds\":        0                      \
        }"_json
//

SampleProvider::SampleProvider(): eof(false), pos(sampleBuffer.rend()){ }
SampleProvider::SampleProvider(string filepath, float start): eof(false), pos(sampleBuffer.rend()){
    #ifdef USE_SERVER
        client = Client(SERVER_URL);
    #endif
    updateFile(filepath, start);
}

vector<SampleType> SampleProvider::getSamples(const unsigned long toRead){
    requestSamples(); // It won't grab any if we don't need them
    if ((pos + toRead) > sampleBuffer.rend())
        pos = sampleBuffer.rend();
    else
        pos += toRead;
    return vector<SampleType>(pos - toRead, pos);
}

void SampleProvider::flush(){
    sampleBuffer.clear();
    pos = sampleBuffer.rend();
}

void SampleProvider::skip(int sec){
    jump(sec + timePos);
    // timePos += sec;

    // //* Check if we have time enough samples to accomadate this
    // auto projectedPos = (pos + (sec * SAMPLERATE));

    // if (projectedPos <= sampleBuffer.rend()){
    //     flush();
    //     requestSamples();
    // }
    // else if (projectedPos >= sampleBuffer.rbegin()){
    //     requestSamples();
    // }
    // else
    //     pos = sampleBuffer.rend();
}

void SampleProvider::jump(int sec){
    timePos = sec;
    flush();
    _debug(timePos);
    requestSamples();
}

#ifdef USE_FFMPEG
    void SampleProvider::updateFile(string filepath, float start){
        timePos = start;
        this->filepath = filepath;
    }

    //* Returns:
    //  >0: number of sample received
    //  0: no samples recieved, but that's okay cause we're full already
    //  <0: end of file (handles errors internally)
    unsigned long SampleProvider::requestSamples(char authcode[4]){
        //* First check if we actually *need* samples
        if(sampleBuffer.size() > MAX_BUFFER_SIZE)
            return 0;

        char* transportBuffer;
        std::stringstream command;

        // If sampleBuffer is empty, reset the pos iterator so it actually points to something
        bool resetPos = false;
        if (sampleBuffer.empty()){
            resetPos = true;
            note(resetting pos)
        }

        // -noaccurate_seek -- we may or may not want this
        command << "ffmpeg -hide_banner -loglevel error";

        //* If it's a .aax file and we are given an authcode, tell ffmpeg so it can decrypt it
        int len = filepath.length() - 1;
        if (filepath[len - 2] == 'a' and filepath[len - 1] == 'a' and filepath[len] == 'x'){
            if (authcode){
                printf("The file ends in .aax, using activation bytes: %s\n", authcode);
                command << " -activation_bytes " << authcode;
            }
            else
                leave(2, "Can't play .aax files without an authcode.");
        }

        command << " -i \"" << filepath << "\""
                << " -codec pcm_" << FFMPEG_TYPE
                << " -vn -f " << FFMPEG_TYPE
                << " -ac " << to_string(CHANNELS)
                << " -ar " << to_string(SAMPLERATE)
                // << " -start_number " << to_string(pos)
                // << " -fs " << to_string(MAX_BUFFER_SIZE)
                << " -ss " << to_string(timePos)
                << " -t "  << to_string(SAMPLE_REQUEST_SIZE)
                << " -";

        timePos += SAMPLE_REQUEST_SIZE;

        auto vec = getCmdOutV(command.str());

        assert(vec.size() < MAX_BUFFER_SIZE);

        if (vec.size() == 0){
            eof = true;
            return -1;
        }

        sampleBuffer.insert(sampleBuffer.begin(), vec.begin(), vec.end());

        if (resetPos)
            pos = sampleBuffer.rend();

        //* If we're full, and we have
        // if (sampleBuffer.size() > MAX_BUFFER_SIZE and (sampleBuffer.rend() - pos) > KEEP_BACKUP_SAMPLES)
            // sampleBuffer.resize(sampleBuffer.rbegin() - pos);

        /*
        printf("Executing command: \"%s\"\n", command.str().c_str());

        pipe = popen(command.str().c_str(), "r");
        if (pipe == NULL) { _debug("Error: Failed to open pipe", 5); }

        // int read = fread(transportBuffer, sizeof(char), MAX_BUFFER_SIZE, pipe);
        // for(int i = 0; i <= read; ++i)
        int read = 0;
        int c = 1;
        while (c != EOF){
            read++;
            c = fgetc(pipe);
            sampleBuffer.push(c);
        }

        note(waiting)
        // usleep(10000);
        // sleep(1);
        int ffmpegReturn = pclose(pipe);
        note(done waiting)
        if (ffmpegReturn)
            leave(ffmpegReturn, "ffmpeg returned an error");

        // system(command.str().c_str());
        */


        /*
        //* Read from the SampleProvider to sonic stream
        // SampleType transportBuffer[samplesNeeded * player->book->channels];
        int currentSamples, samplesRead, samplesReadFromFile, samplesWritten;
            samplesRead = player->book->sampleProvider.getSamples(transportBuffer, samplesNeeded);
            samplesWritten = sonicWriteShortToStream(player->sStream, transportBuffer, samplesRead);

            //* Read from sonic stream to player->sonicBuffer
            do{
                // samplesRead = sonicReadFloatFromStream(player->sStream, player->sonicBuffer + player->sonicPosition, currentSamples);
                samplesRead = sonicReadShortFromStream(player->sStream, player->sonicBuffer + (player->sonicPosition % SONIC_BUFFER_SIZE), currentSamples);
                player->sonicPosition += samplesRead * player->book->channels;

            //* While there's still stuff to be read
            } while (samplesRead > 0);

        //* Just keep calling it until we have enough
        } while ((player->outputPosition + (samplesNeeded * player->book->channels) + 1) > player->sonicPosition);

        //* Read from player->sonicBuffer to audio output
        int prevPos = player->outputPosition;
        for(int i = 0; i < samplesNeeded * player->book->channels; i++){
            out[i] = player->sonicBuffer[player->outputPosition % SONIC_BUFFER_SIZE];
            ++player->outputPosition;
        }
        */



        return vec.size();
    }
#endif




#ifdef USE_SERVER
    void SampleProvider::updateFile(string filepath){
        auto res = client.Post(filepath.c_str(), "text", "application/json");
        // metadata = json::parse(res->body);

        metadata = json::parse(res->body);
    }


    unsigned long SampleProvider::requestSamples(){
        // auto res = client.Get("/");

        std::string body;

        auto res = client.Get("/",
        [&](const char *data, size_t data_length) {
            body.append(data, data_length);
            return true;
        });



        // if (res->status == 200)
        // std::cout << res->body << '\n';




        /*
        //* Read from the SampleProvider to sonic stream
        // SampleType transportBuffer[samplesNeeded * player->book->channels];
        int currentSamples, samplesRead, samplesReadFromFile, samplesWritten;
            samplesRead = player->book->sampleProvider.getSamples(transportBuffer, samplesNeeded);
            samplesWritten = sonicWriteShortToStream(player->sStream, transportBuffer, samplesRead);

            //* Read from sonic stream to player->sonicBuffer
            do{
                // samplesRead = sonicReadFloatFromStream(player->sStream, player->sonicBuffer + player->sonicPosition, currentSamples);
                samplesRead = sonicReadShortFromStream(player->sStream, player->sonicBuffer + (player->sonicPosition % SONIC_BUFFER_SIZE), currentSamples);
                player->sonicPosition += samplesRead * player->book->channels;

            //* While there's still stuff to be read
            } while (samplesRead > 0);

        //* Just keep calling it until we have enough
        } while ((player->outputPosition + (samplesNeeded * player->book->channels) + 1) > player->sonicPosition);

        //* Read from player->sonicBuffer to audio output
        int prevPos = player->outputPosition;
        for(int i = 0; i < samplesNeeded * player->book->channels; i++){
            out[i] = player->sonicBuffer[player->outputPosition % SONIC_BUFFER_SIZE];
            ++player->outputPosition;
        }
        */

        return 0;
    }
#endif