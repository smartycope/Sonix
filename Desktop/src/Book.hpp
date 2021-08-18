#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>

// #include <qpixmap.h>
#include <QPixmap>

#define ARGPARSE_LONG_VERSION_ARG_ONLY
#include "argparse.hpp"

#include "defs.h"
extern bool verbose;

using std::string;
using std::stringstream;
using std::vector;


typedef struct{
    int    num;
    string title;
    ulong  start;
    double startTime;
    ulong  end;
    double endTime;
}Chapter;


class Book{
public:
    Book(string filepath, argparse::ArgumentParser* args = nullptr);
    ~Book();

    QPixmap cover;
    string file;
    vector<Chapter> chapters;
    float actualStartSec;

    //* Metadata
    float  metaStartSec;
    float  duration;
    ulong  size;
    string description;
    string author;
    string releaseDate;
    string title;
    string narrator;
    string publisher;

    static string authcode;

    void printIntro();
    ulong getPosition();
    void  setPosition(int secs);
    Chapter getCurrentChapter();
    FILE* open();
    void close(int signum = 0);

private:
    FILE* ffmpeg;
    int sleepTimer;
    bool cli;

    bool validateFile();
    bool validateAuthcode();
    void printAuthcodeError();
    void loadCover();
    void loadMetadata();
    vector<Chapter> loadChapters();
    bool addAuthcode(stringstream& stream);
    void printChaptersAndExit();
    void printDescriptionAndExit();
    void printPublisherAndExit();
    void printReleaseDateAndExit();
};
