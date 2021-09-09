#include "Global.hpp"

#include <sys/types.h>
#include <string>
#include <sstream>

#include "messages.hpp"
#include "cope.hpp"

Global* Global::_instance = new Global;
bool Global::verbose = false;
QQuickWindow* Global::ui = nullptr;
argparse::ArgumentParser* Global::Global::args = nullptr;
std::string Global::authcode = "";
bool Global::isParentProcess = true;
std::thread* Global::ffmpegThread = nullptr;


Global::~Global(){ delete _instance; }

void Global::exitSigHandler(int signum) {
    if (Global::ffmpegThread)
        if (Global::ffmpegThread->joinable())
            Global::ffmpegThread->join();
    exit(signum);
}

void Global::log(std::string msg){
    if (Global::verbose)
        std::cout << msg << '\n';
}

PrettyTime Global::getPrettyTime(const ulong& secs){
    PrettyTime t;
    t.hour = secs / 3600;
    t.min  = (secs % 3600) / 60;
    t.sec  = (secs % 3600) % 60;
    return t;
}

// I'm sorry, runFfmpegCmd just looks too stupid.
std::string Global::runFFmpegCmd(const std::string& args, bool ffprobe, bool forceQuiet){
    std::stringstream command;
    // Make sure to always hide the banner, and check for verbose output, and to output to stdout (if ffmpeg)
    command << (ffprobe ? "ffprobe": "ffmpeg")
            << " -hide_banner -loglevel "
            << std::string(Global::verbose and not forceQuiet ? "error ": "quiet ")
            << args
            << (ffprobe ? "": " -");

    return getCmdOutS(command.str(), Global::verbose, false);
}

QVariant Global::getUIProperty(std::string item, std::string property){
    QObject* obj = Global::ui->findChild<QObject*>(item.c_str());
    if (obj)
        return obj->property(property.c_str());
    else
        log("No property " + property + " in " + item);
    return QVariant();
}

void Global::setUIProperty(std::string item, std::string property, QVariant to){
    QObject* obj = Global::ui->findChild<QObject*>(item.c_str());
    if (obj)
        obj->setProperty(property.c_str(), to);
    else
        log("No property " + property + " in " + item);
}

void Global::parseArgs(int argc, char* argv[]){
    Global::args = new argparse::ArgumentParser("SAP", "0.1.6");
    Global::args->add_description(ABOUT_MSG);

    Global::args->add_argument("audioFile")
        // .required()
        .help("The file path of the audiobook to play")
        .default_value(std::string());

    Global::args->add_argument("--verbose")
        .default_value(false)
        .implicit_value(true);

    Global::args->add_argument("-s", "--speed")
        .help("The starting playback speed")
        .action([](const std::string& value) { return std::stof(value); })
        .default_value(1.0f);

    Global::args->add_argument("-v", "--volume")
        .help("The starting playback volume (0-100)")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(99);

    Global::args->add_argument("-r", "--rate")
        .help("The starting playback rate")
        .action([](const std::string& value) { return std::stof(value); })
        .default_value(1.0f);

    Global::args->add_argument("-p", "--pitch")
        .help("The starting pitch")
        .action([](const std::string& value) { return std::stof(value); })
        .default_value(1.0f);

    Global::args->add_argument("--emulateChordPitch")
        .help("Set to 1 to emulate human vocal chords when changing pitch")
        .default_value(false)
        .implicit_value(true);

    Global::args->add_argument("--enableNonlinearSpeedup")
        .help("Not sure what this does.")
        .default_value(false)
        .implicit_value(true);

    Global::args->add_argument("--increaseQuality")
        .help("Slightly increase quality, at the expense of speed")
        .default_value(false)
        .implicit_value(true);

    Global::args->add_argument("-br", "--samplerate")
        .help("The output samplerate")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(44100);

    Global::args->add_argument("-c", "--channels")
        .help("The output number of channels")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(2);

    Global::args->add_argument("-a", "--authcode")
        .help("Specify the audible authcode for playing .aax files")
        .default_value(std::string());

    Global::args->add_argument("-ss", "--startSec")
        .help("Start playing x seconds in")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(0);

    Global::args->add_argument("-sm", "--startMin")
        .help("Start playing x minutes in")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(0);

    Global::args->add_argument("-sh", "--startHour")
        .help("Start playing x hours in")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(0);

    Global::args->add_argument("-sc", "--startChapter")
        .help("Start playing at chapter x")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(1);

    Global::args->add_argument("--listChapters")
        .help("Print the chapters in the book (if available) and exit")
        .default_value(false)
        .implicit_value(true);

    Global::args->add_argument("--description")
        .help("Print the book's description (if available) and exit")
        .default_value(false)
        .implicit_value(true);

    Global::args->add_argument("--publisher")
        .help("Print the book's publisher (if available) and exit")
        .default_value(false)
        .implicit_value(true);

    Global::args->add_argument("--released")
        .help("Print the when the book was released (if available) and exit")
        .default_value(false)
        .implicit_value(true);

    Global::args->add_argument("-cli", "--cli")
        .help("Don't open a window")
        .default_value(false)
        .implicit_value(true);

    Global::args->add_argument("-t", "--sleepTimer")
        .help("Stop playing after x minutes")
        .action([](const std::string& value) { return std::stoi(value); })
        .default_value(0);

    Global::args->add_argument("-pos", "--savePosition")
        .help("When you stop, save the position to the file (only works on supporting file formats)")
        .default_value(true)
        .implicit_value(true);

    Global::args->add_argument("-nopos", "--noSavePosition")
        .help("When you stop, don't save the position to the file")
        .default_value(false)
        .implicit_value(true);

    Global::args->add_argument("-sv", "--startSaved")
        .help("If supported by the file format, start at the saved position (overidden by other -s* parameters)")
        .default_value(true)
        .implicit_value(true);

    Global::args->add_argument("-nosv", "--noStartSaved")
        .help("Don't start at the saved position (overidden by other -s* parameters)")
        .default_value(false)
        .implicit_value(true);

    // Global::args->add_argument("-as", "--acclimate")
        // .help("Gradually increase the speed over time")
        // .nGlobal::args(3)
        // .action([](const std::string& value) { return std::stoi(value); })
        // .default_value(vector<float>{1.0f, 5.0f, 2.0f});

    Global::args->add_argument("-ad", "--acclimateTo")
        .help("Gradually increase the speed over time, starting at -s, and going to x")
        .action([](const std::string& value) { return std::stof(value); })
        .default_value(0);

    Global::args->add_argument("-at", "--acclimateTime")
        .help("Gradually increase the speed over x hours, starting at -s.")
        .action([](const std::string& value) { return std::stof(value); })
        .default_value(1);

    Global::args->add_argument("-ai", "--acclimateIncrease")
        .help("Gradually increase the speed over time, starting at -s, and going to -s + x")
        .action([](const std::string& value) { return std::stof(value); })
        .default_value(0);

    //
    try {
        Global::args->parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl << Global::args;
        exit(0);
    }
}
