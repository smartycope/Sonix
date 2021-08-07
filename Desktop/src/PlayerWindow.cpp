#include "PlayerWindow.h"
#include "./ui_PlayerWindow.h"
#include "src/portaudio.h"

PlayerWindow::PlayerWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::PlayerWindow){
    ui->setupUi(this);

    paused = false;
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

    Book* b = new Book(TEST_PATH);
    setBook(b);

    updateAll();
}

PlayerWindow::~PlayerWindow(){
    if (not paused)
        error_check(Pa_StopStream(paStream));

    error_check(Pa_Terminate());
    sonicDestroyStream(sStream);
    // note(Player destructor called!)
    // delete paStream;
    free(sonicBuffer);
    delete book;
    delete ui;
}

void PlayerWindow::updateAll(){
    updateUI();
    updateSonic();
    updatePortaudio();
}

void PlayerWindow::updateSonic(){
    if (book){
        if (not sonicInitalized){
            sStream = sonicCreateStream(book->samplerate, book->channels);
            // _debug(sonicGetSpeed(sStream));
            sonicSetSpeed(sStream, speed);
            sonicSetPitch(sStream, pitch);
            sonicSetRate(sStream, rate);
            sonicSetVolume(sStream, volume);
            sonicSetChordPitch(sStream, emulateChordPitch);
            sonicSetQuality(sStream, quality);

            sonicInitalized = true;
        }
        else{
            sonicSetNumChannels(sStream, book->channels);
            sonicSetSampleRate(sStream, book->samplerate);

            // sonicSetSpeed(sStream, speed);
            // sonicSetPitch(sStream, pitch);
            // sonicSetRate(sStream, rate);
            // sonicSetVolume(sStream, volume);
            // sonicSetChordPitch(sStream, emulateChordPitch);
            // sonicSetQuality(sStream, quality);

        }
    }
}

void PlayerWindow::updatePortaudio(){
    if (book){
        if (not portaudioInitalized){
            paStream = new PaStream*;
            error_check(Pa_Initialize());

            //* Set the output parameters
            paStreamParams.device = Pa_GetDefaultOutputDevice(); // use the default device
            paStreamParams.channelCount = book->channels; // use the same number of channels as our sound file
            paStreamParams.sampleFormat = paFloat32;
            paStreamParams.suggestedLatency = Pa_GetDeviceInfo(paStreamParams.device)->defaultLowOutputLatency;
            paStreamParams.hostApiSpecificStreamInfo = NULL;

            error_check(Pa_OpenStream(&paStream, NULL, &paStreamParams, book->samplerate, FRAMES_PER_BUFFER, paClipOff, audioCallback, this));
            error_check(Pa_StartStream(paStream));

            portaudioInitalized = true;
        }
        //* If it is initialized, but we've changed to a book with a different samplerate or number of channels,
        //      then terminate the current portaudio stream and make a new one (I can't find a way to update it on the fly)
        //*                                                  This should be portaudio.getChannels() or something, but I can't find a way to do that.
        else if ((Pa_GetStreamInfo(paStream)->sampleRate != book->samplerate) or (book->channels != book->channels)){
            if (not paused)
                error_check(Pa_StopStream(paStream));

            error_check(Pa_Terminate());

            portaudioInitalized = false;
            updatePortaudio();
        }
    }
}

void PlayerWindow::updateUI(){
    if (book){
        if (book->coverpath)
            ui->cover->setPixmap(QPixmap(book->coverpath));
        else
            ui->cover->setPixmap(QPixmap(UNSPECIFIED_COVER_PATH));

        _debug(book->title.c_str())
        _debug(book->author.c_str())
        _debug(book->narrator.c_str())
        ui->titleLabel->setText(book->title.c_str());
        ui->authorLabel->setText(book->author.c_str());
        ui->narratorLabel->setText(book->narrator.c_str());
    }
    else{
        ui->cover->setPixmap(QPixmap(UNSPECIFIED_COVER_PATH));
        ui->titleLabel->setText("[Title]");
        ui->authorLabel->setText("[Author]");
        ui->narratorLabel->setText("[Narrator]");
    }

    if (not uiInitalized){
        connect(ui->pauseButton,       SIGNAL(toggled(bool)), this, SLOT(setPaused(bool)));
        connect(ui->skipForwardButton, SIGNAL(pressed()),     this, SLOT(skipForward()));
        connect(ui->skipBackButton,    SIGNAL(pressed()),     this, SLOT(skipBackward()));
        connect(ui->jumpForwardButton, SIGNAL(pressed()),     this, SLOT(jumpForward()));
        connect(ui->jumpBackButton,    SIGNAL(pressed()),     this, SLOT(jumpBackward()));

        connect(ui->speedControl,  SIGNAL(valueChanged(double)), this, SLOT(setSpeed(double)));
        connect(ui->volumeControl, SIGNAL(valueChanged(int)),    this, SLOT(setVolume(int)));

        connect(ui->actionVolumeUp,   SIGNAL(triggered()), this, SLOT(incrementVolume()));
        connect(ui->actionVolumeDown, SIGNAL(triggered()), this, SLOT(decrementVolume()));
        connect(ui->actionFaster,     SIGNAL(triggered()), this, SLOT(incrementSpeed()));
        connect(ui->actionSlower,     SIGNAL(triggered()), this, SLOT(decrementSpeed()));

        connect(ui->actionSkipForward, SIGNAL(triggered()), this, SLOT(skipForward()));
        connect(ui->actionSkipBack,    SIGNAL(triggered()), this, SLOT(skipBackward()));
        connect(ui->actionJumpForward, SIGNAL(triggered()), this, SLOT(jumpForward()));
        connect(ui->actionJumpBack,    SIGNAL(triggered()), this, SLOT(jumpBackward()));

        connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));

        uiInitalized = true;
    }
}

