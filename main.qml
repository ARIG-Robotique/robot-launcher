import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: window
    visible: true
    width: 800
    maximumWidth: 800
    minimumWidth: 800
    height: 480
    maximumHeight: 480
    minimumHeight: 480
    title: qsTr("Robot launcher")

    header: ToolBar {
        id: toolBar
        contentHeight: exitButton.implicitHeight

        Label {
            text: qsTr("Mode d'exécution")
            anchors.centerIn: parent
        }

        ToolButton {
            id: exitButton
            text: "\u274c"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            anchors.right: parent.right
            onClicked: exitConfirmation.open()
        }
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



        Image {
            anchors.left: parent.left
            anchors.right: parent.horizontalCenter
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            source: "2020-nerell.png"
            mipmap: true
            fillMode: Image.PreserveAspectFit
            anchors.rightMargin: 5
            anchors.leftMargin: 10
            anchors.bottomMargin: 10
            anchors.topMargin: 10

        }

        Column {
            id: column
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.horizontalCenter
            anchors.right: parent.right
            anchors.leftMargin: 5
            anchors.rightMargin: 10
            padding: 10
            spacing: 20
            anchors.bottomMargin: 0
            anchors.topMargin: 0

            Button {
                text: qsTr("Run")
                clip: false
            }

            Button {
                text: qsTr("Monitoring")
            }

            Button {
                text: qsTr("Debug")
            }
        }

    }

    Popup {
        id: exitConfirmation
        modal: true
        focus: true
        width: 350
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
                    text: "Non"
                    onClicked: {
                        exitConfirmation.close();
                    }
                }

                Button {
                    text: "Oui"
                    onClicked: {
                        // TODO Quitter
                    }
                }
            }
        }
    }
 }
