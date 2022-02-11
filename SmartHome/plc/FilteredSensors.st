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

FUNCTION_BLOCK FilteredSensors
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
	n  : UINT; (* Tn                     *)
    ES : INT;  (* PLC_Tn_enabled_sensors *)
END_VAR
VAR_IN_OUT
    T1 : INT;  (* PLC_Tn_temperature     *)
    T2 : INT;  (* PLC_Tn_temperature_bis *)
    T3 : INT;  (* PLC_Tn_temperature_ext *)

    H1 : INT;  (* PLC_Tn_humidity        *)
    H2 : INT;  (* PLC_Tn_humidity_bis    *)
    H3 : INT;  (* PLC_Tn_humidity_ext    *)
END_VAR
VAR
    T1_value : INT := TemperatureErrorValue;
    T2_value : INT := TemperatureErrorValue;
    T3_value : INT := TemperatureErrorValue;
	i : INT;
	s : INT;
	m : INT;
	first_time : BOOL := true;
	T1_array : array [1 .. RollingAverageSize] of INT;
	T2_array : array [1 .. RollingAverageSize] of INT;
	T3_array : array [1 .. RollingAverageSize] of INT;
END_VAR

	if first_time then
		first_time := false;
		for i := 1 to RollingAverageSize by 1 do
			T1_array[i] := TemperatureErrorValue;
			T2_array[i] := TemperatureErrorValue;
			T3_array[i] := TemperatureErrorValue;
		end_for;
	end_if;

    Tn_ReadSensors(n, ES, T1_value, T2_value, T3_value, H1, H2, H3);

	if (abs(ES) >= 1) and (T1_value <> TemperatureErrorValue) then
		s := 0;
		for i := 1 to (RollingAverageSize - 1) by 1 do
			T1_array[i] := T1_array[i + 1];
			s := s + T1_array[i];
		end_for;
		T1_array[RollingAverageSize] := T1_value;
		s := s + T1_value;
		m := s / RollingAverageSize;
		if (s mod RollingAverageSize) >= HalfRollingAverageSize then
			m := m + 1;
		end_if;
		if abs(T1_value - m) <= RollingAverageMaxDeltaT then
			T1 := m;
		else
			for i := 1 to RollingAverageSize by 1 do
				T1_array[i] := T1_value;
			end_for;
			T1 := T1_value;
		end_if;
	else
		T1 := TemperatureErrorValue;
	end_if;

	if (abs(ES) >= 2) and (T2_value <> TemperatureErrorValue) then
		s := 0;
		for i := 1 to (RollingAverageSize - 1) by 1 do
			T2_array[i] := T2_array[i + 1];
			s := s + T2_array[i];
		end_for;
		T2_array[RollingAverageSize] := T2_value;
		s := s + T2_value;
		m := s / RollingAverageSize;
		if (s mod RollingAverageSize) >= HalfRollingAverageSize then
			m := m + 1;
		end_if;
		if abs(T2_value - m) <= RollingAverageMaxDeltaT then
			T2 := m;
		else
			for i := 1 to RollingAverageSize by 1 do
				T2_array[i] := T2_value;
			end_for;
			T2 := T2_value;
		end_if;
	else
		T2 := TemperatureErrorValue;
	end_if;

	if (abs(ES) >= 3) and (T3_value <> TemperatureErrorValue) then
		s := 0;
		for i := 1 to (RollingAverageSize - 1) by 1 do
			T3_array[i] := T3_array[i + 1];
			s := s + T3_array[i];
		end_for;
		T3_array[RollingAverageSize] := T3_value;
		s := s + T3_value;
		m := s / RollingAverageSize;
		if (s mod RollingAverageSize) >= HalfRollingAverageSize then
			m := m + 1;
		end_if;
		if abs(T3_value - m) <= RollingAverageMaxDeltaT then
			T3 := m;
		else
			for i := 1 to RollingAverageSize by 1 do
				T3_array[i] := T3_value;
			end_for;
			T3 := T3_value;
		end_if;
	else
		T3 := TemperatureErrorValue;
	end_if;

END_FUNCTION_BLOCK
