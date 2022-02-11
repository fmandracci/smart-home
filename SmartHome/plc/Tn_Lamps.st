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

PROGRAM Tn_Lamps 
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR
    LampImpulse_1 : LampImpulse;
    LampImpulse_2 : LampImpulse;
    LampImpulse_3 : LampImpulse;
    LampImpulse_4 : LampImpulse;
    LampImpulse_5 : LampImpulse;
END_VAR

    if PLC_Iam_T1 then
        if PLC_T1_enabled_lamps >= 1 then LampImpulse_1(x := 1, PLC_Tn_lamp_x := PLC_T1_lamp_1, SRV_Tn_lamp_x := SRV_T1_lamp_1, PLC_Tn_lamp_feedback_x  := PLC_T1_lamp_feedback_1); end_if;
        if PLC_T1_enabled_lamps >= 2 then LampImpulse_2(x := 2, PLC_Tn_lamp_x := PLC_T1_lamp_2, SRV_Tn_lamp_x := SRV_T1_lamp_2, PLC_Tn_lamp_feedback_x  := PLC_T1_lamp_feedback_2); end_if;
        if PLC_T1_enabled_lamps >= 3 then LampImpulse_3(x := 3, PLC_Tn_lamp_x := PLC_T1_lamp_3, SRV_Tn_lamp_x := SRV_T1_lamp_3, PLC_Tn_lamp_feedback_x  := PLC_T1_lamp_feedback_3); end_if;
        if PLC_T1_enabled_lamps >= 4 then LampImpulse_4(x := 4, PLC_Tn_lamp_x := PLC_T1_lamp_4, SRV_Tn_lamp_x := SRV_T1_lamp_4, PLC_Tn_lamp_feedback_x  := PLC_T1_lamp_feedback_4); end_if;
        if PLC_T1_enabled_lamps >= 5 then LampImpulse_5(x := 5, PLC_Tn_lamp_x := PLC_T1_lamp_5, SRV_Tn_lamp_x := SRV_T1_lamp_5, PLC_Tn_lamp_feedback_x  := PLC_T1_lamp_feedback_5); end_if;

    elsif PLC_Iam_T2 then
        if PLC_T2_enabled_lamps >= 1 then LampImpulse_1(x := 1, PLC_Tn_lamp_x := PLC_T2_lamp_1, SRV_Tn_lamp_x := SRV_T2_lamp_1, PLC_Tn_lamp_feedback_x  := PLC_T2_lamp_feedback_1); end_if;
        if PLC_T2_enabled_lamps >= 2 then LampImpulse_2(x := 2, PLC_Tn_lamp_x := PLC_T2_lamp_2, SRV_Tn_lamp_x := SRV_T2_lamp_2, PLC_Tn_lamp_feedback_x  := PLC_T2_lamp_feedback_2); end_if;
        if PLC_T2_enabled_lamps >= 3 then LampImpulse_3(x := 3, PLC_Tn_lamp_x := PLC_T2_lamp_3, SRV_Tn_lamp_x := SRV_T2_lamp_3, PLC_Tn_lamp_feedback_x  := PLC_T2_lamp_feedback_3); end_if;
        if PLC_T2_enabled_lamps >= 4 then LampImpulse_4(x := 4, PLC_Tn_lamp_x := PLC_T2_lamp_4, SRV_Tn_lamp_x := SRV_T2_lamp_4, PLC_Tn_lamp_feedback_x  := PLC_T2_lamp_feedback_4); end_if;
        if PLC_T2_enabled_lamps >= 5 then LampImpulse_5(x := 5, PLC_Tn_lamp_x := PLC_T2_lamp_5, SRV_Tn_lamp_x := SRV_T2_lamp_5, PLC_Tn_lamp_feedback_x  := PLC_T2_lamp_feedback_5); end_if;

    elsif PLC_Iam_T3 then
        if PLC_T3_enabled_lamps >= 1 then LampImpulse_1(x := 1, PLC_Tn_lamp_x := PLC_T3_lamp_1, SRV_Tn_lamp_x := SRV_T3_lamp_1, PLC_Tn_lamp_feedback_x  := PLC_T3_lamp_feedback_1); end_if;
        if PLC_T3_enabled_lamps >= 2 then LampImpulse_2(x := 2, PLC_Tn_lamp_x := PLC_T3_lamp_2, SRV_Tn_lamp_x := SRV_T3_lamp_2, PLC_Tn_lamp_feedback_x  := PLC_T3_lamp_feedback_2); end_if;
        if PLC_T3_enabled_lamps >= 3 then LampImpulse_3(x := 3, PLC_Tn_lamp_x := PLC_T3_lamp_3, SRV_Tn_lamp_x := SRV_T3_lamp_3, PLC_Tn_lamp_feedback_x  := PLC_T3_lamp_feedback_3); end_if;
        if PLC_T3_enabled_lamps >= 4 then LampImpulse_4(x := 4, PLC_Tn_lamp_x := PLC_T3_lamp_4, SRV_Tn_lamp_x := SRV_T3_lamp_4, PLC_Tn_lamp_feedback_x  := PLC_T3_lamp_feedback_4); end_if;
        if PLC_T3_enabled_lamps >= 5 then LampImpulse_5(x := 5, PLC_Tn_lamp_x := PLC_T3_lamp_5, SRV_Tn_lamp_x := SRV_T3_lamp_5, PLC_Tn_lamp_feedback_x  := PLC_T3_lamp_feedback_5); end_if;

    elsif PLC_Iam_T4 then
        if PLC_T4_enabled_lamps >= 1 then LampImpulse_1(x := 1, PLC_Tn_lamp_x := PLC_T4_lamp_1, SRV_Tn_lamp_x := SRV_T4_lamp_1, PLC_Tn_lamp_feedback_x  := PLC_T4_lamp_feedback_1); end_if;
        if PLC_T4_enabled_lamps >= 2 then LampImpulse_2(x := 2, PLC_Tn_lamp_x := PLC_T4_lamp_2, SRV_Tn_lamp_x := SRV_T4_lamp_2, PLC_Tn_lamp_feedback_x  := PLC_T4_lamp_feedback_2); end_if;
        if PLC_T4_enabled_lamps >= 3 then LampImpulse_3(x := 3, PLC_Tn_lamp_x := PLC_T4_lamp_3, SRV_Tn_lamp_x := SRV_T4_lamp_3, PLC_Tn_lamp_feedback_x  := PLC_T4_lamp_feedback_3); end_if;
        if PLC_T4_enabled_lamps >= 4 then LampImpulse_4(x := 4, PLC_Tn_lamp_x := PLC_T4_lamp_4, SRV_Tn_lamp_x := SRV_T4_lamp_4, PLC_Tn_lamp_feedback_x  := PLC_T4_lamp_feedback_4); end_if;
        if PLC_T4_enabled_lamps >= 5 then LampImpulse_5(x := 5, PLC_Tn_lamp_x := PLC_T4_lamp_5, SRV_Tn_lamp_x := SRV_T4_lamp_5, PLC_Tn_lamp_feedback_x  := PLC_T4_lamp_feedback_5); end_if;

    elsif PLC_Iam_T5 then
        if PLC_T5_enabled_lamps >= 1 then LampImpulse_1(x := 1, PLC_Tn_lamp_x := PLC_T5_lamp_1, SRV_Tn_lamp_x := SRV_T5_lamp_1, PLC_Tn_lamp_feedback_x  := PLC_T5_lamp_feedback_1); end_if;
        if PLC_T5_enabled_lamps >= 2 then LampImpulse_2(x := 2, PLC_Tn_lamp_x := PLC_T5_lamp_2, SRV_Tn_lamp_x := SRV_T5_lamp_2, PLC_Tn_lamp_feedback_x  := PLC_T5_lamp_feedback_2); end_if;
        if PLC_T5_enabled_lamps >= 3 then LampImpulse_3(x := 3, PLC_Tn_lamp_x := PLC_T5_lamp_3, SRV_Tn_lamp_x := SRV_T5_lamp_3, PLC_Tn_lamp_feedback_x  := PLC_T5_lamp_feedback_3); end_if;
        if PLC_T5_enabled_lamps >= 4 then LampImpulse_4(x := 4, PLC_Tn_lamp_x := PLC_T5_lamp_4, SRV_Tn_lamp_x := SRV_T5_lamp_4, PLC_Tn_lamp_feedback_x  := PLC_T5_lamp_feedback_4); end_if;
        if PLC_T5_enabled_lamps >= 5 then LampImpulse_5(x := 5, PLC_Tn_lamp_x := PLC_T5_lamp_5, SRV_Tn_lamp_x := SRV_T5_lamp_5, PLC_Tn_lamp_feedback_x  := PLC_T5_lamp_feedback_5); end_if;

    elsif PLC_Iam_T6 then
        if PLC_T6_enabled_lamps >= 1 then LampImpulse_1(x := 1, PLC_Tn_lamp_x := PLC_T6_lamp_1, SRV_Tn_lamp_x := SRV_T6_lamp_1, PLC_Tn_lamp_feedback_x  := PLC_T6_lamp_feedback_1); end_if;
        if PLC_T6_enabled_lamps >= 2 then LampImpulse_2(x := 2, PLC_Tn_lamp_x := PLC_T6_lamp_2, SRV_Tn_lamp_x := SRV_T6_lamp_2, PLC_Tn_lamp_feedback_x  := PLC_T6_lamp_feedback_2); end_if;
        if PLC_T6_enabled_lamps >= 3 then LampImpulse_3(x := 3, PLC_Tn_lamp_x := PLC_T6_lamp_3, SRV_Tn_lamp_x := SRV_T6_lamp_3, PLC_Tn_lamp_feedback_x  := PLC_T6_lamp_feedback_3); end_if;
        if PLC_T6_enabled_lamps >= 4 then LampImpulse_4(x := 4, PLC_Tn_lamp_x := PLC_T6_lamp_4, SRV_Tn_lamp_x := SRV_T6_lamp_4, PLC_Tn_lamp_feedback_x  := PLC_T6_lamp_feedback_4); end_if;
        if PLC_T6_enabled_lamps >= 5 then LampImpulse_5(x := 5, PLC_Tn_lamp_x := PLC_T6_lamp_5, SRV_Tn_lamp_x := SRV_T6_lamp_5, PLC_Tn_lamp_feedback_x  := PLC_T6_lamp_feedback_5); end_if;

    end_if;

END_PROGRAM
