import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.12

ApplicationWindow {
    id: window
//    width: window.width

//    height: window.height
    width: Screen.width
    height: Screen.height

    visible: true
    title: qsTr("Stack")

    Component.onCompleted: {
        console.log("width:" + width + "<----> height:" + height)
    }

    Home{

    }



}
