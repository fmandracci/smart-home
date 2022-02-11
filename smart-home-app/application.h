#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QThread>
#include "modbus.h"
#include <QSettings>


#define TERMOSTATI_COUNT 6


#pragma pack(push, 1)
union int32_union {
    int32_t one;
    struct {
        uint16_t lo;
        uint16_t hi;
    } two;
};
union uint32_union {
    uint32_t one;
    struct {
        uint16_t lo;
        uint16_t hi;
    } two;
};
#pragma pack(pop)

////////////// Expose QList of struct to qml //////////////
struct holding_reg_struct
{
    Q_GADGET
public:

    Q_PROPERTY(bool     b_SRV_connected          MEMBER SRV_connected         )
    Q_PROPERTY(uint     b_SRV_BA_heartbeat       MEMBER SRV_BA_heartbeat      )
    Q_PROPERTY(uint     b_SRV_BA_enabled_sensors MEMBER SRV_BA_enabled_sensors)
    Q_PROPERTY(uint     b_SRV_BA_status          MEMBER SRV_BA_status         )
    Q_PROPERTY(uint32_t b_SRV_BA_config          MEMBER SRV_BA_config         )
    Q_PROPERTY(bool     b_SRV_BA_led_green       MEMBER SRV_BA_led_green      )
    Q_PROPERTY(bool     b_SRV_BA_led_red         MEMBER SRV_BA_led_red        )
    Q_PROPERTY(bool     b_SRV_BA_led_yellow1     MEMBER SRV_BA_led_yellow1    )
    Q_PROPERTY(bool     b_SRV_BA_led_yellow2     MEMBER SRV_BA_led_yellow2    )
    Q_PROPERTY(bool     b_SRV_BA_siren           MEMBER SRV_BA_siren          )
    Q_PROPERTY(bool     b_SRV_BA_relay_A         MEMBER SRV_BA_relay_A        )
    Q_PROPERTY(bool     b_SRV_BA_relay_B         MEMBER SRV_BA_relay_B        )
    Q_PROPERTY(bool     b_SRV_BA_relay_C         MEMBER SRV_BA_relay_C        )
    Q_PROPERTY(bool     b_SRV_BA_input_9         MEMBER SRV_BA_input_9        )
    Q_PROPERTY(bool     b_SRV_BA_input_10        MEMBER SRV_BA_input_10       )
    Q_PROPERTY(bool     b_SRV_BA_input_11        MEMBER SRV_BA_input_11       )
    Q_PROPERTY(bool     b_SRV_BA_input_12        MEMBER SRV_BA_input_12       )
    Q_PROPERTY(uint32_t b_SRV_BA_command         MEMBER SRV_BA_command        )

    bool     SRV_connected;
    uint     SRV_BA_heartbeat;          //UINT     --> 700 --> [RW]TCP7_STATUS NODE_08_STATUS
    uint     SRV_BA_enabled_sensors;    //UINT     --> 701 --> [RW]0, 8, 16, 24, 32
    uint     SRV_BA_status;             //UINT     --> 702 --> [RW]ZERO, IDLE, ARMED, ENABLED, RINGING, MUTED, TESTING
    uint32_t SRV_BA_config;             //UDINT    --> 703 --> [RW]32 bit mask
    bool     SRV_BA_led_green;          //WORD_BIT --> 705 --> [RW]ARMED(blinking), ENABLED, RINGING, MUTED
    bool     SRV_BA_led_red;            //WORD_BIT --> 705 --> [RW]ARMED(if NG), RINGING(blinking), MUTED
    bool     SRV_BA_led_yellow1;        //WORD_BIT --> 705 --> [RW]perimetrale
    bool     SRV_BA_led_yellow2;        //WORD_BIT --> 705 --> [RW]volumetrici
    bool     SRV_BA_siren;              //WORD_BIT --> 705 --> [RW]HPA
    bool     SRV_BA_relay_A;            //WORD_BIT --> 705 --> [RW]
    bool     SRV_BA_relay_B;            //WORD_BIT --> 705 --> [RW]
    bool     SRV_BA_relay_C;            //WORD_BIT --> 705 --> [RW]
    bool     SRV_BA_input_9;            //WORD_BIT --> 705 --> [RW]
    bool     SRV_BA_input_10;           //WORD_BIT --> 705 --> [RW]
    bool     SRV_BA_input_11;           //WORD_BIT --> 705 --> [RW]
    bool     SRV_BA_input_12;           //WORD_BIT --> 705 --> [RW]
    uint32_t SRV_BA_command;            //UDINT    --> 706 --> [RW]ON, OFF, ENABLE, DISABLE, ACK
};
Q_DECLARE_METATYPE(holding_reg_struct)
//////////////////////////////////////////////////////////



