(****************************************************************************
**
** Copyright (C) 2021 Francesco Mandracci
** Contact: https://github.com/fmandracci/smart-home
**
** This file is part of the Smart Home Framework.
**
** Commercial License Usage
** Licensees holding valid commercial licenses may use this file in
** accordance with the terms contained in a written agreement
** between you and the copyright owner.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
****************************************************************************)

PROGRAM Tn_Thermo 
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR	
    Thermostat_1 : Thermostat; FilteredSensors_1 : FilteredSensors;
    Thermostat_2 : Thermostat; FilteredSensors_2 : FilteredSensors;
    Thermostat_3 : Thermostat; FilteredSensors_3 : FilteredSensors;
    Thermostat_4 : Thermostat; FilteredSensors_4 : FilteredSensors;
    Thermostat_5 : Thermostat; FilteredSensors_5 : FilteredSensors;
    Thermostat_6 : Thermostat; FilteredSensors_6 : FilteredSensors;
END_VAR
	
    if PLC_Iam_T1 then
        Tn_Watchdog();
        FilteredSensors_1(   n := 1,              ES:= PLC_T1_enabled_sensors,
                       T1 := PLC_T1_temperature, T2 := PLC_T1_temperature_bis, T3 := PLC_T1_temperature_ext,
                       H1 := PLC_T1_humidity,    H2 := PLC_T1_humidity_bis,    H3 := PLC_T1_humidity_ext    );
        Thermostat_1( N := 1,
		             ES := PLC_T1_enabled_sensors,        NT := PLC_T1_nighttime,
                    T_1 := PLC_T1_temperature,           T_2 := PLC_T1_temperature_bis,
                    H_1 := PLC_T1_humidity,              H_2 := PLC_T1_humidity_bis,
					M_W := PLC_T1_max_request_W,         A_W := PLC_EP_T1_assigned_W, PRW := PLC_T1_requested_W, SRW := SRV_T1_requested_W,
                    TSP := PLC_T1_temperature_setpoint, TSPN := PLC_T1_temperature_setpoint_nt,
                    HSP := PLC_T1_humidity_setpoint,    HSPN := PLC_T1_humidity_setpoint_nt,
             PLC_STATUS := PLC_T1_heating_status,  PLC_TIMER := PLC_T1_heating_timer, PLC_HEATING := PLC_T1_heating,
             SRV_STATUS := SRV_T1_heating_status,  SRV_TIMER := SRV_T1_heating_timer, SRV_HEATING := SRV_T1_heating,
			         DH := PLC_T1_daily_heating_s,        MH := PLC_T1_monthly_heating_s);
    end_if;

    if PLC_Iam_T2 then
        Tn_Watchdog();
        FilteredSensors_2(   n := 2,              ES:= PLC_T2_enabled_sensors,
                       T1 := PLC_T2_temperature, T2 := PLC_T2_temperature_bis, T3 := PLC_T2_temperature_ext,
                       H1 := PLC_T2_humidity,    H2 := PLC_T2_humidity_bis,    H3 := PLC_T2_humidity_ext    );
        Thermostat_2( N := 2,
		             ES := PLC_T2_enabled_sensors,        NT := PLC_T2_nighttime,
                    T_1 := PLC_T2_temperature,           T_2 := PLC_T2_temperature_bis,
                    H_1 := PLC_T2_humidity,              H_2 := PLC_T2_humidity_bis,
					M_W := PLC_T2_max_request_W,         A_W := PLC_EP_T2_assigned_W, PRW := PLC_T2_requested_W, SRW := SRV_T2_requested_W,
                    TSP := PLC_T2_temperature_setpoint, TSPN := PLC_T2_temperature_setpoint_nt,
                    HSP := PLC_T2_humidity_setpoint,    HSPN := PLC_T2_humidity_setpoint_nt,
             PLC_STATUS := PLC_T2_heating_status,  PLC_TIMER := PLC_T2_heating_timer, PLC_HEATING := PLC_T2_heating,
             SRV_STATUS := SRV_T2_heating_status,  SRV_TIMER := SRV_T2_heating_timer, SRV_HEATING := SRV_T2_heating,
			         DH := PLC_T2_daily_heating_s,        MH := PLC_T2_monthly_heating_s);
    end_if;

    if PLC_Iam_T3 then
        Tn_Watchdog();
        FilteredSensors_3(   n := 3,              ES:= PLC_T3_enabled_sensors,
                       T1 := PLC_T3_temperature, T2 := PLC_T3_temperature_bis, T3 := PLC_T3_temperature_ext,
                       H1 := PLC_T3_humidity,    H2 := PLC_T3_humidity_bis,    H3 := PLC_T3_humidity_ext    );
        Thermostat_3( N := 3,
		             ES := PLC_T3_enabled_sensors,        NT := PLC_T3_nighttime,
                    T_1 := PLC_T3_temperature,           T_2 := PLC_T3_temperature_bis,
                    H_1 := PLC_T3_humidity,              H_2 := PLC_T3_humidity_bis,
					M_W := PLC_T3_max_request_W,         A_W := PLC_EP_T3_assigned_W, PRW := PLC_T3_requested_W, SRW := SRV_T3_requested_W,
                    TSP := PLC_T3_temperature_setpoint, TSPN := PLC_T3_temperature_setpoint_nt,
                    HSP := PLC_T3_humidity_setpoint,    HSPN := PLC_T3_humidity_setpoint_nt,
             PLC_STATUS := PLC_T3_heating_status,  PLC_TIMER := PLC_T3_heating_timer, PLC_HEATING := PLC_T3_heating,
             SRV_STATUS := SRV_T3_heating_status,  SRV_TIMER := SRV_T3_heating_timer, SRV_HEATING := SRV_T3_heating,
			         DH := PLC_T3_daily_heating_s,        MH := PLC_T3_monthly_heating_s);
    end_if;

    if PLC_Iam_T4 then
        Tn_Watchdog();
        FilteredSensors_4(   n := 4,              ES:= PLC_T4_enabled_sensors,
                       T1 := PLC_T4_temperature, T2 := PLC_T4_temperature_bis, T3 := PLC_T4_temperature_ext,
                       H1 := PLC_T4_humidity,    H2 := PLC_T4_humidity_bis,    H3 := PLC_T4_humidity_ext    );
        Thermostat_4( N := 4,
		             ES := PLC_T4_enabled_sensors,        NT := PLC_T4_nighttime,
                    T_1 := PLC_T4_temperature,           T_2 := PLC_T4_temperature_bis,
                    H_1 := PLC_T4_humidity,              H_2 := PLC_T4_humidity_bis,
					M_W := PLC_T4_max_request_W,         A_W := PLC_EP_T4_assigned_W, PRW := PLC_T4_requested_W, SRW := SRV_T4_requested_W,
                    TSP := PLC_T4_temperature_setpoint, TSPN := PLC_T4_temperature_setpoint_nt,
                    HSP := PLC_T4_humidity_setpoint,    HSPN := PLC_T4_humidity_setpoint_nt,
             PLC_STATUS := PLC_T4_heating_status,  PLC_TIMER := PLC_T4_heating_timer, PLC_HEATING := PLC_T4_heating,
             SRV_STATUS := SRV_T4_heating_status,  SRV_TIMER := SRV_T4_heating_timer, SRV_HEATING := SRV_T4_heating,
			         DH := PLC_T4_daily_heating_s,        MH := PLC_T4_monthly_heating_s);
    end_if;

    if PLC_Iam_T5 then
        Tn_Watchdog();
        FilteredSensors_5(   n := 5,              ES:= PLC_T5_enabled_sensors,
                       T1 := PLC_T5_temperature, T2 := PLC_T5_temperature_bis, T3 := PLC_T5_temperature_ext,
                       H1 := PLC_T5_humidity,    H2 := PLC_T5_humidity_bis,    H3 := PLC_T5_humidity_ext    );
        Thermostat_5( N := 5,
		             ES := PLC_T5_enabled_sensors,        NT := PLC_T5_nighttime,
                    T_1 := PLC_T5_temperature,           T_2 := PLC_T5_temperature_bis,
                    H_1 := PLC_T5_humidity,              H_2 := PLC_T5_humidity_bis,
					M_W := PLC_T5_max_request_W,         A_W := PLC_EP_T5_assigned_W, PRW := PLC_T5_requested_W, SRW := SRV_T5_requested_W,
                    TSP := PLC_T5_temperature_setpoint, TSPN := PLC_T5_temperature_setpoint_nt,
                    HSP := PLC_T5_humidity_setpoint,    HSPN := PLC_T5_humidity_setpoint_nt,
             PLC_STATUS := PLC_T5_heating_status,  PLC_TIMER := PLC_T5_heating_timer, PLC_HEATING := PLC_T5_heating,
             SRV_STATUS := SRV_T5_heating_status,  SRV_TIMER := SRV_T5_heating_timer, SRV_HEATING := SRV_T5_heating,
			         DH := PLC_T5_daily_heating_s,        MH := PLC_T5_monthly_heating_s);
    end_if;

    if PLC_Iam_T6 then
        Tn_Watchdog();
        FilteredSensors_6(   n := 6,              ES:= PLC_T6_enabled_sensors,
                       T1 := PLC_T6_temperature, T2 := PLC_T6_temperature_bis, T3 := PLC_T6_temperature_ext,
                       H1 := PLC_T6_humidity,    H2 := PLC_T6_humidity_bis,    H3 := PLC_T6_humidity_ext    );
        Thermostat_6( N := 6,
		             ES := PLC_T6_enabled_sensors,        NT := PLC_T6_nighttime,
                    T_1 := PLC_T6_temperature,           T_2 := PLC_T6_temperature_bis,
                    H_1 := PLC_T6_humidity,              H_2 := PLC_T6_humidity_bis,
					M_W := PLC_T6_max_request_W,         A_W := PLC_EP_T6_assigned_W, PRW := PLC_T6_requested_W, SRW := SRV_T6_requested_W,
                    TSP := PLC_T6_temperature_setpoint, TSPN := PLC_T6_temperature_setpoint_nt,
                    HSP := PLC_T6_humidity_setpoint,    HSPN := PLC_T6_humidity_setpoint_nt,
             PLC_STATUS := PLC_T6_heating_status,  PLC_TIMER := PLC_T6_heating_timer, PLC_HEATING := PLC_T6_heating,
             SRV_STATUS := SRV_T6_heating_status,  SRV_TIMER := SRV_T6_heating_timer, SRV_HEATING := SRV_T6_heating,
			         DH := PLC_T6_daily_heating_s,        MH := PLC_T6_monthly_heating_s);
    end_if;

END_PROGRAM

