#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>

// #include <qpixmap.h>
#include <QPixmap>

#include "cope.hpp"
#include "defs.h"

using namespace std;


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
    Book(string filepath);

    QPixmap cover;
    string file;
    vector<Chapter> chapters;

    //* Metadata
    float startSec;
    float duration;
    ulong size;
    string description;
    string author;
    string releaseDate;
    string title;
    string narrator;
    string publisher;

    static string authcode;

    void printIntro();
    ulong getPosition(int outputSamplerate, int outputChannels);
    void  setPosition(int secs);
    void printChaptersAndExit(vector<Chapter> chapters);

private:
    void loadCover();
    void loadMetadata();
    vector<Chapter> loadChapters();
};
