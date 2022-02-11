import QtQuick 2.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    width: 200
    height: 50
    property alias backgroundRect: backgroundRect
    property alias mouseArea: mouseArea
    property alias configIcon: configIcon
    property alias configLabelName: configLabelName
    property var materialLightBlue: "#6ec6ff"

    Rectangle {
        id: backgroundRect
        visible: true
        color: "#6ec6ff"
        //Material.accent
        radius: 12
        border.color: "#6ec6ff"
        border.width: 1
        anchors.fill: parent

        Label {
            id: configLabelName
            height: 36
            color: "#000000"
            text: qsTr("Config")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: configIcon.right
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 15
            font.bold: true
            anchors.rightMargin: 43
            anchors.leftMargin: 8
        }

        Image {
            id: configIcon
            width: 48
            height: 48
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            source: "qrc:/qtquickplugin/images/template_image.png"
            anchors.topMargin: 4
            anchors.bottomMargin: 4
            anchors.leftMargin: 4
            fillMode: Image.PreserveAspectFit
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }
}
