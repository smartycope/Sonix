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

Book::Book(string filepath): _file(filepath.c_str()), sleepTimer(0), actualStartSec(0.0f),
                                             cli(false), /* _cover(QPixmap()), */ _chapters(QVector<Chapter>()),
                                             _metaStartSec(-1), _duration(-1), _size(-1), _author(""),
                                             _releaseDate("0000"), _title(""), _narrator(""),
                                             _publisher(""), ffmpeg(nullptr), amValid(true){
    // This isn't initialized at the initialization list (not quite sure how that works, linters are amazing)
    _description = defaultDescriptionValue;

    // We only care if the authcode is invalid. Otherwise, just make sure we're okay.
    if (validate() <= -2)
        printAuthcodeError();

    else if (amValid){
        loadMetadata();
        loadChapters();
        Global::setUIProperty("cover", "source", "image://cover" + _file);
        Global::log("Now Playing: \"" + _title.toStdString() + "\" " + getIntro().toStdString());
    }

    if (Global::args){
        sleepTimer = Global::args->get<int>("--sleepTimer") * 60;
        cli = Global::args->get<bool>("--cli");

        if (not Global::args->get<bool>("--noStartSaved"))
            actualStartSec = _metaStartSec;
        if (Global::args->get<int>("--startSec") or Global::args->get<int>("--startMin") or Global::args->get<int>("--startHour"))
            actualStartSec = Global::args->get<int>("--startSec") + (Global::args->get<int>("--startMin") * 60) + (Global::args->get<int>("--startHour") * 3600);

        int chap = Global::args->get<int>("--startChapter");
        // Make sure the file even *has* chapters
        if (chap != 1 and not _chapters.empty() and Global::verbose)
            printf("Can't start from chapter %d, file doesn't support chapter metadata", chap);

        if (not _chapters.empty()){
            assert(_chapters[chap - 1].num == chap);
            actualStartSec += _chapters[chap - 1].startTime;
        }

        if (Global::args->get<bool>("--savePosition") and Global::verbose)
            todo("Save metadata position on close");

        if ((Global::args->get<int>("--acclimateTo") or Global::args->get<int>("--acclimateIncrease")) and Global::verbose)
            todo("Acclimation");

        if (Global::args->get<bool>("--listChapters"))
            printChaptersAndExit();

        if (Global::args->get<bool>("--description"))
            printDescriptionAndExit();

        if (Global::args->get<bool>("--publisher"))
            printPublisherAndExit();

        if (Global::args->get<bool>("--released"))
            printReleaseDateAndExit();
    }
}

Book::~Book(){
    close();
}

int Book::validate(){
    bool endsInAax = _file.toLower().endsWith(".aax");
    bool authValid = not endsInAax or (endsInAax and not Global::authcode.empty());
    bool fileValid = validateFile();
    amValid = authValid and fileValid;

    if (not amValid){
        setTitle("");
        Global::setUIProperty("titleLabel", "text", "");
        Global::setUIProperty("introLabel", "text", BAD_BOOK_WARNING);
    }

    if (authValid and not fileValid)
        return -1;
    else if (fileValid and not authValid)
        return -2;
    else if (not authValid and not fileValid)
        return -3;
    else
        return 1;
}

// TODO: Do more here
bool Book::validateFile(){
    if (_file.isEmpty())
        return false;
    else
        return true;
}

void Book::printAuthcodeError(){
    amValid = false;
    //* I can't decide whether this should be contingient on verbose or not
    // Global::log(AUTHCODE_WARNING);
    print(AUTHCODE_WARNING);

    if (not cli and QML_QDIALOG_WORKS){
        Global::setUIProperty("authcodeWarning", "visible", true);
        // QMessageBox msgBox;
        // msgBox.setText(AUTHCODE_WARNING);
        // msgBox.exec();
    }
    else
        if (cli)
            exit(2);
}

string Book::addAuthcode(){
    // Is this actually nessicary here?
    if (validate() <= -2)
        printAuthcodeError();
    else if (amValid and _file.toLower().endsWith(".aax")){
        Global::log("The file ends in .aax, using activation bytes: \"" + Global::authcode + '"');
        return " -activation_bytes " + Global::authcode;
    }

    return "";
}

