#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>

#include <qt5/QtCore/qobject.h>
#include <QThread>
#include <QApplication>
#include <QObject>
#include <QString>
#include <QtCore/qglobal.h>
#include <QIODevice>
#include <QDataStream>
#include <QAudioOutput>
#include <QAudio>
#include <QFile>
#include <QBuffer>
#include <QAudioOutput>
#include <QByteArray>

#include <nlohmann/json.hpp>
#include "audiooutput.h"
#include "sonic.h"
#define ARGPARSE_LONG_VERSION_ARG_ONLY
#include "argparse.hpp"
#include "cope.hpp"

using json = nlohmann::json;
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

typedef struct{
    ulong hour;
    ulong min;
    ulong sec;
}PrettyTime;

FILE* ffmpeg;
bool verbose;
string file;

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

void shutDown(int signum){
    int rtn = pclose(ffmpeg);
    if (rtn) {
        printf("ffmpeg pipe returned: %d\n", rtn);
        exit(rtn);
    }
    exit(1);
}

PrettyTime getPrettyTime(ulong secs){
    PrettyTime t;
    t.hour = secs / 3600;
    t.min  = (secs % 3600) / 60;
    t.sec  = (secs % 3600) % 60;
    return t;
}

void addAuthcode(stringstream &stream, const string authcode){
    int len = file.length() - 1;
    if (file[len - 2] == 'a' and file[len - 1] == 'a' and file[len] == 'x'){
        if (not authcode.empty()){
            stream << " -activation_bytes " << authcode;
            if (verbose)
                printf("The file ends in .aax, using activation bytes: %s\n", authcode.c_str());
        }
        else{
            printf("Can't play .aax files without an authcode.");
            exit(2);
        }
    }
}

ulong getPosition(int outputSamplerate, int outputChannels){
    ulong samples = outputSamplerate * duration;
    ulong totalBytes = samples * outputChannels;
    ulong posRatio = AudioPlayer::bytesRead / totalBytes;
    return floor(duration * posRatio);

}

void setPosition(int secs, string authcode){
    if (verbose)
        todo("Set position");
    return;
    stringstream command;
    command << "ffmpeg -hide_banner -y -loglevel "
            << string(verbose ? "error": "quiet");
    addAuthcode(command, authcode);
    command << " -i \"" << file << '"'
            << " -metadata start_time=" << std::to_string(secs)
            << " \"" << file << '"';

    std::cout << getCmdOutS(command.str(), verbose) << '\n';
}


void loadMetadata(string authcode){
    stringstream command;
    command << "ffprobe -hide_banner -loglevel "
            << string(verbose ? "error": "quiet")
            << " -print_format json -show_format";
    addAuthcode(command, authcode);
    command << " -i \"" << file
            << '"';

    json metadata = json::parse(getCmdOutS(command.str(), verbose))["format"];

    char* end;

    startSec =    strtof(metadata.value<string>("start_time", "0.0").c_str(), &end); if (*end) startSec = 0.0;
    duration =    strtof(metadata.value<string>("duration", "0.0").c_str(), &end);   if (*end) duration = -1.0;
    size =        stoull(metadata.value<string>("size", "-1"));
    // bitrate =     stoi(metadata.value<string>("bitrate", "-1").c_str()); // .get<string>().c_str());

    metadata =    metadata["tags"];
    description = metadata.value<string>("description", "No Description Provided");
    author =      metadata.value<string>("artist", "[Artist]");
    releaseDate = metadata.value<string>("date", "0000");
    title =       metadata.value<string>("title", "[Title]");
    narrator =    metadata.value<string>("composer", "[Narrator]");

    if (description == "No Description Provided")
        description = getCmdOutS(string("mediainfo --Inform=\"General;%Track_More%\" \"") + file + '"');

    if (description == "No Description Provided")
        description = metadata.value<string>("comment", "No Description Provided");

    if (narrator == "[Narrator]")
        narrator = getCmdOutS(string("mediainfo --Inform=\"General;%nrt%\" \"") + file + '"');

    publisher = getCmdOutS(string("mediainfo --Inform=\"General;%pub%\" \"") + file + '"');

    // albumArtist = metadata.value<string>("albumartist", "[Album Artist]");
    // copyright =   metadata.value<string>("copyright", "Free");
    // album =       metadata.value<string>("album", "[Album]");
    // genre =       metadata.value<string>("genre", "Audiobook");
}

vector<Chapter> loadChapters(string authcode){
    vector<Chapter> vec;
    stringstream command;

    command << "ffprobe -hide_banner -loglevel "
            << string(verbose ? "error": "quiet")
            << " -print_format json -show_chapters";
    addAuthcode(command, authcode);
    command << " -i \"" << file
            << '"';

    auto chapters = json::parse(getCmdOutS(command.str(), verbose));

    for (auto chap: chapters["chapters"]){
        Chapter c;
        c.num   =     chap["id"].get<int>() + 1;
        c.title =     chap["tags"].value<string>("title", string("Chapter ") + std::to_string(c.num));
        c.start =     chap["start"].get<ulong>();
        c.startTime = stod(chap["start_time"].get<string>());
        c.end =       chap["end"].get<ulong>();
        c.endTime =   stod(chap["end_time"].get<string>());
        vec.push_back(c);
    }
    return vec;
}

