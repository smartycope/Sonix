#include "Player.h"

Player::Player(Book* book): book(book){
    paused = true;
    speed = 1.0;
    pitch = 1.0;
    rate = 1.0;
    volume = 1.0;
    emulateChordPitch = false;
    quality = 1;

    sonicPosition = 0;

    //* The raspberry pi zero literally doesn't have this much RAM.
    // sonicBuffer = (float*)malloc(sizeof(float) * book->frames * book->channels);
    sonicBuffer = (float*)malloc(sizeof(float) * SONIC_BUFFER_SIZE);
    outputPosition = 0;

    //* Initialize PortAudio
    paStream = new PaStream*;
    error_check(Pa_Initialize());

    _debug(Pa_GetDefaultOutputDevice());

    //* Set the output parameters
    paStreamParams.device = Pa_GetDefaultOutputDevice(); // use the default device
    paStreamParams.channelCount = book->channels; // use the same number of channels as our sound file
    paStreamParams.sampleFormat = paFloat32;
    paStreamParams.suggestedLatency = Pa_GetDeviceInfo(paStreamParams.device)->defaultLowOutputLatency;
    paStreamParams.hostApiSpecificStreamInfo = NULL;

    //* Initialize Sonic
    sStream = sonicCreateStream(book->samplerate, book->channels);
    _debug(sonicGetSpeed(sStream));
    // sonicSetSpeed(sStream, speed);
    // sonicSetPitch(sStream, pitch);
    // sonicSetRate(sStream, rate);
    // sonicSetVolume(sStream, volume);
    // sonicSetChordPitch(sStream, emulateChordPitch);
    // sonicSetQuality(sStream, quality);
    // sonic enableNonlinearSpeedup

    error_check(Pa_OpenStream(&paStream, NULL, &paStreamParams, book->samplerate, FRAMES_PER_BUFFER, paClipOff, audioCallback, this));
    error_check(Pa_StartStream(paStream));


}

Player::~Player(){
    if (not paused)
        error_check(Pa_StopStream(paStream));

    error_check(Pa_Terminate());
    sonicDestroyStream(sStream);
    note(Player destructor called!)
    delete paStream;
    free(sonicBuffer);
}

void Player::setPaused(bool to){
    if (to and paused)
        error_check(Pa_StartStream(paStream));
    else if (not to and not paused)
        error_check(Pa_StopStream(paStream));
    paused = to;
}

void Player::setSpeed(float to){
    sonicSetSpeed(sStream, to);
}

void Player::setPitch(float to){
    sonicSetPitch(sStream, to);
}

void Player::setRate(float to){
    sonicSetRate(sStream, to);
}

void Player::setVolume(float to){
    sonicSetVolume(sStream, to);
    // TODO Consider changing how we raise the volume
    todo("Volume is still set via sonic");
}

void Player::setEmulateChordPitch(bool to){
    sonicSetChordPitch(sStream, to);
}

void Player::setQuality(int to){
    sonicSetQuality(sStream, to);
}

void Player::setEnableNonlinearSpeedup(bool to){
    enableNonlinearSpeedup = to;
    todo("enableNonlinearSpeedup");
}

void Player::error_check(PaError err) {
    if(err != paNoError){
        error_check(Pa_Terminate());

        perror("An error occured with portaudio\n");
        fprintf(stderr, "Error number: %d\n", err);
        printf("Error : %s\n", Pa_GetErrorText(err));
        quit(1);
    }
}

void Player::flushStream(){
    sonicPosition = outputPosition;
}

void Player::skip(int amount){
    if (outputPosition + (amount * book->channels) < 0)
        outputPosition = 0;
    else if (outputPosition + (amount * book->channels) > book->frames)
        outputPosition = book->frames;
    else
        outputPosition += amount * book->channels;

    book->pos = (int)(outputPosition / book->channels);
    flushStream();
}

void Player::jump(int chapters){
    pass
}

bool Player::togglePaused(){
    if (paused)
        error_check(Pa_StartStream(paStream));
    else
        error_check(Pa_StopStream(paStream));
    paused = !paused;

    return paused;
}

void Player::finished(){
    pass
}

void Player::incrementSpeed(){
    setSpeed(getSpeed() + SPEED_INCREMENT);
}

void Player::incrementVolume(){
    setVolume(getVolume() + VOLUME_INCREMENT);
}

void Player::decrementSpeed(){
    setSpeed(getSpeed() - SPEED_INCREMENT);
}

void Player::decrementVolume(){
    setVolume(getVolume() - VOLUME_INCREMENT);
}

void Player::skipForward(){
    skip(SKIP_SAMPLES);
}

void Player::skipBackward(){
    skip(-SKIP_SAMPLES);
}

void Player::jumpForward(){
    jump(1);
}

void Player::jumpBackward(){
    jump(-1);
}



// Callback function for audio output
int audioCallback(const void* input,
                  void* output,
                  const unsigned long samplesNeeded,
                  const PaStreamCallbackTimeInfo* paTimeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* _player){

    Player* player = reinterpret_cast<Player*>(_player); // Cast our data to be usable
    float* out = (float*)output;
    int currentSamples, samplesRead, samplesReadFromFile, samplesWritten;
    float transportBuffer[samplesNeeded * player->book->channels];

    do{
        //* seek to our current file position
        sf_seek(player->book->file, player->book->pos, SEEK_SET);

        //* are we going to read past the end of the file?
        if (samplesNeeded > (player->book->frames - player->book->pos)){
            //* if we are, only read to the end of the file
            currentSamples = player->book->frames - player->book->pos;
            player->finished();
            // return paAbort;
        }
        else{
            //* otherwise, we'll just fill up the rest of the output buffer
            currentSamples = samplesNeeded;
            //* and increment the file position
            player->book->pos += currentSamples;
        }

        //* Read from file to sonic stream
        samplesReadFromFile = sf_readf_float(player->book->file, transportBuffer, currentSamples);
        samplesWritten = sonicWriteFloatToStream(player->sStream, transportBuffer, samplesReadFromFile);

        //* Read from sonic stream to player->sonicBuffer
        do{
            // samplesRead = sonicReadFloatFromStream(player->sStream, player->sonicBuffer + player->sonicPosition, currentSamples);
            samplesRead = sonicReadFloatFromStream(player->sStream, player->sonicBuffer + (player->sonicPosition % SONIC_BUFFER_SIZE), currentSamples);
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

    return paContinue;
}