////////////// Expose struct to qml //////////////
struct holding_reg_struct_termostati
{
    Q_GADGET
public:

    Q_PROPERTY(bool        b_TCP_T1_connected            MEMBER TCP_T1_connected           )
    Q_PROPERTY(uint        b_TCP_T1_heartbeat            MEMBER TCP_T1_heartbeat           )
    Q_PROPERTY(float       b_TCP_T1_enabled_sensors      MEMBER TCP_T1_enabled_sensors     )
    Q_PROPERTY(float       b_TCP_T1_temperature          MEMBER TCP_T1_temperature         )
    Q_PROPERTY(float       b_TCP_T1_temperature_bis      MEMBER TCP_T1_temperature_bis     )
    Q_PROPERTY(float       b_TCP_T1_temperature_ext      MEMBER TCP_T1_temperature_ext     )
    Q_PROPERTY(float       b_TCP_T1_humidity             MEMBER TCP_T1_humidity            )
    Q_PROPERTY(float       b_TCP_T1_temperature_setpoint MEMBER TCP_T1_temperature_setpoint)
    Q_PROPERTY(float       b_TCP_T1_humidity_setpoint    MEMBER TCP_T1_humidity_setpoint   )
    Q_PROPERTY(uint        b_TCP_T1_enabled_lamps        MEMBER TCP_T1_enabled_lamps       )
    Q_PROPERTY(bool        b_TCP_T1_lamp_1               MEMBER TCP_T1_lamp_1              )
    Q_PROPERTY(bool        b_TCP_T1_lamp_2               MEMBER TCP_T1_lamp_2              )
    Q_PROPERTY(bool        b_TCP_T1_lamp_3               MEMBER TCP_T1_lamp_3              )
    Q_PROPERTY(bool        b_TCP_T1_lamp_4               MEMBER TCP_T1_lamp_4              )
    Q_PROPERTY(bool        b_TCP_T1_lamp_5               MEMBER TCP_T1_lamp_5              )
    Q_PROPERTY(uint        b_TCP_T1_enabled_relays       MEMBER TCP_T1_enabled_relays      )
    Q_PROPERTY(bool        b_TCP_T1_relay_A              MEMBER TCP_T1_relay_A             )
    Q_PROPERTY(bool        b_TCP_T1_relay_B              MEMBER TCP_T1_relay_B             )
    Q_PROPERTY(bool        b_TCP_T1_relay_C              MEMBER TCP_T1_relay_C             )
    Q_PROPERTY(uint        b_TCP_T1_control_type         MEMBER TCP_T1_control_type        )
    Q_PROPERTY(bool        b_TCP_T1_heating              MEMBER TCP_T1_heating             )
    Q_PROPERTY(bool        b_TCP_T1_heating_enabled      MEMBER TCP_T1_heating_enabled     )

