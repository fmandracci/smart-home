import QtQuick 2.4

SmartLabelForm {

    QtObject {
        id:privateProperties
        property string strValue: ""
        property string prefix: ""
        property string suffix: ""

        property string oldStrValue: ""
        property string oldPrefix: ""
        property string oldSuffix: ""
    }



    function setValue(value) {
        privateProperties.strValue = value
        labelText.text = privateProperties.prefix + privateProperties.strValue + privateProperties.suffix
    }

    function setPrefix(value) {
        privateProperties.prefix = value
        labelText.text = privateProperties.prefix + privateProperties.strValue + privateProperties.suffix
    }

    function setSuffix(value) {
        privateProperties.suffix = value
        labelText.text = privateProperties.prefix + privateProperties.strValue + privateProperties.suffix
    }


    Timer {
        interval: 500; running: false; repeat: true
        onTriggered: {
            if (privateProperties.strValue != privateProperties.oldStrValue ||
                privateProperties.prefix != privateProperties.oldPrefix ||
                privateProperties.suffix != privateProperties.oldSuffix )
            {
                labelText.text = privateProperties.prefix + privateProperties.strValue + privateProperties.suffix
            }
            privateProperties.oldStrValue   = privateProperties.strValue
            privateProperties.oldPrefix     = privateProperties.prefix
            privateProperties.oldSuffix     = privateProperties.suffix

        }
    }


}
