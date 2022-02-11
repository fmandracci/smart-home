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

FUNCTION BA_CheckSensor
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
	n : UINT;
    konfig : DWORD;
    mask : DWORD;
    PLC_DigIn : BOOL;
END_VAR
VAR_IN_OUT
	ba_ok : UINT;
    all_ok : BOOL;
END_VAR
VAR
	status : UINT;
END_VAR;

	status := ba_ok;

	if PLC_BA_status = ALARM_STATUS_ARMED or PLC_BA_status = ALARM_STATUS_ENABLED
	   or PLC_BA_status = ALARM_STATUS_RINGING or PLC_BA_status = ALARM_STATUS_MUTED then

		(* NB: this function is called only in (ARMED, ENABLED, RINGING, MUTED *)
		if PLC_BA_enabled_sensors >= n then
			if (konfig and mask) <> 0 then
				(* sensor is configured for checking *)

				if PLC_DigIn then
					(* sensor GOOD *)
					if PLC_BA_status = ALARM_STATUS_ARMED then
						status := ALARM_SENSOR_GOOD;
					elsif PLC_BA_status = ALARM_STATUS_ENABLED then
						status := ALARM_SENSOR_GOOD;
					else (* ALARM_STATUS_RINGING or ALARM_STATUS_MUTED *)
						if ba_ok = ALARM_SENSOR_GOOD then
							status := ALARM_SENSOR_GOOD;
						elsif ba_ok = ALARM_SENSOR_NOT_GOOD then
							status := ALARM_SENSOR_WAS_NG;
						else (* ALARM_SENSOR_WAS_NG *)
							status := ALARM_SENSOR_WAS_NG;
						end_if;
					end_if;

				else
					(* sensor NOT GOOD *)
					all_ok := false; (* <--------------------------= *)
					if PLC_BA_status = ALARM_STATUS_ARMED then
						status := ALARM_SENSOR_STILL_NG;
					elsif PLC_BA_status = ALARM_STATUS_ENABLED then
						status := ALARM_SENSOR_NOT_GOOD;
					else (* ALARM_STATUS_RINGING or ALARM_STATUS_MUTED *)
						status := ALARM_SENSOR_NOT_GOOD;
					end_if;
				end_if;		
			else
				(* dark grey: sensor is ignored in this bitmask *)
				status := ALARM_SENSOR_IGNORED;
			end_if;
		else
			(* not visible: sensor is not present *)
			status := ALARM_SENSOR_DISABLED;
		end_if;
	
	end_if;

	if ba_ok <> status then
		ba_ok := status;
	end_if;

END_FUNCTION
