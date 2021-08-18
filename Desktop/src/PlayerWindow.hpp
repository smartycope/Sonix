#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H


#include <string>
#include <cassert>
// #include <functional>
#include <iostream>

#include <QMainWindow>
// #include <qtimer.h>
#include <QFileDialog>
#include <QTimer>
#include "./ui_PlayerWindow.h"
// #include <qlocale.h>
// #include <qwindowdefs.h>

#include "Book.hpp"
#include "cope.hpp"
#include "AudioPlayer.hpp"
#include "defs.h"
extern bool verbose;

QT_BEGIN_NAMESPACE
namespace Ui{ class PlayerWindow; }
QT_END_NAMESPACE


class PlayerWindow: public QMainWindow{
    Q_OBJECT

public:
    PlayerWindow(Book* book = nullptr, QWidget* parent = nullptr);
    ~PlayerWindow();

    Book* book;
    AudioPlayer* player;

    void setBook(Book* book);

public slots:
    void open();
    void about();
    void paulBlart();
    void getAuthcode();
    void openSettings();
    void updateVolumeBar();
    void updateSpeedControl();

private:
    Ui::PlayerWindow *ui;

    void loadChapters();
};

#endif