void printIntro(){
    std::cout << "\"" << title << "\" by " << author << ", narrated by " << narrator << '\n';
}

void printChaptersAndExit(vector<Chapter> chapters){
    for (auto chap: chapters){
        auto start = getPrettyTime(chap.startTime);
        auto end   = getPrettyTime(chap.endTime);
        std::cout << chap.num << ": \"" << chap.title << "\"  "
                  << start.hour << ":" << start.min << ":" << start.sec << " - "
                  << end.hour   << ":" << end.min   << ":" << end.sec   << "\n";
    }
    exit(0);
}

argparse::ArgumentParser parseArgs(int argc, char* argv[]){
    argparse::ArgumentParser args("SAP", "0.1.3");
    args.add_description("Listen to audiobooks!");

    args.add_argument("audioFile")
        .required()
        .help("The file path of the audiobook to play");
        // .action([](const std::string& value) { return value; });

    args.add_argument("--verbose")
        .default_value(false)
        .implicit_value(true);

    args.add_argument("-s", "--speed")
        .help("The starting playback speed")
        .action([](const std::string& value) { return std::stof(value); })
        .default_value(1.0f);

    args.add_argument("-v", "--volume")
        .help("The starting playback volume (0-100)")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(99);

    args.add_argument("-r", "--rate")
        .help("The starting playback rate")
        .action([](const std::string& value) { return std::stof(value); })
        .default_value(1.0f);

    args.add_argument("-p", "--pitch")
        .help("The starting pitch")
        .action([](const std::string& value) { return std::stof(value); })
        .default_value(1.0f);

    args.add_argument("--emulateChordPitch")
        .help("Set to 1 to emulate human vocal chords when changing pitch")
        .default_value(false)
        .implicit_value(true);

    args.add_argument("--enableNonlinearSpeedup")
        .help("Not sure what this does.")
        .default_value(false)
        .implicit_value(true);

    args.add_argument("--increaseQuality")
        .help("Slightly increase quality, at the expense of speed")
        .default_value(false)
        .implicit_value(true);

    args.add_argument("-br", "--samplerate")
        .help("The output samplerate")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(44100);

    args.add_argument("-c", "--channels")
        .help("The output number of channels")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(2);

    args.add_argument("-a", "--authcode")
        .help("Specify the audible authcode for playing .aax files")
        .default_value(string());

    args.add_argument("-ss", "--startSec")
        .help("Start playing x seconds in")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(0);

    args.add_argument("-sm", "--startMin")
        .help("Start playing x minutes in")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(0);

    args.add_argument("-sh", "--startHour")
        .help("Start playing x hours in")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(0);

    args.add_argument("-sc", "--startChapter")
        .help("Start playing at chapter x")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(0);

    args.add_argument("--listChapters")
        .help("Print the chapters in the book (if available) and exit")
        .default_value(false)
        .implicit_value(true);

    args.add_argument("--description")
        .help("Print the book's description (if available) and exit")
        .default_value(false)
        .implicit_value(true);

    args.add_argument("--publisher")
        .help("Print the book's publisher (if available) and exit")
        .default_value(false)
        .implicit_value(true);

    args.add_argument("--released")
        .help("Print the when the book was released (if available) and exit")
        .default_value(false)
        .implicit_value(true);

    args.add_argument("-t", "--sleepTimer")
        .help("Stop playing after x minutes")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(0);

    args.add_argument("-pos", "--savePosition")
        .help("When you stop, save the position to the file (only works on supporting file formats)")
        .default_value(true)
        .implicit_value(true);

    args.add_argument("-nopos", "--noSavePosition")
        .help("When you stop, don't save the position to the file")
        .default_value(false)
        .implicit_value(true);

    args.add_argument("-sv", "--startSaved")
        .help("If supported by the file format, start at the saved position (overidden by other -s* parameters)")
        .default_value(true)
        .implicit_value(true);

    args.add_argument("-nosv", "--noStartSaved")
        .help("Don't start at the saved position (overidden by other -s* parameters)")
        .default_value(false)
        .implicit_value(true);

    // args.add_argument("-as", "--acclimate")
        // .help("Gradually increase the speed over time")
        // .nargs(3)
        // .action([](const std::string& value) { return std::stoi(value); })
        // .default_value(vector<float>{1.0f, 5.0f, 2.0f});

    args.add_argument("-ad", "--acclimateTo")
        .help("Gradually increase the speed over time, starting at -s, and going to x")
        .action([](const std::string& value) { return std::stof(value); })
        .default_value(0);

    args.add_argument("-at", "--acclimateTime")
        .help("Gradually increase the speed over x hours, starting at -s.")
        .action([](const std::string& value) { return std::stof(value); })
        .default_value(1);

    args.add_argument("-ai", "--acclimateIncrease")
        .help("Gradually increase the speed over time, starting at -s, and going to -s + x")
        .action([](const std::string& value) { return std::stof(value); })
        .default_value(0);

    //
    try {
        args.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl << args;
        exit(0);
    }

    return args;
}

