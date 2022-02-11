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

PROGRAM Buzzer 
#import "Crosstable.gvl"
#import "Resource1.gvl"
CONST
	QUIET_status       : UINT  := 0;
	QUIET_sound        : UDINT := 16#00000000;
	QUIET_period       : TIME  := T#2000ms;

	ONE_ALARM_status   : UINT  := 1;
	ONE_ALARM_sound    : UDINT := 16#03193264; (* count=3; off=0.25s; on=0.50s; volume=100%; total=2.25s *)
	ONE_ALARM_period   : TIME  := T#3000ms;

	BOTH_ALARMS_status : UINT  := 2;
	BOTH_ALARMS_sound  : UDINT := 16#03193264; (* count=6; off=0.25s; on=0.50s; volume=100%; total=4.50s *)
	BOTH_ALARMS_period : TIME  := T#5000ms;

	ONE_TIMER_status   : UINT  := 3;
	ONE_TIMER_sound    : UDINT := 16#03030364; (* count=3; off=0.03s; on=0.03s; volume=100%; total=0.18s *)
	ONE_TIMER_period   : TIME  :=  T#500ms;

	BOTH_TIMERS_status : UINT  := 4;
	BOTH_TIMERS_sound  : UDINT := 16#06030364; (* count=6; off=0.03s; on=0.03s; volume=100%; total=0.36s *)
	BOTH_TIMERS_period : TIME  :=  T#500ms;
END_CONST
VAR
	status : UINT := QUIET_status;
	sound : UDINT := QUIET_sound;
	period : TIME := QUIET_period;
	next_status : UINT := QUIET_status;
	timer : TON;
END_VAR;

	(* retrieve alarm status from Burglar Alarm *)
	case PLC_BA_status of
    ALARM_STATUS_ZERO,
    ALARM_STATUS_OFF,
    ALARM_STATUS_ARMED,
    ALARM_STATUS_ENABLED:
        PLC_buzzer_alarm := false;
    ALARM_STATUS_RINGING:
        PLC_buzzer_alarm := true;
    ALARM_STATUS_MUTED,
    ALARM_STATUS_TESTING:
        PLC_buzzer_alarm := false;
    else
        ;
	end_case;

	(* retrieving blackout status from both Electric Panel and Burglar Alarm *)
	PLC_buzzer_blackout_or_overload := PLC_EP_BlackoutDetected or PLC_BA_BlackoutDetected or PLC_EP_OverloadDetected; (* vedi TcpUpdate.st *)

	(* timer values are always from the local hmi *)

	(* buzzer state machine: conditions *)
	if PLC_buzzer_alarm and PLC_buzzer_blackout_or_overload then
		next_status := BOTH_ALARMS_status;
		sound := BOTH_ALARMS_sound;
		period := BOTH_ALARMS_period;
	elsif PLC_buzzer_alarm or PLC_buzzer_blackout_or_overload then
		next_status := ONE_ALARM_status;
		sound := ONE_ALARM_sound;
		period := ONE_ALARM_period;
	elsif PLC_buzzer_timer_1 and PLC_buzzer_timer_2 then
		next_status := BOTH_TIMERS_status;
		sound := BOTH_TIMERS_sound;
		period := BOTH_TIMERS_period;
	elsif PLC_buzzer_timer_1 or PLC_buzzer_timer_2 then
		next_status := ONE_TIMER_status;
		sound := ONE_TIMER_sound;
		period := ONE_TIMER_period;
	else
		next_status := QUIET_status;
		sound := QUIET_sound;
		period := QUIET_period;
	end_if;

	(* buzzer state machine: actions *)
	if status <> next_status then
		(* entering new buzzer status *)
		status := next_status;
		PLC_BUZZER := sound; (* <-----= first buzzer *)
		timer(IN := FALSE);
	else
		(* same buzzer status *)
		timer(IN := TRUE, PT := period ); 
		if timer.Q then
			PLC_BUZZER := sound; (* <-----= buzzer repeat *)
			timer(IN := FALSE);
		end_if;
	end_if;

END_PROGRAM
