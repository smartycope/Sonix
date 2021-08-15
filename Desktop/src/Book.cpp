#include "Book.h"
#include <sstream>


string Book::authcode = string();

Book::Book(string filepath): filepath(filepath) {
    loadMetadata();
    loadChapters();
    loadCover();
    printIntro();
}

void Book::loadCover(){
    vector<char> coverData = getCmdOutV(string("ffmpeg -hide_banner -loglevel error -i \"") +
                          filepath +
                          string("\" -map 0:v -c:v:1 png -disposition:v:1 attached_pic -f apng -"));
    cover.loadFromData(reinterpret_cast<uchar*>(coverData.data()), coverData.size(), "png");
}

void Book::loadMetadata(string authcode){
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

vector<Chapter> Book::loadChapters(string authcode){
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

void Book::printIntro(){
    std::cout << "\"" << title << "\" by " << author << ", narrated by " << narrator << '\n';
}

void Book::printChaptersAndExit(vector<Chapter> chapters){
    for (auto chap: chapters){
        auto start = getPrettyTime(chap.startTime);
        auto end   = getPrettyTime(chap.endTime);
        std::cout << chap.num << ": \"" << chap.title << "\"  "
                  << start.hour << ":" << start.min << ":" << start.sec << " - "
                  << end.hour   << ":" << end.min   << ":" << end.sec   << "\n";
    }
    exit(0);
}

ulong Book::getPosition(int outputSamplerate, int outputChannels){
    ulong samples = outputSamplerate * duration;
    ulong totalBytes = samples * outputChannels;
    ulong posRatio = AudioPlayer::bytesRead / totalBytes;
    return floor(duration * posRatio);

}

void Book::setPosition(int secs, string authcode){
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