void Book::loadMetadata(){
    Global::log("Fetching metadata...");
    validate();
    if (amValid){
        json metadata = json::parse(Global::runFFmpegCmd("-print_format json -show_format " + addAuthcode() + " -i \"" + _file.toStdString() + '"', true))["format"];

        char* end;

        _metaStartSec = strtof(metadata.value<string>("start_time", defaultMetaStartSecValue).c_str(), &end); if (*end) _metaStartSec = 0.0;
        _duration =     strtof(metadata.value<string>("duration", defaultDurationValue).c_str(), &end);       if (*end) _duration = -1.0;
        _size =         stoull(metadata.value<string>("size", defaultSizeValue));
        // bitrate =     stoi(metadata.value<string>("bitrate", "-1").c_str()); // .get<string>().c_str());

        metadata =     metadata["tags"];
        _description = metadata.value<string>("description", defaultDescriptionValue).c_str();
        _author =      metadata.value<string>("artist", defaultAuthorValue).c_str();
        _releaseDate = metadata.value<string>("date", defaultReleaseDateValue).c_str();
        _title =       metadata.value<string>("title", defaultTitleValue).c_str();
        _narrator =    metadata.value<string>("composer", defaultNarratorValue).c_str();

        if (_description == defaultDescriptionValue){
            Global::log("Couldn't find description under description tag, trying the comment tag...");
            _description = metadata.value<string>("comment", defaultDescriptionValue).c_str();
        }

        if (_description == defaultDescriptionValue){
            Global::log("Couldn't get description, trying mediainfo...");
            _description = getCmdOutS(string("mediainfo --Inform=\"General;%Track_More%\" \"") + _file.toStdString() + '"', Global::verbose).c_str();
        }

        if (_narrator == "[Narrator]"){
            Global::log("Couldn't get narrator, trying mediainfo...");
            _narrator = getCmdOutS(string("mediainfo --Inform=\"General;%nrt%\" \"") + _file.toStdString() + '"', Global::verbose).c_str();
        }

        Global::log("Getting publisher independently");
        _publisher = getCmdOutS(string("mediainfo --Inform=\"General;%pub%\" \"") + _file.toStdString() + '"').c_str();

        // albumArtist = metadata.value<string>("albumartist", "[Album Artist]");
        // copyright =   metadata.value<string>("copyright", "Free");
        // album =       metadata.value<string>("album", "[Album]");
        // genre =       metadata.value<string>("genre", "Audiobook");
    }
}

QVector<Chapter> Book::loadChapters(){
    Global::log("Loading chapters...");
    QVector<Chapter> vec;
    validate();
    if (amValid){
        auto jsonChapters = json::parse(Global::runFFmpegCmd("-print_format json -show_chapters " + addAuthcode() + " -i \"" + _file.toStdString() + '"', true));

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
    }
    return vec;
}

Chapter Book::getCurrentChapter(){
    todo("chapters");
    return Chapter();
}

QString Book::getIntro(){
    validate();
    if (amValid){
        stringstream s;

        if (_author != defaultAuthorValue)
            s << "by " << _author.toStdString();
        if (_narrator != defaultNarratorValue)
            s << ", narrated by " << _narrator.toStdString();
        s << '\n';

        return s.str().c_str();
    }
    else
        return BAD_BOOK_WARNING;
}

void Book::printChaptersAndExit(){
    validate();
    if (amValid){
        for (auto chap: _chapters){
            auto start = Global::getPrettyTime(chap.startTime);
            auto end   = Global::getPrettyTime(chap.endTime);
            std::cout << chap.num << ": \"" << chap.title << "\"  "
                    << start.hour << ":" << start.min << ":" << start.sec << " - "
                    << end.hour   << ":" << end.min   << ":" << end.sec   << "\n";
        }
    }
    else
        print(BAD_BOOK_WARNING);
    exit(0);
}

void Book::printDescriptionAndExit(){
    validate();
    if (amValid)
        std::cout << _description.toStdString() << '\n';
    else
        print(BAD_BOOK_WARNING);
    exit(0);
}

void Book::printPublisherAndExit(){
    validate();
    if (amValid)
        std::cout << _publisher.toStdString() << '\n';
    else
        print(BAD_BOOK_WARNING);
    exit(0);
}

void Book::printReleaseDateAndExit(){
    validate();
    if (amValid)
        std::cout << _releaseDate.toStdString() << '\n';
    else
        print(BAD_BOOK_WARNING);
    exit(0);
}

FILE* Book::open(){
    Global::log("Opening ffmpeg pipe...");

    validate();
    if (not amValid)
        return nullptr;

    std::stringstream command;
    command << "ffmpeg -hide_banner -loglevel "
            << string(Global::verbose ? "error": "quiet")
            << " -ss " << actualStartSec
            << addAuthcode()
            <<" -i \"" << _file.toStdString() << "\" -codec pcm_u8 -vn -f u8"
            << " -ac " << AudioPlayer::_channels
            << " -ar " << AudioPlayer::_samplerate;

    if (Book::sleepTimer)
        command << " -t " << Book::sleepTimer;

    command << " -";

    //* Open the file
    if (Global::verbose)
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
        if (Global::verbose)
            printf("ffmpeg pipe returned: %d\n", rtn);
        if (signum)
            exit(rtn);
    }
    if (signum)
        exit(1);
}

ulong Book::getPosition(){
    validate();
    if (not amValid)
        return -1;
    ulong samples = AudioPlayer::_samplerate * _duration;
    ulong totalBytes = samples * AudioPlayer::_channels;
    ulong posRatio = AudioPlayer::bytesRead / totalBytes;
    return floor(_duration * posRatio);

}

void Book::setPosition(int secs){
    if (Global::verbose)
        todo("Set position");
    return;
    // stringstream command;
    // command << "ffmpeg -hide_banner -y -loglevel "
    //         << string(Global::verbose ? "error": "quiet");
    // if (not addAuthcode(command)) return;
    // command << " -i \"" << _file.toStdString() << '"'
    //         << " -metadata start_time=" << std::to_string(secs)
    //         << " \"" << _file.toStdString() << '"';

    // std::cout << getCmdOutS(command.str(), Global::verbose) << '\n';
}
