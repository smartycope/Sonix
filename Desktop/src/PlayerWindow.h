#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QMainWindow>

#include "Book.h"
#include "sonic.h"
#include "cope.hpp"
#include "defs.h"
#include "audiooutput.h"
#include <cassert>
#include <functional>
#include <iostream>
#include <qtimer.h>
#include <string>
#include <QFileDialog>
#include <QTimer>
#include "./ui_PlayerWindow.h"
#include <qlocale.h>
#include <qwindowdefs.h>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui{ class PlayerWindow; }
QT_END_NAMESPACE


#define SKIP_SECONDS 20
#define SKIP_SAMPLES (SAMPLERATE * SKIP_SECONDS)
#define SPEED_INCREMENT .25f
#define VOLUME_INCREMENT 2.0f

#define UNSPECIFIED_COVER_PATH "/home/marvin/hello/C/SAP/Desktop/assets/defaultBookCover.png"


class PlayerWindow: public QMainWindow{
    Q_OBJECT

public:
    PlayerWindow(QWidget* parent = nullptr);
    ~PlayerWindow();

    AudioPlayer player;
    Book* book = nullptr;

    void setBook(Book* book);

    // bool  getPaused()                 { return paused; };
    // float getSpeed()                  { return speed; };
    // float getPitch()                  { return pitch; };
    // float getRate()                   { return rate; };
    // float getVolume()                 { return volume; };
    // bool  getEmulateChordPitch()      { return emulateChordPitch; };
    // int   getQuality()                { return quality; };
    // bool  getEnableNonlinearSpeedup() { return enableNonlinearSpeedup; };

public slots:
    bool togglePaused(); // Returns what the new current paused value is
    void skip(int amount);
    void jump(int chapters);
    void skipForward();
    void skipBackward();
    void jumpForward();
    void jumpBackward();
    void flushStream();
    void finished(); // Called when we've finished the audiobook
    void incrementSpeed();
    void decrementSpeed();
    void incrementVolume();
    void decrementVolume();

    void setPaused(bool to);
    // void setSpeed(double to);
    // void setPitch(float to);
    // void setRate(float to);
    // void setVolume(int percentage);
    // void setEmulateChordPitch(bool to);
    // void setQuality(int to);
    // void setEnableNonlinearSpeedup(bool to);

    void open();
    void about();

private:
    Ui::PlayerWindow *ui;

    void updateSonic();
    void updateUI();
    void updateSampleProvider();
    void updateAll();

    bool sonicInitalized = false;
    bool uiInitalized = false;
    bool sampleProviderInitalized = false;
};
