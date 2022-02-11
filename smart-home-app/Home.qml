import QtQuick 2.12
import QtQuick.Controls 2.12

HomeForm {

    property bool vpnOn: false

    Component.onCompleted: {
        toolButton.text = stackView.depth > 1 ? "\u25C0" : "\u2630"
        toolButton.font.pixelSize= Qt.application.font.pixelSize * 1.6
    }


    toolButton.onClicked: {
        if (stackView.depth > 1) {
            stackView.pop()
        } else {
            drawer.open()
        }
    }

    networkSwitch.switchNetwork.onCheckedChanged: {
        impostazioni.setNetworkInfo(networkSwitch.switchNetwork.checked)
    }


    StackView {
        id: stackView
        //initialItem: "HomeForm.ui.qml"
        anchors.fill: parent
    }


    Drawer {
        id: drawer
        width: window.width * 0.60
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: "About"
                width: parent.width

//                onClicked: {
//                    stackView.push("Impostazioni.qml")
//                    drawer.close()
//                }
            }
        }
    }




}
