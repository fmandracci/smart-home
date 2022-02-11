#ifndef MECT_TYPES_H
#define MECT_TYPES_H

#include <sys/types.h>
#include <modbus.h>
#include <QMutex>

#define MECT_VERSION            "1.0.4"

#define TOTAL_HOLDING_REGS      128
#define TOTAL_WRITING_REGS       64
#define MODBUS_MAX_BLOCK_SIZE    64

#define STANDARD_REFRESH_TIME     2

#define EP_STARTING_REG           0
#define EP_TOTAL_REGS            104

#define THERMO_STARTING_REG     200
#define THERMO_TOTAL_REGS        23

#define THERMO_BLOCK_SIZE       100
#define THERMO_TEMP_SP_DAY_REG    8
#define THERMO_HUM_SP_DAY_REG     9
#define THERMO_HEATING_STATUS    14
#define THERMO_TEMP_SP_NIGHT_REG 18
#define THERMO_HUM_SP_NIGHT_REG  19
#define THERMO_HEATING_TIME    1200

#define BA_STARTING_REG         800
#define BA_COMMAND_REG            7
#define BA_TOTAL_REGS            42

#define ALARM_COMMAND_NONE       0x00000000
#define ALARM_COMMAND_DAYTIME    0xc1a0CC01
#define ALARM_COMMAND_NIGHTTIME  0xc1a0CC02
#define ALARM_COMMAND_EVERYTHING 0xc1a0CC03
#define ALARM_COMMAND_ENABLE     0xc1a0EEEE
#define ALARM_COMMAND_DISABLE    0xc1a0DDDD
#define ALARM_COMMAND_ACK        0xc1a0BBBB
#define ALARM_COMMAND_TEST       0xc1a0FFFF


#pragma pack(push, 1)
union reg32_union {
    uint8_t     u8Value;            // BYTE  BIT        BYTE_BIT   WORD_BIT   DWORD_BIT
    u_int16_t   u16Value;           // UINT  UINT_BA
    uint32_t    u32Value;           // UDINT UDINT_BADC UDINT_CDAB UDINT_DCBA
    int16_t     i16Value;           // INT   INT_BA
    int32_t     i32Value;           // DINT  DINT_BADC  DINT_CDAB  DINT_DCBA
    float       floatValue;         // REAL  REAL_BADC  REAL_CDAB  REAL_DCBA
    struct {
        uint16_t lo;
        uint16_t hi;
    } dWord;
};
#pragma pack(pop)

