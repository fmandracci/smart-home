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

FUNCTION_BLOCK LampImpulse
VAR_INPUT
    x  : UINT;
END_VAR
VAR_IN_OUT
    PLC_Tn_lamp_x : BOOL;
    SRV_Tn_lamp_x : BOOL;
    PLC_Tn_lamp_feedback_x : BOOL;
END_VAR
VAR
	active : BOOL := false;
END_VAR;

	if active then
        Tn_SetDigOut_lamp(x, false);
		PLC_Tn_lamp_x := false;
        SRV_Tn_lamp_x := false;
		active := false;
    else
	    if PLC_Tn_lamp_x or SRV_Tn_lamp_x then
	        Tn_SetDigOut_lamp(x, true);
			active := true;
		end_if;
	end_if;

    PLC_Tn_lamp_feedback_x := Tn_GetDigIn_lamp(x);

END_FUNCTION_BLOCK
