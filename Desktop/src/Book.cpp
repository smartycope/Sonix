#include "Book.h"
#include <sstream>


Book::Book(string filepath): filepath(filepath) {
    // SF_INFO info;
    // file = sf_open(filepath.c_str(), SFM_READ, &info);
    // channels = info.channels;
    // format = info.format;
    // frames = info.frames;
    // samplerate = info.samplerate;
    // sections = info.sections;
    // seekable = info.seekable;

    //* Get metadata here
    // title = sf_get_string(file, SF_STR_TITLE);
    // author = sf_get_string(file, SF_STR_ARTIST);
    // description = sf_get_string(file, SF_STR_COMMENT);
    // copyrightNotice = sf_get_string(file, SF_STR_COPYRIGHT);
    // sf_get_string(file, SF_STR_ALBUM); // Same as Title
    // releaseDate = sf_get_string(file, SF_STR_DATE);
    // sf_get_string(file, SF_STR_GENRE); // "audiobook"
    // sf_get_string(file, SF_STR_LICENSE); // nothing
    // sf_get_string(file, SF_STR_SOFTWARE);
    // sf_get_string(file, SF_STR_TRACKNUMBER);

    vector<char> coverData = getCmdOutV(string("ffmpeg -hide_banner -loglevel error -i \"") +
                          filepath +
                          string("\" -map 0:v -c:v:1 png -disposition:v:1 attached_pic -f apng -"));
    cover.loadFromData(reinterpret_cast<uchar*>(coverData.data()), coverData.size(), "png");

    // std::cout << getCmdOutS(string("ffprobe -loglevel error -hide_banner -print_format json -show_format -i \"") + filepath + '"') << '\n';
    json metadata = json::parse(getCmdOutS(string("ffprobe -loglevel error -hide_banner -print_format json -show_format -i \"") + filepath + '"'))["format"];

    char* end;

    size =        stoull(metadata.value<string>("size", "-1"));
    startSec =    strtof(metadata.value<string>("start_time", "0.0").c_str(), &end); if (*end) startSec = 0.0;
    duration =    strtof(metadata.value<string>("duration", "0.0").c_str(), &end);   if (*end) duration = -1.0;
    bitrate =     stoi(metadata.value<string>("bitrate", "-1").c_str()); // .get<string>().c_str());

    metadata =    metadata["tags"];
    albumArtist = metadata.value<string>("albumartist", "[Album Artist]");
    copyright =   metadata.value<string>("copyright", "Free");
    description = metadata.value<string>("description", "No Description Provided");
    artist =      metadata.value<string>("artist", "[Artist]");
    album =       metadata.value<string>("album", "[Album]");
    releaseDate = stoi(metadata.value<string>("date", "0000"));
    genre =       metadata.value<string>("genre", "Audiobook");
    title =       metadata.value<string>("title", "[Title]");
    composer =    metadata.value<string>("composer", "[Narrator]");

    narrator = composer;
    author = artist;
    frames = size;
    chapters = json::parse(getCmdOutS(string("ffprobe -loglevel error -hide_banner -print_format json -show_chapters -i \"") + filepath + '"'));
    // std::cout << "Chapters: " << chapters << '\n';
}


Book::~Book(){
}


/*
Chapters are formatted as such:
{
    "chapters": [
        {
            "id": 0,
            "time_base": "1/1000",
            "start": 0,
            "start_time": "0.000000",
            "end": 1172608,
            "end_time": "1172.608000",
            "tags": {
                "title": "Chapter 1"
            }
        },
        ...
*/