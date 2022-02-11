#include "application.h"
#include <QVariant>
#include <QDebug>
#include <QCoreApplication>

#define READ_REQUEST_INT_ms 1000


Application::Application(QObject *parent) : QThread(parent)
{

    QCoreApplication::setOrganizationName("Mect S.r.l.");
    QCoreApplication::setApplicationName("smart-home-app");
    objSettings = new QSettings();
    setSettings();

    modBusHandler = new modbus();
    modBusHandler->modbus_set_slave_id(1);
    srv_reg_struct.SRV_connected = false;
    for(int i=0; i<TERMOSTATI_COUNT;i++) {
        holding_reg_struct_termostati tmp_tpc_reg_struct_termostato;
        tmp_tpc_reg_struct_termostato.TCP_T1_connected = false;
        termostatiList.append(tmp_tpc_reg_struct_termostato);
    }
    srv_reg_struct_wattmetri.TCP_EP_connected = false;
    connect(this,&Application::connection_info_changed,this,&Application::update_network_info);
}


void Application::setSettings()
{

    objSettings->beginGroup("Network");
    connection_info.ip_address_wifi = objSettings->value("Wifi_ip", "192.168.5.20").toString();

    connection_info.port_number_wifi = objSettings->value("Wifi_port", "502").toInt();

    connection_info.ip_address_vpn = objSettings->value("Vpn_ip", "10.1.0.141").toString();

    connection_info.port_number_vpn = objSettings->value("Vpn_port", "502").toInt();

    objSettings->endGroup();

}
void Application::saveSettings(QString Wifi_ip,int Wifi_port,QString Vpn_ip, int Vpn_port)
{
    objSettings->beginGroup("Network");
    objSettings->setValue("Wifi_ip", Wifi_ip);
    objSettings->setValue("Wifi_port", Wifi_port);
    objSettings->setValue("Vpn_ip", Vpn_ip);
    objSettings->setValue("Vpn_port", Vpn_port);
    objSettings->endGroup();
    objSettings->sync();
}


void Application::run() {
    qint64 period_ms = READ_REQUEST_INT_ms;
    QElapsedTimer timer;
    qint64 elapsed_ms;

    while (true) {
        timer.restart();
           if(!modBusHandler->isConnected()) {
               open_modBus_connection();
           } else {
               if(update_network) {
                   qDebug()<<"Network Update...";
                   open_modBus_connection();
               }
               read_h_register_antifurto();
               read_h_register_termostati();
               read_h_register_wattmetri();
           }
        elapsed_ms = timer.elapsed();
        QThread::msleep(period_ms);
    }
}


bool Application::open_modBus_connection()
{
    bool fRes = false;
    update_network = false;
    //qDebug()<<"------> VPN STATUS =="<<connection_info.is_VPN_on;
    if (modBusHandler) {
        if (modBusHandler->isConnected()) {
            qWarning()<<"Restarting the connection...";
            close_modBus_connection();
        }
        if(!connection_info.is_VPN_on) {
            // WIFI CONNECT
            qDebug()<<"Connetting with Wifi";
            if ( !connection_info.ip_address_wifi.isEmpty() &&  connection_info.port_number_wifi > 0) {
                if (modBusHandler->modbus_connect(connection_info.ip_address_wifi.toStdString(),connection_info.port_number_wifi)) {
                    fRes = true;
                } else {
                    qCritical()<<"Connection Error";
                }
            } else {
                qCritical()<<"Missing ip address or port number";
            }
        } else {
            // VPN CONNECT
            qDebug()<<"Connetting with VPN";
            if ( !connection_info.ip_address_vpn.isEmpty() &&  connection_info.port_number_vpn > 0) {
                if (modBusHandler->modbus_connect(connection_info.ip_address_vpn.toStdString(),connection_info.port_number_vpn)) {
                    fRes = true;
                } else {
                    qCritical()<<"Connection Error";
                }
            } else {
                qCritical()<<"Missing ip address or port number";
            }
        }
    } else {
        qCritical()<<"ModbusHandler error";
    }
    srv_reg_struct.SRV_connected = fRes;
    for(int i=0; i<TERMOSTATI_COUNT;i++) {
        termostatiList[i].TCP_T1_connected = fRes;
    }
    srv_reg_struct_wattmetri.TCP_EP_connected = fRes;

    return fRes;
}


void Application::close_modBus_connection()
{
    if(modBusHandler) {
        modBusHandler->modbus_close();
    } else {
        qWarning()<<"Connection was already off";
    }
}


