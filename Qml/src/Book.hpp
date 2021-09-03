#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>

// #include <qpixmap.h>
#include <QPixmap>
#include <qobjectdefs.h>
#include <qqml.h>
#include <QVector>
#include <QString>

// #define ARGPARSE_LONG_VERSION_ARG_ONLY
// #include "argparse.hpp"

#include "Global.hpp"

using std::string;
using std::stringstream;
using std::vector;

#define BAD_BOOK_WARNING "No Authcode Provided (or invalid file path)"

struct Chapter{
private:
    Q_GADGET
public:
    int    num;
    string title;
    ulong  start;
    double startTime;
    ulong  end;
    double endTime;
};


class Book: public QObject{
    Q_OBJECT
    // Q_PROPERTY(QPixmap cover             READ cover)
    Q_PROPERTY(QString file              READ file)
    Q_PROPERTY(QVector<Chapter> chapters READ chapters)
    Q_PROPERTY(float  metaStartSec       READ metaStartSec)
    Q_PROPERTY(float  duration           READ duration)
    Q_PROPERTY(ulong  size               READ size)
    Q_PROPERTY(QString description       READ description)
    Q_PROPERTY(QString author            READ author)
    Q_PROPERTY(QString releaseDate       READ releaseDate)
    Q_PROPERTY(QString title             READ title)
    Q_PROPERTY(QString narrator          READ narrator)
    Q_PROPERTY(QString publisher         READ publisher)
    QML_ELEMENT
public:
    Book(string filepath);
    ~Book();

    float actualStartSec;

    QString getIntro();
    FILE* open();
    void close(int signum = 0);

public slots:
    // QPixmap  cover()            { return _cover; }
    QString  file()             { return _file; }
    QVector<Chapter> chapters() { return _chapters; }
    float    metaStartSec()     { return _metaStartSec; }
    float    duration()         { return _duration; }
    ulong    size()             { return _size; }
    QString  description()      { return _description; }
    QString  author()           { return _author; }
    QString  releaseDate()      { return _releaseDate; }
    QString  title()            { return _title; }
    QString  narrator()         { return _narrator; }
    QString  publisher()        { return _publisher; }

    // void setCover(QPixmap to)             { _cover = to; }
    void setFile(QString to)              { _file = to; }
    void setChapters(QVector<Chapter> to) { _chapters = to; }
    void setMetaStartSec(float to)        { _metaStartSec = to; }
    void setDuration(float to)            { _duration = to; }
    void setSize(ulong to)                { _size = to; }
    void setDescription(QString to)       { _description = to; }
    void setAuthor(QString to)            { _author = to; }
    void setReleaseDate(QString to)       { _releaseDate = to; }
    void setTitle(QString to)             { _title = to; }
    void setNarrator(QString to)          { _narrator = to; }
    void setPublisher(QString to)         { _publisher = to; }

    ulong getPosition();
    void  setPosition(int secs);
    Chapter getCurrentChapter();


private:
    // QPixmap _cover;
    QString _file;
    QVector<Chapter> _chapters;

    //* Metadata
    float   _metaStartSec;
    float   _duration;
    ulong   _size;
    QString _description;
    QString _author;
    QString _releaseDate;
    QString _title;
    QString _narrator;
    QString _publisher;

    const char* defaultMetaStartSecValue = "0.0";
    const char* defaultDurationValue = "0.0";
    const char* defaultSizeValue = "-1";
    const char* defaultDescriptionValue = "No Description Provided";
    const char* defaultAuthorValue = "A. N. Author";
    const char* defaultReleaseDateValue = "0000";
    const char* defaultTitleValue = "Title";
    const char* defaultNarratorValue = "A. Narrator";
    const char* defaultPublisherValue;


    FILE* ffmpeg;
    int sleepTimer;
    bool cli;
    // If the book isn't given a valid filepath, or is given a .aax file without an authcode, this is false
    bool amValid;

    // Returns:
    // -1: file is invalid
    // -2: authcode is invalid
    // -3: both are invalid
    //  1: all good
    int validate();
    bool validateFile();
    void printAuthcodeError();
    void loadMetadata();
    QVector<Chapter> loadChapters();
    string addAuthcode();
    void printChaptersAndExit();
    void printDescriptionAndExit();
    void printPublisherAndExit();
    void printReleaseDateAndExit();
};
