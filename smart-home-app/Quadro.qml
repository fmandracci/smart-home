import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

QuadroForm {

    Component.onCompleted: {
        addWattTile("Wattmetro 1","-","-","-","-")
    }


    function addWattTile(tileName,actual,max,delta,total) {
        wattmetriModel.append({   wattmetroName:tileName,
                                   actualWatt   :actual,
                                   maxWatt      :max,
                                   deltaWatt    :delta,
                                   totalWatt    :total,
                                   })
    }


    function updateTiles() {
        if(SmartEngine.m_srv_reg_struct_wattmetri.b_TCP_EP_connected) {

            wattmetriListView.itemAtIndex(0).actualWattLabel.text    = "Watt <br> " + SmartEngine.m_srv_reg_struct_wattmetri.b_TCP_EP_wattmeter01_P           + " W"
            wattmetriListView.itemAtIndex(0).maxWattLabel.text       = "P<sub>Max</sub> " + SmartEngine.m_srv_reg_struct_wattmetri.b_TCP_EP_wattmeter01_Pmax  + " W"
            wattmetriListView.itemAtIndex(0).totalWattLabel.text     = "P<sub>Tot</sub> " + SmartEngine.m_srv_reg_struct_wattmetri.b_TCP_EP_wattmeter01_T     + " kWh"
        }
    }

    function deltaCalc() {
        //wattmetriListView.itemAtIndex(0).deltaWattLabel.text     = SmartEngine.m_srv_reg_struct_wattmetri.
    }


    Timer {
        interval: 5000; running: true; repeat: true
        onTriggered: {
            updateTiles()
        }
    }
}
