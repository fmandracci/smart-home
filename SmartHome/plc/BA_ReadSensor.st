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

FUNCTION BA_ReadSensor : BOOL
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
    n : UINT;
END_VAR

	if PLC_BA_enabled_sensors >= n then

		if PLC_control_type = ControlType_2 then
			(* MPNE_A, MPNE_B on RTU0 *)
			if n <= 16 then
				if NODE_11_STATUS = NODE_NODE_OK then
					case n of
		             1: SetMpneDigDir_IN(MPNE_A_DigDir_1); BA_ReadSensor := MPNE_A_DigIn_1 ;
		             2: SetMpneDigDir_IN(MPNE_A_DigDir_2); BA_ReadSensor := MPNE_A_DigIn_2 ;
		             3: SetMpneDigDir_IN(MPNE_A_DigDir_3); BA_ReadSensor := MPNE_A_DigIn_3 ;
		             4: SetMpneDigDir_IN(MPNE_A_DigDir_4); BA_ReadSensor := MPNE_A_DigIn_4 ;
		             5: SetMpneDigDir_IN(MPNE_A_DigDir_5); BA_ReadSensor := MPNE_A_DigIn_5 ;
		             6: SetMpneDigDir_IN(MPNE_A_DigDir_6); BA_ReadSensor := MPNE_A_DigIn_6 ;
		             7: SetMpneDigDir_IN(MPNE_A_DigDir_7); BA_ReadSensor := MPNE_A_DigIn_7 ;
		             8: SetMpneDigDir_IN(MPNE_A_DigDir_8); BA_ReadSensor := MPNE_A_DigIn_8 ;
		             9:                                    BA_ReadSensor := MPNE_A_DigIn_9 ;
		            10:                                    BA_ReadSensor := MPNE_A_DigIn_10;
		            11:                                    BA_ReadSensor := MPNE_A_DigIn_11;
		            12:                                    BA_ReadSensor := MPNE_A_DigIn_12;
		            13:                                    BA_ReadSensor := MPNE_A_DigIn_13;
		            14:                                    BA_ReadSensor := MPNE_A_DigIn_14;
		            15:                                    BA_ReadSensor := MPNE_A_DigIn_15;
		            16:                                    BA_ReadSensor := MPNE_A_DigIn_16;
					else
						BA_ReadSensor := false;
					end_case;
				else
					BA_ReadSensor := false;
				end_if;
			else
				if NODE_12_STATUS = NODE_NODE_OK then
					case n of
		            17: SetMpneDigDir_IN(MPNE_B_DigDir_1); BA_ReadSensor := MPNE_B_DigIn_1 ;
		            18: SetMpneDigDir_IN(MPNE_B_DigDir_2); BA_ReadSensor := MPNE_B_DigIn_2 ;
		            19: SetMpneDigDir_IN(MPNE_B_DigDir_3); BA_ReadSensor := MPNE_B_DigIn_3 ;
		            20: SetMpneDigDir_IN(MPNE_B_DigDir_4); BA_ReadSensor := MPNE_B_DigIn_4 ;
		            21: SetMpneDigDir_IN(MPNE_B_DigDir_5); BA_ReadSensor := MPNE_B_DigIn_5 ;
		            22: SetMpneDigDir_IN(MPNE_B_DigDir_6); BA_ReadSensor := MPNE_B_DigIn_6 ;
		            23: SetMpneDigDir_IN(MPNE_B_DigDir_7); BA_ReadSensor := MPNE_B_DigIn_7 ;
		            24: SetMpneDigDir_IN(MPNE_B_DigDir_8); BA_ReadSensor := MPNE_B_DigIn_8 ;
		
		            25:                                    BA_ReadSensor := MPNE_B_DigIn_9 ;
		            26:                                    BA_ReadSensor := MPNE_B_DigIn_10;
		            27:                                    BA_ReadSensor := MPNE_B_DigIn_11;
		            28:                                    BA_ReadSensor := MPNE_B_DigIn_12;
		            29:                                    BA_ReadSensor := MPNE_B_DigIn_13;
		            30:                                    BA_ReadSensor := MPNE_B_DigIn_14;
		            31:                                    BA_ReadSensor := MPNE_B_DigIn_15;
		            32:                                    BA_ReadSensor := MPNE_B_DigIn_16;
					else BA_ReadSensor := false;
					end_case;
				else
					BA_ReadSensor := false;
				end_if;
			end_if;
	
		elsif PLC_control_type = ControlType_7 then
			(* Fast I/O on GPIO *)
			case n of
             1: BA_ReadSensor := PLC_FastIO_1 ;
             2: BA_ReadSensor := PLC_FastIO_2 ;
             3: BA_ReadSensor := PLC_FastIO_3 ;
			else BA_ReadSensor := false;
			end_case;

		elsif PLC_control_type = ControlType_12 then
			(* Fast I/O on GPIO *)
			case n of
             1: BA_ReadSensor := PLC_FastIO_1 ;
             2: BA_ReadSensor := PLC_FastIO_2 ;
             3: BA_ReadSensor := PLC_FastIO_3 ;
			else BA_ReadSensor := false;
			end_case;

		elsif PLC_control_type = ControlType_13 then
			(* TPAC1007_04_AD Local I/O on RTU3 *)
			if NODE_31_STATUS = NODE_NODE_OK then
				case n of
	             1: BA_ReadSensor := PLC_DigIn_9 ;
	             2: BA_ReadSensor := PLC_DigIn_10;
	             3: BA_ReadSensor := PLC_DigIn_11;
				else BA_ReadSensor := false;
				end_case;
			else BA_ReadSensor := false;
			end_if;

		elsif PLC_control_type = ControlType_14 or PLC_control_type = ControlType_6 then
			(* MPNC DI16 "A,B" + DO16 "A,B" on RTU0 *)
			if NODE_27_STATUS = NODE_NODE_OK then
				case n of
	             1: BA_ReadSensor := MPNC_DigIn_A_1 ;
	             2: BA_ReadSensor := MPNC_DigIn_A_2 ;
	             3: BA_ReadSensor := MPNC_DigIn_A_3 ;
	             4: BA_ReadSensor := MPNC_DigIn_A_4 ;
	             5: BA_ReadSensor := MPNC_DigIn_A_5 ;
	             6: BA_ReadSensor := MPNC_DigIn_A_6 ;
	             7: BA_ReadSensor := MPNC_DigIn_A_7 ;
	             8: BA_ReadSensor := MPNC_DigIn_A_8 ;
	             9: BA_ReadSensor := MPNC_DigIn_A_9 ;
	            10: BA_ReadSensor := MPNC_DigIn_A_10;
	            11: BA_ReadSensor := MPNC_DigIn_A_11;
	            12: BA_ReadSensor := MPNC_DigIn_A_12;
	            13: BA_ReadSensor := MPNC_DigIn_A_13;
	            14: BA_ReadSensor := MPNC_DigIn_A_14;
	            15: BA_ReadSensor := MPNC_DigIn_A_15;
	            16: BA_ReadSensor := MPNC_DigIn_A_16;
	
	            17: BA_ReadSensor := MPNC_DigIn_B_1 ;
	            18: BA_ReadSensor := MPNC_DigIn_B_2 ;
	            19: BA_ReadSensor := MPNC_DigIn_B_3 ;
	            20: BA_ReadSensor := MPNC_DigIn_B_4 ;
	            21: BA_ReadSensor := MPNC_DigIn_B_5 ;
	            22: BA_ReadSensor := MPNC_DigIn_B_6 ;
	            23: BA_ReadSensor := MPNC_DigIn_B_7 ;
	            24: BA_ReadSensor := MPNC_DigIn_B_8 ;
	            25: BA_ReadSensor := MPNC_DigIn_B_9 ;
	            26: BA_ReadSensor := MPNC_DigIn_B_10;
	            27: BA_ReadSensor := MPNC_DigIn_B_11;
	            28: BA_ReadSensor := MPNC_DigIn_B_12;
	            29: BA_ReadSensor := MPNC_DigIn_B_13;
	            30: BA_ReadSensor := MPNC_DigIn_B_14;
	            31: BA_ReadSensor := MPNC_DigIn_B_15;
	            32: BA_ReadSensor := MPNC_DigIn_B_16;
	            else BA_ReadSensor := false;
				end_case;
			else BA_ReadSensor := false;
			end_if;

		end_if;
	
	else
		BA_ReadSensor := false;

	end_if;

END_FUNCTION
