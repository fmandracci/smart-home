import QtQuick 2.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: item1
    property var materialDarkRed: "#b80000"
    //    width: window.width
    //    height: window.height
    width: 360
    height: 570
    property alias configListView: configListView
    property alias labelConf: labelConf
    property alias labelStatus: labelStatus
    property alias rectangleHeader: rectangleHeader
    property alias statusIcon: statusIcon
    property alias configModel: configModel
    property alias labelHeartBeat: labelHeartBeat

//    Rectangle {
//        id: backgroundRect
//        color: "#ffffff"
//        anchors.fill: parent
//        anchors.rightMargin: 0
//        anchors.bottomMargin: 0
//        anchors.leftMargin: 0
//        anchors.topMargin: 0


        Rectangle {
            id: rectangleHeader
            height: 80
            color: materialDarkRed
            radius: 0
            border.width: 1
            border.color: materialDarkRed
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            z: 1
            anchors.topMargin: 0
            anchors.leftMargin: 0
            anchors.rightMargin: 0

            Label {
                id: labelStatus
                width: 106
                height: 32
                color: "#ffffff"
                text: qsTr("Stato")
                anchors.left: statusIcon.right
                anchors.bottom: parent.bottom
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 14
                anchors.bottomMargin: 8
                font.bold: true
                anchors.leftMargin: 24
            }

            SmartLabel {
                id: labelHeartBeat
                x: 130
                width: 0
                visible: false
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.rightMargin: 14
                anchors.bottomMargin: 53
                anchors.topMargin: 8
                anchors.horizontalCenterOffset: 115
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Label {
                id: labelConf
                width: 118
                height: 32
                color: "#ffffff"
                text: qsTr("Configurazione")
                anchors.left: statusIcon.right
                anchors.top: parent.top
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                anchors.leftMargin: 24
                font.bold: true
                anchors.topMargin: 8
            }

            Image {
                id: statusIcon
                width: 48
                height: 48
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                source: ""
                anchors.leftMargin: 16
                anchors.bottomMargin: 16
                anchors.topMargin: 16
                fillMode: Image.PreserveAspectFit
            }

        }


        ScrollView {
            id: scrollView
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: rectangleHeader.bottom
            anchors.bottom: parent.bottom
            anchors.topMargin: 16
            anchors.bottomMargin: 16
            anchors.leftMargin: 16
            anchors.rightMargin: 16
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff


            ListView {
                id: configListView
                anchors.fill: parent
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.bottomMargin: 8
                anchors.rightMargin: 0
                delegate: ConfigTile {
                     width: configListView.width
                     configLabelName.text: configText
                     configIcon.source: iconSource
                     alarmCommand:      command
                }
                model: configModel
                spacing: 8

            }

        ListModel {
            id: configModel
        }
        }
//    }
}