void PlayerWindow::setBook(Book* book){
    assert(book);
    this->book = book;

    updateAll();
}

void PlayerWindow::open(){
    QString path = QFileDialog::getOpenFileName(this, tr("Audio File"));
    if (path.isNull() == false){
        Book* b = new Book(path.toStdString());
        setBook(b);
    }
}

void PlayerWindow::setPaused(bool wantPaused){
    note();
    if (book){
        error_check(wantPaused ? Pa_StopStream(paStream) : Pa_StartStream(paStream));
        paused = wantPaused;
        _debug(paused)
    }
}

void PlayerWindow::setSpeed(double to){
    note();
    if (book){
        sonicSetSpeed(sStream, to);
        ui->speedControl->setValue(to);
    }
}

void PlayerWindow::setPitch(float to){
    if (book)
        sonicSetPitch(sStream, to);
}

void PlayerWindow::setRate(float to){
    if (book)
        sonicSetRate(sStream, to);
}

void PlayerWindow::setVolume(int percentage){
    note();
    if (book){
        sonicSetVolume(sStream, 5 / percentage);
        ui->volumeControl->setValue(percentage);
    }

    // TODO Change how we raise the volume
    todo("Volume is still set via sonic");
}

void PlayerWindow::setEmulateChordPitch(bool to){
    if (book)
        sonicSetChordPitch(sStream, to);
}

void PlayerWindow::setQuality(int to){
    if (book)
        sonicSetQuality(sStream, to);
}

void PlayerWindow::setEnableNonlinearSpeedup(bool to){
    if (book)
        enableNonlinearSpeedup = to;
    todo("enableNonlinearSpeedup");
}

void PlayerWindow::error_check(PaError err) {
    if(err != paNoError){
        error_check(Pa_Terminate());
        debugf("PortAudio Error %d: %s", err, Pa_GetErrorText(err));
        leave(1);
    }
}

void PlayerWindow::flushStream(){
    sonicPosition = outputPosition;
}

void PlayerWindow::skip(int amount){
    note();
    if (book){
        if (outputPosition + (amount * book->channels) < 0)
            outputPosition = 0;
        else if (outputPosition + (amount * book->channels) > book->frames)
            outputPosition = book->frames;
        else
            outputPosition += amount * book->channels;

        book->pos = (int)(outputPosition / book->channels);
        flushStream();
    }
}

void PlayerWindow::jump(int chapters){
    note();
}

bool PlayerWindow::togglePaused(){
    note();
    if (book){
        if (paused)
            error_check(Pa_StartStream(paStream));
        else
            error_check(Pa_StopStream(paStream));
        paused = !paused;

        return paused;
    }
    else
        return true;
}

void PlayerWindow::finished(){
    note();
}

void PlayerWindow::incrementSpeed(){
    note();
    if (book)
        setSpeed(getSpeed() + SPEED_INCREMENT);
}

void PlayerWindow::incrementVolume(){
    note();
    if (book)
        setVolume(getVolume() + VOLUME_INCREMENT);
}

void PlayerWindow::decrementSpeed(){
    note();
    if (book)
        setSpeed(getSpeed() - SPEED_INCREMENT);
}

void PlayerWindow::decrementVolume(){
    note();
    if (book)
        setVolume(getVolume() - VOLUME_INCREMENT);
}

void PlayerWindow::skipForward(){
    note();
    if (book)
        skip(SKIP_SAMPLES);
}

void PlayerWindow::skipBackward(){
    note();
    if (book)
        skip(-SKIP_SAMPLES);
}

void PlayerWindow::jumpForward(){
    note();
    if (book)
        jump(1);
}

void PlayerWindow::jumpBackward(){
    note();
    if (book)
        jump(-1);
}



// Callback function for audio output
int audioCallback(const void* input,
                  void* output,
                  const unsigned long samplesNeeded,
                  const PaStreamCallbackTimeInfo* paTimeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* self){

    PlayerWindow* player = reinterpret_cast<PlayerWindow*>(self); // Cast our data to be usable
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