    bool        TCP_T1_connected;
    uint        TCP_T1_heartbeat            ;    // UINT     --> 100 --> [RO]TCP1_STATUS NODE_02_STATUS
    float       TCP_T1_enabled_sensors      ;    // INT      --> 101 --> [RO]
    float       TCP_T1_temperature          ;    // INT      --> 102 --> [RO]
    float       TCP_T1_temperature_bis      ;    // INT      --> 103 --> [RO]
    float       TCP_T1_temperature_ext      ;    // INT      --> 104 --> [RO]
    float       TCP_T1_humidity             ;    // INT      --> 105 --> [RO]
    float       TCP_T1_temperature_setpoint ;    // INT      --> 106 --> [RW]
    float       TCP_T1_humidity_setpoint    ;    // INT      --> 107 --> [RW]
    uint        TCP_T1_enabled_lamps        ;    // UINT     --> 108 --> [RO]
    bool        TCP_T1_lamp_1               ;    // WORD_BIT --> 109 --> [RW]
    bool        TCP_T1_lamp_2               ;    // WORD_BIT --> 109 --> [RW]
    bool        TCP_T1_lamp_3               ;    // WORD_BIT --> 109 --> [RW]
    bool        TCP_T1_lamp_4               ;    // WORD_BIT --> 109 --> [RW]
    bool        TCP_T1_lamp_5               ;    // WORD_BIT --> 109 --> [RW]
    uint        TCP_T1_enabled_relays       ;    // UINT     --> 110 --> [RO]
    bool        TCP_T1_relay_A              ;    // WORD_BIT --> 111 --> [RW]
    bool        TCP_T1_relay_B              ;    // WORD_BIT --> 111 --> [RW]
    bool        TCP_T1_relay_C              ;    // WORD_BIT --> 111 --> [RW]
    uint        TCP_T1_control_type         ;    // UINT     --> 112 --> [RO]
    bool        TCP_T1_heating              ;    // WORD_BIT --> 113 --> [RO]
    bool        TCP_T1_heating_enabled      ;    // WORD_BIT --> 114 --> [RW]
};
Q_DECLARE_METATYPE(holding_reg_struct_termostati)
//////////////////////////////////////////////////////////

