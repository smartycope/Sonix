#pragma once

#include <stdint.h>
#include <string>

#include <QVector>
#include <QString>
#include <QObject>
#include <QFile>
#include <qqml.h>

#include "messages.hpp"


using std::string;
using std::stringstream;

struct Chapter{
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
    QFile ffmpegFile;

    QString getIntro();
    void open();
    void close(int signum = 0);

  public slots:
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

    Chapter getCurrentChapter(int posSecs);


  private:
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
    const char* defaultDurationValue     = "0.0";
    const char* defaultSizeValue         = "-1";
    const char* defaultDescriptionValue  = "No Description Provided";
    const char* defaultAuthorValue       = "A. N. Author";
    const char* defaultReleaseDateValue  = "0000";
    const char* defaultTitleValue        = "Title";
    const char* defaultNarratorValue     = "A. Narrator";
    const char* defaultPublisherValue;

    FILE* ffmpegInternal;
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
