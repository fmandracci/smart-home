import QtQuick 2.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

AntifurtoForm {
    property var daytimeIcon    : "Icons/daytime.png"
    property var nighttimeIcon  : "Icons/nighttime.png"
    property var everythingIcon : "Icons/enable_all.png"
    property var ringingIcon    : "Icons/ringing.png"
    property var mutedIcon      : "Icons/muted.png"
    property var armedIcon      : "Icons/armed.png"
    property var enabledIcon    : "Icons/enabled.png"
    property var disconnectedIcon: "Icons/disconnected.png"
    property var unconfiguredIcon: "Icons/not_configured.png"

    //GREEN LED BLINK VARs
    property var greenledflag: false

    //RED LED BLINK VARs
    property var redledflag: false

    // ANTIFURTO Status
    property var notConnectedStatus     : -1
    property var idleStatus             : 1
    property var armedStatus            : 2
    property var enabledStatus          : 3
    property var ringingStatus          : 4
    property var mutedStatus            : 5

    property var statusVar      : notConnectedStatus
    property var oldStatusVar   : "-"


  property var m_ALARM_COMMAND_NONE       : "0x00000000"
  property var m_ALARM_COMMAND_ARM        : "0xc1a0AAAA"
  property var m_ALARM_COMMAND_NOTHING    : "0xc1a0CC00"
  property var m_ALARM_COMMAND_DAYTIME    : "0xc1a0CC01"
  property var m_ALARM_COMMAND_NIGHTTIME  : "0xc1a0CC02"
  property var m_ALARM_COMMAND_EVERYTHING : "0xc1a0CC03"
  property var m_ALARM_COMMAND_ENABLE     : "0xc1a0EEEE"
  property var m_ALARM_COMMAND_DISABLE    : "0xc1a0DDDD"
  property var m_ALARM_COMMAND_ACK        : "0xc1a0BBBB"
  property var m_ALARM_COMMAND_TEST       : "0xc1a0FFFF"



    Component.onCompleted: {
        configModel.clear()
        labelHeartBeat.setPrefix("Heartbeat: ")
        addConfigTile("Idle",  unconfiguredIcon,    m_ALARM_COMMAND_DISABLE)      // configListView item 0
        addConfigTile("Daytime", daytimeIcon,       m_ALARM_COMMAND_DAYTIME)      // configListView item 1
        addConfigTile("Nighttime",nighttimeIcon,    m_ALARM_COMMAND_NIGHTTIME)    // configListView item 2
        addConfigTile("Everything",everythingIcon,  m_ALARM_COMMAND_EVERYTHING)   // configListView item 3
        addConfigTile("Enable",  enabledIcon,       m_ALARM_COMMAND_ENABLE)       // configListView item 4
        addConfigTile("Muted",   mutedIcon,         m_ALARM_COMMAND_ACK)          // configListView item 5
    }



    function addConfigTile(configName,icon,commandHex) {
        configModel.append({configText: configName,iconSource: icon, command: commandHex})
    }


    function stateMachine(connection_status,currentStatus,previousStatus,led_yellow_01,led_yellow_02) {

        //console.log("currentStatus = " + currentStatus, "---> previousStatus = " + previousStatus)
        if(connection_status) {
            // CONFIG SETTER ///////////////
            if (led_yellow_01 === true && led_yellow_02 === true) {
                labelConf.text = "Everything"
            } else if (led_yellow_01 === true && led_yellow_02 === false) {
                labelConf.text = "Nighttime"
            }  else if (led_yellow_01 === false && led_yellow_02 === true) {
                labelConf.text = "Daytime"
            }
            //////////////////////////////

            switch(currentStatus){
            case idleStatus:
                if(previousStatus !== idleStatus) {
                    greenledflag  = false
                    redledflag    = false
                    configListView.itemAtIndex(0).enableForm(false)
                    configListView.itemAtIndex(1).enableForm(true)
                    configListView.itemAtIndex(2).enableForm(true)
                    configListView.itemAtIndex(3).enableForm(true)
                    configListView.itemAtIndex(4).enableForm(false)
                    configListView.itemAtIndex(5).enableForm(false)
                    rectangleHeader.color = materialDarkRed
                    rectangleHeader.border.color = materialDarkRed
                    labelConf.text = "Non configurato"
                    labelStatus.text = "Idle"
                    statusIcon.source = unconfiguredIcon
                    oldStatusVar = idleStatus
                }
                break
            case armedStatus:
                if (previousStatus !== armedStatus) {
                    configListView.itemAtIndex(0).enableForm(true)
                    configListView.itemAtIndex(1).enableForm(true)
                    configListView.itemAtIndex(2).enableForm(true)
                    configListView.itemAtIndex(3).enableForm(true)
                    configListView.itemAtIndex(4).enableForm(true)
                    configListView.itemAtIndex(5).enableForm(false)
                    oldStatusVar = armedStatus
                } else {
                    if (greenledflag === false) {
                        rectangleHeader.color = Material.color(Material.LightGreen)
                        rectangleHeader.border.color = Material.color(Material.LightGreen)
                        labelStatus.text = "Armed"
                        statusIcon.source = ""
                        greenledflag = true;
                    } else {
                        rectangleHeader.color = Material.color(Material.Green)
                        rectangleHeader.border.color = Material.color(Material.Green)
                        labelStatus.text = "Armed"
                        statusIcon.source = armedIcon
                        greenledflag = false;
                    }
                    oldStatusVar = armedStatus
                }

                break
            case enabledStatus:
                if (previousStatus !== enabledStatus) {
                    greenledflag = true
                    configListView.itemAtIndex(0).enableForm(true)
                    configListView.itemAtIndex(1).enableForm(false)
                    configListView.itemAtIndex(2).enableForm(false)
                    configListView.itemAtIndex(3).enableForm(false)
                    configListView.itemAtIndex(4).enableForm(false)
                    configListView.itemAtIndex(5).enableForm(false)
                    rectangleHeader.color = Material.color(Material.Green)
                    rectangleHeader.border.color = Material.color(Material.Green)
                    labelStatus.text = "Enabled"
                    statusIcon.source = enabledIcon
                    oldStatusVar = enabledStatus
                }
                break

            case ringingStatus:
                if (previousStatus !== ringingStatus) {
                    configListView.itemAtIndex(0).enableForm(false)
                    configListView.itemAtIndex(1).enableForm(false)
                    configListView.itemAtIndex(2).enableForm(false)
                    configListView.itemAtIndex(3).enableForm(false)
                    configListView.itemAtIndex(4).enableForm(false)
                    configListView.itemAtIndex(5).enableForm(true)
                    oldStatusVar = ringingStatus
                } else {
                    if (redledflag === false) {
                        rectangleHeader.color = Material.color(Material.Red)
                        rectangleHeader.border.color = Material.color(Material.Red)
                        labelStatus.text = "Ringing"
                        statusIcon.source = ""
                        redledflag = true;
                    } else {
                        rectangleHeader.color = Material.color(Material.DeepOrange)
                        rectangleHeader.border.color = Material.color(Material.DeepOrange)
                        labelStatus.text = "Ringing"
                        statusIcon.source = ringingIcon
                        redledflag = false;
                    }
                    oldStatusVar = ringingStatus
                }
                break
            case mutedStatus:
                if (previousStatus !== mutedStatus) {
                    redledflag  = true
                    configListView.itemAtIndex(0).enableForm(true)
                    configListView.itemAtIndex(1).enableForm(false)
                    configListView.itemAtIndex(2).enableForm(false)
                    configListView.itemAtIndex(3).enableForm(false)
                    configListView.itemAtIndex(4).enableForm(false)
                    configListView.itemAtIndex(5).enableForm(false)
                    rectangleHeader.color = Material.color(Material.Red)
                    rectangleHeader.border.color = Material.color(Material.Red)
                    labelStatus.text = "Muted"
                    statusIcon.source = mutedIcon
                    oldStatusVar = mutedStatus
                }
                break

            case 0:
                configListView.itemAtIndex(0).enableForm(false)
                configListView.itemAtIndex(1).enableForm(false)
                configListView.itemAtIndex(2).enableForm(false)
                configListView.itemAtIndex(3).enableForm(false)
                configListView.itemAtIndex(4).enableForm(false)
                configListView.itemAtIndex(5).enableForm(false)
                oldStatusVar = notConnectedStatus
                break

            }
        } else {
            configListView.itemAtIndex(0).enableForm(false)
            configListView.itemAtIndex(1).enableForm(false)
            configListView.itemAtIndex(2).enableForm(false)
            configListView.itemAtIndex(3).enableForm(false)
            configListView.itemAtIndex(4).enableForm(false)
            configListView.itemAtIndex(5).enableForm(false)
            rectangleHeader.color = materialDarkRed
            rectangleHeader.border.color = materialDarkRed
            labelConf.text = "Non Connesso"
            labelStatus.text = "-"
            statusIcon.source = disconnectedIcon
            oldStatusVar = statusVar
            statusVar = notConnectedStatus
        }
    }


    Timer {
        interval: 1000; running: true; repeat: true
        onTriggered: {
            stateMachine(SmartEngine.m_srv_reg_struct.b_SRV_connected,
                         SmartEngine.m_srv_reg_struct.b_SRV_BA_status,oldStatusVar,
                         SmartEngine.m_srv_reg_struct.b_SRV_BA_led_yellow1,
                         SmartEngine.m_srv_reg_struct.b_SRV_BA_led_yellow2)
        }
    }


}
