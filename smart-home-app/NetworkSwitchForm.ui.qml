import QtQuick 2.4
import QtQuick.Controls 2.12

Item {
    id: item1
    width: 110
    height: 40
    property alias switchNetwork: switchNetwork

    Label {
        id: label
        text: qsTr("Wifi")
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.leftMargin: 0
        anchors.bottomMargin: 0
        anchors.topMargin: 0
    }

    Switch {
        id: switchNetwork
        y: 26
        width: 70
        height: 40
        text: qsTr("")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.rightMargin: 2
        anchors.leftMargin: 0
        display: AbstractButton.IconOnly
    }


    Label {
        id: label1
        text: qsTr("Vpn")
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.rightMargin: 0
        anchors.topMargin: 0
        anchors.bottomMargin: 0
        transformOrigin: Item.Center
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:3}
}
##^##*/
