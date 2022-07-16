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

PROGRAM Init
#import "Crosstable.gvl"
#import "Resource1.gvl"

	PLC_PLC_Version := 1201;

	(* Fast I/O on TPX1043_03_C only *)
	if PLC_PRODUCT_ID = 16#1043030C then
	    PLC_FastIO_Ena := 16#000000FF;
	    PLC_FastIO_Dir := 16#000000F0;
	end_if;

	(* NB: in hmi.ini: disable_all_nodes=true *)

	if Vbase_Ventola < 100 then Vbase_Ventola := 100; end_if;

	(* TCP0..TCP7 *)
	if (PLC_EP_exists     and not PLC_Iam_EP) then NODE_01_STATUS := 1; end_if;
	if (PLC_Tn_count >= 1 and not PLC_Iam_T1) then NODE_02_STATUS := 1; end_if;
	if (PLC_Tn_count >= 2 and not PLC_Iam_T2) then NODE_03_STATUS := 1; end_if;
	if (PLC_Tn_count >= 3 and not PLC_Iam_T3) then NODE_04_STATUS := 1; end_if;
	if (PLC_Tn_count >= 4 and not PLC_Iam_T4) then NODE_05_STATUS := 1; end_if;
	if (PLC_Tn_count >= 5 and not PLC_Iam_T5) then NODE_06_STATUS := 1; end_if;
	if (PLC_Tn_count >= 6 and not PLC_Iam_T6) then NODE_07_STATUS := 1; end_if;
	if (PLC_BA_exists     and not PLC_Iam_BA) then NODE_08_STATUS := 1; end_if;

    if (PLC_Iam_EP or PLC_Iam_T1 or PLC_Iam_T2 or PLC_Iam_T3 or PLC_Iam_T4 or PLC_Iam_T5 or PLC_Iam_T6 or PLC_Iam_BA) then
		(* TCPS *)
		NODE_09_STATUS := 1;
	end_if;

	if PLC_Iam_EP then (* --------------------------------------------------------- *)

		(* INPUT: wattmeters *)
		if PLC_EP_enabled_wattmeters >= 1 then
			if PLC_control_type = ControlType_1 or PLC_control_type = ControlType_7 or PLC_control_type = ControlType_12 or PLC_control_type = ControlType_13 or PLC_control_type = ControlType_14 or PLC_control_type = ControlType_15 then
				(* Finder 7M.24/7M.38 wattmeters 1..12 on RTU0 *)
				if PLC_EP_enabled_wattmeters >=  1 then NODE_15_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  2 then NODE_16_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  3 then NODE_17_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  4 then NODE_18_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  5 then NODE_19_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  6 then NODE_20_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  7 then NODE_21_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  8 then NODE_22_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  9 then NODE_23_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >= 10 then NODE_24_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >= 11 then NODE_25_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >= 12 then NODE_26_STATUS := 1; end_if;
			elsif PLC_control_type = ControlType_6 then
				(* Finder 7E.64 wattmeters 1..12 on RTU0 *)
				if PLC_EP_enabled_wattmeters >=  1 then NODE_32_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  2 then NODE_33_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  3 then NODE_34_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  4 then NODE_35_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  5 then NODE_36_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  6 then NODE_37_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  7 then NODE_38_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  8 then NODE_39_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >=  9 then NODE_40_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >= 10 then NODE_41_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >= 11 then NODE_42_STATUS := 1; end_if;
				if PLC_EP_enabled_wattmeters >= 12 then NODE_43_STATUS := 1; end_if;
			end_if;
		end_if;

		(* OUTPUT: relays *)
		if abs(PLC_EP_enabled_relays) >= 1 then
			if PLC_control_type = ControlType_1 then
				if PLC_PRODUCT_ID = 16#1043030C then
					(* Fast I/O on GPIO *);
				elsif PLC_PRODUCT_ID = 16#100704AD or PLC_PRODUCT_ID = 16#100704AE or PLC_PRODUCT_ID = 16#100704AA or PLC_PRODUCT_ID = 16#100704AC then
					(* TPAC1007_04_AD/E/A/C Local I/O on RTU3 *)
					NODE_31_STATUS := 1;
				else
					; (* TP.. *)
				end_if; 
			elsif PLC_control_type = ControlType_7 then
				(* Fast I/O on GPIO *);
			elsif PLC_control_type = ControlType_12 then
				(* Fast I/O on GPIO *);
			elsif PLC_control_type = ControlType_13 then
				(* TPAC1007_04_AD Local I/O on RTU3 *)
				NODE_31_STATUS := 1;
			elsif PLC_control_type = ControlType_6 then
				(* MPNC base on RTU0 *)
				NODE_27_STATUS := 1;
			elsif PLC_control_type = ControlType_14 then
				(* MPNC DO16 "C" on RTU0 *)
				NODE_27_STATUS := 1;
			end_if;
		end_if;

	end_if;

	if PLC_Iam_T1 then (* --------------------------------------------------------- *)

		(* INPUT: sensors *)
		if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 or PLC_control_type = ControlType_13 or PLC_control_type = ControlType_15 then			
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O AI1..3 on RTU3 *)
		elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 or PLC_control_type = ControlType_12 then
			NODE_28_STATUS := 1; (* first (T,H) sensor on RTU3 *)
			if PLC_T1_enabled_sensors <= -2 then NODE_29_STATUS := 1; end_if; (* second (T,H) sensor on RTU3 *)
			if PLC_T1_enabled_sensors <= -3 then NODE_30_STATUS := 1; end_if; (* third (T,H) sensor on RTU3 *)
		elsif PLC_control_type = ControlType_14 or PLC_control_type = ControlType_6 then
			NODE_27_STATUS := 1; (* MPNC 4xAI4 on RTU0 *)
		elsif PLC_control_type = ControlType_7 or PLC_control_type = ControlType_10 then
			NODE_13_STATUS := 1; (* MPNE_C AI2+AO1 on RTU0 *)
		elsif PLC_control_type = ControlType_11 then
			NODE_13_STATUS := 1; (* MPNE_C AI2+AO1 on RTU0 *)
		end_if;

		(* INPUT/OUTPUT: lamps *)
		if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO1..5 DI7..11 on RTU3 *)
		elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_10_STATUS := 1; (* Fast I/O FO5..8 FI1..4 on GPIO *)
		else 
			; (* no lamps *)
		end_if;

		(* OUTPUT: thermo *)
		if PLC_control_type = ControlType_3 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO6 on RTU3 *)
		elsif PLC_control_type = ControlType_4 or PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_10_STATUS := 1; (* ARQ01 on RTU0 *)
		elsif PLC_control_type = ControlType_6 then
			NODE_27_STATUS := 1; (* MPNC DO5..8 on RTU0 *)
		elsif PLC_control_type = ControlType_14 then
			NODE_27_STATUS := 1; (* MPNC DO1..4 on RTU0 *)
		elsif PLC_control_type = ControlType_7 or PLC_control_type = ControlType_10 then
			NODE_13_STATUS := 1; (* MPNE_C DO1..4 on RTU0 *)
		elsif PLC_control_type = ControlType_12 then
			; (* Fast I/O FO8 on GPIO *)
		elsif PLC_control_type = ControlType_13 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO1..3+4 on RTU3 *)
		elsif PLC_control_type = ControlType_15 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO8 on RTU3 *)
		end_if;

		(* retentives *)

		SRV_T1_temperature_setpoint := Tn_CheckSetPoint_T(PLC_T1_temperature_setpoint);
		SRV_T1_temperature_setpoint_nt := Tn_CheckSetPoint_T(PLC_T1_temperature_setpoint_nt);
		SRV_T1_humidity_setpoint := Tn_CheckSetPoint_H(PLC_T1_humidity_setpoint);
		SRV_T1_humidity_setpoint_nt := Tn_CheckSetPoint_H(PLC_T1_humidity_setpoint_nt);
		SRV_T1_heating_status := PLC_T1_heating_status;
		PLC_T1_sunrise := PLC_sunrise; PLC_T1_sunset := PLC_sunset;
		SRV_T1_sunrise := PLC_sunrise; SRV_T1_sunset := PLC_sunset;
		SRV_T1_lamp_1 := PLC_T1_lamp_1; SRV_T1_lamp_2 := PLC_T1_lamp_2; SRV_T1_lamp_3 := PLC_T1_lamp_3; SRV_T1_lamp_4 := PLC_T1_lamp_4; SRV_T1_lamp_5 := PLC_T1_lamp_5;
	end_if;

	if PLC_Iam_T2 then (* --------------------------------------------------------- *)

		(* INPUT: sensors *)
		if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 or PLC_control_type = ControlType_13 or PLC_control_type = ControlType_15 then			
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O AI1..3 on RTU3 *)
		elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_28_STATUS := 1; (* first (T,H) sensor on RTU3 *)
			if PLC_T2_enabled_sensors <= -2 then NODE_29_STATUS := 1; end_if; (* second (T,H) sensor on RTU3 *)
			if PLC_T2_enabled_sensors <= -3 then NODE_30_STATUS := 1; end_if; (* third (T,H) sensor on RTU3 *)
		elsif PLC_control_type = ControlType_14 or PLC_control_type = ControlType_6 then
			NODE_27_STATUS := 1; (* MPNC 4xAI4 on RTU0 *)
		elsif PLC_control_type = ControlType_7 or PLC_control_type = ControlType_10 then
			NODE_13_STATUS := 1; (* MPNE_C AI2+AO1 on RTU0 *)
		elsif PLC_control_type = ControlType_11 then
			NODE_13_STATUS := 1; (* MPNE_C AI2+AO1 on RTU0 *)
		end_if;

		(* INPUT/OUTPUT: lamps *)
		if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO1..5 DI7..11 on RTU3 *)
		elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_10_STATUS := 1; (* Fast I/O FO5..8 FI1..4 on GPIO *)
		else 
			; (* no lamps *)
		end_if;

		(* OUTPUT: thermo *)
		if PLC_control_type = ControlType_3 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO6 on RTU3 *)
		elsif PLC_control_type = ControlType_4 or PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_10_STATUS := 1; (* ARQ01 on RTU0 *)
		elsif PLC_control_type = ControlType_6 then
			NODE_27_STATUS := 1; (* MPNC DO5..8 on RTU0 *)
		elsif PLC_control_type = ControlType_14 then
			NODE_27_STATUS := 1; (* MPNC DO1..4 on RTU0 *)
		elsif PLC_control_type = ControlType_7 or PLC_control_type = ControlType_10 then
			NODE_13_STATUS := 1; (* MPNE_C DO1..4 on RTU0 *)
		elsif PLC_control_type = ControlType_13 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO1..3+4 on RTU3 *)
		elsif PLC_control_type = ControlType_15 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO8 on RTU3 *)
		end_if;

		(* retentives *)
		SRV_T2_temperature_setpoint := Tn_CheckSetPoint_T(PLC_T2_temperature_setpoint);
		SRV_T2_temperature_setpoint_nt := Tn_CheckSetPoint_T(PLC_T2_temperature_setpoint_nt);
		SRV_T2_humidity_setpoint := Tn_CheckSetPoint_H(PLC_T2_humidity_setpoint);
		SRV_T2_humidity_setpoint_nt := Tn_CheckSetPoint_H(PLC_T2_humidity_setpoint_nt);
		SRV_T2_heating_status := PLC_T2_heating_status;
		PLC_T2_sunrise := PLC_sunrise; PLC_T2_sunset := PLC_sunset;
		SRV_T2_sunrise := PLC_sunrise; SRV_T2_sunset := PLC_sunset;
        SRV_T2_temperature_setpoint_nt := PLC_T2_temperature_setpoint_nt; SRV_T2_humidity_setpoint_nt := PLC_T2_humidity_setpoint_nt;
        SRV_T2_lamp_1 := PLC_T2_lamp_1; SRV_T2_lamp_2 := PLC_T2_lamp_2; SRV_T2_lamp_3 := PLC_T2_lamp_3; SRV_T2_lamp_4 := PLC_T2_lamp_4; SRV_T2_lamp_5 := PLC_T2_lamp_5;
	end_if;

	if PLC_Iam_T3 then (* --------------------------------------------------------- *)

		(* INPUT: sensors *)
		if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 or PLC_control_type = ControlType_13 or PLC_control_type = ControlType_15 then			
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O AI1..3 on RTU3 *)
		elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_28_STATUS := 1; (* first (T,H) sensor on RTU3 *)
			if PLC_T3_enabled_sensors <= -2 then NODE_29_STATUS := 1; end_if; (* second (T,H) sensor on RTU3 *)
			if PLC_T3_enabled_sensors <= -3 then NODE_30_STATUS := 1; end_if; (* third (T,H) sensor on RTU3 *)
		elsif PLC_control_type = ControlType_14 or PLC_control_type = ControlType_6 then
			NODE_27_STATUS := 1; (* MPNC 4xAI4 on RTU0 *)
		elsif PLC_control_type = ControlType_7 or PLC_control_type = ControlType_10 then
			NODE_13_STATUS := 1; (* MPNE_C AI2+AO1 on RTU0 *)
		elsif PLC_control_type = ControlType_11 then
			NODE_14_STATUS := 1; (* MPNE_D AI2+AO1 on RTU0 *)
		end_if;

		(* INPUT/OUTPUT: lamps *)
		if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO1..5 DI7..11 on RTU3 *)
		elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_10_STATUS := 1; (* Fast I/O FO5..8 FI1..4 on GPIO *)
		else 
			; (* no lamps *)
		end_if;

		(* OUTPUT: thermo *)
		if PLC_control_type = ControlType_3 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO6 on RTU3 *)
		elsif PLC_control_type = ControlType_4 or PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_10_STATUS := 1; (* ARQ01 on RTU0 *)
		elsif PLC_control_type = ControlType_6 then
			NODE_27_STATUS := 1; (* MPNC DO5..8 on RTU0 *)
		elsif PLC_control_type = ControlType_14 then
			NODE_27_STATUS := 1; (* MPNC DO1..4 on RTU0 *)
		elsif PLC_control_type = ControlType_7 or PLC_control_type = ControlType_10 then
			NODE_13_STATUS := 1; (* MPNE_C DO1..4 on RTU0 *)
		elsif PLC_control_type = ControlType_13 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO1..3+4 on RTU3 *)
		elsif PLC_control_type = ControlType_15 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO8 on RTU3 *)
		end_if;

		(* retentives *)
		SRV_T3_temperature_setpoint := Tn_CheckSetPoint_T(PLC_T3_temperature_setpoint);
		SRV_T3_temperature_setpoint_nt := Tn_CheckSetPoint_T(PLC_T3_temperature_setpoint_nt);
		SRV_T3_humidity_setpoint := Tn_CheckSetPoint_H(PLC_T3_humidity_setpoint);
		SRV_T3_humidity_setpoint_nt := Tn_CheckSetPoint_H(PLC_T3_humidity_setpoint_nt);
		SRV_T3_heating_status := PLC_T3_heating_status;
		PLC_T3_sunrise := PLC_sunrise; PLC_T3_sunset := PLC_sunset;
		SRV_T3_sunrise := PLC_sunrise; SRV_T3_sunset := PLC_sunset;
        SRV_T3_temperature_setpoint_nt := PLC_T3_temperature_setpoint_nt; SRV_T3_humidity_setpoint_nt := PLC_T3_humidity_setpoint_nt;
        SRV_T3_lamp_1 := PLC_T3_lamp_1; SRV_T3_lamp_2 := PLC_T3_lamp_2; SRV_T3_lamp_3 := PLC_T3_lamp_3; SRV_T3_lamp_4 := PLC_T3_lamp_4; SRV_T3_lamp_5 := PLC_T3_lamp_5;
	end_if;

	if PLC_Iam_T4 then (* --------------------------------------------------------- *)

		(* INPUT: sensors *)
		if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 (*or PLC_control_type = ControlType_13*) or PLC_control_type = ControlType_15 then			
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O AI1..3 on RTU3 *)
		elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_28_STATUS := 1; (* first (T,H) sensor on RTU3 *)
			if PLC_T4_enabled_sensors <= -2 then NODE_29_STATUS := 1; end_if; (* second (T,H) sensor on RTU3 *)
			if PLC_T4_enabled_sensors <= -3 then NODE_30_STATUS := 1; end_if; (* third (T,H) sensor on RTU3 *)
		elsif PLC_control_type = ControlType_6 then
			NODE_27_STATUS := 1; (* MPNC base AI1,2 on RTU0 *)
		elsif PLC_control_type = ControlType_14 or PLC_control_type = ControlType_6 then
			NODE_27_STATUS := 1; (* MPNC 4xAI4 on RTU0 *)
		elsif PLC_control_type = ControlType_7 or PLC_control_type = ControlType_10 then
			NODE_13_STATUS := 1; (* MPNE_C AI2+AO1 on RTU0 *)
		elsif PLC_control_type = ControlType_11 then
			NODE_14_STATUS := 1; (* MPNE_D AI2+AO1 on RTU0 *)
		end_if;

		(* INPUT/OUTPUT: lamps *)
		if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO1..5 DI7..11 on RTU3 *)
		elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_10_STATUS := 1; (* Fast I/O FO5..8 FI1..4 on GPIO *)
		else 
			; (* no lamps *)
		end_if;

		(* OUTPUT: thermo *)
		if PLC_control_type = ControlType_3 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO6 on RTU3 *)
		elsif PLC_control_type = ControlType_4 or PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_10_STATUS := 1; (* ARQ01 on RTU0 *)
		elsif PLC_control_type = ControlType_6 then
			NODE_27_STATUS := 1; (* MPNC DO5..8 on RTU0 *)
		elsif PLC_control_type = ControlType_14 then
			NODE_27_STATUS := 1; (* MPNC DO1..4 on RTU0 *)
		elsif PLC_control_type = ControlType_7 or PLC_control_type = ControlType_10 then
			NODE_13_STATUS := 1; (* MPNE_C DO1..4 on RTU0 *)
		elsif PLC_control_type = ControlType_13 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO1..3+4 on RTU3 *)
		elsif PLC_control_type = ControlType_15 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO8 on RTU3 *)
		end_if;

		(* retentives *)
		SRV_T4_temperature_setpoint := Tn_CheckSetPoint_T(PLC_T4_temperature_setpoint);
		SRV_T4_temperature_setpoint_nt := Tn_CheckSetPoint_T(PLC_T4_temperature_setpoint_nt);
		SRV_T4_humidity_setpoint := Tn_CheckSetPoint_H(PLC_T4_humidity_setpoint);
		SRV_T4_humidity_setpoint_nt := Tn_CheckSetPoint_H(PLC_T4_humidity_setpoint_nt);
		SRV_T4_heating_status := PLC_T4_heating_status;
		PLC_T4_sunrise := PLC_sunrise; PLC_T4_sunset := PLC_sunset;
		SRV_T4_sunrise := PLC_sunrise; SRV_T4_sunset := PLC_sunset;
        SRV_T4_temperature_setpoint_nt := PLC_T4_temperature_setpoint_nt; SRV_T4_humidity_setpoint_nt := PLC_T4_humidity_setpoint_nt;
        SRV_T4_lamp_1 := PLC_T4_lamp_1; SRV_T4_lamp_2 := PLC_T4_lamp_2; SRV_T4_lamp_3 := PLC_T4_lamp_3; SRV_T4_lamp_4 := PLC_T4_lamp_4; SRV_T4_lamp_5 := PLC_T4_lamp_5;
	end_if;

	if PLC_Iam_T5 then (* --------------------------------------------------------- *)

		(* INPUT: sensors *)
		if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 (*or PLC_control_type = ControlType_13*) or PLC_control_type = ControlType_15 then			
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O AI1..3 on RTU3 *)
		elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_28_STATUS := 1; (* first (T,H) sensor on RTU3 *)
			if PLC_T5_enabled_sensors <= -2 then NODE_29_STATUS := 1; end_if; (* second (T,H) sensor on RTU3 *)
			if PLC_T5_enabled_sensors <= -3 then NODE_30_STATUS := 1; end_if; (* third (T,H) sensor on RTU3 *)
		elsif PLC_control_type = ControlType_7 then
			NODE_28_STATUS := 1; (* first (T,H) sensor on RTU3 *)
		elsif PLC_control_type = ControlType_11 or PLC_control_type = ControlType_14 or PLC_control_type = ControlType_6 then
			; (* T1..T4 only *)
		elsif PLC_control_type = ControlType_10 then
			NODE_13_STATUS := 1; (* MPNE_C AI2+AO1 on RTU0 *)
		end_if;

		(* INPUT/OUTPUT: lamps *)
		if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO1..5 DI7..11 on RTU3 *)
		elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_10_STATUS := 1; (* Fast I/O FO5..8 FI1..4 on GPIO *)
		else 
			; (* no lamps *)
		end_if;

		(* OUTPUT: thermo *)
		if PLC_control_type = ControlType_3 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO6 on RTU3 *)
		elsif PLC_control_type = ControlType_4 or PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_10_STATUS := 1; (* ARQ01 on RTU0 *)
		elsif PLC_control_type = ControlType_7 then
			NODE_13_STATUS := 1; (* MPNE_C DO5 on RTU0 *)
		elsif PLC_control_type = ControlType_11 or PLC_control_type = ControlType_14 or PLC_control_type = ControlType_6 then
			; (* T1..T4 only *)
		elsif PLC_control_type = ControlType_10 then
			NODE_13_STATUS := 1; (* MPNE_C DO1 on RTU0 *)
		elsif PLC_control_type = ControlType_13 then
			; (* no output *)
		elsif PLC_control_type = ControlType_15 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO8 on RTU3 *)
		end_if;

		(* retentives *)
		SRV_T5_temperature_setpoint := Tn_CheckSetPoint_T(PLC_T5_temperature_setpoint);
		SRV_T5_temperature_setpoint_nt := Tn_CheckSetPoint_T(PLC_T5_temperature_setpoint_nt);
		SRV_T5_humidity_setpoint := Tn_CheckSetPoint_H(PLC_T5_humidity_setpoint);
		SRV_T5_humidity_setpoint_nt := Tn_CheckSetPoint_H(PLC_T5_humidity_setpoint_nt);
		SRV_T5_heating_status := PLC_T5_heating_status;
		PLC_T5_sunrise := PLC_sunrise; PLC_T5_sunset := PLC_sunset;
		SRV_T5_sunrise := PLC_sunrise; SRV_T5_sunset := PLC_sunset;
        SRV_T5_temperature_setpoint_nt := PLC_T5_temperature_setpoint_nt; SRV_T5_humidity_setpoint_nt := PLC_T5_humidity_setpoint_nt;
        SRV_T5_lamp_1 := PLC_T5_lamp_1; SRV_T5_lamp_2 := PLC_T5_lamp_2; SRV_T5_lamp_3 := PLC_T5_lamp_3; SRV_T5_lamp_4 := PLC_T5_lamp_4; SRV_T5_lamp_5 := PLC_T5_lamp_5;
	end_if;

	if PLC_Iam_T6 then (* --------------------------------------------------------- *)

		(* INPUT: sensors *)
		if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 (*or PLC_control_type = ControlType_13*) or PLC_control_type = ControlType_15 then			
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O AI1..3 on RTU3 *)
		elsif PLC_control_type = ControlType_13 then
			; (* T1..T5 only *)
		elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_28_STATUS := 1; (* first (T,H) sensor on RTU3 *)
			if PLC_T6_enabled_sensors <= -2 then NODE_29_STATUS := 1; end_if; (* second (T,H) sensor on RTU3 *)
			if PLC_T6_enabled_sensors <= -3 then NODE_30_STATUS := 1; end_if; (* third (T,H) sensor on RTU3 *)
		elsif PLC_control_type = ControlType_7 then
			NODE_29_STATUS := 1; (* second (T,H) sensor on RTU3 *)
		elsif PLC_control_type = ControlType_11 or PLC_control_type = ControlType_14 or PLC_control_type = ControlType_6 then
			; (* T1..T4 only *)
		elsif PLC_control_type = ControlType_10 then
			NODE_13_STATUS := 1; (* MPNE_C AI2+AO1 on RTU0 *)
		end_if;

		(* INPUT/OUTPUT: lamps *)
		if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO1..5 DI7..11 on RTU3 *)
		elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_10_STATUS := 1; (* Fast I/O FO5..8 FI1..4 on GPIO *)
		else 
			; (* no lamps *)
		end_if;

		(* OUTPUT: thermo *)
		if PLC_control_type = ControlType_3 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO6 on RTU3 *)
		elsif PLC_control_type = ControlType_4 or PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
			NODE_10_STATUS := 1; (* ARQ01 on RTU0 *)
		elsif PLC_control_type = ControlType_7 then
			NODE_13_STATUS := 1; (* MPNE_C DO6 on RTU0 *)
		elsif PLC_control_type = ControlType_11 or PLC_control_type = ControlType_14 or PLC_control_type = ControlType_6 then
			; (* T1..T4 only *)
		elsif PLC_control_type = ControlType_10 then
			NODE_13_STATUS := 1; (* MPNE_C DO1 on RTU0 *)
		elsif PLC_control_type = ControlType_13 then
			; (* T1..T5 only *)
		elsif PLC_control_type = ControlType_15 then
			NODE_31_STATUS := 1; (* TPAC1007_04_AD Local I/O DO8 on RTU3 *)
		end_if;

		(* retentives *)
		SRV_T6_temperature_setpoint := Tn_CheckSetPoint_T(PLC_T6_temperature_setpoint);
		SRV_T6_temperature_setpoint_nt := Tn_CheckSetPoint_T(PLC_T6_temperature_setpoint_nt);
		SRV_T6_humidity_setpoint := Tn_CheckSetPoint_H(PLC_T6_humidity_setpoint);
		SRV_T6_humidity_setpoint_nt := Tn_CheckSetPoint_H(PLC_T6_humidity_setpoint_nt);
		SRV_T6_heating_status := PLC_T6_heating_status;
		PLC_T6_sunrise := PLC_sunrise; PLC_T6_sunset := PLC_sunset;
		SRV_T6_sunrise := PLC_sunrise; SRV_T6_sunset := PLC_sunset;
        SRV_T6_temperature_setpoint_nt := PLC_T6_temperature_setpoint_nt; SRV_T6_humidity_setpoint_nt := PLC_T6_humidity_setpoint_nt;
        SRV_T6_lamp_1 := PLC_T6_lamp_1; SRV_T6_lamp_2 := PLC_T6_lamp_2; SRV_T6_lamp_3 := PLC_T6_lamp_3; SRV_T6_lamp_4 := PLC_T6_lamp_4; SRV_T6_lamp_5 := PLC_T6_lamp_5;
	end_if;

    if (PLC_Iam_BA) then (* --------------------------------------------------------- *)

		PLC_BA_just_started := true;
		if PLC_BA_daytime_bitmask = 0 and PLC_BA_nighttime_bitmask = 0 and PLC_BA_everything_bitmask = 0 then
			if PLC_control_type = ControlType_6 then
				PLC_BA_daytime_bitmask := ALARM_MASK_DAYTIME_DEFAULT_6;
				PLC_BA_nighttime_bitmask := ALARM_MASK_NIGHTTIME_DEFAULT_6;
				PLC_BA_everything_bitmask := ALARM_MASK_EVERYTHING_DEFAULT_6;
			elsif PLC_control_type = ControlType_7 or PLC_control_type = ControlType_12 or PLC_control_type = ControlType_13 then
				PLC_BA_daytime_bitmask := ALARM_MASK_DAYTIME_DEFAULT_3;
				PLC_BA_nighttime_bitmask := ALARM_MASK_NIGHTTIME_DEFAULT_3;
				PLC_BA_everything_bitmask := ALARM_MASK_EVERYTHING_DEFAULT_3;
			else
				PLC_BA_daytime_bitmask := ALARM_MASK_DAYTIME_DEFAULT;
				PLC_BA_nighttime_bitmask := ALARM_MASK_NIGHTTIME_DEFAULT;
				PLC_BA_everything_bitmask := ALARM_MASK_EVERYTHING_DEFAULT;
			end_if;
		end_if;
		if PLC_BA_config_index >= ALARM_INDEX_COUNT then
			PLC_BA_config_index := ALARM_INDEX_NOTHING;
		end_if;

		if PLC_control_type = ControlType_2 then
			(* MPNE_A, MPNE_B on RTU0 *)
			if (PLC_BA_enabled_sensors >=  1) then NODE_11_STATUS := 1; end_if;
	        if (PLC_BA_enabled_sensors >= 17) then NODE_12_STATUS := 1; end_if;
			if PLC_PRODUCT_ID = 16#100704AD or PLC_PRODUCT_ID = 16#100704AE or PLC_PRODUCT_ID = 16#100704AA or PLC_PRODUCT_ID = 16#100704AC then
				(* leds and commands Local I/O on RTU3 *)
				NODE_31_STATUS := 1;
			else
				(* Fast I/O on GPIO *);
			end_if;
		elsif PLC_control_type = ControlType_7 then
			;(* Fast I/O on GPIO *)
		elsif PLC_control_type = ControlType_12 then
			;(* Fast I/O on GPIO *)
		elsif PLC_control_type = ControlType_13 then
			(* TPAC1007_04_AD Local I/O on RTU3 *)
			NODE_31_STATUS := 1;
		elsif PLC_control_type = ControlType_6 then
			(* MPNC DI16 "A,B" + DO16 "A" on RTU0 *)
			(* no leds and commands *)
			NODE_27_STATUS := 1;
		elsif PLC_control_type = ControlType_14 then
			(* MPNC DI16 "A,B" + DO16 "A,B" on RTU0 *)
			(* leds and commands on MPNC DO16 "C" *)
			NODE_27_STATUS := 1;
		end_if;

	end_if;

END_PROGRAM

