import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
Item {
    width: 250
    height: 150
    property alias wattmetroLabel: wattmetroLabel
    property alias totalWattLabel: totalWattLabel
    property alias deltaWattLabel: deltaWattLabel
    property alias maxWattLabel: maxWattLabel
    property alias actualWattLabel: actualWattLabel
    property var materialOrange: "#FF9800"



    Rectangle {
        id: backgroundRect
        width: 250
        height: 150
        color: materialOrange
        border.color: materialOrange
        radius: 12
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        Label {
            id: wattmetroLabel
            width: 114
            height: 22
            color: "#ffffff"
            text: qsTr("Wattmetro")
            anchors.left: parent.left
            anchors.top: parent.top
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            anchors.leftMargin: 8
            anchors.topMargin: 2
        }

        Label {
            id: actualWattLabel
            width: 100
            color: "#ffffff"
            text: qsTr("W")
            anchors.left: parent.left
            anchors.top: wattmetroLabel.bottom
            anchors.bottom: parent.bottom
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 20
            anchors.bottomMargin: 30
            anchors.leftMargin: 8
            font.pointSize: 35
            font.bold: true
        }

        Label {
            id: maxWattLabel
            x: 154
            width: 88
            height: 17
            color: "#ffffff"
            text: qsTr("P<sub>Max</sub>")
            anchors.right: parent.right
            anchors.top: parent.top
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 44
            anchors.rightMargin: 8
            font.bold: true
            textFormat: Text.RichText
        }

        Label {
            id: deltaWattLabel
            x: 149
            width: 93
            height: 17
            color: "#ffffff"
            text: qsTr("&#916;")
            anchors.right: parent.right
            anchors.top: maxWattLabel.bottom
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 13
            anchors.rightMargin: 8
            font.bold: true
            textFormat: Text.RichText
        }

        Label {
            id: totalWattLabel
            x: 149
            width: 93
            height: 17
            color: "#ffffff"
            text: qsTr("P<sub>Total</sub>")
            anchors.right: parent.right
            anchors.top: deltaWattLabel.bottom
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 12
            anchors.rightMargin: 8
            font.bold: true
            textFormat: Text.RichText
        }
    }
}
