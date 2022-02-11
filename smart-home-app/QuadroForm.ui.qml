import QtQuick 2.4
import QtQuick.Controls 2.12

Item {
    id: item1
    //    width: window.width
    //    height: window.height
    width: 360
    height: 570
    property alias wattmetriModel: wattmetriModel
    property alias wattmetriListView: wattmetriListView

        ScrollView {
            id: scrollView
            height: 200
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            z: 0
            anchors.leftMargin: 8
            anchors.bottomMargin: 8
            anchors.topMargin: 8
            anchors.rightMargin: 8
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

            ListView {
                id: wattmetriListView
                anchors.fill: parent
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.bottomMargin: 8
                anchors.rightMargin: 0
                delegate: WattTile {
                     width: wattmetriListView.width
                     wattmetroLabel.text:   wattmetroName
                     actualWattLabel.text:  actualWatt
                     maxWattLabel.text:     maxWatt
                     deltaWattLabel.text:   deltaWatt
                     totalWattLabel.text:   totalWatt
                }
                model: wattmetriModel
                spacing: 2

            }
        }
        ListModel {
            id: wattmetriModel
        }
}
