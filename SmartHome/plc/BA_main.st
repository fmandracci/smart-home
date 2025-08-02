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

PROGRAM BA_main 
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR
	substatus : UINT := 0;
	timer : TON;
	NEXT_STATUS : UINT := 0;
	NEXT_INDEX : UINT := 0;
END_VAR
CONST
	WaitSensorsDelay : TIME := T#2000ms;
END_CONST;

	if not PLC_Iam_BA then
		return;
	end_if;
	if PLC_BA_just_started then
		PLC_BA_just_started := false;
		timer(IN := FALSE);
		substatus := 0;
	end_if;

	BA_Watchdog();

	NEXT_STATUS := PLC_BA_status;
	NEXT_INDEX := PLC_BA_config_index;

	case substatus of

	0: (* ----- recover config  ------------------------------------------- *)

		case PLC_BA_status of
		ALARM_STATUS_ZERO:
			NEXT_INDEX := ALARM_INDEX_NOTHING;
			NEXT_STATUS := ALARM_STATUS_OFF;
		ALARM_STATUS_OFF:
			NEXT_INDEX := ALARM_INDEX_NOTHING;
		ALARM_STATUS_ARMED:
			;
		ALARM_STATUS_ENABLED:
			;
		ALARM_STATUS_RINGING:
			;
		ALARM_STATUS_MUTED:
			;
		ALARM_STATUS_TESTING:
			;
		else
			NEXT_INDEX := ALARM_INDEX_NOTHING;
			NEXT_STATUS := ALARM_STATUS_OFF;
		end_case;

		BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
		PLC_BA_command := ALARM_COMMAND_NONE;
		substatus := 1;

	1: (* ----- waiting config after write -------------------------------- *)

		timer(IN := TRUE, PT := ControlPeriod);
		if timer.Q then
			timer(IN := FALSE);
			substatus := 2;
		end_if;

	2: (* ----- read sensors ---------------------------------------------- *)

		if not BA_ReadSensorsReady() then
			substatus := 3;
		else
			PLC_BA_blackout_digin := BA_ReadSensor(0); (* blackout detection *)
			PLC_BA_DigIn_1 := BA_ReadSensor(1 );
			PLC_BA_DigIn_2 := BA_ReadSensor(2 );
			PLC_BA_DigIn_3 := BA_ReadSensor(3 );
			PLC_BA_DigIn_4 := BA_ReadSensor(4 );
			PLC_BA_DigIn_5 := BA_ReadSensor(5 );
			PLC_BA_DigIn_6 := BA_ReadSensor(6 );
			PLC_BA_DigIn_7 := BA_ReadSensor(7 );
			PLC_BA_DigIn_8 := BA_ReadSensor(8 );
			PLC_BA_DigIn_9 := BA_ReadSensor(9 );
			PLC_BA_DigIn_10:= BA_ReadSensor(10);
			PLC_BA_DigIn_11:= BA_ReadSensor(11);
			PLC_BA_DigIn_12:= BA_ReadSensor(12);
			PLC_BA_DigIn_13:= BA_ReadSensor(13);
			PLC_BA_DigIn_14:= BA_ReadSensor(14);
			PLC_BA_DigIn_15:= BA_ReadSensor(15);
			PLC_BA_DigIn_16:= BA_ReadSensor(16);
			PLC_BA_DigIn_17:= BA_ReadSensor(17);
			PLC_BA_DigIn_18:= BA_ReadSensor(18);
			PLC_BA_DigIn_19:= BA_ReadSensor(19);
			PLC_BA_DigIn_20:= BA_ReadSensor(20);
			PLC_BA_DigIn_21:= BA_ReadSensor(21);
			PLC_BA_DigIn_22:= BA_ReadSensor(22);
			PLC_BA_DigIn_23:= BA_ReadSensor(23);
			PLC_BA_DigIn_24:= BA_ReadSensor(24);
			PLC_BA_DigIn_25:= BA_ReadSensor(25);
			PLC_BA_DigIn_26:= BA_ReadSensor(26);
			PLC_BA_DigIn_27:= BA_ReadSensor(27);
			PLC_BA_DigIn_28:= BA_ReadSensor(28);
			PLC_BA_DigIn_29:= BA_ReadSensor(29);
			PLC_BA_DigIn_30:= BA_ReadSensor(30);
			PLC_BA_DigIn_31:= BA_ReadSensor(31);
			PLC_BA_DigIn_32:= BA_ReadSensor(32);

			substatus := 4;
		end_if;
	
	3: (* ----- wait for ready sensors (only once) ------------------------ *)

		timer(IN := TRUE, PT := WaitSensorsDelay);
		if timer.Q then
			timer(IN := FALSE);
			if BA_ReadSensorsReady() then
				PLC_BA_blackout_digin := BA_ReadSensor(0); (* blackout detection *)
				PLC_BA_DigIn_1 := BA_ReadSensor(1 );
				PLC_BA_DigIn_2 := BA_ReadSensor(2 );
				PLC_BA_DigIn_3 := BA_ReadSensor(3 );
				PLC_BA_DigIn_4 := BA_ReadSensor(4 );
				PLC_BA_DigIn_5 := BA_ReadSensor(5 );
				PLC_BA_DigIn_6 := BA_ReadSensor(6 );
				PLC_BA_DigIn_7 := BA_ReadSensor(7 );
				PLC_BA_DigIn_8 := BA_ReadSensor(8 );
				PLC_BA_DigIn_9 := BA_ReadSensor(9 );
				PLC_BA_DigIn_10:= BA_ReadSensor(10);
				PLC_BA_DigIn_11:= BA_ReadSensor(11);
				PLC_BA_DigIn_12:= BA_ReadSensor(12);
				PLC_BA_DigIn_13:= BA_ReadSensor(13);
				PLC_BA_DigIn_14:= BA_ReadSensor(14);
				PLC_BA_DigIn_15:= BA_ReadSensor(15);
				PLC_BA_DigIn_16:= BA_ReadSensor(16);
				PLC_BA_DigIn_17:= BA_ReadSensor(17);
				PLC_BA_DigIn_18:= BA_ReadSensor(18);
				PLC_BA_DigIn_19:= BA_ReadSensor(19);
				PLC_BA_DigIn_20:= BA_ReadSensor(20);
				PLC_BA_DigIn_21:= BA_ReadSensor(21);
				PLC_BA_DigIn_22:= BA_ReadSensor(22);
				PLC_BA_DigIn_23:= BA_ReadSensor(23);
				PLC_BA_DigIn_24:= BA_ReadSensor(24);
				PLC_BA_DigIn_25:= BA_ReadSensor(25);
				PLC_BA_DigIn_26:= BA_ReadSensor(26);
				PLC_BA_DigIn_27:= BA_ReadSensor(27);
				PLC_BA_DigIn_28:= BA_ReadSensor(28);
				PLC_BA_DigIn_29:= BA_ReadSensor(29);
				PLC_BA_DigIn_30:= BA_ReadSensor(30);
				PLC_BA_DigIn_31:= BA_ReadSensor(31);
				PLC_BA_DigIn_32:= BA_ReadSensor(32);
			else
				PLC_BA_blackout_digin := false;
				PLC_BA_DigIn_1 := false;
				PLC_BA_DigIn_2 := false;
				PLC_BA_DigIn_3 := false;
				PLC_BA_DigIn_4 := false;
				PLC_BA_DigIn_5 := false;
				PLC_BA_DigIn_6 := false;
				PLC_BA_DigIn_7 := false;
				PLC_BA_DigIn_8 := false;
				PLC_BA_DigIn_9 := false;
				PLC_BA_DigIn_10:= false;
				PLC_BA_DigIn_11:= false;
				PLC_BA_DigIn_12:= false;
				PLC_BA_DigIn_13:= false;
				PLC_BA_DigIn_14:= false;
				PLC_BA_DigIn_15:= false;
				PLC_BA_DigIn_16:= false;
				PLC_BA_DigIn_17:= false;
				PLC_BA_DigIn_18:= false;
				PLC_BA_DigIn_19:= false;
				PLC_BA_DigIn_20:= false;
				PLC_BA_DigIn_21:= false;
				PLC_BA_DigIn_22:= false;
				PLC_BA_DigIn_23:= false;
				PLC_BA_DigIn_24:= false;
				PLC_BA_DigIn_25:= false;
				PLC_BA_DigIn_26:= false;
				PLC_BA_DigIn_27:= false;
				PLC_BA_DigIn_28:= false;
				PLC_BA_DigIn_29:= false;
				PLC_BA_DigIn_30:= false;
				PLC_BA_DigIn_31:= false;
				PLC_BA_DigIn_32:= false;
			end_if;

			substatus := 4;
		end_if;

	4: (* ----- check sensors --------------------------------------------- *)

		case PLC_BA_status of

		ALARM_STATUS_ZERO:
			BA_ClearOKs();
			NEXT_INDEX := ALARM_INDEX_NOTHING;
			NEXT_STATUS := ALARM_STATUS_OFF;
			BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
			substatus := 1;

		ALARM_STATUS_OFF:
			BA_ClearOKs();
			if PLC_BA_command = ALARM_COMMAND_DAYTIME then
				NEXT_STATUS := ALARM_STATUS_ARMED;
				NEXT_INDEX := ALARM_INDEX_DAYTIME;
				BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
				substatus := 1;
			elsif PLC_BA_command = ALARM_COMMAND_NIGHTTIME then
				NEXT_STATUS := ALARM_STATUS_ARMED;
				NEXT_INDEX := ALARM_INDEX_NIGHTTIME;
				BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
				substatus := 1;
			elsif PLC_BA_command = ALARM_COMMAND_EVERYTHING then
				NEXT_STATUS := ALARM_STATUS_ARMED;
				NEXT_INDEX := ALARM_INDEX_EVERYTHING;
				BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
				substatus := 1;
			elsif PLC_BA_command = ALARM_COMMAND_TEST then
				NEXT_STATUS := ALARM_STATUS_TESTING;
				(* NEXT_INDEX := ALARM_INDEX_NOTHING; *)
			 	(* no BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);     *)
				substatus := 2;
			else
				substatus := 2;
			end_if;

		ALARM_STATUS_ARMED:
			if PLC_BA_command = ALARM_COMMAND_DAYTIME then
				NEXT_INDEX := ALARM_INDEX_DAYTIME;
				BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
				substatus := 1;
			elsif PLC_BA_command = ALARM_COMMAND_NIGHTTIME then
				NEXT_INDEX := ALARM_INDEX_NIGHTTIME;
				BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
				substatus := 1;
			elsif PLC_BA_command = ALARM_COMMAND_EVERYTHING then
				NEXT_INDEX := ALARM_INDEX_EVERYTHING;
				BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
				substatus := 1;
			elsif PLC_BA_command = ALARM_COMMAND_DISABLE then
				NEXT_STATUS := ALARM_STATUS_OFF;
				NEXT_INDEX := ALARM_INDEX_NOTHING;
				BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
				substatus := 1;
			elsif PLC_BA_command = ALARM_COMMAND_ENABLE then
				NEXT_STATUS := ALARM_STATUS_ENABLED;
				substatus := 2;
			elsif PLC_BA_command = ALARM_COMMAND_TEST then
				NEXT_STATUS := ALARM_STATUS_TESTING;
				substatus := 2;
			elsif BA_CheckSensors(PLC_BA_config_index) then
				substatus := 2;
			else
				substatus := 2;
			end_if;

		ALARM_STATUS_ENABLED:
			if PLC_BA_command = ALARM_COMMAND_DISABLE then
				NEXT_STATUS := ALARM_STATUS_OFF;
				NEXT_INDEX := ALARM_INDEX_NOTHING;
				BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
				substatus := 1;
			elsif PLC_BA_command = ALARM_COMMAND_TEST then
				NEXT_STATUS := ALARM_STATUS_TESTING;
				substatus := 2;
			elsif BA_CheckSensors(PLC_BA_config_index) then
				substatus := 2;
			else
				NEXT_STATUS := ALARM_STATUS_RINGING;
				substatus := 2;
			end_if;

		ALARM_STATUS_RINGING:
			if PLC_BA_command = ALARM_COMMAND_ACK then
				NEXT_STATUS := ALARM_STATUS_MUTED;
				substatus := 2;
			elsif PLC_BA_command = ALARM_COMMAND_TEST then
				NEXT_STATUS := ALARM_STATUS_TESTING;
				substatus := 2;
			elsif BA_CheckSensors(PLC_BA_config_index) then
				substatus := 2;
			else
				NEXT_STATUS := ALARM_STATUS_RINGING;
				substatus := 2;
			end_if;

		ALARM_STATUS_MUTED:
			if PLC_BA_command = ALARM_COMMAND_DISABLE then
				NEXT_STATUS := ALARM_STATUS_OFF;
				NEXT_INDEX := ALARM_INDEX_NOTHING;
				BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
				substatus := 1;
			elsif PLC_BA_command = ALARM_COMMAND_TEST then
				NEXT_STATUS := ALARM_STATUS_TESTING;
				substatus := 2;
			elsif BA_CheckSensors(PLC_BA_config_index) then
				substatus := 2;
			else
				substatus := 2;
			end_if;

		ALARM_STATUS_TESTING:
			if PLC_BA_command = ALARM_COMMAND_DISABLE then
				NEXT_STATUS := ALARM_STATUS_OFF;
				NEXT_INDEX := ALARM_INDEX_NOTHING;
				BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
				substatus := 1;
			else
				BA_TestConfig();
				substatus := 1;
			end_if;

		else
			BA_ClearOKs();
			NEXT_INDEX := ALARM_INDEX_NOTHING;
			NEXT_STATUS := ALARM_STATUS_OFF;
			BA_WriteConfig(NEXT_INDEX, PLC_BA_config_index, PLC_BA_config_mask);
			substatus := 1;
		end_case;
	
		(* NB: only here !! *)
		if PLC_BA_command <> ALARM_COMMAND_NONE then
			SRV_BA_command := ALARM_COMMAND_NONE;
		end_if;

	else (* ------------------------------------------------------------- *)
		substatus := 0;

	end_case;

	BA_WriteLeds(NEXT_INDEX, NEXT_STATUS);
	if PLC_BA_status <> NEXT_STATUS then
		PLC_BA_status  := NEXT_STATUS;
		if NEXT_STATUS = ALARM_STATUS_RINGING then
			if not PLC_BA_ringing_flag then PLC_BA_ringing_flag := true; end_if;
		else
			if PLC_BA_ringing_flag then PLC_BA_ringing_flag := false; end_if;
		end_if;

	end_if;

END_PROGRAM
