import QtQuick 2.4
import QtQuick.Controls 2.12


ImpostazioniForm {


    Component.onCompleted: {
        textFieldWifiIP.placeholderText = SmartEngine.m_connection_info.b_ip_address_wifi
        textFieldVpnIP.placeholderText = SmartEngine.m_connection_info.b_ip_address_vpn

        setNetworkInfo(false)
    }

    networkSaveButton.onClicked: {
        setNetworkInfo(false)
    }


    function setNetworkInfo(vpnOn) {
        var wifiIp   = textFieldWifiIP.text
        if(wifiIp === "") {
            wifiIp   = textFieldWifiIP.placeholderText
        }

        var vpnIp    = textFieldVpnIP.text
        if(vpnIp === "") {
            vpnIp   = textFieldVpnIP.placeholderText
        }
        var wifiPort = 502
        var vpnPort  = 502

        SmartEngine.m_connection_info.b_ip_address_wifi = wifiIp
        SmartEngine.m_connection_info.b_ip_address_vpn = vpnIp
        SmartEngine.m_connection_info.b_port_number_wifi = wifiPort
        SmartEngine.m_connection_info.b_port_number_vpn = vpnPort
        SmartEngine.m_connection_info.b_is_VPN_on = vpnOn
        SmartEngine.saveSettings(wifiIp,wifiPort,vpnIp,vpnPort)
    }

}
