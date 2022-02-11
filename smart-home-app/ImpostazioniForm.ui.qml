import QtQuick 2.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: settingsPage
    //    width: window.width
    //    height: window.height
    width: 360
    height: 570
    property alias networkSaveButton: networkSaveButton
    property alias settingsPage: settingsPage
    property alias textFieldWifiIP: textFieldWifiIP
    property alias textFieldVpnIP: textFieldVpnIP

//    Rectangle {
//        id: backgroundRect
//        color: "#ffffff"
//        anchors.fill: parent

        Label {
            id: labelNetwork
            x: 8
            y: 16
            text: qsTr("Network")
            anchors.left: parent.left
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 16
            anchors.leftMargin: 16
            color: Material.accent
        }


        Rectangle {
            id: networkRect
            height: 50
            color: "#00ffffff"
            radius: 6
            border.width: 2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: labelNetwork.bottom
            anchors.topMargin: 4
            anchors.leftMargin: 16
            anchors.rightMargin: 16

            Label {
                id: labelWifiIP
                y: 23
                text: qsTr("Wifi IP Address")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: textFieldWifiIP.left
                font.bold: true
                font.family: "Sans"
                anchors.rightMargin: 48
                anchors.leftMargin: 24
            }

            TextField {
                id: textFieldWifiIP
                x: 177
                y: 27
                width: 140
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                horizontalAlignment: Text.AlignHCenter
                anchors.rightMargin: 32
                placeholderText: qsTr("192.168.5.20")
            }

        }

        Rectangle {
            id: networkRect1
            y: 101
            height: 50
            color: "#00ffffff"
            radius: 6
            border.width: 2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: networkRect.bottom
            Label {
                id: labelWifiIP1
                y: 23
                text: qsTr("Vpn IP Address")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: textFieldVpnIP.left
                font.italic: false
                font.bold: true
                anchors.rightMargin: 48
                anchors.leftMargin: 24
            }

            TextField {
                id: textFieldVpnIP
                x: 177
                y: 27
                width: 140
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                horizontalAlignment: Text.AlignHCenter
                anchors.rightMargin: 32
                placeholderText: qsTr("10.1.0.141")
            }
            anchors.rightMargin: 16
            anchors.topMargin: 16
            anchors.leftMargin: 16
        }

        RoundButton {
            id: networkSaveButton
            height: 48
            radius: 10
            text: "SALVA"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: networkRect1.bottom
            anchors.leftMargin: 233
            anchors.rightMargin: 16
            anchors.topMargin: 8
        }



//    }

}
