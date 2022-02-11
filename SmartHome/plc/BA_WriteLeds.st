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

FUNCTION BA_WriteLeds
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
    index : UINT;
    status : UINT;
END_VAR
VAR
	green    : BOOL;
	red      : BOOL;
	yellow1  : BOOL;
	yellow2  : BOOL;

	siren    : BOOL;
	enable_A : BOOL;
	enable_B : BOOL;
	enable_C : BOOL;
END_VAR;

	(* ----- checking ----- *)

	case status of

	ALARM_STATUS_ZERO:
		green    := false;
		red      := false;
		yellow1  := false;
		yellow2  := false;

		siren    := false;
		enable_A := false;
		enable_B := false;
		enable_C := false;

	ALARM_STATUS_OFF:
		green    := false;
		red      := false;
		yellow1  := false;
		yellow2  := false;

		siren    := false;
		enable_A := false;
		enable_B := false;
		enable_C := false;

	ALARM_STATUS_ARMED:
		green    := (PLC_Seconds mod 2) = 0; (* blinking 1 s on and 1 s off *)
		red      := false;
		yellow1  := (index = ALARM_INDEX_NIGHTTIME) or (index = ALARM_INDEX_EVERYTHING);
		yellow2  := (index = ALARM_INDEX_DAYTIME) or (index = ALARM_INDEX_EVERYTHING);

		siren    := false;
		enable_A := (index = ALARM_INDEX_DAYTIME) or (index = ALARM_INDEX_NIGHTTIME) or (index = ALARM_INDEX_EVERYTHING);
		enable_B := (index = ALARM_INDEX_NIGHTTIME) or (index = ALARM_INDEX_EVERYTHING);
		enable_C := (index = ALARM_INDEX_EVERYTHING);

	ALARM_STATUS_ENABLED:
		green    := true;
		red      := false;
		yellow1  := (index = ALARM_INDEX_NIGHTTIME) or (index = ALARM_INDEX_EVERYTHING);
		yellow2  := (index = ALARM_INDEX_DAYTIME) or (index = ALARM_INDEX_EVERYTHING);

		siren    := false;
		enable_A := (index = ALARM_INDEX_DAYTIME) or (index = ALARM_INDEX_NIGHTTIME) or (index = ALARM_INDEX_EVERYTHING);
		enable_B := (index = ALARM_INDEX_NIGHTTIME) or (index = ALARM_INDEX_EVERYTHING);
		enable_C := (index = ALARM_INDEX_EVERYTHING);

	ALARM_STATUS_RINGING:
		green    := true;
		red      := (PLC_Seconds mod 2) = 0; (* blinking 1 s on and 1 s off *)
		yellow1  := (index = ALARM_INDEX_NIGHTTIME) or (index = ALARM_INDEX_EVERYTHING);
		yellow2  := (index = ALARM_INDEX_DAYTIME) or (index = ALARM_INDEX_EVERYTHING);

		siren    := true; (********************** SIREN *******************************)
		enable_A := (index = ALARM_INDEX_DAYTIME) or (index = ALARM_INDEX_NIGHTTIME) or (index = ALARM_INDEX_EVERYTHING);
		enable_B := (index = ALARM_INDEX_NIGHTTIME) or (index = ALARM_INDEX_EVERYTHING);
		enable_C := (index = ALARM_INDEX_EVERYTHING);

	ALARM_STATUS_MUTED:
		green    := true;
		red      := true;
		yellow1  := (index = ALARM_INDEX_NIGHTTIME) or (index = ALARM_INDEX_EVERYTHING);
		yellow2  := (index = ALARM_INDEX_DAYTIME) or (index = ALARM_INDEX_EVERYTHING);

		siren    := false;
		enable_A := (index = ALARM_INDEX_DAYTIME) or (index = ALARM_INDEX_NIGHTTIME) or (index = ALARM_INDEX_EVERYTHING);
		enable_B := (index = ALARM_INDEX_NIGHTTIME) or (index = ALARM_INDEX_EVERYTHING);
		enable_C := (index = ALARM_INDEX_EVERYTHING);

	ALARM_STATUS_TESTING:
		(* values from page046 *)
		green    := PLC_BA_led_green;
		red      := PLC_BA_led_red;
		yellow1  := PLC_BA_led_yellow1;
		yellow2  := PLC_BA_led_yellow2;

		siren    := PLC_BA_siren;
		enable_A := PLC_BA_relay_A;
		enable_B := PLC_BA_relay_B;
		enable_C := PLC_BA_relay_C;

	else
		green    := false;
		red      := false;
		yellow1  := false;
		yellow2  := false;

		siren    := false;
		enable_A := false;
		enable_B := false;
		enable_C := false;

	end_case;

	(* ----- crosstable assignments -----*)

    PLC_BA_led_green   := green       ;
    PLC_BA_led_red     := red         ;
    PLC_BA_led_yellow1 := yellow1     ;
    PLC_BA_led_yellow2 := yellow2     ;

    if SRV_BA_led_green   <> green   then SRV_BA_led_green   := green  ; end_if; 
    if SRV_BA_led_red     <> red     then SRV_BA_led_red     := red    ; end_if; 
    if SRV_BA_led_yellow1 <> yellow1 then SRV_BA_led_yellow1 := yellow1; end_if; 
    if SRV_BA_led_yellow2 <> yellow2 then SRV_BA_led_yellow2 := yellow2; end_if; 

    PLC_BA_siren       := siren       ;
    PLC_BA_relay_A     := enable_A    ;
    PLC_BA_relay_B     := enable_B    ;
    PLC_BA_relay_C     := enable_C    ;

	(* ----- fieldbus assignments ----- *)

    BA_SetDigOuts(green, red, yellow1, yellow2, siren, enable_A, enable_B, enable_C);

END_FUNCTION