struct holding_reg_struct_wattmetri
{
    Q_GADGET
public:
    Q_PROPERTY(bool        b_TCP_EP_connected               MEMBER    TCP_EP_connected                  )
    Q_PROPERTY(uint        b_TCP_EP_heartbeat               MEMBER    TCP_EP_heartbeat               )
    Q_PROPERTY(uint        b_TCP_EP_enabled_wattmeters      MEMBER    TCP_EP_enabled_wattmeters      )
    Q_PROPERTY(int         b_TCP_EP_wattmeter01_U           MEMBER    TCP_EP_wattmeter01_U           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter01_C           MEMBER    TCP_EP_wattmeter01_C           )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter01_Texp        MEMBER    TCP_EP_wattmeter01_Texp        )
    Q_PROPERTY(int         b_TCP_EP_wattmeter01_P           MEMBER    TCP_EP_wattmeter01_P           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter01_Pmax        MEMBER    TCP_EP_wattmeter01_Pmax        )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter01_T           MEMBER    TCP_EP_wattmeter01_T           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter02_P           MEMBER    TCP_EP_wattmeter02_P           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter02_Pmax        MEMBER    TCP_EP_wattmeter02_Pmax        )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter02_T           MEMBER    TCP_EP_wattmeter02_T           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter03_P           MEMBER    TCP_EP_wattmeter03_P           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter03_Pmax        MEMBER    TCP_EP_wattmeter03_Pmax        )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter03_T           MEMBER    TCP_EP_wattmeter03_T           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter04_P           MEMBER    TCP_EP_wattmeter04_P           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter04_Pmax        MEMBER    TCP_EP_wattmeter04_Pmax        )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter04_T           MEMBER    TCP_EP_wattmeter04_T           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter05_P           MEMBER    TCP_EP_wattmeter05_P           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter05_Pmax        MEMBER    TCP_EP_wattmeter05_Pmax        )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter05_T           MEMBER    TCP_EP_wattmeter05_T           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter06_P           MEMBER    TCP_EP_wattmeter06_P           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter06_Pmax        MEMBER    TCP_EP_wattmeter06_Pmax        )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter06_T           MEMBER    TCP_EP_wattmeter06_T           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter07_P           MEMBER    TCP_EP_wattmeter07_P           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter07_Pmax        MEMBER    TCP_EP_wattmeter07_Pmax        )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter07_T           MEMBER    TCP_EP_wattmeter07_T           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter08_P           MEMBER    TCP_EP_wattmeter08_P           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter08_Pmax        MEMBER    TCP_EP_wattmeter08_Pmax        )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter08_T           MEMBER    TCP_EP_wattmeter08_T           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter09_P           MEMBER    TCP_EP_wattmeter09_P           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter09_Pmax        MEMBER    TCP_EP_wattmeter09_Pmax        )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter09_T           MEMBER    TCP_EP_wattmeter09_T           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter10_P           MEMBER    TCP_EP_wattmeter10_P           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter10_Pmax        MEMBER    TCP_EP_wattmeter10_Pmax        )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter10_T           MEMBER    TCP_EP_wattmeter10_T           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter11_P           MEMBER    TCP_EP_wattmeter11_P           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter11_Pmax        MEMBER    TCP_EP_wattmeter11_Pmax        )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter11_T           MEMBER    TCP_EP_wattmeter11_T           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter12_P           MEMBER    TCP_EP_wattmeter12_P           )
    Q_PROPERTY(int         b_TCP_EP_wattmeter12_Pmax        MEMBER    TCP_EP_wattmeter12_Pmax        )
    Q_PROPERTY(uint32_t    b_TCP_EP_wattmeter12_T           MEMBER    TCP_EP_wattmeter12_T           )
    Q_PROPERTY(uint        b_TCP_EP_Pmax_reset              MEMBER    TCP_EP_Pmax_reset              )

    bool        TCP_EP_connected;
    uint        TCP_EP_heartbeat               ;// UINT    --> 0    --> [RO]TCP0_STATUS NODE_01_STATUS
    uint        TCP_EP_enabled_wattmeters      ;// UINT    --> 1    --> [RO]0 .. 12
    int         TCP_EP_wattmeter01_U           ;// INT     --> 2    --> [RO]xxx.xx V
    int         TCP_EP_wattmeter01_C           ;// INT     --> 3    --> [RO]+/- x.xxx
    uint32_t    TCP_EP_wattmeter01_Texp        ;// UDINT   --> 4    --> [RO]xxxxxxxxx.x kWh
    int         TCP_EP_wattmeter01_P           ;// INT     --> 6    --> [RO]+/- xxxx W
    int         TCP_EP_wattmeter01_Pmax        ;// INT     --> 7    --> [RO]+/- xxxx W
    uint32_t    TCP_EP_wattmeter01_T           ;// UDINT   --> 8    --> [RO]xxxxxxxxx.x kWh
    int         TCP_EP_wattmeter02_P           ;// INT     --> 10   --> [RO]+/- xxxx W
    int         TCP_EP_wattmeter02_Pmax        ;// INT     --> 11   --> [RO]+/- xxxx W
    uint32_t    TCP_EP_wattmeter02_T           ;// UDINT   --> 12   --> [RO]xxxxxxxxx.x kWh
    int         TCP_EP_wattmeter03_P           ;// INT     --> 14   --> [RO]+/- xxxx W
    int         TCP_EP_wattmeter03_Pmax        ;// INT     --> 15   --> [RO]+/- xxxx W
    uint32_t    TCP_EP_wattmeter03_T           ;// UDINT   --> 16   --> [RO]xxxxxxxxx.x kWh
    int         TCP_EP_wattmeter04_P           ;// INT     --> 18   --> [RO]+/- xxxx W
    int         TCP_EP_wattmeter04_Pmax        ;// INT     --> 19   --> [RO]+/- xxxx W
    uint32_t    TCP_EP_wattmeter04_T           ;// UDINT   --> 20   --> [RO]xxxxxxxxx.x kWh
    int         TCP_EP_wattmeter05_P           ;// INT     --> 22   --> [RO]+/- xxxx W
    int         TCP_EP_wattmeter05_Pmax        ;// INT     --> 23   --> [RO]+/- xxxx W
    uint32_t    TCP_EP_wattmeter05_T           ;// UDINT   --> 24   --> [RO]xxxxxxxxx.x kWh
    int         TCP_EP_wattmeter06_P           ;// INT     --> 26   --> [RO]+/- xxxx W
    int         TCP_EP_wattmeter06_Pmax        ;// INT     --> 27   --> [RO]+/- xxxx W
    uint32_t    TCP_EP_wattmeter06_T           ;// UDINT   --> 28   --> [RO]xxxxxxxxx.x kWh
    int         TCP_EP_wattmeter07_P           ;// INT     --> 30   --> [RO]+/- xxxx W
    int         TCP_EP_wattmeter07_Pmax        ;// INT     --> 31   --> [RO]+/- xxxx W
    uint32_t    TCP_EP_wattmeter07_T           ;// UDINT   --> 32   --> [RO]xxxxxxxxx.x kWh
    int         TCP_EP_wattmeter08_P           ;// INT     --> 34   --> [RO]+/- xxxx W
    int         TCP_EP_wattmeter08_Pmax        ;// INT     --> 35   --> [RO]+/- xxxx W
    uint32_t    TCP_EP_wattmeter08_T           ;// UDINT   --> 36   --> [RO]xxxxxxxxx.x kWh
    int         TCP_EP_wattmeter09_P           ;// INT     --> 38   --> [RO]+/- xxxx W
    int         TCP_EP_wattmeter09_Pmax        ;// INT     --> 39   --> [RO]+/- xxxx W
    uint32_t    TCP_EP_wattmeter09_T           ;// UDINT   --> 40   --> [RO]xxxxxxxxx.x kWh
    int         TCP_EP_wattmeter10_P           ;// INT     --> 42   --> [RO]+/- xxxx W
    int         TCP_EP_wattmeter10_Pmax        ;// INT     --> 43   --> [RO]+/- xxxx W
    uint32_t    TCP_EP_wattmeter10_T           ;// UDINT   --> 44   --> [RO]xxxxxxxxx.x kWh
    int         TCP_EP_wattmeter11_P           ;// INT     --> 46   --> [RO]+/- xxxx W
    int         TCP_EP_wattmeter11_Pmax        ;// INT     --> 47   --> [RO]+/- xxxx W
    uint32_t    TCP_EP_wattmeter11_T           ;// UDINT   --> 48   --> [RO]xxxxxxxxx.x kWh
    int         TCP_EP_wattmeter12_P           ;// INT     --> 50   --> [RO]+/- xxxx W
    int         TCP_EP_wattmeter12_Pmax        ;// INT     --> 51   --> [RO]+/- xxxx W
    uint32_t    TCP_EP_wattmeter12_T           ;// UDINT   --> 52   --> [RO]xxxxxxxxx.x kWh
    uint        TCP_EP_Pmax_reset              ;// UINT    --> 54   --> [RW]index 1..12
};
Q_DECLARE_METATYPE(holding_reg_struct_wattmetri)
/////////////////////////////////////////////////////////