//////////////////////////////   ANTIFURTO  ///////////////////////////////////////////////////////////////////////////
bool Application::read_h_register_antifurto()
{
    bool fRes = false;
    uint16_t holding_regs_array[7];
    int read_res = modBusHandler->modbus_read_holding_registers(700, 6, holding_regs_array);

    if(read_res == 0) {
        parse_holding_register_antifurto(holding_regs_array);
        fRes = true;
    } else if(read_res == -1){
            qCritical()<<"Bad connection";
    } else {
            qWarning()<<"Bad Data lenght or Address";
    }
    return fRes;
}


void Application::parse_holding_register_antifurto(uint16_t holding_regs_array[])
{
    uint32_union uint32Reg;
    srv_reg_struct.SRV_BA_heartbeat         = holding_regs_array[0];
    srv_reg_struct.SRV_BA_enabled_sensors   = holding_regs_array[1];
    srv_reg_struct.SRV_BA_status            = holding_regs_array[2];
    uint32Reg.two.lo                        = holding_regs_array[3];
    uint32Reg.two.hi                        = holding_regs_array[4];
    srv_reg_struct.SRV_BA_config            = uint32Reg.one;

    srv_reg_struct.SRV_BA_led_green         = holding_regs_array[5] & 0x0001;
    srv_reg_struct.SRV_BA_led_red           = holding_regs_array[5] & 0x0002;
    srv_reg_struct.SRV_BA_led_yellow1       = holding_regs_array[5] & 0x0004;
    srv_reg_struct.SRV_BA_led_yellow2       = holding_regs_array[5] & 0x0008;
    srv_reg_struct.SRV_BA_siren             = holding_regs_array[5] & 0x0010;
    srv_reg_struct.SRV_BA_relay_A           = holding_regs_array[5] & 0x0020;
    srv_reg_struct.SRV_BA_relay_B           = holding_regs_array[5] & 0x0040;
    srv_reg_struct.SRV_BA_relay_C           = holding_regs_array[5] & 0x0080;
    srv_reg_struct.SRV_BA_input_9           = holding_regs_array[5] & 0x0100;
    srv_reg_struct.SRV_BA_input_10          = holding_regs_array[5] & 0x0200;
    srv_reg_struct.SRV_BA_input_11          = holding_regs_array[5] & 0x0400;
    srv_reg_struct.SRV_BA_input_12          = holding_regs_array[5] & 0x0800;

    srv_reg_struct.SRV_BA_command           = holding_regs_array[6];

    //debug_print_srv_reg_struct_antifurto();
}

bool Application::write_h_register_antifurto(QString status)
{
    bool fRes = false;
    uint16_t write_regs[2];//{low, high};
    bool ok;
    uint16_t tmp_code = status.remove("0x").right(4).toInt(&ok,16);

    if(ok) {
        write_regs[0] = tmp_code;
        tmp_code = status.remove("0x").left(4).toInt(&ok,16);
        if(ok) {
            write_regs[1] = tmp_code;
            int result = modBusHandler->modbus_write_registers(706, 2, write_regs);
            if( result == 0) {
                fRes = true;
            }
        }
    }
    return fRes;
}

