import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.1
import org.arig.model 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 480

    function getBooleanColor(value) {
        switch(value) {
            case 0 : return "gray";
            case 1 : return "red";
            case 2 : return "orange";
            default : return "green";
        }
    }

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
        onTriggered: LauncherModel.refresh()
    }

    RowLayout {
        id: row
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10

        spacing: 20

        Column {
            id: frame
            anchors.left: parent.left
            anchors.right: parent.horizontalCenter
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            padding: 10
            spacing: 5

            StateComponent {
                id: stateNerell
                libelle: "Nerell"
                address: LauncherModel.nerellAddress
                stateColor: getBooleanColor(LauncherModel.nerellState)
            }
            StateComponent {
                id: stateOdin
                libelle: "Overlord"
                address: LauncherModel.overlordAddress
                stateColor: getBooleanColor(LauncherModel.overlordState)
            }
            StateComponent {
                id: stateTriangle
                libelle: "Triangle"
                address: LauncherModel.triangleAddress
                stateColor: getBooleanColor(LauncherModel.triangleState)
            }
            StateComponent {
                id: stateCarre
                libelle: "Carré"
                address: LauncherModel.carreAddress
                stateColor: getBooleanColor(LauncherModel.carreState)
            }
            StateComponent {
                id: stateRond
                libelle: "Rond"
                address: LauncherModel.rondAddress
                stateColor: getBooleanColor(LauncherModel.rondState)
            }

            Image {
                height: 300
                anchors.horizontalCenter: parent.horizontalCenter
                source: "file:./robot.png"
                fillMode: Image.PreserveAspectFit
            }

        }

        ColumnLayout {
            id: column
            anchors.left: parent.horizontalCenter
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 5

            Row {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top

                Image {
                    height: 150
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "qrc:logo.png"
                    fillMode: Image.PreserveAspectFit
                }

                Image {
                    height: 150
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "qrc:coupe.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Button {
                height: 70
                text: qsTr("Run")
                font.pointSize: 15
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                onClicked: {
                    LauncherModel.action = "run"
                }
            }

            Button {
                height: 70
                text: qsTr("Monitoring")
                font.pointSize: 15
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                onClicked: {
                    LauncherModel.action = "monitoring"
                }
            }

            Button {
                height: 70
                text: qsTr("Debug")
                font.pointSize: 15
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