struct network_struct
{
    Q_GADGET
public:
    Q_PROPERTY(QString b_ip_address_wifi  MEMBER ip_address_wifi      )
    Q_PROPERTY(QString b_ip_address_vpn   MEMBER ip_address_vpn       )
    Q_PROPERTY(int     b_port_number_wifi  MEMBER port_number_wifi    )
    Q_PROPERTY(int     b_port_number_vpn  MEMBER port_number_vpn      )
    Q_PROPERTY(bool    b_is_VPN_on    MEMBER is_VPN_on       )


    QString ip_address_wifi;
    QString ip_address_vpn;

    int     port_number_wifi;
    int     port_number_vpn;

    bool    is_VPN_on;

};
Q_DECLARE_METATYPE(network_struct)



class Application : public QThread
{
    Q_OBJECT

    ////////////// Expose network_struct to qml //////////////
    Q_PROPERTY(network_struct m_connection_info READ get_connection_info WRITE set_connection_info NOTIFY connection_info_changed)
    //////////////////////////////////////////////////////////

    ////////////// Expose holding_reg_struct to qml //////////////
    Q_PROPERTY(holding_reg_struct m_srv_reg_struct READ get_srv_reg_struct)
    //////////////////////////////////////////////////////////

    ////////////// Expose holding_reg_struct to qml //////////////
    Q_PROPERTY(QList<holding_reg_struct_termostati> m_termostati_list READ get_termostati_list)
    Q_PROPERTY(int m_termostati_list_count READ get_termostati_list_count)
    //////////////////////////////////////////////////////////

