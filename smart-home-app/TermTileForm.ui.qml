import QtQuick 2.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Shapes 1.12
import QtQml 2.14


Item {
    id: item1
    width: 250
    height: 150
    property alias labelHeating: labelHeating
    property alias circularSlider: circularSlider
    property alias item1: item1
    property alias temp3Label: temp3Label
    property alias temp2Label: temp2Label
    property alias tempSetPoint: tempSetPoint
    property alias temp1Label: temp1Label
    property alias enableSwitch: enableSwitch
    property alias termostatoLabel: termostatoLabel
    property alias backgroundRect: backgroundRect
    property var materialDeepOrange: "#FF5722"


    Rectangle {
        id: backgroundRect
        width: 250
        height: 150
        color: materialDeepOrange
        border.color: materialDeepOrange
        radius: 12
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        Label {
            id: termostatoLabel
            width: 114
            height: 22
            color: "#ffffff"
            text: qsTr("Termostato")
            anchors.left: parent.left
            anchors.top: parent.top
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            anchors.leftMargin: 8
            anchors.topMargin: 2
        }

        Switch {
            id: enableSwitch
            x: 154
            width: 39
            height: 22
            text: qsTr("")
            anchors.right: parent.right
            anchors.top: parent.top
            checked: false
            anchors.topMargin: 8
            anchors.rightMargin: 8
            display: AbstractButton.IconOnly
        }

        Label {
            id: temp2Label
            x: 92
            width: 150
            height: 24
            color: "#ffffff"
            text: qsTr("T<sub>2</sub>")
            anchors.right: parent.right
            anchors.top: enableSwitch.bottom
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            textFormat: Text.RichText
            anchors.topMargin: 8
            anchors.rightMargin: 8
            font.bold: true
        }

        Label {
            id: temp3Label
            x: 92
            width: 150
            height: 24
            color: "#ffffff"
            text: qsTr("T<sub>ext</sub>")
            anchors.right: parent.right
            anchors.top: temp2Label.bottom
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            textFormat: Text.RichText
            anchors.topMargin: 16
            anchors.rightMargin: 8
            font.bold: true
        }

        Label {
            id: tempSetPoint
            x: 92
            width: 150
            height: 24
            color: "#ffffff"
            text: qsTr("T<sub>setpoint</sub>")
            anchors.right: parent.right
            anchors.top: temp3Label.bottom
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            textFormat: Text.RichText
            anchors.topMargin: 16
            anchors.rightMargin: 8
            font.bold: true
        }

        Label {
            id: labelHeating
            y: 113
            height: 17
            color: "#ffffff"
            text: qsTr("HEATING")
            anchors.left: circularSlider.right
            anchors.right: circularSlider.left
            anchors.bottom: circularSlider.top
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: -131
            anchors.rightMargin: -132
            anchors.bottomMargin: -102
            font.italic: false
            font.bold: false
        }

        Label {
            id: temp1Label
            y: 150
            height: 58
            color: "#ffffff"
            text: qsTr("T<sub>1</sub>")
            anchors.left: circularSlider.right
            anchors.right: circularSlider.left
            anchors.top: circularSlider.bottom
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            textFormat: Text.RichText
            anchors.leftMargin: -131
            anchors.rightMargin: -131
            anchors.topMargin: -102
            font.pointSize: 24
            font.bold: true
        }

        CircularSlider {
            id: circularSlider
            width: 159
            height: 121
            anchors.left: parent.left
            anchors.top: termostatoLabel.bottom
            anchors.bottom: parent.bottom
            minValue: 0
            maxValue: 2
            rotation: -120
            stepSize: 0.5
            endAngle: 240
            startAngle: 0
            trackWidth: 8
            anchors.leftMargin: 0
            anchors.bottomMargin: -4
            anchors.topMargin: 4
            progressWidth: 12
            handleHeight: 16
            handleVerticalOffset: 0
            handleWidth: 16
            handleColor: "#ffffff"
            progressColor: "#ffc107"
        }

        Label {
            id: label10
            color: "#ffffff"
            text: qsTr("10°")
            anchors.left: circularSlider.right
            anchors.right: circularSlider.left
            anchors.top: circularSlider.bottom
            anchors.bottom: circularSlider.top
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: -78
            anchors.bottomMargin: -139
            anchors.rightMargin: -35
            anchors.leftMargin: -172
            font.bold: true
            font.pointSize: 8
        }

        Label {
            id: label20
            y: 113
            color: "#ffffff"
            text: qsTr("30°")
            anchors.left: circularSlider.right
            anchors.right: circularSlider.left
            anchors.top: circularSlider.bottom
            anchors.bottom: circularSlider.top
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.bottomMargin: -102
            anchors.leftMargin: -21
            anchors.rightMargin: -157
            font.bold: true
            anchors.topMargin: -41
            font.pointSize: 8
        }



    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.659999966621399}D{i:6}D{i:10}D{i:11}
}
##^##*/
