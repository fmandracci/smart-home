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

FUNCTION EP_SetDigOut_relay
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
    n : UINT;
    value : BOOL;
END_VAR

	if PLC_control_type = ControlType_1 then
		if PLC_PRODUCT_ID = 16#1043030C then
			(* Fast I/O on GPIO *);
			case n of
        	1: if PLC_FastIO_5 <> value then PLC_FastIO_5 := value; end_if;
        	2: if PLC_FastIO_6 <> value then PLC_FastIO_6 := value; end_if;
        	3: if PLC_FastIO_7 <> value then PLC_FastIO_7 := value; end_if;
        	4: if PLC_FastIO_8 <> value then PLC_FastIO_8 := value; end_if;
			else ;
			end_case;
		elsif PLC_PRODUCT_ID = 16#100704AD or PLC_PRODUCT_ID = 16#100704AE or PLC_PRODUCT_ID = 16#100704AA or PLC_PRODUCT_ID = 16#100704AC then
			case n of
        	1: if PLC_DigDir_1 <> DigDir_OUT then PLC_DigDir_1 := DigDir_OUT; end_if;
        	2: if PLC_DigDir_2 <> DigDir_OUT then PLC_DigDir_2 := DigDir_OUT; end_if;
        	3: if PLC_DigDir_3 <> DigDir_OUT then PLC_DigDir_3 := DigDir_OUT; end_if;
        	4: if PLC_DigDir_4 <> DigDir_OUT then PLC_DigDir_4 := DigDir_OUT; end_if;
        	5: if PLC_DigDir_5 <> DigDir_OUT then PLC_DigDir_5 := DigDir_OUT; end_if;
        	6: if PLC_DigDir_6 <> DigDir_OUT then PLC_DigDir_6 := DigDir_OUT; end_if;
        	7: if PLC_DigDir_7 <> DigDir_OUT then PLC_DigDir_7 := DigDir_OUT; end_if;
        	8: if PLC_DigDir_8 <> DigDir_OUT then PLC_DigDir_8 := DigDir_OUT; end_if;
			else ;
			end_case;
			case n of
        	1: if PLC_DigOut_1 <> value then PLC_DigOut_1 := value; end_if;
        	2: if PLC_DigOut_2 <> value then PLC_DigOut_2 := value; end_if;
        	3: if PLC_DigOut_3 <> value then PLC_DigOut_3 := value; end_if;
        	4: if PLC_DigOut_4 <> value then PLC_DigOut_4 := value; end_if;
        	5: if PLC_DigOut_5 <> value then PLC_DigOut_5 := value; end_if;
        	6: if PLC_DigOut_6 <> value then PLC_DigOut_6 := value; end_if;
        	7: if PLC_DigOut_7 <> value then PLC_DigOut_7 := value; end_if;
        	8: if PLC_DigOut_8 <> value then PLC_DigOut_8 := value; end_if;
			else ;
			end_case;
		else
			; (* TP.. *)
		end_if; 

	elsif PLC_control_type = ControlType_7 or PLC_control_type = ControlType_9 then
		(* Fast I/O 7,8 on GPIO *);
		case n of
    	1: if PLC_FastIO_5 <> value then PLC_FastIO_5 := value; end_if;
    	2: if PLC_FastIO_6 <> value then PLC_FastIO_6 := value; end_if;
    	3: if PLC_FastIO_7 <> value then PLC_FastIO_7 := value; end_if;
    	4: if PLC_FastIO_8 <> value then PLC_FastIO_8 := value; end_if;
		else ;
		end_case;

	elsif PLC_control_type = ControlType_99 then
		;

	elsif PLC_control_type = ControlType_12 then
		(* Fast I/O on GPIO *);
		case n of
    	1: if PLC_FastIO_7 <> value then PLC_FastIO_7 := value; end_if;
		else ;
		end_case;

	elsif PLC_control_type = ControlType_13 then
		(* TPAC1007_04_AD Local I/O on RTU3 *)
		case n of
    	1: if PLC_DigDir_7 <> DigDir_OUT then PLC_DigDir_7 := DigDir_OUT; end_if;
    	2: if PLC_DigDir_8 <> DigDir_OUT then PLC_DigDir_8 := DigDir_OUT; end_if;
		else ;
		end_case;
		case n of
    	1: if PLC_DigOut_7 <> value then PLC_DigOut_7 := value; end_if;
    	2: if PLC_DigOut_8 <> value then PLC_DigOut_8 := value; end_if;
		else ;
		end_case;

	elsif PLC_control_type = ControlType_6 then
		(* n=1..4: MPNC base DigOut_1..4 *)
		case n of
		1:
	    	if MPNC_DigDir_1 <> DigDir_OUT then MPNC_DigDir_1 := DigDir_OUT; end_if;
	        if MPNC_DigOut_1 <> value      then MPNC_DigOut_1 := value     ; end_if;
		2:
	    	if MPNC_DigDir_2 <> DigDir_OUT then MPNC_DigDir_2 := DigDir_OUT; end_if;
	        if MPNC_DigOut_2 <> value      then MPNC_DigOut_2 := value     ; end_if;
		3:
	    	if MPNC_DigDir_3 <> DigDir_OUT then MPNC_DigDir_3 := DigDir_OUT; end_if;
	        if MPNC_DigOut_3 <> value      then MPNC_DigOut_3 := value     ; end_if;
		4:
	    	if MPNC_DigDir_4 <> DigDir_OUT then MPNC_DigDir_4 := DigDir_OUT; end_if;
	        if MPNC_DigOut_4 <> value      then MPNC_DigOut_4 := value     ; end_if;
		else ;
		end_case;

	elsif PLC_control_type = ControlType_14 then
		(* MPNC DO16 "C" on RTU0 *)
		case n of
    	1: if MPNC_DigOut_C_1 <> value then MPNC_DigOut_C_1 := value; end_if;
    	2: if MPNC_DigOut_C_2 <> value then MPNC_DigOut_C_2 := value; end_if;
    	3: if MPNC_DigOut_C_3 <> value then MPNC_DigOut_C_3 := value; end_if;
    	4: if MPNC_DigOut_C_4 <> value then MPNC_DigOut_C_4 := value; end_if;
    	5: if MPNC_DigOut_C_5 <> value then MPNC_DigOut_C_5 := value; end_if;
    	6: if MPNC_DigOut_C_6 <> value then MPNC_DigOut_C_6 := value; end_if;
    	7: if MPNC_DigOut_C_7 <> value then MPNC_DigOut_C_7 := value; end_if;
    	8: if MPNC_DigOut_C_8 <> value then MPNC_DigOut_C_8 := value; end_if;
		else ;
		end_case;

	elsif PLC_control_type = ControlType_15 then

		case n of
    	1: if PLC_DigDir_1 <> DigDir_OUT then PLC_DigDir_1 := DigDir_OUT; end_if;
    	2: if PLC_DigDir_2 <> DigDir_OUT then PLC_DigDir_2 := DigDir_OUT; end_if;
    	3: if PLC_DigDir_3 <> DigDir_OUT then PLC_DigDir_3 := DigDir_OUT; end_if;
    	4: if PLC_DigDir_4 <> DigDir_OUT then PLC_DigDir_4 := DigDir_OUT; end_if;
    	5: if PLC_DigDir_5 <> DigDir_OUT then PLC_DigDir_5 := DigDir_OUT; end_if;
    	6: if PLC_DigDir_6 <> DigDir_OUT then PLC_DigDir_6 := DigDir_OUT; end_if;
    	7: if PLC_DigDir_7 <> DigDir_OUT then PLC_DigDir_7 := DigDir_OUT; end_if;
		else ;
		end_case;
		case n of
    	1: if PLC_DigOut_1 <> value then PLC_DigOut_1 := value; end_if;
    	2: if PLC_DigOut_2 <> value then PLC_DigOut_2 := value; end_if;
    	3: if PLC_DigOut_3 <> value then PLC_DigOut_3 := value; end_if;
    	4: if PLC_DigOut_4 <> value then PLC_DigOut_4 := value; end_if;
    	5: if PLC_DigOut_5 <> value then PLC_DigOut_5 := value; end_if;
    	6: if PLC_DigOut_6 <> value then PLC_DigOut_6 := value; end_if;
    	7: if PLC_DigOut_7 <> value then PLC_DigOut_7 := value; end_if;
		else ;
		end_case;

	elsif PLC_control_type = ControlType_13 then
		(* TPAC1007_04_AD Local I/O on RTU3 *)
		; 
	end_if;

END_FUNCTION
