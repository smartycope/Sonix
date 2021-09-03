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
    property alias window: window
    property alias chapterBox: chapterBox
    property alias openButton: openButton
    property alias narratorLabel: narratorLabel
    property alias authorLabel: authorLabel
    property alias speedControl: speedControl
    property alias skipForwardButton: skipForwardButton
    property alias cover: cover
    property alias skipBackwardButton: skipBackwardButton
    property alias jumpForwardButton: jumpForwardButton
    property alias jumpBackwardButton: jumpBackwardButton
    property alias titleLabel: titleLabel
    property alias progressBar: progressBar
    property alias pauseButton: pauseButton
    title: qsTr("SuperSonic Audiobook Player")

    ProgressBar {
        id: progressBar
        x: 20
        y: 437
        width: 495
        height: 22
        value: 0.5
    }

    RoundButton {
        id: pauseButton
        x: 280
        y: 309
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
        id: titleLabel
        x: 220
        y: 10
        width: 201
        height: 37
//        text: player.book.title
        text: "Title"
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 20
    }

    RoundButton {
        id: jumpBackwardButton
        x: 214
        y: 319
        width: 60
        height: 60
        text: "<"
        TapHandler{
            onTapped: player.jumpBackward()
        }
    }

    RoundButton {
        id: jumpForwardButton
        x: 366
        y: 319
        width: 60
        height: 60
        text: ">"
        TapHandler{
            onTapped: player.jumpForward()
//            onTapped: console.log("jump forward pressed!")
        }
    }

    RoundButton {
        id: skipForwardButton
        x: 432
        y: 329
        text: ">|"
        TapHandler{
            onTapped: player.skipForward()
        }
    }

    RoundButton {
        id: skipBackwardButton
        x: 168
        y: 329
        text: "|<"
        TapHandler{
            onTapped: player.skipBackward()
        }
    }

    Image {
        id: cover
        x: 196
        y: 53
        width: 250
        height: 250
        source: "assets/defaultBookCover.png"
        fillMode: Image.Stretch
    }

    SpinBox {
        id: speedControl
        x: 516
        y: 432
        width: 124
        height: 32
        wheelEnabled: false
        stepSize: 0
        value: 1
        to: 20
        from: 0
    }

    Text {
        id: authorLabel
        x: 20
        y: 18
        width: 131
        height: 21
        text: qsTr("Author:")
        font.pixelSize: 12
    }

    Text {
        id: narratorLabel
        x: 20
        y: 33
        width: 135
        height: 21
        text: qsTr("Narrator:")
        font.pixelSize: 12
    }

    RoundButton {
        id: openButton
        x: 590
        y: 10
        text: "+"
        flat: false
    }

    ComboBox {
        id: chapterBox
        x: 156
        y: 399
        width: 331
        height: 32
        displayText: "No Chapters Provided"
        flat: true
    }
}
