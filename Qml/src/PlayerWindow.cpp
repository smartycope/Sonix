#include "PlayerWindow.hpp"
#include "CoverProvider.hpp"
#include "src/AudioPlayer.hpp"
#include <QMessageBox>
// #include <QDialog>
#include <QQmlContext>
#include <QStringList>
#include <QInputDialog>
#include <QQuickItem>
#include <qlabel.h>
#include <qobject.h>
#include <qqmlcontext.h>


PlayerWindow::PlayerWindow(QWidget *parent): _book(nullptr), _player(nullptr), QObject(parent){ }

void PlayerWindow::init(string filepath){
    if (not filepath.empty()){
        _book = new Book(filepath);
        _player = new AudioPlayer(_book);
    }

    if (_book){
        Global::setUIProperty("titleLabel", "text", _book->title());
        Global::setUIProperty("introLabel", "text", _book->getIntro());
        // ui->progressBar->setValue(book->getPosition() / book->duration);
    }
}

PlayerWindow::~PlayerWindow(){
    delete _book;
    delete _player;
    // delete ui;
}

void PlayerWindow::updateVolumeBar(){
    // ui->_volumeControl->setValue(_player->getVolume());
}

void PlayerWindow::updateSpeedControl(){
    // ui->_speedControl->setValue(_player->speed);
}

void PlayerWindow::setBook(Book* to){
    assert(to);
    if (_book)
        delete _book;
    _book = to;

    if (not _player)
        _player = new AudioPlayer(_book);
    else
        _player->updateBook(_book);

    // Global::setUIProperty("cover", something, QPixmap)
    Global::setUIProperty("titleLabel", "text", _book->title());
    Global::setUIProperty("introLabel", "text", _book->getIntro());

    // ui->progressBar->setValue(book->getPosition() / book->duration);
}

void PlayerWindow::open(QString filepath){
    if (filepath.startsWith("file://"))
        filepath = filepath.right(filepath.length() - 7);
    Book* b = new Book(filepath.toStdString());
    //
    // CoverProvider::filepath = filepath.toStdString();
    setBook(b);
}

void PlayerWindow::about(){
    QMessageBox msgBox;
    msgBox.setText(ABOUT_MSG);
    msgBox.exec();
}

void PlayerWindow::loadChapters(){
    QStringList chaps;
    if (_book and not _book->chapters().empty())
        for (auto chap: _book->chapters())
            chaps.insert(chap.num - 1, (std::to_string(chap.num) + ": " + chap.title).c_str());
            // ui->chapterSelect->insertItem(chap.num - 1, (std::to_string(chap.num) + ": " + chap.title).c_str());
    else
        chaps.insert(1, "File doesn't support chapters");
        // ui->chapterSelect->insertItem(0, "[File doesn't support chapters]");

    Global::setUIProperty("chapterBox", "model", chaps);
}

void PlayerWindow::paulBlart(){
    // ui->cover->setPixmap(QPixmap(PAUL_BLART));
    // ui->titleLabel->setText("Paul Blart");
    // ui->authorLabel->setText("Paul Blart");
    // ui->narratorLabel->setText("Also Paul Blart");
    // ui->speedControl->setValue(10.0);
}

void PlayerWindow::openSettings(){
    todo("Settings");
}

void PlayerWindow::getAuthcode(){
    bool ok;
    // auto text = QInputDialog::getText(this, tr("Enter Authcode"), tr("Authcode:"), QLineEdit::Normal, "", &ok);
    auto text = QInputDialog::getText(nullptr, tr("Enter Authcode"), tr("Authcode:"), QLineEdit::Normal, "", &ok);
    if (ok and !text.isEmpty()){
        _debug(text.toStdString())
        Global::authcode = text.toStdString();
    }
    else
        note(failed)
}