struct dati_electric_panel  {
	uint		EP_heartbeat 				;	 // UINT Decimal=0 R=0 			[RO]	
	uint		EP_enabled_wattmeters 		;	 // UINT Decimal=0 R=1 			[RO]	0 .. 12
	uint		EP_wattmeters_ok 			;	 // UINT Decimal=0 R=2 			[RO]	bit mask (node status)
    int         EP_wattmeter_M_W 			;	 // INT Decimal=0 R=3 			[RO]	+/- xxxx W
	int			EP_wattmeter_M_var 			;	 // INT Decimal=0 R=4 			[RO]	+/- xxxx var
	int			EP_wattmeter_M_VA 			;	 // INT Decimal=0 R=5 			[RO]	+/- xxxx VA
	float       EP_wattmeter_M_pf 			;	 // INT Decimal=3 R=6 			[RO]	+/- x.xxx
    float       EP_wattmeter_M_Hz 			;	 // INT Decimal=2 R=7 			[RO]	xxx.xx Hz
	float       EP_wattmeter_M_V 			;	 // INT Decimal=2 R=8 			[RO]	xxx.xx V
	float       EP_wattmeter_M_A 			;	 // INT Decimal=3 R=9 			[RO]	xx.xxx A
	float       EP_wattmeter_M_kWh 			;	 // DINT Decimal=1 R=10 		[RO]	xxxxxxxxx.x +kWh
	float       EP_wattmeter_M_e_kWh 		;	 // DINT Decimal=1 R=12 		[RO]	xxxxxxxxx.x -kWh
	int			EP_wattmeter_F_W 			;	 // INT Decimal=0 R=14 			[RO]	+/- xxxx W
	int			EP_wattmeter_F_var 			;	 // INT Decimal=0 R=15 			[RO]	+/- xxxx var
	int			EP_wattmeter_F_VA 			;	 // INT Decimal=0 R=16 			[RO]	+/- xxxx VA
	float       EP_wattmeter_F_pf 			;	 // INT Decimal=3 R=17 			[RO]	+/- x.xxx
    float       EP_wattmeter_F_Hz 			;	 // INT Decimal=2 R=18 			[RO]	xxx.xx Hz
	float       EP_wattmeter_F_V 			;	 // INT Decimal=2 R=19 			[RO]	xxx.xx V
	float       EP_wattmeter_F_A 			;	 // INT Decimal=3 R=20 			[RO]	xx.xxx A
	float       EP_wattmeter_F_kWh 			;	 // DINT Decimal=1 R=21 		[RO]	xxxxxxxxx.x +kWh
	float       EP_wattmeter_F_e_kWh 		;	 // DINT Decimal=1 R=23 		[RO]	xxxxxxxxx.x -kWh
	int			EP_wattmeter01_W 			;	 // INT Decimal=0 R=25 			[RO]	+/- xxxx W
	int			EP_wattmeter01_var 			;	 // INT Decimal=0 R=26 			[RO]	+/- xxxx var
	int			EP_wattmeter01_VA 			;	 // INT Decimal=0 R=27 			[RO]	+/- xxxx VA
	float       EP_wattmeter01_kWh 			;	 // DINT Decimal=1 R=28 		[RO]	xxxxxxxxx.x +kWh
	int			EP_wattmeter02_W 			;	 // INT Decimal=0 R=30 			[RO]	+/- xxxx W
	int			EP_wattmeter02_var 			;	 // INT Decimal=0 R=31 			[RO]	+/- xxxx var
	int			EP_wattmeter02_VA 			;	 // INT Decimal=0 R=32 			[RO]	+/- xxxx VA
	float       EP_wattmeter02_kWh 			;	 // DINT Decimal=1 R=33 		[RO]	xxxxxxxxx.x +kWh
	int			EP_wattmeter03_W 			;	 // INT Decimal=0 R=35 			[RO]	+/- xxxx W
	int			EP_wattmeter03_var 			;	 // INT Decimal=0 R=36 			[RO]	+/- xxxx var
	int			EP_wattmeter03_VA 			;	 // INT Decimal=0 R=37 			[RO]	+/- xxxx VA
	float       EP_wattmeter03_kWh 			;	 // DINT Decimal=1 R=38 		[RO]	xxxxxxxxx.x +kWh
	int			EP_wattmeter04_W 			;	 // INT Decimal=0 R=40 			[RO]	+/- xxxx W
	int			EP_wattmeter04_var 			;	 // INT Decimal=0 R=41 			[RO]	+/- xxxx var
	int			EP_wattmeter04_VA 			;	 // INT Decimal=0 R=42 			[RO]	+/- xxxx VA
	float       EP_wattmeter04_kWh 			;	 // DINT Decimal=1 R=43 		[RO]	xxxxxxxxx.x +kWh
	int			EP_wattmeter05_W 			;	 // INT Decimal=0 R=45 			[RO]	+/- xxxx W
	int			EP_wattmeter05_var 			;	 // INT Decimal=0 R=46 			[RO]	+/- xxxx var
	int			EP_wattmeter05_VA 			;	 // INT Decimal=0 R=47 			[RO]	+/- xxxx VA
	float       EP_wattmeter05_kWh 			;	 // DINT Decimal=1 R=48 		[RO]	xxxxxxxxx.x +kWh
	int			EP_wattmeter06_W 			;	 // INT Decimal=0 R=50 			[RO]	+/- xxxx W
	int			EP_wattmeter06_var 			;	 // INT Decimal=0 R=51 			[RO]	+/- xxxx var
	int			EP_wattmeter06_VA 			;	 // INT Decimal=0 R=52 			[RO]	+/- xxxx VA
	float       EP_wattmeter06_kWh 			;	 // DINT Decimal=1 R=53 		[RO]	xxxxxxxxx.x +kWh
	int			EP_wattmeter07_W 			;	 // INT Decimal=0 R=55 			[RO]	+/- xxxx W
	int			EP_wattmeter07_var 			;	 // INT Decimal=0 R=56 			[RO]	+/- xxxx var
	int			EP_wattmeter07_VA 			;	 // INT Decimal=0 R=57 			[RO]	+/- xxxx VA
	float       EP_wattmeter07_kWh 			;	 // DINT Decimal=1 R=58 		[RO]	xxxxxxxxx.x +kWh
	int			EP_wattmeter08_W 			;	 // INT Decimal=0 R=60 			[RO]	+/- xxxx W
	int			EP_wattmeter08_var 			;	 // INT Decimal=0 R=61 			[RO]	+/- xxxx var
	int			EP_wattmeter08_VA 			;	 // INT Decimal=0 R=62 			[RO]	+/- xxxx VA
	float       EP_wattmeter08_kWh 			;	 // DINT Decimal=1 R=63 		[RO]	xxxxxxxxx.x +kWh
	int			EP_wattmeter09_W 			;	 // INT Decimal=0 R=65 			[RO]	+/- xxxx W
	int			EP_wattmeter09_var 			;	 // INT Decimal=0 R=66 			[RO]	+/- xxxx var
	int			EP_wattmeter09_VA 			;	 // INT Decimal=0 R=67 			[RO]	+/- xxxx VA
	float       EP_wattmeter09_kWh 			;	 // DINT Decimal=1 R=68 		[RO]	xxxxxxxxx.x +kWh
	int			EP_wattmeter10_W 			;	 // INT Decimal=0 R=70 			[RO]	+/- xxxx W
	int			EP_wattmeter10_var 			;	 // INT Decimal=0 R=71 			[RO]	+/- xxxx var
	int			EP_wattmeter10_VA 			;	 // INT Decimal=0 R=72 			[RO]	+/- xxxx VA
	float       EP_wattmeter10_kWh 			;	 // DINT Decimal=1 R=73 		[RO]	xxxxxxxxx.x +kWh
	float       EP_wattmeter_M_kWh_60s 		;	 // INT Decimal=1 R=75 			[RO]	xxx.x kWh
	float       EP_wattmeter_M_e_kWh_60s 	;	 // INT Decimal=1 R=76 			[RO]	xxx.x kWh
	float       EP_wattmeter_F_kWh_60s 		;	 // INT Decimal=1 R=77 			[RO]	xxx.x kWh
	float       EP_wattmeter_F_e_kWh_60s 	;	 // INT Decimal=1 R=78 			[RO]	xxx.x kWh
	float       EP_wattmeter01_kWh_60s 		;	 // INT Decimal=1 R=79 			[RO]	xxx.x kWh
	float       EP_wattmeter02_kWh_60s 		;	 // INT Decimal=1 R=80 			[RO]	xxx.x kWh
	float       EP_wattmeter03_kWh_60s 		;	 // INT Decimal=1 R=81 			[RO]	xxx.x kWh
	float       EP_wattmeter04_kWh_60s 		;	 // INT Decimal=1 R=82 			[RO]	xxx.x kWh
	float       EP_wattmeter05_kWh_60s 		;	 // INT Decimal=1 R=83 			[RO]	xxx.x kWh
	float       EP_wattmeter06_kWh_60s 		;	 // INT Decimal=1 R=84 			[RO]	xxx.x kWh
	float       EP_wattmeter07_kWh_60s 		;	 // INT Decimal=1 R=85 			[RO]	xxx.x kWh
	float       EP_wattmeter08_kWh_60s 		;	 // INT Decimal=1 R=86 			[RO]	xxx.x kWh
	float       EP_wattmeter09_kWh_60s 		;	 // INT Decimal=1 R=87 			[RO]	xxx.x kWh
	float       EP_wattmeter10_kWh_60s 		;	 // INT Decimal=1 R=88 			[RO]	xxx.x kWh
	bool        EP_BlackoutDetected 		;	 // WORD_BIT Decimal=1 R=89 	[RO]	
	bool        EP_OverloadDetected 		;	 // WORD_BIT Decimal=2 R=89 	[RO]	
	int			EP_enabled_relays 			;	 // INT Decimal=0 R=90 			[RO]	0 .. 8
	bool        EP_relay_A 					;	 // WORD_BIT Decimal=1 R=91 	[RW]	
	bool        EP_relay_B 					;	 // WORD_BIT Decimal=2 R=91 	[RW]	
	bool        EP_relay_C 					;	 // WORD_BIT Decimal=3 R=91 	[RW]	
	bool        EP_relay_D 					;	 // WORD_BIT Decimal=4 R=91 	[RW]	
	bool        EP_relay_E 					;	 // WORD_BIT Decimal=5 R=91 	[RW]	
	bool        EP_relay_F 					;	 // WORD_BIT Decimal=6 R=91 	[RW]	
	bool        EP_relay_G 					;	 // WORD_BIT Decimal=7 R=91 	[RW]	
	bool        EP_relay_H 					;	 // WORD_BIT Decimal=8 R=91 	[RW]	
	uint		EP_overload_W 				;	 // UINT Decimal=0 R=92 		[RO]	
	uint		EP_max_assigned_W			;	 // UINT Decimal=0 R=93 		[RO]	
	uint		EP_tic_in_tac				;	 // UINT Decimal=0 R=94 		[RO]		
	uint		EP_requested_W 				;	 // UINT Decimal=0 R=95 		[RO]	
	uint		EP_T1_assigned_W 			;	 // UINT Decimal=0 R=96 		[RO]	
	uint		EP_T2_assigned_W 			;	 // UINT Decimal=0 R=97 		[RO]	
	uint		EP_T3_assigned_W 			;	 // UINT Decimal=0 R=98 		[RO]	
	uint		EP_T4_assigned_W 			;	 // UINT Decimal=0 R=99 		[RO]	
	uint		EP_T5_assigned_W 			;	 // UINT Decimal=0 R=100 		[RO]	
	uint		EP_T6_assigned_W 			;	 // UINT Decimal=0 R=101 		[RO]	
	uint		EP_assigned_W				;	 // UINT Decimal=0 R=102 		[RO]	
	uint		EP_control_type				;	 // UINT Decimal=0 R=103 		[RO]	
};

