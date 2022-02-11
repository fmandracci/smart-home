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
END_VAR;

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

		BA_ReadSensors();
		substatus := 3;
	
	3: (* ----- check sensors --------------------------------------------- *)

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
