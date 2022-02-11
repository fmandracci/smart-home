import QtQuick 2.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

ConfigTileForm {

    property var alarmCommand: "-"

    mouseArea.onClicked: {
        if(backgroundRect.color == materialLightBlue) {
            backgroundRect.color = Material.accent
            backgroundRect.border.color = Material.accent
            configLabelName.color = "#ffffff"
            writeModbus()
        } else {
            backgroundRect.color = materialLightBlue
            backgroundRect.border.color = materialLightBlue
            configLabelName.color = "#000000"
        }
    }

    function enableForm(check) {
        mouseArea.enabled = check

        if(check) {
            backgroundRect.color = materialLightBlue
            backgroundRect.border.color = materialLightBlue
            configLabelName.color = "#000000"
        } else {
            backgroundRect.color = Material.color(Material.Grey)
            backgroundRect.border.color = Material.color(Material.Grey)
            configLabelName.color = "#ffffff"
        }
    }


    function writeModbus(){
        SmartEngine.write_h_register_antifurto(alarmCommand)
    }


    states: State {
        name: "pressed";
        when: mouseArea.pressed
        PropertyChanges {   target: backgroundRect
                            scale: 0.92 }
    }

    transitions: Transition {
        NumberAnimation {   properties: "scale";
                            duration: 200;
                            easing.type: Easing.InOutQuad }
    }
}
