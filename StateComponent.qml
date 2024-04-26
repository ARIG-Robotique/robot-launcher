import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

RowLayout {
    Layout.maximumHeight: 35
    Layout.minimumHeight: 35

    property string libelle: libelle
    property string address: address
    property string stateColor: "gray"

    Rectangle {
        Layout.fillHeight: true
        width: 35
        color: stateColor
        radius: 10
    }

    Label {
        Layout.fillHeight: true
        width: 70
        text: libelle
        font.pointSize: 16
        verticalAlignment: Text.AlignVCenter
    }

    Label {
        Layout.fillWidth: true
        Layout.fillHeight: true
        text: address
        font.pointSize: 16
        verticalAlignment: Text.AlignVCenter
    }
}
