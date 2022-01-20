import QtQuick 2.12
import QtQuick.Controls 2.5
import org.arig.model 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 480

    header: ToolBar {
        id: toolBar
        contentHeight: exitButton.implicitHeight

        Label {
            text: qsTr("Mode d'exécution")
            anchors.centerIn: parent
            font.pixelSize: Qt.application.font.pixelSize * 1.6
        }

        ToolButton {
            id: exitButton
            text: "\u274c"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            anchors.right: parent.right
            onClicked: exitConfirmation.open()
        }
    }

    Timer {
        interval: 2000
        running: true
        repeat: true
        onTriggered: LauncherModel.networkInfo = "refresh"
    }

    Row {
        id: row
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        padding: 10
        spacing: 20

        Frame {
            id: frame
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: 400
            anchors.leftMargin: 0
            anchors.bottomMargin: 0
            anchors.topMargin: 0

            Image {
                anchors.fill: parent
                source: "file:./robot.png"
                fillMode: Image.PreserveAspectFit

            }

            Image {
                width: 125
                height: 126
                anchors.left: parent.left
                anchors.top: parent.top
                source: "qrc:coupe.png"
                anchors.leftMargin: 0
                anchors.topMargin: 0
                fillMode: Image.PreserveAspectFit
            }
        }

        Column {
            id: column
            anchors.left: parent.horizontalCenter
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 5
            anchors.rightMargin: 10
            padding: 10
            spacing: 5
            anchors.bottomMargin: 0
            anchors.topMargin: 0

            Image {
                anchors.left: parent.left
                anchors.right: parent.right
                source: "logo.png"
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                fillMode: Image.PreserveAspectFit


            }

            Button {
                height: 55
                text: qsTr("Run")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                onClicked: {
                    LauncherModel.action = "run"
                }
            }

            Button {
                height: 55
                text: qsTr("Monitoring")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                onClicked: {
                    LauncherModel.action = "monitoring"
                }
            }

            Button {
                height: 55
                text: qsTr("Debug")
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                onClicked: {
                    LauncherModel.action = "debug"
                }
            }

            Label {
                text: LauncherModel.networkInfo
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.leftMargin: 10
            }
        }
    }

    Popup {
        id: exitConfirmation
        modal: true
        focus: true
        width: 400
        height: 150
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        enter: Transition {
            NumberAnimation {
                property: "opacity"
                from: 0.0
                to: 1.0
            }
        }
        exit: Transition {
            NumberAnimation {
                property: "opacity"
                from: 1.0
                to: 0.0
            }
        }

        anchors.centerIn: Overlay.overlay

        contentItem:  Column {
            padding: 5
            spacing: 10

            Label {
                text: "Quitter le programme ?"
                font.pointSize: 16
            }

            Row {
                padding: 5
                spacing: 10
                anchors.right: parent.right
                anchors.rightMargin: 5

                Button {
                    text: "Annuler"
                    onClicked: {
                        exitConfirmation.close();
                    }
                }

                Button {
                    text: "Reboot"
                    onClicked: {
                        LauncherModel.action = "reboot"
                    }
                }

                Button {
                    text: "Poweroff"
                    onClicked: {
                        LauncherModel.action = "poweroff"
                    }
                }

                Button {
                    text: "Stop"
                    onClicked: {
                        LauncherModel.action = "exit"
                    }
                }
            }
        }
    }
 }
