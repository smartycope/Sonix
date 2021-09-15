#include <string>
#include <csignal>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>

#include "CoverProvider.hpp"
#include "PlayerWindow.hpp"
#include "Global.hpp"
#include "messages.hpp"

using std::string;


int main(int argc, char* argv[]) {
    // Parse args
    Global::parseArgs(argc, argv);
    Global::authcode = Global::args->get<string>("--authcode");
    Global::verbose =  Global::args->get<bool>("--verbose");

    // If we close the program, we want to join the ffmpeg thread too
    signal(SIGINT, Global::exitSigHandler);

    // Initialize the Qml application
    QGuiApplication app(argc, argv);
    QGuiApplication::setOrganizationName("Beepus and Boopus Inc.");

    // Allocate player1 before the engine to ensure that it outlives it
    QScopedPointer<PlayerWindow> player(new PlayerWindow);
    QQmlApplicationEngine engine;

    // Add our custom image provider for the cover
    engine.addImageProvider("cover", new CoverProvider);

    // Register the singleton type provider with QML by calling this function in an initialization function.
    qmlRegisterSingletonInstance("PlayerWindow", 1, 0, "Player", player.get());


    // _debug(player.)

    // Load the main .qml file we have
    engine.load("qrc:/ui/player.qml");

    // We want everything to have access to the ui
    Global::ui = qobject_cast<QQuickWindow*>(engine.rootObjects().first());
    // Just so everything is synced
    Global::setUIProperty("authcodeWarning", "text", AUTHCODE_WARNING);

    // Initialze seperately, because for SOME REASON the AudioPlayer constructor
    // refuses to accept a nullptr as a parameter
    player->init(Global::args->get<string>("audioFile"));

    // TODO do this
    // if (not args.get<bool>("--cli"))
    //     win.show();
    // _debug(player)
    // _debug(player.get())
    // _debug(player->player())

    int code = app.exec();
    return code;
}
