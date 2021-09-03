#pragma once

#include <stdint.h>
#include <sys/types.h>
#include <string>
#include <sstream>
#include <QQuickWindow>

#define ARGPARSE_LONG_VERSION_ARG_ONLY
#include "argparse.hpp"

#include "cope.hpp"

// They have a bug in their QDialog and QWarning QML types
#define QML_QDIALOG_WORKS false

// https://github.com/inAudible-NG/audible-activator
// https://github.com/bymarlin04/audible-activation-extractor

// https://openaudible.org/
// https://github.com/KrumpetPirate/AAXtoMP3


#define ABOUT_MSG "This is the SuperSonic Audiobook player!\n" \
                  "It allows you to listen to any audiobook, in any format, at any speed.\n"\
                  "This program is free software (free as in freedom, not free beer). It lets\n" \
                  "you listen to YOUR books how YOU like. To listen to audible books, you can\n" \
                  "download them, and either convert them to a 'normal' file format, or you\n" \
                  "can even listen to them directly. In order to do that, however, you need to\n" \
                  "get and enter your audible activation code.\n" \
                  "\n" \
                  "To download books, you can either download audible books directly from their \n" \
                  "website (go to library and click the download button), or free software like\n" \
                  "OpenAudible (https://openaudible.org/) can do it for you.\n" \
                  "\n" \
                  "To convert books, OpenAudible can automatically convert audible books for you,\n" \
                  "or you can do it with other free software such as:\n" \
                  "https://github.com/KrumpetPirate/AAXtoMP3\n" \
                  "\n" \
                  "To get the audible activation code linked with your account, so you can play\n" \
                  ".aax files directly, you can use free programs such as:\n" \
                  "https://github.com/inAudible-NG/audible-activator\n" \
                  "https://github.com/bymarlin04/audible-activation-extractor\n" \
                  "\n" \
                  "If you like this program, since it is free software (free as in freedom AND\n" \
                  "free beer), consider donating to me to pay for my ever growing addiction to\n" \
                  "audiobooks.\n" \
                  "If instead, you hate this program and would like to point out what's wrong\n" \
                  "with it, please do! I made this myself in my proverbial basement. I would\n" \
                  "love feedback.\n" \
                  "Either way, feel free to reach out to me at smartycope@gmail.com.\n"\
                  "\n"\
                  "NOT-copyright 2021, Copeland Carter. No rights reserved."

#define AUTHCODE_WARNING "Error: Can't play .aax files without an authcode.\n" \
                         "\n" \
                         "You can get yours with these free and legal tools:\n" \
                         "https://github.com/inAudible-NG/audible-activator\n" \
                         "https://github.com/bymarlin04/audible-activation-extractor\n" \
                         "\n" \
                         "If that's too difficult, you can also use these free and\n" \
                         "legal tools to convert to a better file format:\n" \
                         "https://openaudible.org/\n" \
                         "https://github.com/KrumpetPirate/AAXtoMP3\n" \
                         "\n" \
                         "(The .m4a/.m4b format is recommended just because it has\n" \
                         "a lot of metadata to work with.)\n"


#define todo(feature) if (Global::verbose){ printDebugCount(); printMetaData(); printclrsl(TODO_COLOR, "Todo: "); printclr(REGULAR_DEBUG_COLOR, feature); printVscodeLink(); }

typedef struct{
    ulong hour;
    ulong min;
    ulong sec;
}PrettyTime;

class Global {
  private:
    // Private constructor so that no objects can be created.
    explicit Global() { }
    static Global* _instance;

  public:
    static bool verbose;
    static QQuickWindow* ui;
    static argparse::ArgumentParser* args;
    static std::string authcode;

    static Global* get() {
        if (!_instance)
            _instance = new Global;
        return _instance;
    }

    static void log(std::string msg){
        if (verbose)
            std::cout << msg << '\n';
    }

    static PrettyTime getPrettyTime(const ulong& secs){
        PrettyTime t;
        t.hour = secs / 3600;
        t.min  = (secs % 3600) / 60;
        t.sec  = (secs % 3600) % 60;
        return t;
    }

    // I'm sorry, runFfmpegCmd just looks too stupid.
    static std::string runFFmpegCmd(const std::string& args, bool ffprobe = false, bool forceQuiet = false){
        std::stringstream command;
        // Make sure to always hide the banner, and check for verbose output, and to output to stdout (if ffmpeg)
        command << (ffprobe ? "ffprobe": "ffmpeg")
                << " -hide_banner -loglevel "
                << std::string(verbose and not forceQuiet ? "error ": "quiet ")
                << args
                << (ffprobe ? "": " -");

        return getCmdOutS(command.str(), verbose, false);
    }

    static QVariant getUIProperty(std::string item, std::string property){
        QObject* obj = ui->findChild<QObject*>(item.c_str());
        if (obj)
            return obj->property(property.c_str());
        else
            log("No property " + property + " in " + item);
        return QVariant();
    }

    static void setUIProperty(std::string item, std::string property, QVariant to){
        QObject* obj = ui->findChild<QObject*>(item.c_str());
        if (obj)
            obj->setProperty(property.c_str(), to);
        else
            log("No property " + property + " in " + item);
    }

