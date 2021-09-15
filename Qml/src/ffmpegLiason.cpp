#include "ffmpegLiason.hpp"

// #include <stdio.h>

#include "Global.hpp"
// #include <unistd.h>
#include <QString>
#include <vector>
#include <thread>
#include <regex>
#include <future>
#include "ffmpeg.hpp"


FILE* runFFmpeg(const std::string& args, bool ffprobe, bool forceQuiet){
    std::stringstream command;
    std::vector<std::string> v;

    // Make a temporary file
    char name[] = "/tmp/fileXXXXXX";
    int fd = mkstemp(name);

    // char name[L_tmpnam];
    // tmpnam(name);

    if (ffprobe)
        todo("ffprobe");

    forceQuiet = true;

    // Make sure to always hide the banner, and check for verbose output, and to output to stdout (if ffmpeg)
    command << (ffprobe ? "ffprobe": "ffmpeg")
            << " -hide_banner -loglevel "
            << std::string(Global::verbose and not forceQuiet ? "error ": "quiet ")
            // << "verbose "
            << "-y "
            << args
            << ' '
            // << '-';
            << (ffprobe ? "": name);

    _debug(command.str())


    //* Parse the arguements into argc and argv
    Global::log("Executing command: \"" + command.str() + '"');

    QStringList params = QString(command.str().c_str()).split(' ', Qt::SkipEmptyParts);

    // Remember to put the spaces back
    for (const QString& s: params)
        v.push_back(std::regex_replace(s.toStdString(), std::regex(REPLACEMENT_CHAR), " "));



    //* Fork method
    // Global::isParentProcess = fork();
    // Parent
    // if (Global::isParentProcess != 0)
        // return fdopen(fd, "wb+");
    // Child
    // else
        // Global::log("Main ffmpeg exit code: " + std::to_string(ffmpeg(v.size(), result.data())));

    // return nullptr;


    //* Thread method
    Global::ffmpegThread = new std::thread(ffmpeg, v);
    Global::ffmpegThread->detach();

    return fdopen(fd, "wb+");

    //* Asyncronous method
    // auto rtnCode = std::async(std::launch::async, ffmpeg, v);
    // return stdout;
}