    ////////////// Expose holding_reg_struct to qml //////////////
    Q_PROPERTY(holding_reg_struct_wattmetri m_srv_reg_struct_wattmetri READ get_srv_reg_struct_wattmetri)
    //////////////////////////////////////////////////////////


public:
    explicit Application(QObject *parent = nullptr);

    void run() override;
    //Vars:
    network_struct  connection_info;
    holding_reg_struct srv_reg_struct;
    holding_reg_struct_wattmetri srv_reg_struct_wattmetri;
    QList <holding_reg_struct_termostati> termostatiList;


public slots:
    Q_INVOKABLE    bool open_modBus_connection();
    Q_INVOKABLE    void close_modBus_connection();

    ///////////// Antifurto ///////////////////////////////////////////
    Q_INVOKABLE    bool read_h_register_antifurto();
    Q_INVOKABLE    bool write_h_register_antifurto(QString status);
    ///////////////////////////////////////////////////////////////////

    ///////////// Termostato ///////////////////////////////////////////
    Q_INVOKABLE    bool read_h_register_termostati();
    Q_INVOKABLE    bool write_h_register_termostati_Enabled(bool termEnabled);
    Q_INVOKABLE    bool write_h_register_termostati_SetPoint(int setPoint);
    ///////////////////////////////////////////////////////////////////


    ///////////// Wattmetri ///////////////////////////////////////////
    Q_INVOKABLE    bool read_h_register_wattmetri();
    ///////////////////////////////////////////////////////////////////

    ///////////// Settings ////////////////////////////////////////////
    void saveSettings(QString Wifi_ip, int Wifi_port, QString Vpn_ip, int Vpn_port);
    Q_INVOKABLE    void setSettings();
    ///////////////////////////////////////////////////////////////////


private slots:

    ///////////// Antifurto ///////////////////////////////////////////
    void parse_holding_register_antifurto(uint16_t read_holding_regs[]);
    void debug_print_srv_reg_struct_antifurto();
    ///////////////////////////////////////////////////////////////////

    ///////////// Termostato ///////////////////////////////////////////
    void parse_holding_register_termostati(uint16_t read_holding_regs[], int termostati_list_index);
    void debug_print_srv_reg_struct_termostati(int index);
    ///////////////////////////////////////////////////////////////////

    ///////////// Wattmetri ///////////////////////////////////////////
    void parse_holding_register_wattmetri(uint16_t read_holding_regs[]);
    void debug_print_srv_reg_struct_wattmetri();
    ///////////////////////////////////////////////////////////////////

    //bool connection_info_changed();
    void update_network_info(){update_network = true;}

    ////////////// Expose network_struct to qml //////////////
    network_struct get_connection_info() { return connection_info; }
    void set_connection_info(network_struct val){connection_info = val;emit connection_info_changed();}
    //////////////////////////////////////////////////////////

    ////////////// Expose holding_reg_struct to qml //////////////
    holding_reg_struct get_srv_reg_struct() const {return srv_reg_struct;}
    //////////////////////////////////////////////////////////

    ////////////// Expose holding_reg_struct_termostati to qml //////////////
    QList<holding_reg_struct_termostati> get_termostati_list() const {return termostatiList;}
    int get_termostati_list_count() const {return termostatiList.count();}
    //////////////////////////////////////////////////////////

    ////////////// Expose srv_reg_struct_wattmetri to qml //////////////
    holding_reg_struct_wattmetri get_srv_reg_struct_wattmetri() const {return srv_reg_struct_wattmetri;}
    //////////////////////////////////////////////////////////



private:
    modbus *modBusHandler;
    bool    update_network;
    QSettings  *objSettings;


signals:
    void connection_info_changed();

};

#endif // APPLICATION_H