int main(int argc, char* argv[]) {
    //* Parse args
    argparse::ArgumentParser args = parseArgs(argc, argv);

    file = args.get<string>("audioFile");
    AudioPlayer::setVolume(args.get<int>("--volume"));
    AudioPlayer::speed = args.get<float>("--speed");
    AudioPlayer::rate = args.get<float>("--rate");
    AudioPlayer::pitch = args.get<float>("--pitch");
    AudioPlayer::emulateChordPitch = args.get<bool>("--emulateChordPitch");
    AudioPlayer::enableNonlinearSpeedup = args.get<bool>("--enableNonlinearSpeedup");
    AudioPlayer::quality = args.get<bool>("--increaseQuality");
    AudioPlayer::samplerate = args.get<int>("--samplerate");
    AudioPlayer::channels = args.get<int>("--channels");

    int ss;
    if (not args.get<bool>("--noStartSaved"))
        ss = startSec;
    ss = args.get<int>("--startSec") + (args.get<int>("--startMin") * 60) + (args.get<int>("--startHour") * 3600);
    int ts = args.get<int>("--sleepTimer") * 60;
    verbose = args.get<bool>("--verbose");
    string authcode = args.get<string>("--authcode");

    if (args.get<bool>("--savePosition") and verbose)
        todo("Save metadata position on close");

    if ((args.get<int>("--acclimateTo") or args.get<int>("--acclimateIncrease")) and verbose)
        todo("Acclimation");

    vector<Chapter> chapters = loadChapters(authcode);
    loadMetadata(authcode);
    printIntro();

    int chap = args.get<int>("--startChapter");
    if (chap){
        assert(chapters[chap].num == chap + 1);
        ss += chapters[chap].startTime;
    }

    if (args.get<bool>("--listChapters"))
        printChaptersAndExit(chapters);

    if (args.get<bool>("--description")){
        std::cout << description << '\n';
        return 0;
    }
    if (args.get<bool>("--publisher")){
        std::cout << publisher << '\n';
        return 0;
    }
    if (args.get<bool>("--released")){
        std::cout << releaseDate << '\n';
        return 0;
    }

    QApplication app(argc, argv);
    app.setApplicationName("SuperSonic Audiobook Player");

    //* Generate the command
    std::stringstream command;
    command << "ffmpeg -hide_banner -loglevel error " << " -ss " << ss;

    // If it's a .aax file and we are given an authcode, tell ffmpeg so it can decrypt it
    addAuthcode(command, authcode);

    command <<" -i \"" << file << "\" -codec pcm_u8 -vn -f u8"
            << " -ac " << AudioPlayer::channels
            << " -ar " << AudioPlayer::samplerate;

    if (ts)
        command << " -t "  << ts;

    command << " -";

    //* Open the file
    if (verbose)
        printf("Executing command: \"%s\"\n", command.str().c_str());

    ffmpeg = popen(command.str().c_str(), "r");
    if (ffmpeg == NULL) { printf("Error: Failed to open pipe"); return 5; }

    signal(SIGINT, shutDown);

    //* Main loop
    AudioPlayer player(ffmpeg);
    app.exec();

    //* Close up and exit
    int rtn = pclose(ffmpeg);
    if (rtn) { printf("\"%s\" returned error: %d\n", command.str().c_str(), rtn); return rtn; }

    return 0;
}


/*
static int setargs(char *args, char **argv){
    int count = 0;

    while (isspace(*args)) ++args;
    while (*args) {
        if (argv) argv[count] = args;
        while (*args && !isspace(*args)) ++args;
        if (argv && *args) *args++ = '\0';
        while (isspace(*args)) ++args;
        count++;
    }
}

char **parsedargs(char *args, int *argc){
    char **argv = NULL;
    int    argn = 0;

    if (args && *args
        && (args = strdup(args))
        && (argn = setargs(args,NULL))
        && (argv = malloc((argn+1) * sizeof(char *)))) {
          *argv++ = args;
          argn = setargs(args,argv);
    }

    if (args && !argv) free(args);

    *argc = argn;
    return argv;
}

void freeparsedargs(char **argv){
    if (argv) {
        free(argv[-1]);
        free(argv-1);
    }
}
    return count;
}

int main(){
    char **argv;
    char *cmd;
    int argc;

    cmd = "ffmpeg -i infile outfile";
    argv = parsedargs(cmd,&argc);
    ffmpeg(argc, argv);
}
*/