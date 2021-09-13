#pragma once

#include <stdint.h>
#include <thread>

#include <QQuickWindow>

#define ARGPARSE_LONG_VERSION_ARG_ONLY
#include "argparse.hpp"
#include "cope.hpp"

// They have a bug in their QDialog and QWarning QML types
#define QML_QDIALOG_WORKS false

// Overwriting the todo in cope.hpp with one conditional on verbose
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
    ~Global();

  public:
    static bool verbose;
    static QQuickWindow* ui;
    static argparse::ArgumentParser* args;
    static std::string authcode;
    static bool isParentProcess;
    static std::thread* ffmpegThread;

    static void log(std::string msg);
    static void exitSigHandler(int signum);
    static PrettyTime getPrettyTime(const ulong& secs);
    static void parseArgs(int argc, char* argv[]);
    // I'm sorry, runFfmpegCmd just looks too stupid
    static std::string runFFmpegCmd(const std::string& args, bool ffprobe = false, bool forceQuiet = false);
    static QVariant getUIProperty(std::string item, std::string property);
    static void setUIProperty(std::string item, std::string property, QVariant to);
};
