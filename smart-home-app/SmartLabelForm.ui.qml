import QtQuick 2.4
import QtQuick.Controls 2.12

Item {
    width: 100
    height: 40
    property alias rectBackground: rectBackground
    property alias labelText: labelText

    Rectangle {
        id: rectBackground
        width: 100
        height: 40
        color: "#ffffff"


        Label {
            id: labelText
            color: "#000000"
            text: qsTr("")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:4}D{i:2}
}
##^##*/
