import QtQuick 2.4

SmartLedForm {

    property string ledOn : "Icons/LedOn.png"
    property string ledOff: "Icons/LedOff.png"
    property string ledUnk: "Icons/LedGrey.png"


    QtObject {
      id: privateProperties
      property int ledValue: -1
      property int oldVal: -1
    }



    function setLedOn() {
        ledImage.source = ledOn
    }

    function setLedOff() {
        ledImage.source = ledOff
    }

    function setLedUnk() {
        ledImage.source = ledUnk
    }


    function setLedOnImage(newIcon) {
        ledOn = newIcon
    }

    function setLedOffImage(newIcon) {
        ledOff = newIcon
    }

    function setLedUnkImage(newIcon) {
        ledUnk = newIcon
    }



    function setLedValue(newValue) {
        if(newValue)
            privateProperties.ledValue = 1
        else
            privateProperties.ledValue = 0


        if(privateProperties.ledValue != privateProperties.oldVal) {
            if (privateProperties.ledValue > 0) {
                setLedOn()
            } else if (privateProperties.ledValue == 0) {
                setLedOff()
            } else {
                setLedUnk()
            }
        }
    }

    function getLedValue() {
        return privateProperties.ledValue
    }



    Timer {
        interval: 500; running: false; repeat: true
        onTriggered: {
            if(privateProperties.ledValue != privateProperties.oldVal) {
                if (privateProperties.ledValue > 0) {
                    setLedOn()
                } else if (privateProperties.ledValue == 0) {
                    setLedOff()
                } else {
                    setLedUnk()
                }
            }
            privateProperties.oldVal = privateProperties.ledValue
        }
    }


}
