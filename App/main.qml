import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
//import Player 1.0
//import Book 1.0

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("SuperSonic Audiobook Player")

//    Image {
//        id: cover
//        x: 207
//        y: 23
//        width: 215
//        height: 193
////        source: player.book.cover
//        source: "qrc:/defaultBookCover.png"
////        source: "/home/rebecca/hello/C++/SonicPlaceholder/assets/defaultBookCover.jpeg"
//        fillMode: Image.PreserveAspectFit
//    }

    ProgressBar {
        id: position
        x: 20
        y: 437
        width: 601
        height: 22
//        value: player.book.position
        value: 0.5
    }

    RoundButton {
        id: pause
        x: 280
        y: 313
        width: 80
        height: 80
        text: "||"
        hoverEnabled: false
//        checkable: true
//        onCheckedChanged: player.togglePaused()
//        onPressed: player.togglePaused()

        TapHandler{
            onTapped: player.togglePause()
//            onTapped: console.log("pause pressed!")
        }
    }

    Label {
        id: title
        x: 214
        y: 222
        width: 201
        height: 37
//        text: player.book.title
        text: "Hello world!"
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 20
    }

    RoundButton {
        id: jumpBackward
        x: 214
        y: 323
        width: 60
        height: 60
        text: "<"
        TapHandler{
            onTapped: player.jumpBackward()
        }
    }

    RoundButton {
        id: jumpForward
        x: 366
        y: 323
        width: 60
        height: 60
        text: ">"
        TapHandler{
            onTapped: player.jumpForward()
//            onTapped: console.log("jump forward pressed!")
        }
    }

    RoundButton {
        id: skipForward
        x: 432
        y: 333
        text: ">|"
        TapHandler{
            onTapped: player.skipForward()
        }
    }

    RoundButton {
        id: skipBackward
        x: 168
        y: 333
        text: "|<"
        TapHandler{
            onTapped: player.skipBackward()
        }
    }
}
