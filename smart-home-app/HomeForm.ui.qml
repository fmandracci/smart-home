import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: page
    width: window.width
    height: window.height
    property alias networkSwitch: networkSwitch
    property alias impostazioni: impostazioni
    //property alias tabBtnTermostati: tabBtnTermostati
    property alias toolButton: toolButton
    property alias lblTitle: lblTitle
    property alias toolBar: toolBar
    property alias swipeView: swipeView



    ToolBar {
        id: toolBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.leftMargin: 0
        anchors.rightMargin: 0

        ToolButton {
            id: toolButton
            width: 44
            text: qsTr("-")
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0
            anchors.bottomMargin: 0
            anchors.topMargin: 0

        }

        Label {
            id: lblTitle
            x: 170
            y: 16
            text: qsTr("Smart Home App")
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: -20
            anchors.horizontalCenter: parent.horizontalCenter
        }

        NetworkSwitch {
            id: networkSwitch
            x: 258
            width: 103
            height: 50
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0
            anchors.rightMargin: 4
        }
    }

    TabBar {
        id: tabBar
        width: window.width
        height: 50
        //height: 100
        position: TabBar.Footer
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: toolBar.bottom
        font.bold: true
        anchors.topMargin: 0
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        currentIndex: swipeView.currentIndex

        Repeater {
            //model: ["Termostati", "Antifurto", "Quadro", "Impostazioni"]
            model: ["Icons/HeatCool.png", "Icons/Antifurto.png", "Icons/Wattmeter.png", "Icons/System.png"]
            // Cambia il numerino giù   "width: tabBar.width / 4"
            TabButton {
                id: tabButton
                //text: modelData
                width: tabBar.width / 4
                //width: implicitWidth
                Image {
                    id: imageTab

                    width: 42
                    height: 42
                    anchors.verticalCenter: parent.verticalCenter
                    source: modelData
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.PreserveAspectFit
                }

            }
        }
    }

    Rectangle {
        id: separator
        width: 5
        height: 5
        color: "#666666"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: tabBar.bottom
        anchors.topMargin: 0
        anchors.leftMargin: 0
        anchors.rightMargin: 0
    }


    SwipeView {
        id: swipeView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: separator.bottom
        anchors.bottom: parent.bottom
        z: -1
        anchors.bottomMargin: 0
        currentIndex: tabBar.currentIndex
        anchors.topMargin: 0
        anchors.leftMargin: 0
        anchors.rightMargin: 0

        Termostasti {
            id: termostasti
        }

        Antifurto {
            id: antifurto
        }

        Quadro {
            id: quadro
        }

        Impostazioni {
            id: impostazioni
        }
    }

    Ledbar {
        id: ledbar
        x: 46
        y: 0
        width: 12
        height: 48
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/
