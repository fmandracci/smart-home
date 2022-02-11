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

FUNCTION Tn_SetDigOut_lamp
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
    x : UINT;
    value : BOOL;
END_VAR

	if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 then
		(* TPAC1007_04_AD Local I/O DO1..5 DI7..11 on RTU3 *)
		case x of
		1: if PLC_DigDir_1 <> DigDir_OUT then PLC_DigDir_1 := DigDir_OUT; end_if;
	       if PLC_DigOut_1 <> value      then PLC_DigOut_1 := value; end_if;
		2: if PLC_DigDir_2 <> DigDir_OUT then PLC_DigDir_2 := DigDir_OUT; end_if;
	       if PLC_DigOut_2 <> value      then PLC_DigOut_2 := value; end_if;
		3: if PLC_DigDir_3 <> DigDir_OUT then PLC_DigDir_3 := DigDir_OUT; end_if;
	       if PLC_DigOut_3 <> value      then PLC_DigOut_3 := value; end_if;
		4: if PLC_DigDir_4 <> DigDir_OUT then PLC_DigDir_4 := DigDir_OUT; end_if;
	       if PLC_DigOut_4 <> value      then PLC_DigOut_4 := value; end_if;
		5: if PLC_DigDir_5 <> DigDir_OUT then PLC_DigDir_5 := DigDir_OUT; end_if;
	       if PLC_DigOut_5 <> value      then PLC_DigOut_5 := value; end_if;
 	    else ;
	    end_case;

	elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
		(* Fast I/O FO5..8 FO5..8 on GPIO *)
		case x of
		1: if PLC_FastIO_5 <> value then PLC_FastIO_5 := value; end_if;
		2: if PLC_FastIO_6 <> value then PLC_FastIO_6 := value; end_if;
		3: if PLC_FastIO_7 <> value then PLC_FastIO_7 := value; end_if;
		4: if PLC_FastIO_8 <> value then PLC_FastIO_8 := value; end_if;
 	    else ;
	    end_case;

	else 
		; (* no lamps *)
	end_if;


END_FUNCTION
