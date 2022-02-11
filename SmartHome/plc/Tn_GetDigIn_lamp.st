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

FUNCTION Tn_GetDigIn_lamp : BOOL
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
    x : UINT;
END_VAR

	if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 then
		(* TPAC1007_04_AD Local I/O DO1..5 DI7..11 on RTU3 *)
		case x of
		1: if PLC_DigDir_7  <> DigDir_IN then PLC_DigDir_7 := DigDir_IN; end_if;
	       Tn_GetDigIn_lamp := PLC_DigIn_7;
		2: if PLC_DigDir_8  <> DigDir_IN then PLC_DigDir_8 := DigDir_IN; end_if;
	       Tn_GetDigIn_lamp := PLC_DigIn_8;
		3: Tn_GetDigIn_lamp := PLC_DigIn_9;
		4: Tn_GetDigIn_lamp := PLC_DigIn_10;
		5: Tn_GetDigIn_lamp := PLC_DigIn_11;
 	    else Tn_GetDigIn_lamp := false;
	    end_case;

	elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
		(* Fast I/O FO5..8 FI1..4 on GPIO *)
		case x of
		1: Tn_GetDigIn_lamp := PLC_FastIO_1;
		2: Tn_GetDigIn_lamp := PLC_FastIO_2;
		3: Tn_GetDigIn_lamp := PLC_FastIO_3;
		4: Tn_GetDigIn_lamp := PLC_FastIO_4;
 	    else Tn_GetDigIn_lamp := false;
	    end_case;

	else 
		Tn_GetDigIn_lamp := false; (* no lamps *)
	end_if;

END_FUNCTION