void Application::debug_print_srv_reg_struct_antifurto()
{
    qDebug()<<"SRV_BA_heartbeat      = "<<QString("0x%1").arg(srv_reg_struct.SRV_BA_heartbeat, 4, 16, QLatin1Char( '0' ));
    qDebug()<<"SRV_BA_enabled_sensor = "<<QString("0x%1").arg(srv_reg_struct.SRV_BA_enabled_sensors, 4, 16, QLatin1Char( '0' ));
    qDebug()<<"SRV_BA_status         = "<<QString("0x%1").arg(srv_reg_struct.SRV_BA_status , 4, 16, QLatin1Char( '0' ));
    qDebug()<<"SRV_BA_config         = "<<QString("0x%1").arg(srv_reg_struct.SRV_BA_config, 8, 16, QLatin1Char( '0' ));
    qDebug()<<"SRV_BA_led_green      = "<<srv_reg_struct.SRV_BA_led_green     ;
    qDebug()<<"SRV_BA_led_red        = "<<srv_reg_struct.SRV_BA_led_red       ;
    qDebug()<<"SRV_BA_led_yellow1    = "<<srv_reg_struct.SRV_BA_led_yellow1   ;
    qDebug()<<"SRV_BA_led_yellow2    = "<<srv_reg_struct.SRV_BA_led_yellow2   ;
    qDebug()<<"SRV_BA_siren          = "<<srv_reg_struct.SRV_BA_siren         ;
    qDebug()<<"SRV_BA_relay_A        = "<<srv_reg_struct.SRV_BA_relay_A       ;
    qDebug()<<"SRV_BA_relay_B        = "<<srv_reg_struct.SRV_BA_relay_B       ;
    qDebug()<<"SRV_BA_relay_C        = "<<srv_reg_struct.SRV_BA_relay_C       ;
    qDebug()<<"SRV_BA_input_9        = "<<srv_reg_struct.SRV_BA_input_9       ;
    qDebug()<<"SRV_BA_input_10       = "<<srv_reg_struct.SRV_BA_input_10      ;
    qDebug()<<"SRV_BA_input_11       = "<<srv_reg_struct.SRV_BA_input_11      ;
    qDebug()<<"SRV_BA_input_12       = "<<srv_reg_struct.SRV_BA_input_12      ;
    qDebug()<<"SRV_BA_command        = "<<QString("0x%1").arg(srv_reg_struct.SRV_BA_command, 8, 16, QLatin1Char( '0' ));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////  TERMOSTATI  /////////////////////////////////////////////////////////////////////////////
bool Application::read_h_register_termostati()
{
    bool fRes = false;
    uint16_t holding_regs_array[15];

    for(int i =0; i< TERMOSTATI_COUNT; i++) {
        int read_res = modBusHandler->modbus_read_holding_registers(100*(i+1), 15, holding_regs_array);

        if(read_res == 0) {
            parse_holding_register_termostati(holding_regs_array,i);
            fRes = true;
        } else if(read_res == -1){
                qCritical()<<"Bad connection";
        } else {
                qWarning()<<"Bad Data lenght or Address";
        }
    }
    return fRes;
}


void Application::parse_holding_register_termostati(uint16_t holding_regs_array[],int termostati_list_index)
{

    termostatiList[termostati_list_index].TCP_T1_heartbeat           = holding_regs_array[0];
    termostatiList[termostati_list_index].TCP_T1_enabled_sensors     = holding_regs_array[1];
    termostatiList[termostati_list_index].TCP_T1_temperature         = holding_regs_array[2] / 10.0;
    termostatiList[termostati_list_index].TCP_T1_temperature_bis     = holding_regs_array[3] / 10.0;
    termostatiList[termostati_list_index].TCP_T1_temperature_ext     = holding_regs_array[4] / 10.0;
    termostatiList[termostati_list_index].TCP_T1_humidity            = holding_regs_array[5] / 10.0;
    termostatiList[termostati_list_index].TCP_T1_temperature_setpoint= holding_regs_array[6] / 10.0;
    termostatiList[termostati_list_index].TCP_T1_humidity_setpoint   = holding_regs_array[7] / 10.0;
    termostatiList[termostati_list_index].TCP_T1_enabled_lamps       = holding_regs_array[8];
    termostatiList[termostati_list_index].TCP_T1_lamp_1              = holding_regs_array[9] & 0x0001;
    termostatiList[termostati_list_index].TCP_T1_lamp_2              = holding_regs_array[9] & 0x0002;
    termostatiList[termostati_list_index].TCP_T1_lamp_3              = holding_regs_array[9] & 0x0004;
    termostatiList[termostati_list_index].TCP_T1_lamp_4              = holding_regs_array[9] & 0x0008;
    termostatiList[termostati_list_index].TCP_T1_lamp_5              = holding_regs_array[9] & 0x0010;
    termostatiList[termostati_list_index].TCP_T1_enabled_relays      = holding_regs_array[10];
    termostatiList[termostati_list_index].TCP_T1_relay_A             = holding_regs_array[11] & 0x0001;
    termostatiList[termostati_list_index].TCP_T1_relay_B             = holding_regs_array[11] & 0x0002;
    termostatiList[termostati_list_index].TCP_T1_relay_C             = holding_regs_array[11] & 0x0004;
    termostatiList[termostati_list_index].TCP_T1_control_type        = holding_regs_array[12];
    termostatiList[termostati_list_index].TCP_T1_heating             = holding_regs_array[13];
    termostatiList[termostati_list_index].TCP_T1_heating_enabled     = holding_regs_array[24];

    //debug_print_srv_reg_struct_termostati(0);
}

bool Application::write_h_register_termostati_Enabled(bool termEnabled)
{
    bool fRes = false;
//    uint16_t write_regs[2];//{low, high};
//    bool ok;
//    uint16_t tmp_code = status.remove("0x").right(4).toInt(&ok,16);

//    if(ok) {
//        write_regs[0] = tmp_code;
//        tmp_code = status.remove("0x").left(4).toInt(&ok,16);
//        if(ok) {
//            write_regs[1] = tmp_code;
//            int result = modBusHandler->modbus_write_registers(706, 2, write_regs);
//            if( result == 0) {
//                fRes = true;
//            }
//        }
//    }
    return fRes;
}

bool Application::write_h_register_termostati_SetPoint(int setPoint)
{
    bool fRes = false;
    uint16_t write_regs[1];//{low, high};
    int val = (setPoint/5) *5;
    qDebug()<<val;

    write_regs[0] = val;
    int result = modBusHandler->modbus_write_registers(106, 1, write_regs);
    if( result == 0) {
        fRes = true;
    }
    qDebug()<< "Writing = "<<fRes;
    return fRes;
}

void Application::debug_print_srv_reg_struct_termostati(int index)
{
        qDebug()<<"TCP_T1_heartbeat           = "<<termostatiList.at(index).TCP_T1_heartbeat        ;
        qDebug()<<"TCP_T1_enabled_sensors     = "<<termostatiList.at(index).TCP_T1_enabled_sensors  ;
        qDebug()<<"TCP_T1_temperature         = "<<termostatiList.at(index).TCP_T1_temperature      ;
        qDebug()<<"TCP_T1_temperature_bis     = "<<termostatiList.at(index).TCP_T1_temperature_bis  ;
        qDebug()<<"TCP_T1_temperature_ext     = "<<termostatiList.at(index).TCP_T1_temperature_ext  ;
        qDebug()<<"TCP_T1_humidity            = "<<termostatiList.at(index).TCP_T1_humidity         ;
        qDebug()<<"TCP_T1_temperature_setpoint= "<<termostatiList.at(index).TCP_T1_temperature_setpoint;
        qDebug()<<"TCP_T1_humidity_setpoint   = "<<termostatiList.at(index).TCP_T1_humidity_setpoint;
        qDebug()<<"TCP_T1_enabled_lamps       = "<<termostatiList.at(index).TCP_T1_enabled_lamps    ;
        qDebug()<<"TCP_T1_lamp_1              = "<<termostatiList.at(index).TCP_T1_lamp_1           ;
        qDebug()<<"TCP_T1_lamp_2              = "<<termostatiList.at(index).TCP_T1_lamp_2           ;
        qDebug()<<"TCP_T1_lamp_3              = "<<termostatiList.at(index).TCP_T1_lamp_3           ;
        qDebug()<<"TCP_T1_lamp_4              = "<<termostatiList.at(index).TCP_T1_lamp_4           ;
        qDebug()<<"TCP_T1_lamp_5              = "<<termostatiList.at(index).TCP_T1_lamp_5           ;
        qDebug()<<"TCP_T1_enabled_relays      = "<<termostatiList.at(index).TCP_T1_enabled_relays   ;
        qDebug()<<"TCP_T1_relay_A             = "<<termostatiList.at(index).TCP_T1_relay_A          ;
        qDebug()<<"TCP_T1_relay_B             = "<<termostatiList.at(index).TCP_T1_relay_B          ;
        qDebug()<<"TCP_T1_relay_C             = "<<termostatiList.at(index).TCP_T1_relay_C          ;
        qDebug()<<"TCP_T1_control_type        = "<<termostatiList.at(index).TCP_T1_control_type     ;
        qDebug()<<"TCP_T1_heating             = "<<termostatiList.at(index).TCP_T1_heating          ;
        qDebug()<<"TCP_T1_heating_enabled     = "<<termostatiList.at(index).TCP_T1_heating_enabled  ;
}


//////////////////////////////   WattMETRI  ///////////////////////////////////////////////////////////////////////////
bool Application::read_h_register_wattmetri()
{
    bool fRes = false;
    uint16_t holding_regs_array[55];
    int read_res = modBusHandler->modbus_read_holding_registers(0, 55, holding_regs_array);

    if(read_res == 0) {
        parse_holding_register_wattmetri(holding_regs_array);
        fRes = true;
    } else if(read_res == -1){
            qCritical()<<"Bad connection";
    } else {
            qWarning()<<"Bad Data lenght or Address";
    }
    return fRes;
}


void Application::parse_holding_register_wattmetri(uint16_t holding_regs_array[])
{
    uint32_union uint32Reg;
    srv_reg_struct_wattmetri.TCP_EP_heartbeat         = holding_regs_array[0];
    srv_reg_struct_wattmetri.TCP_EP_enabled_wattmeters= holding_regs_array[1];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter01_U     = holding_regs_array[2];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter01_C     = holding_regs_array[3];
    uint32Reg.two.lo                                  = holding_regs_array[4];
    uint32Reg.two.hi                                  = holding_regs_array[5];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter01_Texp  = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_wattmeter01_P     = holding_regs_array[6];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter01_Pmax  = holding_regs_array[7];
    uint32Reg.two.lo                                  = holding_regs_array[8];
    uint32Reg.two.hi                                  = holding_regs_array[9];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter01_T     = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_wattmeter02_P     = holding_regs_array[10];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter02_Pmax  = holding_regs_array[11];
    uint32Reg.two.lo                                  = holding_regs_array[12];
    uint32Reg.two.hi                                  = holding_regs_array[13];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter02_T     = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_wattmeter03_P     = holding_regs_array[14];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter03_Pmax  = holding_regs_array[15];
    uint32Reg.two.lo                                  = holding_regs_array[16];
    uint32Reg.two.hi                                  = holding_regs_array[17];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter03_T     = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_wattmeter04_P     = holding_regs_array[18];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter04_Pmax  = holding_regs_array[19];
    uint32Reg.two.lo                                  = holding_regs_array[20];
    uint32Reg.two.hi                                  = holding_regs_array[21];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter04_T     = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_wattmeter05_P     = holding_regs_array[22];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter05_Pmax  = holding_regs_array[23];
    uint32Reg.two.lo                                  = holding_regs_array[24];
    uint32Reg.two.hi                                  = holding_regs_array[25];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter05_T     = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_wattmeter06_P     = holding_regs_array[26];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter06_Pmax  = holding_regs_array[27];
    uint32Reg.two.lo                                  = holding_regs_array[28];
    uint32Reg.two.hi                                  = holding_regs_array[29];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter06_T     = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_wattmeter07_P     = holding_regs_array[30];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter07_Pmax  = holding_regs_array[31];
    uint32Reg.two.lo                                  = holding_regs_array[32];
    uint32Reg.two.hi                                  = holding_regs_array[33];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter07_T     = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_wattmeter08_P     = holding_regs_array[34];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter08_Pmax  = holding_regs_array[35];
    uint32Reg.two.lo                                  = holding_regs_array[36];
    uint32Reg.two.hi                                  = holding_regs_array[37];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter08_T     = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_wattmeter09_P     = holding_regs_array[38];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter09_Pmax  = holding_regs_array[39];
    uint32Reg.two.lo                                  = holding_regs_array[40];
    uint32Reg.two.hi                                  = holding_regs_array[41];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter09_T     = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_wattmeter10_P     = holding_regs_array[42];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter10_Pmax  = holding_regs_array[43];
    uint32Reg.two.lo                                  = holding_regs_array[44];
    uint32Reg.two.hi                                  = holding_regs_array[45];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter10_T     = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_wattmeter11_P     = holding_regs_array[46];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter11_Pmax  = holding_regs_array[47];
    uint32Reg.two.lo                                  = holding_regs_array[48];
    uint32Reg.two.hi                                  = holding_regs_array[49];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter11_T     = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_wattmeter12_P     = holding_regs_array[50];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter12_Pmax  = holding_regs_array[51];
    uint32Reg.two.lo                                  = holding_regs_array[52];
    uint32Reg.two.hi                                  = holding_regs_array[53];
    srv_reg_struct_wattmetri.TCP_EP_wattmeter12_T     = uint32Reg.one;
    srv_reg_struct_wattmetri.TCP_EP_Pmax_reset        = holding_regs_array[54];

    //debug_print_srv_reg_struct_wattmetri();
}

void Application::debug_print_srv_reg_struct_wattmetri()
{
    qDebug()<<"TCP_EP_heartbeat          = "<< srv_reg_struct_wattmetri.TCP_EP_heartbeat          ;
    qDebug()<<"TCP_EP_enabled_wattmeters = "<< srv_reg_struct_wattmetri.TCP_EP_enabled_wattmeters ;
    qDebug()<<"TCP_EP_wattmeter01_U      = "<< srv_reg_struct_wattmetri.TCP_EP_wattmeter01_U      ;
    qDebug()<<"TCP_EP_wattmeter01_C      = "<< srv_reg_struct_wattmetri.TCP_EP_wattmeter01_C      ;
    qDebug()<<"TCP_EP_wattmeter01_Texp   = "<< srv_reg_struct_wattmetri.TCP_EP_wattmeter01_Texp   ;
    qDebug()<<"TCP_EP_wattmeter01_P      = "<< srv_reg_struct_wattmetri.TCP_EP_wattmeter01_P      ;
    qDebug()<<"TCP_EP_wattmeter01_Pmax   = "<< srv_reg_struct_wattmetri.TCP_EP_wattmeter01_Pmax   ;
    qDebug()<<"TCP_EP_wattmeter01_T      = "<< srv_reg_struct_wattmetri.TCP_EP_wattmeter01_T      ;

}




