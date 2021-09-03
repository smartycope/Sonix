#pragma once

#include <qobject.h>
#include <qobjectdefs.h>
#include <qquickitem.h>
#include <qvariant.h>
#include <string>
#include <cassert>
// #include <functional>
#include <iostream>

#include <qqml.h>
// #include <QMainWindow>
#include <QQuickWindow>
// #include <qtimer.h>
#include <QFileDialog>
#include <QTimer>
// #include "./ui_PlayerWindow.h"
// #include <qlocale.h>
// #include <qwindowdefs.h>

#include "Book.hpp"
#include "cope.hpp"
#include "AudioPlayer.hpp"
#include "Global.hpp"


class PlayerWindow: public QObject{
    Q_OBJECT
    Q_PROPERTY(Book*        book   READ book   WRITE setBook NOTIFY bookChanged)
    Q_PROPERTY(AudioPlayer* player READ player)
    QML_SINGLETON

  public:
    // init() is seperate from the constructor (which doesn't do anything) so
    // we can call it AFTER the ui is initialized, so we can update all the labels
    PlayerWindow(QWidget* parent = nullptr);
    ~PlayerWindow();

    void init(string filepath = "");
    void setBook(Book* book);
    void setPlayer(AudioPlayer* player){ _player = player; }

  public slots:
    void myprint(QString msg){ std::cout << msg.toStdString() << std::endl; }
    Book* book()          { return _book; }
    AudioPlayer* player() { return _player; }
    // void updateUI();
    void open(QString filepath);
    void about();
    void paulBlart();
    void getAuthcode();
    void openSettings();
    void updateVolumeBar();
    void updateSpeedControl();

  signals:
    void bookChanged();

  private:
    Book* _book;
    AudioPlayer* _player;
    QVariant getProperty(string item, string property);
    void setProperty(string item, string property, QVariant to);
    void loadChapters();
};
