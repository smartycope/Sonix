#include "PlayerWindow.hpp"
#include <QMessageBox>
// #include <QDialog>
#include <QInputDialog>



#define PAUL_BLART "/home/marvin/hello/C/SAP/Desktop/assets/paulblart.png"

PlayerWindow::PlayerWindow(Book* book, QWidget *parent): book(book), player(new AudioPlayer(book)), QMainWindow(parent), ui(new Ui::PlayerWindow){
    ui->setupUi(this);

    connect(ui->pauseButton,       SIGNAL(toggled(bool)), this->player, SLOT(togglePause(bool)));
    connect(ui->skipForwardButton, SIGNAL(pressed()),     this->player, SLOT(skipForward()));
    connect(ui->skipBackButton,    SIGNAL(pressed()),     this->player, SLOT(skipBackward()));
    connect(ui->jumpForwardButton, SIGNAL(pressed()),     this->player, SLOT(jumpForward()));
    connect(ui->jumpBackButton,    SIGNAL(pressed()),     this->player, SLOT(jumpBackward()));

    connect(ui->actionSkipForward, SIGNAL(triggered()),   this->player, SLOT(skipForward()));
    connect(ui->actionSkipBack,    SIGNAL(triggered()),   this->player, SLOT(skipBackward()));
    connect(ui->actionJumpForward, SIGNAL(triggered()),   this->player, SLOT(jumpForward()));
    connect(ui->actionJumpBack,    SIGNAL(triggered()),   this->player, SLOT(jumpBackward()));

    connect(ui->speedControl,      SIGNAL(valueChanged(double)), this->player, SLOT(setSpeed(double)));
    connect(ui->volumeControl,     SIGNAL(valueChanged(int)),    this->player, SLOT(setVolume(int)));

    connect(ui->actionVolumeUp,    SIGNAL(triggered()),   this->player, SLOT(incrementVolume()));
    connect(ui->actionVolumeUp,    SIGNAL(triggered()),   this,         SLOT(updateVolumeBar()));
    connect(ui->actionVolumeDown,  SIGNAL(triggered()),   this->player, SLOT(decrementVolume()));
    connect(ui->actionVolumeDown,  SIGNAL(triggered()),   this,         SLOT(updateVolumeBar()));
    connect(ui->actionFaster,      SIGNAL(triggered()),   this->player, SLOT(incrementSpeed()));
    connect(ui->actionFaster,      SIGNAL(triggered()),   this,         SLOT(updateSpeedControl()));
    connect(ui->actionSlower,      SIGNAL(triggered()),   this->player, SLOT(decrementSpeed()));
    connect(ui->actionSlower,      SIGNAL(triggered()),   this,         SLOT(updateSpeedControl()));

    connect(ui->actionOpen,        SIGNAL(triggered()),   this, SLOT(open()));
    connect(ui->actionAbout,       SIGNAL(triggered()),   this, SLOT(about()));
    connect(ui->actionOpenSettings,SIGNAL(triggered()),   this, SLOT(openSettings()));
    connect(ui->actionAuthcode,    SIGNAL(triggered()),   this, SLOT(getAuthcode()));
    connect(ui->paulBlart,         SIGNAL(triggered()),   this, SLOT(paulBlart()));

    if (book){
        ui->cover->setPixmap(book->cover);
        ui->titleLabel->setText(book->title.c_str());
        ui->authorLabel->setText(book->author.c_str());
        ui->narratorLabel->setText(book->narrator.c_str());
    }
    else
        ui->cover->setPixmap(QPixmap(UNSPECIFIED_COVER_PATH));


    ui->speedControl->setValue(AudioPlayer::speed);
    ui->volumeControl->setValue(player->getVolume());
    // ui->progressBar->setValue(book->getPosition() / book->duration);
}

PlayerWindow::~PlayerWindow(){
    delete book;
    delete player;
    delete ui;
}

void PlayerWindow::updateVolumeBar(){
    ui->volumeControl->setValue(player->getVolume());
}

void PlayerWindow::updateSpeedControl(){
    ui->speedControl->setValue(player->speed);
}


void PlayerWindow::setBook(Book* book){
    assert(book);
    if (this->book)
        delete this->book;
    this->book = book;

    player->updateBook(book);

    ui->cover->setPixmap(book->cover);
    ui->titleLabel->setText(book->title.c_str());
    ui->authorLabel->setText(book->author.c_str());
    ui->narratorLabel->setText(book->narrator.c_str());
    // ui->progressBar->setValue(book->getPosition() / book->duration);
}

void PlayerWindow::open(){
    QString path = QFileDialog::getOpenFileName(this, tr("Audio File"));
    if (path.isNull() == false){
        Book* b = new Book(path.toStdString());
        setBook(b);
    }
}

void PlayerWindow::about(){
    QMessageBox msgBox;
    msgBox.setText(ABOUT_MSG);
    msgBox.exec();
}

void PlayerWindow::loadChapters(){
    if (book and not book->chapters.empty()){
        for (auto chap: book->chapters){
            ui->chapterSelect->insertItem(chap.num - 1, (std::to_string(chap.num) + ": " + chap.title).c_str());
        }
    }
    else
        ui->chapterSelect->insertItem(0, "[File doesn't support chapters]");
}

void PlayerWindow::paulBlart(){
    ui->cover->setPixmap(QPixmap(PAUL_BLART));
    ui->titleLabel->setText("Paul Blart");
    ui->authorLabel->setText("Paul Blart");
    ui->narratorLabel->setText("Also Paul Blart");
    ui->speedControl->setValue(10.0);
}

void PlayerWindow::openSettings(){
    todo("Settings");
}

void PlayerWindow::getAuthcode(){
    bool ok;
    auto text = QInputDialog::getText(this, tr("Enter Authcode"), tr("Authcode:"), QLineEdit::Normal, "", &ok);
    if (ok and !text.isEmpty()){
        _debug(text.toStdString())
        Book::authcode = text.toStdString();
    }
    else
        note(failed)
}