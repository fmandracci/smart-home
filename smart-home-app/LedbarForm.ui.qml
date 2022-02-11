import QtQuick 2.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: item1
    width: 15
    height: 60
    property alias yellowLed2: yellowLed2
    property alias yellowLed1: yellowLed1
    property alias redLed: redLed
    property alias greenLed: greenLed

    Rectangle {
        id: greenLed
        height: parent.width
        color: "#ffffff"
        radius: 50
        border.width: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
    }

    Rectangle {
        id: redLed
        height:  parent.width
        color: "#ffffff"
        radius: 50
        border.width: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: greenLed.bottom
        anchors.topMargin: 0
        anchors.rightMargin: 0
        anchors.leftMargin: 0
    }

    Rectangle {
        id: yellowLed1
        height:  parent.width
        color: "#ffffff"
        radius: 50
        border.width: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: redLed.bottom
        anchors.topMargin: 0
        anchors.leftMargin: 0
        anchors.rightMargin: 0
    }

    Rectangle {
        id: yellowLed2
        height:  parent.width
        color: "#ffffff"
        radius: 50
        border.width: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: yellowLed1.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        anchors.leftMargin: 0
        anchors.rightMargin: 0
    }
}
