#pragma once

#include <QString>
#include <QUrl>
#include <QObject>
#include <QtQml/qqml.h>
#include <iostream>
#include "cope.cpp"
#include "sndfile.h"

#define FILENAME "/home/rebecca/Downloads/art_of_war_librivox_64kb_mp3/art_of_war_01-02_sun_tzu_64kb.wav"

class Book: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString author    READ author   WRITE setAuthor   NOTIFY onAuthorChanged)
    Q_PROPERTY(QString title     READ title    WRITE setTitle    NOTIFY onTitleChanged)
    Q_PROPERTY(QUrl    cover     READ cover    WRITE setCover    NOTIFY onCoverChanged)
    Q_PROPERTY(double  position  READ position WRITE setPosition NOTIFY onPositionChanged)
    QML_ELEMENT

signals:
    void onAuthorChanged();
    void onTitleChanged();
    void onCoverChanged();
    void onPositionChanged();

public:
    explicit Book(QObject *parent = nullptr): QObject(parent),
        _author(QString("AUTHOR")),
        _title(QString("TITLE")),
        _cover(QUrl("really/not/a/cover/path")),
        _position(0.f),
        file(sf_open(FILENAME, SFM_READ, &fileInfo)){
            // debugs("called book explicit constructor\n");
            init();
        }
    Book(QUrl path):
        _author(QString("AUTHOR")),
        _title(QString("TITLE")),
        _cover(path),
        _position(0.f),
        file(sf_open(FILENAME, SFM_READ, &fileInfo)){
            // debugs("Regular book constructed");
            init();
        };
    Book(const Book& book):
        _author(book._author),
        _title(book._title),
        _cover(book._cover),
        _position(book._position),
        file(sf_open(FILENAME, SFM_READ, &fileInfo)){
            // debugs("book copy constructor called");
            init();
        }

    QString _author;
    QString _title;
    QUrl    _cover;
    double  _position;
    SNDFILE* file;
    SF_INFO  fileInfo;

    Q_INVOKABLE void _onAuthorChanged();
    Q_INVOKABLE void _onTitleChanged();
    Q_INVOKABLE void _onCoverChanged();
    Q_INVOKABLE void _onPositionChanged();


    Q_INVOKABLE QString author(){   return _author;    }
    Q_INVOKABLE QString title(){    return _title;     }
    Q_INVOKABLE QUrl    cover(){    return _cover;     }
    Q_INVOKABLE double  position(){ return _position;  }

    Q_INVOKABLE void setAuthor(QString  tmp){ _author   = tmp; }
    Q_INVOKABLE void setTitle(QString   tmp){ _title    = tmp; }
    Q_INVOKABLE void setCover(QUrl      tmp){ _cover    = tmp; }
    Q_INVOKABLE void setPosition(double tmp){ _position = tmp; }

     const Book& operator =(const Book& book);

private:
     void init();
};
