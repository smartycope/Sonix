#include "CoverProvider.hpp"
#include "PlayerWindow.hpp"
#include "src/AudioPlayer.hpp"

// #include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <iostream>
#include <QQuickWindow>
#include <qmainwindow.h>
#include <qquickwindow.h>

#include "Global.hpp"

#define EXAMPLE_PATH "/home/marvin/Media/Audiobooks/DragonsEgg.m4b"

// #include "cope.hpp"


#include <QObject>
#include <QString>
#include <qqml.h>


Global* Global::_instance = new Global;
// Eventually this will be false
bool Global::verbose = true;
QQuickWindow* Global::ui = nullptr;
argparse::ArgumentParser* Global::args = nullptr;
string Global::authcode = "";


int main(int argc, char* argv[]) {
    //* Parse args
    Global::parseArgs(argc, argv);
    Global::authcode = Global::args->get<string>("--authcode");
    Global::verbose =  Global::args->get<bool>("--verbose");

    QGuiApplication app(argc, argv);
    QGuiApplication::setOrganizationName("Beepus and Boopus Inc.");

    // allocate example before the engine to ensure that it outlives it
    // Book* book = new Book(EXAMPLE_PATH);
    QScopedPointer<PlayerWindow> player(new PlayerWindow);
    QQmlApplicationEngine engine;

    // Add our custom image provider for the cover
    engine.addImageProvider("cover", new CoverProvider);

    // Register the singleton type provider with QML by calling this
    // function in an initialization function.
    qmlRegisterSingletonInstance("PlayerWindow", 1, 0, "Player", player.get());

    engine.load("qrc:/ui/player.qml");
    Global::ui = qobject_cast<QQuickWindow*>(engine.rootObjects().first());
    Global::setUIProperty("authcodeWarning", "text", AUTHCODE_WARNING);

    player->init(Global::args->get<string>("audioFile"));

    // TODO do this
    // if (not args.get<bool>("--cli"))
    //     win.show();

    int code = app.exec();
    return code;
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
