import QtQuick 2.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

LedbarForm {

    Component.onCompleted: {
        greenLed.color =    Material.color(Material.Grey)
        redLed.color =      Material.color(Material.Grey)
        yellowLed1.color =  Material.color(Material.Grey)
        yellowLed2.color =  Material.color(Material.Grey)
    }



    function ledStatusUpdate(ledGreen,ledRed,ledYellow1,ledYellow2){

        //console.log(ledGreen,ledRed,ledYellow1,ledYellow2)
        if(ledGreen) {
            greenLed.color =  Material.color(Material.Green)
        } else {
            greenLed.color =  Material.color(Material.Grey)
        }

        if(ledRed) {
            redLed.color = Material.color(Material.Red)
        } else {
            redLed.color =  Material.color(Material.Grey)
        }

        if(ledYellow1) {
            yellowLed1.color = Material.color(Material.Yellow)
        } else {
            yellowLed1.color =  Material.color(Material.Grey)
        }

        if(ledYellow2) {
            yellowLed2.color = Material.color(Material.Yellow)
        } else {
            yellowLed2.color =  Material.color(Material.Grey)
        }
    }


    Timer {
        interval: 1000; running: true; repeat: true
        onTriggered: {
            ledStatusUpdate( SmartEngine.m_srv_reg_struct.b_SRV_BA_led_green,
                             SmartEngine.m_srv_reg_struct.b_SRV_BA_led_red,
                             SmartEngine.m_srv_reg_struct.b_SRV_BA_led_yellow1,
                             SmartEngine.m_srv_reg_struct.b_SRV_BA_led_yellow2)
        }
    }
}
