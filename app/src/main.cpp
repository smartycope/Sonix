#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>


// #include "Book.h"
#include "Player.h"
//#include "Contact/contactmodel.h"

int main(int argc, char *argv[]){
    //*  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    // qmlRegisterType<Book>("Book", 1, 0, "Book");
    // qRegisterMetaType<Book>("Book");
    // qmlRegisterType<Player>("Player", 1, 0, "Player");


    Player* player = new Player();

    // qRegisterMetaType<Player>("Player");
//    qmlRegisterType<ContactModel>("Backend", 1, 0, "ContactModel");


//    QQmlComponent component(&engine, QUrl("qrc:example.qml"));
//    auto *player= qobject_cast<Player*>(component.create());

//    if (player){
//        debugs("player happened")

    engine.rootContext()->setContextProperty("player", player);


    engine.load(url);

    int code = app.exec();

    // delete player;

    return code;

}


// cd build; make -j$(expr $(nproc) + 1); if [ $? -eq 0 ]; then ../bin/$PROJECT; fi; cd ..

// my authcode = 3100e20a
// how to extract just the cover image: ffmpeg -loglevel error -activation_bytes <authcode> -i <aax file> -an -codec:v copy <output path>.jpg

// to convert the .aax file to wav (or anything, really): ffmpeg -loglevel error -activation_bytes <authcode> -i <aax file> <output file>