    static void parseArgs(int argc, char* argv[]){
        args = new argparse::ArgumentParser("SAP", "0.1.6");
        args->add_description(ABOUT_MSG);

        args->add_argument("audioFile")
            // .required()
            .help("The file path of the audiobook to play")
            .default_value(std::string());

        args->add_argument("--verbose")
            .default_value(false)
            .implicit_value(true);

        args->add_argument("-s", "--speed")
            .help("The starting playback speed")
            .action([](const std::string& value) { return std::stof(value); })
            .default_value(1.0f);

        args->add_argument("-v", "--volume")
            .help("The starting playback volume (0-100)")
            .action([](const std::string& value) { return std::stoi(value); })
            .default_value(99);

        args->add_argument("-r", "--rate")
            .help("The starting playback rate")
            .action([](const std::string& value) { return std::stof(value); })
            .default_value(1.0f);

        args->add_argument("-p", "--pitch")
            .help("The starting pitch")
            .action([](const std::string& value) { return std::stof(value); })
            .default_value(1.0f);

        args->add_argument("--emulateChordPitch")
            .help("Set to 1 to emulate human vocal chords when changing pitch")
            .default_value(false)
            .implicit_value(true);

        args->add_argument("--enableNonlinearSpeedup")
            .help("Not sure what this does.")
            .default_value(false)
            .implicit_value(true);

        args->add_argument("--increaseQuality")
            .help("Slightly increase quality, at the expense of speed")
            .default_value(false)
            .implicit_value(true);

        args->add_argument("-br", "--samplerate")
            .help("The output samplerate")
            .action([](const std::string& value) { return std::stoi(value); })
            .default_value(44100);

        args->add_argument("-c", "--channels")
            .help("The output number of channels")
            .action([](const std::string& value) { return std::stoi(value); })
            .default_value(2);

        args->add_argument("-a", "--authcode")
            .help("Specify the audible authcode for playing .aax files")
            .default_value(std::string());

        args->add_argument("-ss", "--startSec")
            .help("Start playing x seconds in")
            .action([](const std::string& value) { return std::stoi(value); })
            .default_value(0);

        args->add_argument("-sm", "--startMin")
            .help("Start playing x minutes in")
            .action([](const std::string& value) { return std::stoi(value); })
            .default_value(0);

        args->add_argument("-sh", "--startHour")
            .help("Start playing x hours in")
            .action([](const std::string& value) { return std::stoi(value); })
            .default_value(0);

        args->add_argument("-sc", "--startChapter")
            .help("Start playing at chapter x")
            .action([](const std::string& value) { return std::stoi(value); })
            .default_value(1);

        args->add_argument("--listChapters")
            .help("Print the chapters in the book (if available) and exit")
            .default_value(false)
            .implicit_value(true);

        args->add_argument("--description")
            .help("Print the book's description (if available) and exit")
            .default_value(false)
            .implicit_value(true);

        args->add_argument("--publisher")
            .help("Print the book's publisher (if available) and exit")
            .default_value(false)
            .implicit_value(true);

        args->add_argument("--released")
            .help("Print the when the book was released (if available) and exit")
            .default_value(false)
            .implicit_value(true);

        args->add_argument("-cli", "--cli")
            .help("Don't open a window")
            .default_value(false)
            .implicit_value(true);

        args->add_argument("-t", "--sleepTimer")
            .help("Stop playing after x minutes")
            .action([](const std::string& value) { return std::stoi(value); })
            .default_value(0);

        args->add_argument("-pos", "--savePosition")
            .help("When you stop, save the position to the file (only works on supporting file formats)")
            .default_value(true)
            .implicit_value(true);

        args->add_argument("-nopos", "--noSavePosition")
            .help("When you stop, don't save the position to the file")
            .default_value(false)
            .implicit_value(true);

        args->add_argument("-sv", "--startSaved")
            .help("If supported by the file format, start at the saved position (overidden by other -s* parameters)")
            .default_value(true)
            .implicit_value(true);

        args->add_argument("-nosv", "--noStartSaved")
            .help("Don't start at the saved position (overidden by other -s* parameters)")
            .default_value(false)
            .implicit_value(true);

        // args->add_argument("-as", "--acclimate")
            // .help("Gradually increase the speed over time")
            // .nargs(3)
            // .action([](const std::string& value) { return std::stoi(value); })
            // .default_value(vector<float>{1.0f, 5.0f, 2.0f});

        args->add_argument("-ad", "--acclimateTo")
            .help("Gradually increase the speed over time, starting at -s, and going to x")
            .action([](const std::string& value) { return std::stof(value); })
            .default_value(0);

        args->add_argument("-at", "--acclimateTime")
            .help("Gradually increase the speed over x hours, starting at -s.")
            .action([](const std::string& value) { return std::stof(value); })
            .default_value(1);

        args->add_argument("-ai", "--acclimateIncrease")
            .help("Gradually increase the speed over time, starting at -s, and going to -s + x")
            .action([](const std::string& value) { return std::stof(value); })
            .default_value(0);

        //
        try {
            args->parse_args(argc, argv);
        }
        catch (const std::runtime_error& err) {
            std::cout << err.what() << std::endl << args;
            exit(0);
        }
    }
};