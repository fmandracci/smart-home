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

FUNCTION BA_TestConfig
#import "Crosstable.gvl"
#import "Resource1.gvl"

    BA_values[ 1] := PLC_BA_DigOut_1 ;
    BA_values[ 2] := PLC_BA_DigOut_2 ;
    BA_values[ 3] := PLC_BA_DigOut_3 ;
    BA_values[ 4] := PLC_BA_DigOut_4 ;
    BA_values[ 5] := PLC_BA_DigOut_5 ;
    BA_values[ 6] := PLC_BA_DigOut_6 ;
    BA_values[ 7] := PLC_BA_DigOut_7 ;
    BA_values[ 8] := PLC_BA_DigOut_8 ;

    BA_values[ 9] := PLC_BA_DigOut_9 ;
    BA_values[10] := PLC_BA_DigOut_10;
    BA_values[11] := PLC_BA_DigOut_11;
    BA_values[12] := PLC_BA_DigOut_12;
    BA_values[13] := PLC_BA_DigOut_13;
    BA_values[14] := PLC_BA_DigOut_14;
    BA_values[15] := PLC_BA_DigOut_15;
    BA_values[16] := PLC_BA_DigOut_16;

    BA_values[17] := PLC_BA_DigOut_17;
    BA_values[18] := PLC_BA_DigOut_18;
    BA_values[19] := PLC_BA_DigOut_19;
    BA_values[20] := PLC_BA_DigOut_20;
    BA_values[21] := PLC_BA_DigOut_21;
    BA_values[22] := PLC_BA_DigOut_22;
    BA_values[23] := PLC_BA_DigOut_23;
    BA_values[24] := PLC_BA_DigOut_24;

    BA_values[25] := PLC_BA_DigOut_25;
    BA_values[26] := PLC_BA_DigOut_26;
    BA_values[27] := PLC_BA_DigOut_27;
    BA_values[28] := PLC_BA_DigOut_28;
    BA_values[29] := PLC_BA_DigOut_29;
    BA_values[30] := PLC_BA_DigOut_30;
    BA_values[31] := PLC_BA_DigOut_31;
    BA_values[32] := PLC_BA_DigOut_32;

    BA_WriteConfigBits(BA_values);

END_FUNCTION
