#include <csignal>
#include <sstream>
#include <iostream>

// #include <QErrorMessage>
#include <QMessageBox>
#include <nlohmann/json.hpp>

#include "Book.hpp"
#include "cope.hpp"
#include "AudioPlayer.hpp"

using json = nlohmann::json;

string Book::authcode = string();

Book::Book(string filepath, argparse::ArgumentParser* args): file(filepath), sleepTimer(0), actualStartSec(0.0f),
                                                             cli(false), cover(QPixmap()), chapters(vector<Chapter>()),
                                                             metaStartSec(-1), duration(-1), size(-1),
                                                             description("No Description Provided"), author(""),
                                                             releaseDate("0000"), title(""), narrator(""),
                                                             publisher(""), ffmpeg(nullptr){

    if (validateFile()){
        if (validateAuthcode()){
            loadMetadata();
            loadChapters();
            loadCover();
            printIntro();
        }
        else
            printAuthcodeError();

        if (args){
            sleepTimer = args->get<int>("--sleepTimer") * 60;
            authcode = args->get<string>("--authcode");
            cli = args->get<bool>("--cli");

            if (not args->get<bool>("--noStartSaved"))
                actualStartSec = metaStartSec;
            if (args->get<int>("--startSec") or args->get<int>("--startMin") or args->get<int>("--startHour"))
                actualStartSec = args->get<int>("--startSec") + (args->get<int>("--startMin") * 60) + (args->get<int>("--startHour") * 3600);

            int chap = args->get<int>("--startChapter");
            // Make sure the file even *has* chapters
            if (chap != 1 and not chapters.empty() and verbose)
                printf("Can't start from chapter %d, file doesn't support chapter metadata", chap);

            if (not chapters.empty()){
                assert(chapters[chap - 1].num == chap);
                actualStartSec += chapters[chap - 1].startTime;
            }

            if (args->get<bool>("--savePosition") and verbose)
                todo("Save metadata position on close");

            if ((args->get<int>("--acclimateTo") or args->get<int>("--acclimateIncrease")) and verbose)
                todo("Acclimation");

            if (args->get<bool>("--listChapters"))
                printChaptersAndExit();

            if (args->get<bool>("--description"))
                printDescriptionAndExit();

            if (args->get<bool>("--publisher"))
                printPublisherAndExit();

            if (args->get<bool>("--released"))
                printReleaseDateAndExit();
        }
    }
}

Book::~Book(){
    close();
}

bool Book::validateAuthcode(){
    bool endsInAax = QString(file.c_str()).toLower().endsWith(".aax");
    return validateFile() and (not endsInAax or (endsInAax and not authcode.empty()));
}

void Book::printAuthcodeError(){
    if (verbose)
        printf(AUTHCODE_WARNING);

    if (not cli){
        // QErrorMessage msgBox;
        // msgBox.setWindowTitle("No Authcode Provided");
        // msgBox.showMessage(AUTHCODE_WARNING);
        // msgBox.exec();
        QMessageBox msgBox;
        msgBox.setText(AUTHCODE_WARNING);
        msgBox.exec();

        cover = QPixmap(UNSPECIFIED_COVER_PATH);
    }
    else
        exit(2);
}

bool Book::addAuthcode(stringstream& stream){
    validateAuthcode();
    if (QString(file.c_str()).toLower().endsWith(".aax") and not authcode.empty()){
        stream << " -activation_bytes " << authcode;
        if (verbose)
            printf("The file ends in .aax, using activation bytes: %s\n", authcode.c_str());
        return true;
    }
    else{
        // printAuthcodeError();
        return false;
    }
}

bool Book::validateFile(){
    // TODO: Do more here
    if (file.empty())
        return false;
    else
        return true;
}

void Book::loadCover(){
    stringstream command;
    command << "ffmpeg -hide_banner -loglevel quiet";
    if (not addAuthcode(command)) return;
    command << " -i \"" << file
            << "\" -map 0:v? -c:v:1 png -disposition:v:1 attached_pic -f apng -";

    vector<char> coverData = getCmdOutV(command.str(), verbose, false);
    if (coverData.size() < 64)
        cover = QPixmap(UNSPECIFIED_COVER_PATH);
    else
        cover.loadFromData(reinterpret_cast<uchar*>(coverData.data()), coverData.size(), "png");
}

