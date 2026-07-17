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

FUNCTION_BLOCK Thermostat
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
	N : UINT;   (* Tn                             *)
    ES : INT;   (* PLC_Tn_enabled_sensors         *)
	NT : BOOL;  (* PLC_Tn_nighttime               *)

    T_1 : INT;  (* PLC_Tn_temperature             *)
    T_2 : INT;  (* PLC_Tn_temperature_bis         *)

    H_1 : INT;  (* PLC_Tn_humidity                *)
    H_2 : INT;  (* PLC_Tn_humidity_bis            *)

	M_W : UINT; (* PLC_Tn_max_request_W           *)
	A_W : UINT; (* PLC_EP_Tn_assigned_W           *)
END_VAR
VAR_IN_OUT
	PRW : UINT; (* PLC_Tn_requested_W             *)
	SRW : UINT; (* SRV_Tn_requested_W             *)

    TSP : INT;  (* PLC_Tn_temperature_setpoint    *)
    TSPN: INT;  (* PLC_Tn_temperature_setpoint_nt *)

    HSP : INT;  (* PLC_Tn_humidity_setpoint       *)
    HSPN: INT;  (* PLC_Tn_humidity_setpoint_nt    *)

    PLC_STATUS  : INT ; (* PLC_Tn_heating_status  *)
    PLC_TIMER   : INT ; (* PLC_Tn_heating_timer   *)
    PLC_HEATING : BOOL; (* PLC_Tn_heating         *)

    SRV_STATUS  : INT ; (* SRV_Tn_heating_status  *)
    SRV_TIMER   : INT ; (* SRV_Tn_heating_timer   *)
    SRV_HEATING : BOOL; (* SRV_Tn_heating         *)

    DH  : UDINT ; (* PLC_Tn_daily_heating_s       *)
    MH  : UDINT ; (* PLC_Tn_monthly_heating_s     *)
END_VAR
VAR
	HEATING : BOOL;
	TIMER : INT;
	STATUS : INT;
	A_TSP : INT; (* actual temperature setpoint, changed by ECONOMY, COMFORT, BOOST and nightime *)
	A_HSP : INT; (* actual humidity setpoint, NOT changed by ECONOMY, COMFORT, BOOST and nightime *)
	last_R : UINT := 0;
