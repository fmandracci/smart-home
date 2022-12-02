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

FUNCTION BA_SetDigOuts
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
	green    : BOOL;
	red      : BOOL;
	yellow1  : BOOL;
	yellow2  : BOOL;

	siren    : BOOL;
	enable_A : BOOL;
	enable_B : BOOL;
	enable_C : BOOL;
END_VAR

	if PLC_control_type = ControlType_2 then
		if PLC_PRODUCT_ID = 16#100704AD or PLC_PRODUCT_ID = 16#100704AA or PLC_PRODUCT_ID = 16#100704AC then
			(* sensors: MPNE_A, MPNE_B on RTU0; leds: TPAC1007_04_AD/AA/AC Local I/O on RTU3 *)

        	if PLC_DigDir_1 <> DigDir_OUT then PLC_DigDir_1 := DigDir_OUT; end_if;
        	if PLC_DigDir_2 <> DigDir_OUT then PLC_DigDir_2 := DigDir_OUT; end_if;
        	if PLC_DigDir_3 <> DigDir_OUT then PLC_DigDir_3 := DigDir_OUT; end_if;
        	if PLC_DigDir_4 <> DigDir_OUT then PLC_DigDir_4 := DigDir_OUT; end_if;

        	if PLC_DigDir_5 <> DigDir_OUT then PLC_DigDir_5 := DigDir_OUT; end_if;
        	if PLC_DigDir_6 <> DigDir_OUT then PLC_DigDir_6 := DigDir_OUT; end_if;
        	if PLC_DigDir_7 <> DigDir_OUT then PLC_DigDir_7 := DigDir_OUT; end_if;
        	if PLC_DigDir_8 <> DigDir_OUT then PLC_DigDir_8 := DigDir_OUT; end_if;

	        if PLC_DigOut_1 <> green    then PLC_DigOut_1 := green   ; end_if;
	        if PLC_DigOut_2 <> red      then PLC_DigOut_2 := red     ; end_if;
	        if PLC_DigOut_3 <> yellow1  then PLC_DigOut_3 := yellow1 ; end_if;
	        if PLC_DigOut_4 <> yellow2  then PLC_DigOut_4 := yellow2 ; end_if;

	        if PLC_DigOut_5 <> siren    then PLC_DigOut_5 := siren   ; end_if;
	        if PLC_DigOut_6 <> enable_A then PLC_DigOut_6 := enable_A; end_if;
	        if PLC_DigOut_7 <> enable_B then PLC_DigOut_7 := enable_B; end_if;
	        if PLC_DigOut_8 <> enable_C then PLC_DigOut_8 := enable_C; end_if;

		elsif PLC_PRODUCT_ID = 16#100704AE then
			(* sensors: MPNE_A, MPNE_B on RTU0; leds: TPAC1007_04_AE Local I/O on RTU3 *)
        	if PLC_DigDir_1 <> DigDir_OUT then PLC_DigDir_1 := DigDir_OUT; end_if;
        	if PLC_DigDir_2 <> DigDir_OUT then PLC_DigDir_2 := DigDir_OUT; end_if;
        	if PLC_DigDir_3 <> DigDir_OUT then PLC_DigDir_3 := DigDir_OUT; end_if;
        	if PLC_DigDir_4 <> DigDir_OUT then PLC_DigDir_4 := DigDir_OUT; end_if;

        	if PLC_DigDir_5 <> DigDir_OUT then PLC_DigDir_5 := DigDir_OUT; end_if;
        	if PLC_DigDir_6 <> DigDir_OUT then PLC_DigDir_6 := DigDir_OUT; end_if;
        	if PLC_DigDir_7 <> DigDir_OUT then PLC_DigDir_7 := DigDir_OUT; end_if;
        	if PLC_DigDir_8 <> DigDir_OUT then PLC_DigDir_8 := DigDir_OUT; end_if;

            if getBit(PLC_AnInConf_1, 16#0001) <> green    then setBit(16#0001, green   , PLC_AnInConf_1); end_if;
            if getBit(PLC_AnInConf_1, 16#0002) <> red      then setBit(16#0002, red     , PLC_AnInConf_1); end_if;
            if getBit(PLC_AnInConf_1, 16#0004) <> yellow1  then setBit(16#0004, yellow1 , PLC_AnInConf_1); end_if;
            if getBit(PLC_AnInConf_1, 16#0008) <> yellow2  then setBit(16#0008, yellow2 , PLC_AnInConf_1); end_if;

            if getBit(PLC_AnInConf_1, 16#0010) <> siren    then setBit(16#0010, siren   , PLC_AnInConf_1); end_if;
            if getBit(PLC_AnInConf_1, 16#0020) <> enable_A then setBit(16#0020, enable_A, PLC_AnInConf_1); end_if;
            if getBit(PLC_AnInConf_1, 16#0040) <> enable_B then setBit(16#0040, enable_B, PLC_AnInConf_1); end_if;
            if getBit(PLC_AnInConf_1, 16#0080) <> enable_C then setBit(16#0080, enable_C, PLC_AnInConf_1); end_if;

	    elsif PLC_PRODUCT_ID = 16#1043030C then
			(* sensors: MPNE_A, MPNE_B on RTU0; leds: Fast I/O on GPIO *)
			(* no leds *)
	        if PLC_FastIO_5 <> siren    then PLC_FastIO_5 := siren   ; end_if;
	        if PLC_FastIO_6 <> enable_A then PLC_FastIO_6 := enable_A; end_if;
	        if PLC_FastIO_7 <> enable_B then PLC_FastIO_7 := enable_B; end_if;
	        if PLC_FastIO_8 <> enable_C then PLC_FastIO_8 := enable_C; end_if;
	
		end_if;

	elsif PLC_control_type = ControlType_7 then
		(* Fast I/O on GPIO *)
		(* no leds, all enabled in one DigOut *)
        if PLC_FastIO_5 <> siren                              then PLC_FastIO_5 := siren                             ; end_if;
        if PLC_FastIO_6 <> (enable_A or enable_B or enable_C) then PLC_FastIO_6 := (enable_A or enable_B or enable_C); end_if;

	elsif PLC_control_type = ControlType_12 then
		(* Fast I/O on GPIO *)
		(* no leds, all enabled in one DigOut *)
        if PLC_FastIO_5 <> siren                              then PLC_FastIO_5 := siren                             ; end_if;
        if PLC_FastIO_6 <> (enable_A or enable_B or enable_C) then PLC_FastIO_6 := (enable_A or enable_B or enable_C); end_if;

	elsif PLC_control_type = ControlType_13 then
		(* TPAC1007_04_AD Local I/O on RTU3 *)
		(* no leds, all enabled in one DigOut *)
    	if PLC_DigDir_5 <> DigDir_OUT then PLC_DigDir_5 := DigDir_OUT; end_if;
    	if PLC_DigDir_6 <> DigDir_OUT then PLC_DigDir_6 := DigDir_OUT; end_if;

        if PLC_DigOut_5 <> siren                              then PLC_DigOut_5 := siren                             ; end_if;
        if PLC_DigOut_6 <> (enable_A or enable_B or enable_C) then PLC_DigOut_6 := (enable_A or enable_B or enable_C); end_if;

	elsif PLC_control_type = ControlType_6 then
		; (* no leds nor digouts *)

	elsif PLC_control_type = ControlType_14 then
		(* MPNC DI16 "A,B" + DO16 "A,B" on RTU0; leds on base DO *)
		(* no leds*)

    	if MPNC_DigDir_5 <> DigDir_OUT then MPNC_DigDir_5 := DigDir_OUT; end_if;
    	if MPNC_DigDir_6 <> DigDir_OUT then MPNC_DigDir_6 := DigDir_OUT; end_if;
    	if MPNC_DigDir_7 <> DigDir_OUT then MPNC_DigDir_7 := DigDir_OUT; end_if;
    	if MPNC_DigDir_8 <> DigDir_OUT then MPNC_DigDir_8 := DigDir_OUT; end_if;

        if MPNC_DigOut_5 <> siren    then MPNC_DigOut_5 := siren   ; end_if;
        if MPNC_DigOut_6 <> enable_A then MPNC_DigOut_6 := enable_A; end_if;
        if MPNC_DigOut_7 <> enable_B then MPNC_DigOut_7 := enable_B; end_if;
        if MPNC_DigOut_8 <> enable_C then MPNC_DigOut_8 := enable_C; end_if;

	elsif PLC_control_type = ControlType_16 then
		(* TPAC1007_04_AD Local I/O on RTU3 *)
    	if PLC_DigDir_5 <> DigDir_OUT then PLC_DigDir_5 := DigDir_OUT; end_if;
    	if PLC_DigDir_6 <> DigDir_OUT then PLC_DigDir_6 := DigDir_OUT; end_if;
    	if PLC_DigDir_7 <> DigDir_OUT then PLC_DigDir_7 := DigDir_OUT; end_if;

        if PLC_DigOut_5 <> siren                  then PLC_DigOut_5 := siren;                  end_if;
        if PLC_DigOut_6 <> (enable_A or enable_B) then PLC_DigOut_6 := (enable_A or enable_B); end_if;
        if PLC_DigOut_7 <> (enable_C)             then PLC_DigOut_7 := (enable_C);             end_if;

	end_if;

END_FUNCTION
