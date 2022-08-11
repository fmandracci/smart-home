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

FUNCTION Tn_OverHeat : BOOL
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
    n : UINT;
	temperature : INT;
	temperature_bis : INT;
END_VAR

	if PLC_control_type = ControlType_3 then
		(* TPAC1007_04_AD DigOut 6 *)
    	Tn_OverHeat := false;

	elsif PLC_control_type = ControlType_4 or PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
		(* ARQ01 relè *)
    	Tn_OverHeat := false;

	elsif PLC_control_type = ControlType_7 then
		(* n=1..4: MPNE_C DigOut 1..4 *)
    	Tn_OverHeat := false;

	elsif PLC_control_type = ControlType_12 then
		(* FastI/O FO 8 *)
    	Tn_OverHeat := false;

	elsif PLC_control_type = ControlType_13 then
		(* n=1..4: TPAC1007_04_AD DigOut_1..4 *)
    	Tn_OverHeat := false;

	elsif PLC_control_type = ControlType_6 then
		(* MPNC 4xAI4 on RTU0 1=C+6 2=B+7 3=A+8 4=base+5, bis,ext varies *)
    	Tn_OverHeat := false;

	elsif PLC_control_type = ControlType_14 then
		(* n=1..4: MPNC base DigOut_1..4 *)
    	Tn_OverHeat := false;

	elsif PLC_control_type = ControlType_15 or PLC_control_type = ControlType_16 then
		(* TPAC1007_04_AD DigOut_8 *)
    	Tn_OverHeat := false;

	end_if;

END_FUNCTION
