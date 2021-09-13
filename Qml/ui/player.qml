import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import PlayerWindow 1.0
import QtQuick.Dialogs 1.3


Window {
    id: window
    objectName: "mainWindow"
    visible: true
    color: "#989696"
    width: 400
    height: 520
    title: qsTr("Sonix")

    // fileDialog
    FileDialog {
        id: fileDialog
        objectName: "fileDialog"
        title: "Select an audio file"
        folder: shortcuts.home
        onAccepted: {
            Player.myprint("You chose: " + fileDialog.fileUrls)
            Player.open(fileDialog.fileUrls)
        }
        onRejected: {
            Player.myprint("Canceled")
        }
    }

    /*
    // authcodeWarning
    MessageDialog {
        id: authcodeWarning
        objectName: "authcodeWarning"
        icon: StandardIcon.Warning
        title: "Error: No Authcode Provided"
        text: "Text Not Set"
        standardButtons: StandardButton.Ok
        onAccepted: visible = false
        // Component.onCompleted: visible = true
    }

    // authcodeWarning
    Dialog {
        id: authcodeWarning
        objectName: "authcodeWarning"
        // visible: true
        title: "Error: No Authcode Provided
        contentItem: Rectangle {
            color: "white"
            implicitWidth: 400
            implicitHeight: 100
            Text {
                text: "Hello blue sky!"
                color: "black"
                anchors.centerIn: parent
            }
        }
        standardButtons: StandardButton.Ok
        onAccepted: visible = false
        // Component.onCompleted: visible = true
    }
    */


    // pauseButton
    RoundButton {
        id: pauseButton
        objectName: "pauseButton"
        x: 280
        width: 80
        height: 80
        ////text: "||"
        anchors.top: cover.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        hoverEnabled: false
        onClicked: Player.player.togglePause()
    }


    // skipBackwardButton
    RoundButton {
        id: skipBackwardButton
        objectName: "skipBackwardButton"
        x: 214
        y: 319
        width: 60
        height: 60
        text: "<"
        anchors.verticalCenter: pauseButton.verticalCenter
        anchors.right: pauseButton.left
        anchors.rightMargin: 10
        onClicked: Player.player.skipBackward()
    }


    // skipForwardButton
    RoundButton {
        id: skipForwardButton
        objectName: "skipForwardButton"
        y: 319
        width: 60
        height: 60
        text: ">"
        anchors.verticalCenter: pauseButton.verticalCenter
        anchors.left: pauseButton.right
        anchors.leftMargin: 10
        onClicked: Player.player.skipForward()
    }

    // jumpForwardButton
    RoundButton {
        id: jumpForwardButton
        objectName: "jumpForwardButton"
        y: 329
        text: ">l"
        anchors.verticalCenter: pauseButton.verticalCenter
        anchors.left: skipForwardButton.right
        anchors.leftMargin: 10
        anchors.horizontalCenterOffset: -75
        onClicked: Player.player.jumpForward()
    }

    // jumpBackwardButton
    RoundButton {
        id: jumpBackwardButton
        objectName: "jumpBackwardButton"
        x: 168
        y: 329
        text: "l<"
        anchors.verticalCenter: pauseButton.verticalCenter
        anchors.right: skipBackwardButton.left
        anchors.rightMargin: 10
        onClicked: Player.player.jumpBackward()
    }

    // titleLabel
    Label {
        id: titleLabel
        objectName: "titleLabel"
        x: 220
        y: 10
        width: 201
        height: 37
        text: "Title"
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 20
    }

    // introLabel
    Text {
        id: introLabel
        objectName: "introLabel"
        //x: 38
        text: qsTr("")
        anchors.top: titleLabel.bottom
        font.pixelSize: 12
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 0
    }

    // cover
    Image {
        id: cover
        objectName: "cover"
        x: 196
        width: 250
        height: 250
        anchors.top: introLabel.bottom
        source: "image://cover/default"
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.Stretch
    }

    // chapterBox
    ComboBox {
        id: chapterBox
        x: 156
        objectName: "chapterBox"
        y: 426
        width: 235
        height: 32
        anchors.right: parent.right
        anchors.bottom: progressBar.top
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        font.preferShaping: true
        anchors.horizontalCenter: parent.horizontalCenter
        hoverEnabled: true
        font.capitalization: Font.Capitalize
        displayText: "No Chapters Provided"
        flat: true
        onAccepted: Player.player.updateChapter()
    }

    // progressBar
    ProgressBar {
        id: progressBar
        objectName: "progressBar"
        y: 437
        height: 22
        anchors.left: parent.left
        anchors.right: speedControl.left
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        focus: false
        anchors.bottomMargin: 10
        value: 0
    }

    // speedControl
    SpinBox {
        id: speedControl
        objectName: "speedControl"
        //x: 516
        //y: 432
        //width: 124
        //height: 32
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        wheelEnabled: false
        from: 005
        value: 100
        to: 2000
        stepSize: 010

        property int decimals: 2
        property real realValue: value / 100

        validator: DoubleValidator {
            bottom: Math.min(speedControl.from, speedControl.to)
            top:  Math.max(speedControl.from, speedControl.to)
        }

        textFromValue: function(value, locale) {
            return Number(value / 100).toLocaleString(locale, 'f', speedControl.decimals)
        }

        valueFromText: function(text, locale) {
            return Number.fromLocaleString(locale, text) * 100
        }

        onValueModified: Player.player.updateSpeed()

        // Connections {
        //     target: speedControl
        //     onClicked: Player.player.updateSpeed()
        // }
        //onClicked: Player.player.updateSpeed()
    }

    // openButton
    RoundButton {
        id: openButton
        objectName: "openButton"
        x: 590
        text: "+"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.rightMargin: 10
        flat: false

        onClicked: fileDialog.open()
    }
}