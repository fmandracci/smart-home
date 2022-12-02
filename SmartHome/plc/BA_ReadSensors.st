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

FUNCTION BA_ReadSensors
#import "Crosstable.gvl"
#import "Resource1.gvl"

		(* 1/2 alarm sensors *)

        PLC_BA_DigIn_1 := BA_ReadSensor(1 );
        PLC_BA_DigIn_2 := BA_ReadSensor(2 );
        PLC_BA_DigIn_3 := BA_ReadSensor(3 );
        PLC_BA_DigIn_4 := BA_ReadSensor(4 );
        PLC_BA_DigIn_5 := BA_ReadSensor(5 );
        PLC_BA_DigIn_6 := BA_ReadSensor(6 );
        PLC_BA_DigIn_7 := BA_ReadSensor(7 );
        PLC_BA_DigIn_8 := BA_ReadSensor(8 );

        PLC_BA_DigIn_9 := BA_ReadSensor(9 );
        PLC_BA_DigIn_10:= BA_ReadSensor(10);
        PLC_BA_DigIn_11:= BA_ReadSensor(11);
        PLC_BA_DigIn_12:= BA_ReadSensor(12);
        PLC_BA_DigIn_13:= BA_ReadSensor(13);
        PLC_BA_DigIn_14:= BA_ReadSensor(14);
        PLC_BA_DigIn_15:= BA_ReadSensor(15);
        PLC_BA_DigIn_16:= BA_ReadSensor(16);

        PLC_BA_DigIn_17:= BA_ReadSensor(17);
        PLC_BA_DigIn_18:= BA_ReadSensor(18);
        PLC_BA_DigIn_19:= BA_ReadSensor(19);
        PLC_BA_DigIn_20:= BA_ReadSensor(20);
        PLC_BA_DigIn_21:= BA_ReadSensor(21);
        PLC_BA_DigIn_22:= BA_ReadSensor(22);
        PLC_BA_DigIn_23:= BA_ReadSensor(23);
        PLC_BA_DigIn_24:= BA_ReadSensor(24);

        PLC_BA_DigIn_25:= BA_ReadSensor(25);
        PLC_BA_DigIn_26:= BA_ReadSensor(26);
        PLC_BA_DigIn_27:= BA_ReadSensor(27);
        PLC_BA_DigIn_28:= BA_ReadSensor(28);
        PLC_BA_DigIn_29:= BA_ReadSensor(29);
        PLC_BA_DigIn_30:= BA_ReadSensor(30);
        PLC_BA_DigIn_31:= BA_ReadSensor(31);
        PLC_BA_DigIn_32:= BA_ReadSensor(32);

		(* 2/2 other sensors (blackout detection, ...) *)

		if PLC_control_type = ControlType_2 then
			(* MPNE_A, MPNE_B on RTU0 *)
			if PLC_PRODUCT_ID = 16#100704AD or PLC_PRODUCT_ID = 16#100704AA or PLC_PRODUCT_ID = 16#100704AC then
				PLC_BA_input_9  := PLC_DigIn_9 ;
			    PLC_BA_input_10 := PLC_DigIn_10;
			    PLC_BA_input_11 := PLC_DigIn_11;
				PLC_BA_input_12 := PLC_DigIn_12;
				PLC_BA_blackout_digin := PLC_DigIn_12; (* --> PLC_BA_BlackoutDetected Alarm *)
			elsif  PLC_PRODUCT_ID = 16#1043030C then
				PLC_BA_input_9  := PLC_FastIO_1 ;
			    PLC_BA_input_10 := PLC_FastIO_2;
			    PLC_BA_input_11 := PLC_FastIO_3;
				PLC_BA_input_12 := PLC_FastIO_4;
				PLC_BA_blackout_digin := PLC_FastIO_4; (* --> PLC_BA_BlackoutDetected Alarm *)
			else (* 16#100704AE *)
				PLC_BA_input_9  := false;
			    PLC_BA_input_10 := false;
			    PLC_BA_input_11 := false;
				PLC_BA_input_12 := false;
				PLC_BA_blackout_digin := false; (* --> PLC_BA_BlackoutDetected Alarm *)
			end_if;

		elsif PLC_control_type = ControlType_7 then
			(* Fast I/O on GPIO *)
			PLC_BA_input_9  := false;
		    PLC_BA_input_10 := false;
		    PLC_BA_input_11 := false;
			PLC_BA_input_12 := PLC_FastIO_4;
			PLC_BA_blackout_digin := PLC_FastIO_4; (* --> PLC_BA_BlackoutDetected Alarm *)

		elsif PLC_control_type = ControlType_12 then
			(* Fast I/O on GPIO *)
			PLC_BA_input_9  := false;
		    PLC_BA_input_10 := false;
		    PLC_BA_input_11 := false;
			PLC_BA_input_12 := PLC_FastIO_4;
			PLC_BA_blackout_digin := PLC_FastIO_4; (* --> PLC_BA_BlackoutDetected Alarm *)

		elsif PLC_control_type = ControlType_13 then
			(* TPAC1007_04_AD Local I/O on RTU3 *)
			PLC_BA_input_9  := PLC_DigIn_9 ;
		    PLC_BA_input_10 := PLC_DigIn_10;
		    PLC_BA_input_11 := PLC_DigIn_11;
			PLC_BA_input_12 := PLC_DigIn_12;
			PLC_BA_blackout_digin := PLC_DigIn_12; (* --> PLC_BA_BlackoutDetected Alarm *)

		elsif PLC_control_type = ControlType_14 or PLC_control_type = ControlType_6 then
			(* MPNC DI16 "A,B" + DO16 "A,B" on RTU0 *)
			PLC_BA_input_9  := false ;
		    PLC_BA_input_10 := false;
		    PLC_BA_input_11 := false;
			PLC_BA_input_12 := false;
			PLC_BA_blackout_digin := false; (* --> PLC_BA_BlackoutDetected Alarm *)

		elsif PLC_control_type = ControlType_16 then
			(* TPAC1007_04_AD Local I/O on RTU3 *)
			PLC_BA_input_9  := false ;
		    PLC_BA_input_10 := false;
		    PLC_BA_input_11 := false;
			PLC_BA_input_12 := false;
			PLC_BA_blackout_digin := PLC_DigIn_8; (* --> PLC_BA_BlackoutDetected Alarm *)

		end_if;
	
END_FUNCTION
