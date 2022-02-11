import QtQuick 2.4

TermostastiForm {

    property int counter: 0
    property string tScale: " °C"

    Component.onCompleted: {

                addTermostatoTile("Term1","Termostato 1","-","-","-","-",1,false,false)
                addTermostatoTile("Term2","Termostato 2","-","-","-","-",1,false,false)
                addTermostatoTile("Term3","Termostato 3","-","-","-","-",1,false,false)
                addTermostatoTile("Term4","Termostato 4","-","-","-","-",1,false,false)
                addTermostatoTile("Term5","Termostato 5","-","-","-","-",1,false,false)
                addTermostatoTile("Term6","Termostato 6","-","-","-","-",1,false,false)
    }




    function addTermostatoTile(tileID,tileName,firstTemp,secondTemp,extTemp,setPointTemp,sValue,status,heating_ON) {
        termostatiModel.append({   tileId:tileID,
                                   termostatoName:tileName,
                                   temp1:firstTemp,
                                   temp2:secondTemp,
                                   temp3:extTemp,
                                   setPoint:setPointTemp,
                                   sliderValue: sValue,
                                   termosatoStatus:status,
                                   heating_isON: heating_ON
                                   })
    }

    function updateTiles() {

        for(var i =0; i<termostatiListView.count; i++) {
            if(SmartEngine.m_termostati_list[i].b_TCP_T1_connected) {
                var sensorsNum = SmartEngine.m_termostati_list[i].b_TCP_T1_enabled_sensors
                if(sensorsNum > 0) {
                    termostatiListView.itemAtIndex(i).backgroundRect.visible = true
                    switch (sensorsNum) {
                        case 1:
                            termostatiListView.itemAtIndex(i).temp2Label.visible  = false
                            termostatiListView.itemAtIndex(i).temp3Label.visible  = false
                            break
                        case 2:
                            termostatiListView.itemAtIndex(i).temp3Label.visible  = false
                            break
                        default:
                            termostatiListView.itemAtIndex(i).temp2Label.visible  = true
                            termostatiListView.itemAtIndex(i).temp3Label.visible  = true
                   }
                } else {
                    termostatiListView.itemAtIndex(i).backgroundRect.visible = false
                }

                termostatiListView.itemAtIndex(i).temp1Label.text  =    "T<sub>1</sub> <br>"  +            Number((SmartEngine.m_termostati_list[i].b_TCP_T1_temperature).toFixed(1)) + tScale
                termostatiListView.itemAtIndex(i).temp2Label.text  =    "T<sub>2</sub> " +      Number((SmartEngine.m_termostati_list[i].b_TCP_T1_temperature_bis).toFixed(1)) + tScale
                termostatiListView.itemAtIndex(i).temp3Label.text  =    "T<sub>ext</sub> " +    Number((SmartEngine.m_termostati_list[i].b_TCP_T1_temperature_ext).toFixed(1)) + tScale
                termostatiListView.itemAtIndex(i).tempSetPoint.text  =  "T<sub>setpoint</sub> "+Number((SmartEngine.m_termostati_list[i].b_TCP_T1_temperature_setpoint).toFixed(1)) + tScale
                if(SmartEngine.m_termostati_list[i].b_TCP_T1_temperature_setpoint > 0) {
                    termostatiListView.itemAtIndex(i).circularSlider.value =  Number(((SmartEngine.m_termostati_list[i].b_TCP_T1_temperature_setpoint).toFixed(1)-10) /10)
                } else {
                    termostatiListView.itemAtIndex(i).circularSlider.value =  0
                }

                termostatiListView.itemAtIndex(i).enableSwitch.checked =   SmartEngine.m_termostati_list[i].b_TCP_T1_heating_enabled
                termostatiListView.itemAtIndex(i).labelHeating.visible =   SmartEngine.m_termostati_list[i].b_TCP_T1_heating
            } else {
                for(var j =0; j<termostatiListView.count; j++) {
                    termostatiListView.itemAtIndex(j).temp1Label.text  =    "T1 <br>"  +               "-" + tScale
                    termostatiListView.itemAtIndex(j).temp2Label.text  =    "T<sub>2</sub> " +         "-" + tScale
                    termostatiListView.itemAtIndex(j).temp3Label.text  =    "T<sub>ext</sub> " +       "-" + tScale
                    termostatiListView.itemAtIndex(j).tempSetPoint.text  =  "T<sub>setpoint</sub> "+   "-" + tScale
                    termostatiListView.itemAtIndex(i).circularSlider.value =  0
                    termostatiListView.itemAtIndex(j).enableSwitch.checked =   false
                    termostatiListView.itemAtIndex(i).labelHeating.visible =   false
                }
            }
        }
    }


    Timer {
        interval: 5000; running: true; repeat: true
        onTriggered: {
                updateTiles()
        }
    }
}
