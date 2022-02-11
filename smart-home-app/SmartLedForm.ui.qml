import QtQuick 2.4

Item {
    width: 15
    height: 15
    property alias ledImage: ledImage

    Image {
        id: ledImage
        anchors.fill: parent
        source: "Icons/LedGrey.png"
        mipmap: false
        fillMode: Image.Stretch
    }
}
