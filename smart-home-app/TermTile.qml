import QtQuick 2.4

TermTileForm {
    property var tileID: ""


    Component.onCompleted: {


    }

    circularSlider.onPressedChanged: {
        console.log((Number(((circularSlider.value ).toFixed(2))*10)+10)*10 )
        SmartEngine.write_h_register_termostati_SetPoint((Number(((circularSlider.value ).toFixed(2))*10)+10)*10)
    }

    enableSwitch.onCheckedChanged: {
        //console.log(enableSwitch.checked)
        SmartEngine.write_h_register_termostati_Enabled(enableSwitch.checked)
    }

}