struct dati_termostato  {
	uint        TH_heartbeat 				;    // UINT Decimal=0 R=200  		[RO]
	int			TH_enabled_sensors 			;    // INT Decimal=0 R=201         [RO]
	float       TH_temperature 				;    // INT Decimal=1 R=202         [RO]
	float       TH_temperature_bis 			;    // INT Decimal=1 R=203         [RO]
	float       TH_temperature_ext 			;    // INT Decimal=1 R=204         [RO]
	float       TH_humidity 				;    // INT Decimal=1 R=205  	    [RO]
	float       TH_humidity_bis 			;    // INT Decimal=1 R=206  	    [RO]
	float       TH_humidity_ext 			;    // INT Decimal=1 R=207  	    [RO]
	float       TH_temperature_setpoint 	;    // INT Decimal=1 R=208  	    [RW]
	float       TH_humidity_setpoint 		;    // INT Decimal=1 R=209  	    [RW]
	uint        TH_enabled_lamps 			;    // UINT Decimal=0 R=210  	    [RO]
	bool        TH_lamp_1 					;    // WORD_BIT Decimal=1 R=211    [RW]
	bool        TH_lamp_2 					;    // WORD_BIT Decimal=2 R=211    [RW]
	bool        TH_lamp_3 					;    // WORD_BIT Decimal=3 R=211    [RW]
	bool        TH_lamp_4 					;    // WORD_BIT Decimal=4 R=211    [RW]
	bool        TH_lamp_5 					;    // WORD_BIT Decimal=5 R=211    [RW]
	uint        TH_max_request_W 			;    // UINT Decimal=0 R=212  	    [RO]
	bool        TH_heating 					;    // WORD_BIT Decimal=1 R=213    [RO]
	bool        TH_nighttime 				;    // WORD_BIT Decimal=2 R=213 	[RO]
	int			TH_heating_status 			;    // INT Decimal=0 R=214         [RW]
	int			TH_heating_timer 			;    // INT Decimal=0 R=215  	    [RW]
	uint        TH_sunrise 					;    // UINT Decimal=0 R=216        [RW]
	uint        TH_sunset 					;    // UINT Decimal=0 R=217        [RW]
	float       TH_temperature_setpoint_nt 	;    // INT Decimal=1 R=218         [RW]
	float       TH_humidity_setpoint_nt 	;    // INT Decimal=1 R=219  	    [RW]
	bool        TH_lamp_feedback_1 			;    // WORD_BIT Decimal=1 R=220    [RO]
	bool        TH_lamp_feedback_2 			;    // WORD_BIT Decimal=2 R=220    [RO]
	bool        TH_lamp_feedback_3 			;    // WORD_BIT Decimal=3 R=220    [RO]
	bool        TH_lamp_feedback_4 			;    // WORD_BIT Decimal=4 R=220    [RO]
	bool        TH_lamp_feedback_5 			;    // WORD_BIT Decimal=5 R=220    [RO]
    uint        TH_requested_W 				;    // UINT Decimal=0 R=221  	    [RO]
    uint        TH_control_type 			;    // UINT Decimal=0 R=222  	    [RO]
};

