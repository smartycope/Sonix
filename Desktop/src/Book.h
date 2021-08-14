#pragma once

#include <qpixmap.h>
#include <string>
#include <sstream>
#include "sndfile.h"
#include "defs.h"
// #include "cope.cpp"
#include "SampleProvider.hpp"
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <QPixmap>

using namespace std;

class Book{
public:
    string filepath;

    QPixmap cover;
    json chapters;

    unsigned long long size, frames;
    float  startSec;
    float  duration;
    int    bitrate;

    string albumArtist;
    string copyright;
    string description;
    string artist, author;
    string album;
    int    releaseDate;
    string genre;
    string title;
    string composer, narrator;

    Book(string filepath);
    ~Book();

private:
};
