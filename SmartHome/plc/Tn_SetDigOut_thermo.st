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

FUNCTION Tn_SetDigOut_thermo
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
    n : UINT;
    heating : BOOL;
	only_mantain: BOOL;
	temperature : INT;
	temperature_bis : INT;
END_VAR
VAR_IN_OUT
	last_R : UINT;
END_VAR

	if PLC_control_type = ControlType_3 then
		(* TPAC1007_04_AD DigOut 6 *)
		if NODE_31_STATUS = NODE_NODE_OK then
	    	if PLC_DigDir_6 <> DigDir_OUT then PLC_DigDir_6 := DigDir_OUT; end_if;
			if only_mantain then
				; (* do nothing *)
			else
		        if PLC_DigOut_6 <> HEATING then PLC_DigOut_6 := HEATING; end_if;
		    end_if;
	    end_if;

	elsif PLC_control_type = ControlType_4 or PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 then
		(* ARQ01 relè *)
		if NODE_10_STATUS = NODE_NODE_OK then
		    if only_mantain then
				; (* do nothing *)
			else
		        if ARQ_Rele <> HEATING then ARQ_Rele := HEATING; end_if;
			end_if;
		end_if;

	elsif PLC_control_type = ControlType_7 then
		(* n=1..4: MPNE_C DigOut 1..4 *)
		if NODE_13_STATUS = NODE_NODE_OK then
			if only_mantain then
				; (* do nothing *)
			else
	    		case n of
				1:
			    	if MPNE_C_DigDir_1 <> DigDir_OUT then MPNE_C_DigDir_1 := DigDir_OUT; end_if;
			        if MPNE_C_DigOut_1 <> HEATING    then MPNE_C_DigOut_1 := HEATING   ; end_if;
				2:
			    	if MPNE_C_DigDir_2 <> DigDir_OUT then MPNE_C_DigDir_2 := DigDir_OUT; end_if;
			        if MPNE_C_DigOut_2 <> HEATING    then MPNE_C_DigOut_2 := HEATING   ; end_if;
				3:
			    	if MPNE_C_DigDir_3 <> DigDir_OUT then MPNE_C_DigDir_3 := DigDir_OUT; end_if;
			        if MPNE_C_DigOut_3 <> HEATING    then MPNE_C_DigOut_3 := HEATING   ; end_if;
				4:
			    	if MPNE_C_DigDir_4 <> DigDir_OUT then MPNE_C_DigDir_4 := DigDir_OUT; end_if;
			        if MPNE_C_DigOut_4 <> HEATING    then MPNE_C_DigOut_4 := HEATING   ; end_if;
				5:
			    	if MPNE_C_DigDir_5 <> DigDir_OUT then MPNE_C_DigDir_5 := DigDir_OUT; end_if;
			        if MPNE_C_DigOut_5 <> HEATING    then MPNE_C_DigOut_5 := HEATING   ; end_if;
				6:
			    	if MPNE_C_DigDir_6 <> DigDir_OUT then MPNE_C_DigDir_6 := DigDir_OUT; end_if;
			        if MPNE_C_DigOut_6 <> HEATING    then MPNE_C_DigOut_6 := HEATING   ; end_if;
				else ;
				end_case;
			end_if;
		end_if;

	elsif PLC_control_type = ControlType_10 then
		(* MPNE_C DigOut 1 *)
		if NODE_13_STATUS = NODE_NODE_OK then
	    	if MPNE_C_DigDir_1 <> DigDir_OUT then MPNE_C_DigDir_1 := DigDir_OUT; end_if;
	
			if only_mantain then
				; (* do nothing *)
			else
		        if heating then (* see also Tn_OverHeat() *)
			    	if not MPNE_C_DigOut_1 then MPNE_C_DigOut_1 := true; end_if;
				else
			    	if MPNE_C_DigOut_1 then MPNE_C_DigOut_1 := false; end_if;
				end_if;
			end_if;
		end_if;

	elsif PLC_control_type = ControlType_11 then
		(* i=1..4: MPNE_C/_D DigOut 1.2 *)
		if n <= 2 then
			if NODE_13_STATUS = NODE_NODE_OK then
				if only_mantain then
					; (* do nothing *)
				else
					case n of
					1:
				    	if MPNE_C_DigDir_1 <> DigDir_OUT then MPNE_C_DigDir_1 := DigDir_OUT; end_if;
						if only_mantain then
							; (* do nothing *)
						else
					        if heating then (* see also Tn_OverHeat() *)
						    	if not MPNE_C_DigOut_1 then MPNE_C_DigOut_1 := true; end_if;
							else
						    	if MPNE_C_DigOut_1 then MPNE_C_DigOut_1 := false; end_if;
							end_if;
						end_if;
					2:
				    	if MPNE_C_DigDir_2 <> DigDir_OUT then MPNE_C_DigDir_2 := DigDir_OUT; end_if;
						if only_mantain then
							; (* do nothing *)
						else
					        if heating then (* see also Tn_OverHeat() *)
						    	if not MPNE_C_DigOut_2 then MPNE_C_DigOut_2 := true; end_if;
							else
						    	if MPNE_C_DigOut_2 then MPNE_C_DigOut_2 := false; end_if;
							end_if;
						end_if;
					else ;
					end_case;
				end_if;
			end_if;
		else
			if NODE_14_STATUS = NODE_NODE_OK then
				if only_mantain then
					; (* do nothing *)
				else
					case n of
					3:
				    	if MPNE_D_DigDir_1 <> DigDir_OUT then MPNE_D_DigDir_1 := DigDir_OUT; end_if;
						if only_mantain then
							; (* do nothing *)
						else
					        if heating then (* see also Tn_OverHeat() *)
						    	if not MPNE_D_DigOut_1 then MPNE_D_DigOut_1 := true; end_if;
							else
						    	if MPNE_D_DigOut_1 then MPNE_D_DigOut_1 := false; end_if;
							end_if;
						end_if;
					4:
				    	if MPNE_D_DigDir_2 <> DigDir_OUT then MPNE_D_DigDir_2 := DigDir_OUT; end_if;
						if only_mantain then
							; (* do nothing *)
						else
					        if heating then (* see also Tn_OverHeat() *)
						    	if not MPNE_D_DigOut_2 then MPNE_D_DigOut_2 := true; end_if;
							else
						    	if MPNE_D_DigOut_2 then MPNE_D_DigOut_2 := false; end_if;
							end_if;
						end_if;
					else ;
					end_case;
				end_if;
			end_if;
		end_if;

	elsif PLC_control_type = ControlType_12 then
		(* FastI/O FO 8 *)
        if only_mantain then
			; (* do nothing *)
		else
	        if PLC_FastIO_8 <> HEATING then PLC_FastIO_8 := HEATING; end_if;
		end_if;

	elsif PLC_control_type = ControlType_13 then
		(* n=1..4: TPAC1007_04_AD DigOut_1..4 *)
		if NODE_31_STATUS = NODE_NODE_OK then
			if only_mantain then
				; (* do nothing *)
			else
		        case n of
				1:
			    	if PLC_DigDir_1 <> DigDir_OUT then PLC_DigDir_1 := DigDir_OUT; end_if;
			        if PLC_DigOut_1 <> HEATING    then PLC_DigOut_1 := HEATING   ; end_if;
				2:
			    	if PLC_DigDir_2 <> DigDir_OUT then PLC_DigDir_2 := DigDir_OUT; end_if;
			        if PLC_DigOut_2 <> HEATING    then PLC_DigOut_2 := HEATING   ; end_if;
				3:
			    	if PLC_DigDir_3 <> DigDir_OUT then PLC_DigDir_3 := DigDir_OUT; end_if;
			        if PLC_DigOut_3 <> HEATING    then PLC_DigOut_3 := HEATING   ; end_if;
				4:
			    	if PLC_DigDir_4 <> DigDir_OUT then PLC_DigDir_4 := DigDir_OUT; end_if;
			        if PLC_DigOut_4 <> HEATING    then PLC_DigOut_4 := HEATING   ; end_if;
				else ;
				end_case;
			end_if;
		end_if;

	elsif PLC_control_type = ControlType_6 then
		(* MPNC 4xAI4 on RTU0 1=C+6 2=B+7 3=A+8 4=base+5, bis,ext varies *)
		if NODE_27_STATUS = NODE_NODE_OK then
			if only_mantain then
				; (* do nothing *)
			else
		        case n of
				1:
			    	if MPNC_DigDir_6 <> DigDir_OUT then MPNC_DigDir_6 := DigDir_OUT; end_if;
			        if MPNC_DigOut_6 <> HEATING    then MPNC_DigOut_6 := HEATING   ; end_if;
				2:
			    	if MPNC_DigDir_7 <> DigDir_OUT then MPNC_DigDir_7 := DigDir_OUT; end_if;
			        if MPNC_DigOut_7 <> HEATING    then MPNC_DigOut_7 := HEATING   ; end_if;
				3:
			    	if MPNC_DigDir_8 <> DigDir_OUT then MPNC_DigDir_8 := DigDir_OUT; end_if;
			        if MPNC_DigOut_8 <> HEATING    then MPNC_DigOut_8 := HEATING   ; end_if;
				4:
			    	if MPNC_DigDir_5 <> DigDir_OUT then MPNC_DigDir_5 := DigDir_OUT; end_if;
			        if MPNC_DigOut_5 <> HEATING    then MPNC_DigOut_5 := HEATING   ; end_if;
				else ;
				end_case;
			end_if;
		end_if;

	elsif PLC_control_type = ControlType_14 then
		(* n=1..4: MPNC base DigOut_1..4 *)
		if NODE_27_STATUS = NODE_NODE_OK then
			if only_mantain then
				; (* do nothing *)
			else
		        case n of
				1:
			    	if MPNC_DigDir_1 <> DigDir_OUT then MPNC_DigDir_1 := DigDir_OUT; end_if;
			        if MPNC_DigOut_1 <> HEATING    then MPNC_DigOut_1 := HEATING   ; end_if;
				2:
			    	if MPNC_DigDir_2 <> DigDir_OUT then MPNC_DigDir_2 := DigDir_OUT; end_if;
			        if MPNC_DigOut_2 <> HEATING    then MPNC_DigOut_2 := HEATING   ; end_if;
				3:
			    	if MPNC_DigDir_3 <> DigDir_OUT then MPNC_DigDir_3 := DigDir_OUT; end_if;
			        if MPNC_DigOut_3 <> HEATING    then MPNC_DigOut_3 := HEATING   ; end_if;
				4:
			    	if MPNC_DigDir_4 <> DigDir_OUT then MPNC_DigDir_4 := DigDir_OUT; end_if;
			        if MPNC_DigOut_4 <> HEATING    then MPNC_DigOut_4 := HEATING   ; end_if;
				else ;
				end_case;
		    end_if;
	    end_if;

	elsif PLC_control_type = ControlType_15 then
		(* TPAC1007_04_AD DigOut_8 *)
		if NODE_31_STATUS = NODE_NODE_OK then
	    	if PLC_DigDir_8 <> DigDir_OUT then PLC_DigDir_8 := DigDir_OUT; end_if;
	        if only_mantain then
				; (* do nothing *)
			else
		        if PLC_DigOut_8 <> HEATING then PLC_DigOut_8 := HEATING; end_if;
			end_if;
	    end_if;

	end_if;

END_FUNCTION
