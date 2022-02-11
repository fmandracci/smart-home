import QtQuick 2.4
import QtQuick.Controls 2.12

Item {
    id: item1
//    width: window.width
//    height: window.height
    width: 360
    height: 570
    property alias termostatiListView: termostatiListView
    property alias termostatiModel: termostatiModel
//    property alias backgroundRect: backgroundRect

//    Rectangle {
//        id: backgroundRect
//        color: "#ffffff"
//        anchors.fill: parent
//        z: -6

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
                id: termostatiListView
                anchors.fill: parent
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.bottomMargin: 8
                anchors.rightMargin: 0
                delegate: TermTile {
                     width: termostatiListView.width
                     tileID: tileId
                     termostatoLabel.text: termostatoName
                     temp1Label.text: temp1
                     temp2Label.text: temp2
                     temp3Label.text: temp3
                     tempSetPoint.text: setPoint
                     circularSlider.value: sliderValue
                     enableSwitch.checked: termosatoStatus
                     labelHeating.visible: heating_isON
                }
                model: termostatiModel
                spacing: 2

            }
        }
        ListModel {
            id: termostatiModel
        }

//    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