END_VAR;

	STATUS := PLC_STATUS;
	TIMER := PLC_TIMER;
	HEATING := PLC_HEATING;

	(* ----------------- 1/4 common ----------------- *)

	(* check nightime and limits *)
	if NT then
		A_TSP := Tn_CheckSetpoint_T(TSPN);
		A_HSP := Tn_CheckSetpoint_H(HSPN);
		(* NB: may change setpoints <---------------- *)
		if TSPN <> A_TSP then TSPN := A_TSP; end_if;
		if HSPN <> A_HSP then HSPN := A_HSP; end_if;
	else
		A_TSP := Tn_CheckSetpoint_T(TSP);
		A_HSP := Tn_CheckSetpoint_H(HSP);
		(* NB: may change setpoints <---------------- *)
		if TSP <> A_TSP then TSP := A_TSP; end_if;
		if HSP <> A_HSP then HSP := A_HSP; end_if;
	end_if;

	(* check timer *)
	if STATUS > HEATING_AUTO then
		if TIMER > 0 then
		    TIMER := TIMER - 1;
		else
			STATUS := HEATING_AUTO;
			TIMER := 0;
		end_if;
	end_if;

	(* check special states *)
	case STATUS of
	HEATING_AUTO:
		A_TSP := A_TSP;
	HEATING_ECONOMY:
		A_TSP := A_TSP - 20; (* -2°C*) (* ex: -10% A_TSP - (A_TSP * 100) / 10; *)
	HEATING_COMFORT:
		A_TSP := A_TSP + 20; (* +2°C*) (* ex: +10% A_TSP + (A_TSP * 100) / 10; *)
	HEATING_BOOST:
		A_TSP := TemperatureSetPoint_max;
	else
		;
	end_case;

	(* check limits after changes *)
	A_TSP := Tn_CheckSetpoint_T(A_TSP);
	A_HSP := Tn_CheckSetpoint_H(A_HSP);

	(* ----------------- 2/4 common control ----------------- *)

	if PLC_control_type = ControlType_0 or PLC_control_type = ControlType_1  or PLC_control_type = ControlType_2 then
		(* no thermostat *)
	    HEATING := false;

	elsif ES = 0 or (abs(ES) >= 1 and T_1 = TemperatureErrorValue) or (abs(ES) >= 2 and T_2 = TemperatureErrorValue) then
		(* sensor read error *)
	    HEATING := false;

	elsif (ES <= -1 and H_1 = HumidityErrorValue) or (ES <= -2 and H_2 = HumidityErrorValue) then
		(* sensor read error *)
	    HEATING := false;

	elsif (PLC_control_type = ControlType_6 and n = 4) or (PLC_control_type = ControlType_15 and n = 1) then
		(* differential thermostat (puffer) *)
		if PLC_UPTIME_s <= 25 then
			(* waiting for sensors settling *)
			HEATING := false;
		elsif STATUS >= HEATING_AUTO then
			(* heating enabled *)
			if HEATING then
				(* heating was ON *)
				if T_1 < (T_2 - TemperatureHysteresis) then
					(* puffer is colder than thermo water *)
					HEATING := false;
				end_if;
			else
				(* heating was off *)
				if  T_1 >= (T_2 + TemperatureHysteresis) then
					(* puffer is warmer than thermo water *)
					HEATING := true;
				end_if;
			end_if;
		else
			HEATING := false;
			TIMER := 0;
		end_if;
 
	else
		(* standard thermostat *)
		if PLC_UPTIME_s <= 25 then
			(* waiting for sensors settling *)
			HEATING := false;
		elsif STATUS >= HEATING_AUTO then
			(* heating enabled *)
			if HEATING then
				(* heating was ON *)
				if (ES <= -2)   and ( T_1 >= (A_TSP + TemperatureHysteresis) AND T_2 >= (A_TSP + TemperatureHysteresis) AND H_1 <= (A_HSP - HumidityHysteresis) AND H_2 <= (A_HSP - HumidityHysteresis) ) then
					(* two T,H sensors *)
					HEATING := false;
				elsif (ES = -1) and ( T_1 >= (A_TSP + TemperatureHysteresis)                                            AND H_1 <= (A_HSP - HumidityHysteresis)                                     ) then
					(* one T,H sensor *)
					HEATING := false;
				elsif (ES = 0) then
					(* nothing *)
					HEATING := false;
				elsif (ES = 1)  and ( T_1 >= (A_TSP + TemperatureHysteresis) ) then
					(* one Pt100 *)
					HEATING := false;
				elsif (ES >= 2) and ( T_1 >= (A_TSP + TemperatureHysteresis) AND T_2 >= (A_TSP + TemperatureHysteresis)  ) then
					(* two Pt100s *)
					HEATING := false;
				end_if;
			else
				(* heating was off *)
				if (ES <= -2)   and ( T_1 <= (A_TSP - TemperatureHysteresis) OR T_2 <= (A_TSP - TemperatureHysteresis) OR H_1 >= (A_HSP + HumidityHysteresis) OR H_2 >= (A_HSP + HumidityHysteresis) ) then
					(* two T,H sensors *)
					HEATING := true;
				elsif (ES = -1) and ( T_1 <= (A_TSP - TemperatureHysteresis)                                           OR H_1 >= (A_HSP + HumidityHysteresis)                                    ) then
					(* one T,H sensor *)
					HEATING := true;
				elsif (ES = 0) then
					(* nothing *)
					HEATING := false;
				elsif (ES = 1)  and ( T_1 <= (A_TSP - TemperatureHysteresis) ) then
					(* one Pt100 *)
					HEATING := true;
				elsif (ES >= 2) and ( T_1 <= (A_TSP - TemperatureHysteresis) OR T_2 <= (A_TSP - TemperatureHysteresis) ) then
					(* two Pt100s *)
					HEATING := true;
				end_if;
			end_if;
		else
			HEATING := false;
			TIMER := 0;
		end_if;

	end_if;

	(* ----------------- 3/4 specific control and action ----------------- *)

	if HEATING and Tn_OverHeat(n, T_1, T_2) then
		HEATING := false;
	end_if;

	if M_W = 0 or not PLC_EP_exists then
		(* no load balancing *)
	   	Tn_SetDigOut_thermo(n, HEATING, false, T_1, T_2, last_R);
		if PRW <> 0 then
			PRW := 0; (* PLC_Tn_requested_W := 0 *)
		end_if;

	elsif not PLC_EP_isOK then
		(* safe state *)
		HEATING := false;
	   	Tn_SetDigOut_thermo(n, false, false, T_1, T_2, last_R);

	elsif not HEATING then
		(* simply power off *)
	   	Tn_SetDigOut_thermo(n, false, false, T_1, T_2, last_R);
		PRW := 0; (* PLC_Tn_requested_W *)
		if SRW <> 0 then SRW := 0; end_if; (* SRV_Tn_requested_W *)

	else

		case PLC_EP_tic_in_tac of

	    0: (* request time *)
			PRW := M_W; (* PLC_Tn_requested_W := PLC_Tn_max_request_W *)
			if SRW <> M_W then
				SRW := M_W; (* SRV_Tn_requested_W := PLC_Tn_max_request_W *)
			end_if;
			(* wait, only maintain the current status *)
			Tn_SetDigOut_thermo(n, false, true, T_1, T_2, last_R);

		1: (* transmission time *)
			(* wait, only maintain the current status *)
			Tn_SetDigOut_thermo(n, false, true, T_1, T_2, last_R);

		Decision_TicInTac: (* decision time *)
			(* wait, only maintain the current status *)
			Tn_SetDigOut_thermo(n, false, true, T_1, T_2, last_R);

		3: (* transmission time *)
			(* wait, only maintain the current status *)
			Tn_SetDigOut_thermo(n, false, true, T_1, T_2, last_R);

		4:	(* power off time *)
			if A_W >= M_W then (* PLC_EP_Tn_assigned_W >= PLC_Tn_max_request_W *)
				(* wait, only maintain the current status *)
				Tn_SetDigOut_thermo(n, false, true, T_1, T_2, last_R);
			else
				(* power off *)
			   	Tn_SetDigOut_thermo(n, false, false, T_1, T_2, last_R);
			end_if;

		5:
			(* action time *)
			if A_W >= M_W then (* PLC_EP_Tn_assigned_W >= PLC_Tn_max_request_W *)
			   	Tn_SetDigOut_thermo(n, true, false, T_1, T_2, last_R);
			else
			   	Tn_SetDigOut_thermo(n, false, false, T_1, T_2, last_R);
			end_if;

		6:
			(* action time bis *)
			if A_W >= M_W then (* PLC_EP_Tn_assigned_W >= PLC_Tn_max_request_W *)
			   	Tn_SetDigOut_thermo(n, true, false, T_1, T_2, last_R);
			else
			   	Tn_SetDigOut_thermo(n, false, false, T_1, T_2, last_R);
			end_if;

		end_case;

	end_if;

	(* ----------------- 4/4 update ----------------- *)

	if PLC_STATUS <> STATUS then
		PLC_STATUS := STATUS;
		SRV_STATUS := STATUS;
	end_if;
	if PLC_TIMER <> TIMER then
		PLC_TIMER := TIMER;
		SRV_TIMER := TIMER;
	end_if;
	if PLC_HEATING <> HEATING then
		PLC_HEATING := HEATING;
		SRV_HEATING := HEATING;
	end_if;

	if (PLC_Hours = 0) and (PLC_Minutes = 0) and (PLC_Seconds = 0) then
		DH := 0;
		if PLC_Day = 1 then
			MH := 0;
		end_if;
	elsif HEATING then
		DH := DH + 1;
		MH := MH + 1;
	end_if;

END_FUNCTION_BLOCK
