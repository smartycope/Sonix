#pragma once

#include <string>
#include "sndfile.h"
// #include <mp4v2/mp4v2.h>
#include "cope.cpp"

using namespace std;



class Book{
public:
    SNDFILE* file;
    string filepath;
    char* coverpath = nullptr;

    int channels;
    int format;
    long frames;
    int samplerate;
    int sections;
    int seekable;

    int pos;
    string title;
    string author;
    string narrator;
    string description;
    string releaseDate;
    string copyrightNotice;

    Book(string filepath);
    ~Book();
};