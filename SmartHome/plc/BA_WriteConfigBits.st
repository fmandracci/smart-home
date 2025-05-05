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

FUNCTION BA_WriteConfigBits
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
    values: ARRAY [1..32] OF BOOL;
END_VAR;

        if PLC_control_type = ControlType_2 then
        (* MPNE_A, MPNE_B on RTU0 *)
            if MPNE_A_DigOut_17 <> values[ 1] then MPNE_A_DigOut_17 := values[ 1]; end_if;
            if MPNE_A_DigOut_18 <> values[ 2] then MPNE_A_DigOut_18 := values[ 2]; end_if;
            if MPNE_A_DigOut_19 <> values[ 3] then MPNE_A_DigOut_19 := values[ 3]; end_if;
            if MPNE_A_DigOut_20 <> values[ 4] then MPNE_A_DigOut_20 := values[ 4]; end_if;
            if MPNE_A_DigOut_21 <> values[ 5] then MPNE_A_DigOut_21 := values[ 5]; end_if;
            if MPNE_A_DigOut_22 <> values[ 6] then MPNE_A_DigOut_22 := values[ 6]; end_if;
            if MPNE_A_DigOut_23 <> values[ 7] then MPNE_A_DigOut_23 := values[ 7]; end_if;
            if MPNE_A_DigOut_24 <> values[ 8] then MPNE_A_DigOut_24 := values[ 8]; end_if;
            if MPNE_A_DigOut_25 <> values[ 9] then MPNE_A_DigOut_25 := values[ 9]; end_if;
            if MPNE_A_DigOut_26 <> values[10] then MPNE_A_DigOut_26 := values[10]; end_if;
            if MPNE_A_DigOut_27 <> values[11] then MPNE_A_DigOut_27 := values[11]; end_if;
            if MPNE_A_DigOut_28 <> values[12] then MPNE_A_DigOut_28 := values[12]; end_if;
            if MPNE_A_DigOut_29 <> values[13] then MPNE_A_DigOut_29 := values[13]; end_if;
            if MPNE_A_DigOut_30 <> values[14] then MPNE_A_DigOut_30 := values[14]; end_if;
            if MPNE_A_DigOut_31 <> values[15] then MPNE_A_DigOut_31 := values[15]; end_if;
            if MPNE_A_DigOut_32 <> values[16] then MPNE_A_DigOut_32 := values[16]; end_if;

            if MPNE_B_DigOut_17 <> values[17] then MPNE_B_DigOut_17 := values[17]; end_if;
            if MPNE_B_DigOut_18 <> values[18] then MPNE_B_DigOut_18 := values[18]; end_if;
            if MPNE_B_DigOut_19 <> values[19] then MPNE_B_DigOut_19 := values[19]; end_if;
            if MPNE_B_DigOut_20 <> values[20] then MPNE_B_DigOut_20 := values[20]; end_if;
            if MPNE_B_DigOut_21 <> values[21] then MPNE_B_DigOut_21 := values[21]; end_if;
            if MPNE_B_DigOut_22 <> values[22] then MPNE_B_DigOut_22 := values[22]; end_if;
            if MPNE_B_DigOut_23 <> values[23] then MPNE_B_DigOut_23 := values[23]; end_if;
            if MPNE_B_DigOut_24 <> values[24] then MPNE_B_DigOut_24 := values[24]; end_if;
            if MPNE_B_DigOut_25 <> values[25] then MPNE_B_DigOut_25 := values[25]; end_if;
            if MPNE_B_DigOut_26 <> values[26] then MPNE_B_DigOut_26 := values[26]; end_if;
            if MPNE_B_DigOut_27 <> values[27] then MPNE_B_DigOut_27 := values[27]; end_if;
            if MPNE_B_DigOut_28 <> values[28] then MPNE_B_DigOut_28 := values[28]; end_if;
            if MPNE_B_DigOut_29 <> values[29] then MPNE_B_DigOut_29 := values[29]; end_if;
            if MPNE_B_DigOut_30 <> values[30] then MPNE_B_DigOut_30 := values[30]; end_if;
            if MPNE_B_DigOut_31 <> values[31] then MPNE_B_DigOut_31 := values[31]; end_if;
            if MPNE_B_DigOut_32 <> values[32] then MPNE_B_DigOut_32 := values[32]; end_if;

    	elsif PLC_control_type = ControlType_9 then
			(* MPNE_E on RTU3 *)
            if MPNE_E_DigOut_17 <> values[ 1] then MPNE_E_DigOut_17 := values[ 1]; end_if;
            if MPNE_E_DigOut_18 <> values[ 2] then MPNE_E_DigOut_18 := values[ 2]; end_if;
            if MPNE_E_DigOut_19 <> values[ 3] then MPNE_E_DigOut_19 := values[ 3]; end_if;
            if MPNE_E_DigOut_20 <> values[ 4] then MPNE_E_DigOut_20 := values[ 4]; end_if;
            if MPNE_E_DigOut_21 <> values[ 5] then MPNE_E_DigOut_21 := values[ 5]; end_if;
            if MPNE_E_DigOut_22 <> values[ 6] then MPNE_E_DigOut_22 := values[ 6]; end_if;
            if MPNE_E_DigOut_23 <> values[ 7] then MPNE_E_DigOut_23 := values[ 7]; end_if;
            if MPNE_E_DigOut_24 <> values[ 8] then MPNE_E_DigOut_24 := values[ 8]; end_if;

        elsif PLC_control_type = ControlType_12 then
            (* Fast I/O on GPIO *)
            ; (* one enable only *)

        elsif PLC_control_type = ControlType_13 then
            (* TPAC1007_04_AD Local I/O on RTU3 *)
            ; (* one enable only *)

        elsif PLC_control_type = ControlType_6 then
            (* MPNC DI16 "A,B" + DO16 "A" on RTU0 *)
            if MPNC_DigOut_A_1  <> (values[ 1] or values[17]) then MPNC_DigOut_A_1  := (values[ 1] or values[17]); end_if;
            if MPNC_DigOut_A_2  <> (values[ 2] or values[18]) then MPNC_DigOut_A_2  := (values[ 2] or values[18]); end_if;
            if MPNC_DigOut_A_3  <> (values[ 3] or values[19]) then MPNC_DigOut_A_3  := (values[ 3] or values[19]); end_if;
            if MPNC_DigOut_A_4  <> (values[ 4] or values[20]) then MPNC_DigOut_A_4  := (values[ 4] or values[20]); end_if;
            if MPNC_DigOut_A_5  <> (values[ 5] or values[21]) then MPNC_DigOut_A_5  := (values[ 5] or values[21]); end_if;
            if MPNC_DigOut_A_6  <> (values[ 6] or values[22]) then MPNC_DigOut_A_6  := (values[ 6] or values[22]); end_if;
            if MPNC_DigOut_A_7  <> (values[ 7] or values[23]) then MPNC_DigOut_A_7  := (values[ 7] or values[23]); end_if;
            if MPNC_DigOut_A_8  <> (values[ 8] or values[24]) then MPNC_DigOut_A_8  := (values[ 8] or values[24]); end_if;
            if MPNC_DigOut_A_9  <> (values[ 9] or values[25]) then MPNC_DigOut_A_9  := (values[ 9] or values[25]); end_if;
            if MPNC_DigOut_A_10 <> (values[10] or values[26]) then MPNC_DigOut_A_10 := (values[10] or values[26]); end_if;
            if MPNC_DigOut_A_11 <> (values[11] or values[27]) then MPNC_DigOut_A_11 := (values[11] or values[27]); end_if;
            if MPNC_DigOut_A_12 <> (values[12] or values[28]) then MPNC_DigOut_A_12 := (values[12] or values[28]); end_if;
            if MPNC_DigOut_A_13 <> (values[13] or values[29]) then MPNC_DigOut_A_13 := (values[13] or values[29]); end_if;
            if MPNC_DigOut_A_14 <> (values[14] or values[30]) then MPNC_DigOut_A_14 := (values[14] or values[30]); end_if;
            if MPNC_DigOut_A_15 <> (values[15] or values[31]) then MPNC_DigOut_A_15 := (values[15] or values[31]); end_if;
            if MPNC_DigOut_A_16 <> (values[16] or values[32]) then MPNC_DigOut_A_16 := (values[16] or values[32]); end_if;

        elsif PLC_control_type = ControlType_14 then
            (* MPNC DI16 "A,B" + DO16 "A,B" on RTU0 *)
            if MPNC_DigOut_A_1  <> values[ 1] then MPNC_DigOut_A_1  := values[ 1]; end_if;
            if MPNC_DigOut_A_2  <> values[ 2] then MPNC_DigOut_A_2  := values[ 2]; end_if;
            if MPNC_DigOut_A_3  <> values[ 3] then MPNC_DigOut_A_3  := values[ 3]; end_if;
            if MPNC_DigOut_A_4  <> values[ 4] then MPNC_DigOut_A_4  := values[ 4]; end_if;
            if MPNC_DigOut_A_5  <> values[ 5] then MPNC_DigOut_A_5  := values[ 5]; end_if;
            if MPNC_DigOut_A_6  <> values[ 6] then MPNC_DigOut_A_6  := values[ 6]; end_if;
            if MPNC_DigOut_A_7  <> values[ 7] then MPNC_DigOut_A_7  := values[ 7]; end_if;
            if MPNC_DigOut_A_8  <> values[ 8] then MPNC_DigOut_A_8  := values[ 8]; end_if;
            if MPNC_DigOut_A_9  <> values[ 9] then MPNC_DigOut_A_9  := values[ 9]; end_if;
            if MPNC_DigOut_A_10 <> values[10] then MPNC_DigOut_A_10 := values[10]; end_if;
            if MPNC_DigOut_A_11 <> values[11] then MPNC_DigOut_A_11 := values[11]; end_if;
            if MPNC_DigOut_A_12 <> values[12] then MPNC_DigOut_A_12 := values[12]; end_if;
            if MPNC_DigOut_A_13 <> values[13] then MPNC_DigOut_A_13 := values[13]; end_if;
            if MPNC_DigOut_A_14 <> values[14] then MPNC_DigOut_A_14 := values[14]; end_if;
            if MPNC_DigOut_A_15 <> values[15] then MPNC_DigOut_A_15 := values[15]; end_if;
            if MPNC_DigOut_A_16 <> values[16] then MPNC_DigOut_A_16 := values[16]; end_if;

            if MPNC_DigOut_B_1  <> values[17] then MPNC_DigOut_B_1  := values[17]; end_if;
            if MPNC_DigOut_B_2  <> values[18] then MPNC_DigOut_B_2  := values[18]; end_if;
            if MPNC_DigOut_B_3  <> values[19] then MPNC_DigOut_B_3  := values[19]; end_if;
            if MPNC_DigOut_B_4  <> values[20] then MPNC_DigOut_B_4  := values[20]; end_if;
            if MPNC_DigOut_B_5  <> values[21] then MPNC_DigOut_B_5  := values[21]; end_if;
            if MPNC_DigOut_B_6  <> values[22] then MPNC_DigOut_B_6  := values[22]; end_if;
            if MPNC_DigOut_B_7  <> values[23] then MPNC_DigOut_B_7  := values[23]; end_if;
            if MPNC_DigOut_B_8  <> values[24] then MPNC_DigOut_B_8  := values[24]; end_if;
            if MPNC_DigOut_B_9  <> values[25] then MPNC_DigOut_B_9  := values[25]; end_if;
            if MPNC_DigOut_B_10 <> values[26] then MPNC_DigOut_B_10 := values[26]; end_if;
            if MPNC_DigOut_B_11 <> values[27] then MPNC_DigOut_B_11 := values[27]; end_if;
            if MPNC_DigOut_B_12 <> values[28] then MPNC_DigOut_B_12 := values[28]; end_if;
            if MPNC_DigOut_B_13 <> values[29] then MPNC_DigOut_B_13 := values[29]; end_if;
            if MPNC_DigOut_B_14 <> values[30] then MPNC_DigOut_B_14 := values[30]; end_if;
            if MPNC_DigOut_B_15 <> values[31] then MPNC_DigOut_B_15 := values[31]; end_if;
            if MPNC_DigOut_B_16 <> values[32] then MPNC_DigOut_B_16 := values[32]; end_if;

        elsif PLC_control_type = ControlType_16 then
            (* TPAC1007_04_AD Local I/O on RTU3 *)
			;
        end_if;

END_FUNCTION