struct dati_antifurto  {
	uint        BA_heartbeat				;    //  UINT	 Decimal=0 R=800 	[RO]		TCP7_STATUS NODE_08_STATUS				
	uint        BA_enabled_sensors			;    //  UINT Decimal=0 R=801 		[RO]		0, 8, 16, 24, 32			
	uint        BA_status					;    //  UINT Decimal=0 R=802 		[RO]		ZERO, OFF, ARMED, ENABLED, RINGING, MUTED, TESTING					
	uint        BA_config_index				;    //  UINT Decimal=0 R=803 		[RO]		0 1 2 3			
	uint        BA_config_mask				;    //  UDINT Decimal=0 R=804 		[RO]		32 bit mask				
	bool        BA_led_green				;    //  WORD_BIT Decimal=1 R=806 	[RO]		ARMED(blinking), ENABLED, RINGING, MUTED				
	bool        BA_led_red					;    //  WORD_BIT Decimal=2 R=806 	[RO]		ARMED(if NG), RINGING(blinking), MUTED					
	bool        BA_led_yellow1				;    //  WORD_BIT Decimal=3 R=806 	[RO]		NIGHTIME, EVERYTHING				
	bool        BA_led_yellow2				;    //  WORD_BIT Decimal=4 R=806 	[RO]		DAYTIME, EVERYTHING				
	bool        BA_siren					;    //  WORD_BIT Decimal=5 R=806 	[RO]		HPA					
	bool        BA_relay_A					;    //  WORD_BIT Decimal=6 R=806 	[RO]				
	bool        BA_relay_B					;    //  WORD_BIT Decimal=7 R=806 	[RO]				
	bool        BA_relay_C					;    //  WORD_BIT Decimal=8 R=806 	[RO]				
	bool        BA_input_9					;    //  WORD_BIT Decimal=9 R=806 	[RO]				
	bool        BA_input_10					;    //  WORD_BIT Decimal=10 R=806 	[RO]			
	bool        BA_input_11					;    //  WORD_BIT Decimal=11 R=806 	[RO]			
	bool        BA_input_12					;    //  WORD_BIT Decimal=12 R=806 	[RO]			
	bool        BA_BlackoutDetected			;    //  WORD_BIT Decimal=13 R=806 	[RO]	
	uint        BA_command					;    //  UDINT Decimal=0 R=807 		[RW]		NONE, ARM, NOTHING, DAYTIME, NIGHTIME, EVERYTHING, ENABLE, DISABLE, ACK, TEST					
	uint        BA_OK_1						;    //  UINT Decimal=0 R=809 		[RO]			
	uint        BA_OK_2						;    //  UINT Decimal=0 R=810 		[RO]			
	uint        BA_OK_3						;    //  UINT Decimal=0 R=811 		[RO]			
	uint        BA_OK_4						;    //  UINT Decimal=0 R=812 		[RO]			
	uint        BA_OK_5						;    //  UINT Decimal=0 R=813 		[RO]			
	uint        BA_OK_6						;    //  UINT Decimal=0 R=814 		[RO]			
	uint        BA_OK_7						;    //  UINT Decimal=0 R=815 		[RO]			
	uint        BA_OK_8						;    //  UINT Decimal=0 R=816 		[RO]			
    uint        BA_OK_9						;    //  UINT Decimal=0 R=817 		[RO]
	uint        BA_OK_10					;    //  UINT Decimal=0 R=818 		[RO]			
	uint        BA_OK_11					;    //  UINT Decimal=0 R=819 		[RO]			
	uint        BA_OK_12					;    //  UINT Decimal=0 R=820 		[RO]			
	uint        BA_OK_13					;    //  UINT Decimal=0 R=821 		[RO]			
	uint        BA_OK_14					;    //  UINT Decimal=0 R=822 		[RO]			
	uint        BA_OK_15					;    //  UINT Decimal=0 R=823 		[RO]			
	uint        BA_OK_16					;    //  UINT Decimal=0 R=824 		[RO]			
	uint        BA_OK_17					;    //  UINT Decimal=0 R=825 		[RO]			
	uint        BA_OK_18					;    //  UINT Decimal=0 R=826 		[RO]			
	uint        BA_OK_19					;    //  UINT Decimal=0 R=827 		[RO]			
	uint        BA_OK_20					;    //  UINT Decimal=0 R=828 		[RO]			
	uint        BA_OK_21					;    //  UINT Decimal=0 R=829 		[RO]			
	uint        BA_OK_22					;    //  UINT Decimal=0 R=830 		[RO]			
	uint        BA_OK_23					;    //  UINT Decimal=0 R=831 		[RO]			
	uint        BA_OK_24					;    //  UINT Decimal=0 R=832 		[RO]			
	uint        BA_OK_25					;    //  UINT Decimal=0 R=833 		[RO]			
	uint        BA_OK_26					;    //  UINT Decimal=0 R=834 		[RO]			
	uint        BA_OK_27					;    //  UINT Decimal=0 R=835 		[RO]			
	uint        BA_OK_28					;    //  UINT Decimal=0 R=836 		[RO]			
	uint        BA_OK_29					;    //  UINT Decimal=0 R=837 		[RO]			
	uint        BA_OK_30					;    //  UINT Decimal=0 R=838 		[RO]			
	uint        BA_OK_31					;    //  UINT Decimal=0 R=839 		[RO]			
	uint        BA_OK_32					;    //  UINT Decimal=0 R=840 		[RO]			
	uint        BA_control_type 			;    //  UINT Decimal=0 R=841  	    [RO]
};

struct dati_device  {
    int                         firstModbusReg;
    int                         regsToRead;
    QString                     szMyIPaddress;
    int                         nMyPort;
    int                         refreshTime;
    int                         myId;
    QString                     myName;
    QTimer                      *readTimer;
    QMutex                      *deviceMutex;
    bool                        isConnected;
    modbus                      *modBusHandler;
    uint16_t                    holdingRegisters[TOTAL_HOLDING_REGS];
    uint16_t                    singleRegisterValue;
    uint16_t                    writeHoldingRegistersValues[TOTAL_WRITING_REGS];
    int                         readLoop;
    bool                        isNightTime;
    // Dati interpretati dalla lettura Modbus
    struct dati_termostato      *datiTH;
    struct dati_electric_panel  *datiEP;
    struct dati_antifurto       *datiBA;

};


#endif // MECT_TYPES_H








