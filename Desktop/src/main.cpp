#include "PlayerWindow.hpp"

#include <QApplication>
#include "defs.h"
extern bool verbose;

#define ARGPARSE_LONG_VERSION_ARG_ONLY
#include "argparse.hpp"
#include "cope.hpp"


argparse::ArgumentParser parseArgs(int argc, char* argv[]){
    argparse::ArgumentParser args("SAP", "0.1.3");
    args.add_description(ABOUT_MSG);

    args.add_argument("audioFile")
        // .required()
        .help("The file path of the audiobook to play (NOTE: Spaces in the filepath are not currently supported. Please open it via the GUI.)")
        .default_value(string());

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
        .default_value(1);

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

    args.add_argument("-cli", "--cli")
        .help("Don't open a window")
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

    QApplication app(argc, argv);
    app.setApplicationName("SuperSonic Audiobook Player");

    //* These are book-independant. Set these even if no filepath was provided
    AudioPlayer::linVolume = args.get<int>("--volume");
    AudioPlayer::speed = args.get<float>("--speed");
    AudioPlayer::rate = args.get<float>("--rate");
    AudioPlayer::pitch = args.get<float>("--pitch");
    AudioPlayer::emulateChordPitch = args.get<bool>("--emulateChordPitch");
    AudioPlayer::enableNonlinearSpeedup = args.get<bool>("--enableNonlinearSpeedup");
    AudioPlayer::highQuality = args.get<bool>("--increaseQuality");
    AudioPlayer::samplerate = args.get<int>("--samplerate");
    AudioPlayer::channels = args.get<int>("--channels");
    verbose = args.get<bool>("--verbose");

    string file = args.get<string>("audioFile");
    Book* book;
    if (not file.empty())
        book = new Book(file, &args);
    else
        book = nullptr;

    auto win = PlayerWindow(book);
    if (not args.get<bool>("--cli"))
        win.show();
    return app.exec();
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