void Book::loadMetadata(){
    stringstream command;
    command << "ffprobe -hide_banner -loglevel "
            << string(verbose ? "error": "quiet")
            << " -print_format json -show_format";
    if (not addAuthcode(command)) return;
    command << " -i \"" << file
            << '"';

    json metadata = json::parse(getCmdOutS(command.str(), verbose))["format"];

    char* end;

    metaStartSec = strtof(metadata.value<string>("start_time", "0.0").c_str(), &end); if (*end) metaStartSec = 0.0;
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

vector<Chapter> Book::loadChapters(){
    vector<Chapter> vec;
    stringstream command;

    command << "ffprobe -hide_banner -loglevel "
            << string(verbose ? "error": "quiet")
            << " -print_format json -show_chapters";
    if (not addAuthcode(command)) return vec;
    command << " -i \"" << file
            << '"';

    auto jsonChapters = json::parse(getCmdOutS(command.str(), verbose));

    for (auto chap: jsonChapters["chapters"]){
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

void Book::printIntro(){
    std::cout << "\"" << title << "\" by " << author << ", narrated by " << narrator << '\n';
}

void Book::printChaptersAndExit(){
    for (auto chap: chapters){
        auto start = getPrettyTime(chap.startTime);
        auto end   = getPrettyTime(chap.endTime);
        std::cout << chap.num << ": \"" << chap.title << "\"  "
                  << start.hour << ":" << start.min << ":" << start.sec << " - "
                  << end.hour   << ":" << end.min   << ":" << end.sec   << "\n";
    }
    exit(0);
}

void Book::printDescriptionAndExit(){
    std::cout << description << '\n';
    exit(0);
}

void Book::printPublisherAndExit(){
    std::cout << publisher << '\n';
    exit(0);
}

void Book::printReleaseDateAndExit(){
    std::cout << releaseDate << '\n';
    exit(0);
}

FILE* Book::open(){
    if (not validateFile())
        return nullptr;

    std::stringstream command;
    command << "ffmpeg -hide_banner -loglevel "
            << string(verbose ? "error": "quiet")
            << " -ss " << actualStartSec;

    // If it's a .aax file and we are given an authcode, tell ffmpeg so it can decrypt it
    if (not addAuthcode(command)) return nullptr;

    command <<" -i \"" << file << "\" -codec pcm_u8 -vn -f u8"
            << " -ac " << AudioPlayer::channels
            << " -ar " << AudioPlayer::samplerate;

    if (Book::sleepTimer)
        command << " -t "  << Book::sleepTimer;

    command << " -";

    //* Open the file
    if (verbose)
        printf("Executing command: \"%s\"\n", command.str().c_str());

    ffmpeg = popen(command.str().c_str(), "r");
    if (ffmpeg == NULL) {
        debugs("Error: Failed to open pipe");
        exit(5);
    }

    // signal(SIGINT, close);
    return ffmpeg;
}

void Book::close(int signum){
    int rtn = 0;
    if (ffmpeg)
        rtn = pclose(ffmpeg);
    if (rtn) {
        if (verbose)
            printf("ffmpeg pipe returned: %d\n", rtn);
        if (signum)
            exit(rtn);
    }
    if (signum)
        exit(1);
}

ulong Book::getPosition(){
    ulong samples = AudioPlayer::samplerate * duration;
    ulong totalBytes = samples * AudioPlayer::channels;
    ulong posRatio = AudioPlayer::bytesRead / totalBytes;
    return floor(duration * posRatio);

}

void Book::setPosition(int secs){
    if (verbose)
        todo("Set position");
    return;
    stringstream command;
    command << "ffmpeg -hide_banner -y -loglevel "
            << string(verbose ? "error": "quiet");
    if (not addAuthcode(command)) return;
    command << " -i \"" << file << '"'
            << " -metadata start_time=" << std::to_string(secs)
            << " \"" << file << '"';

    std::cout << getCmdOutS(command.str(), verbose) << '\n';
}
