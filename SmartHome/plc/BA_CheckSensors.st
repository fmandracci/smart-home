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

FUNCTION BA_CheckSensors : BOOL
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
    index : UINT;
END_VAR
VAR
	mask : UDINT;
	konfig: DWORD;
	all_ok : BOOL;
END_VAR;

	case index of
	ALARM_INDEX_NOTHING: mask := ALARM_MASK_NOTHING;
	ALARM_INDEX_DAYTIME: mask := PLC_BA_daytime_bitmask;
	ALARM_INDEX_NIGHTTIME: mask := PLC_BA_nighttime_bitmask;
	ALARM_INDEX_EVERYTHING: mask := PLC_BA_everything_bitmask;
	else mask := ALARM_MASK_NOTHING;
	end_case;

	konfig := UDINT_TO_DWORD(mask);
	all_ok := true;

    BA_CheckSensor(1 , konfig, 16#00000001, PLC_BA_DigIn_1 , PLC_BA_OK_1 , all_ok);
    BA_CheckSensor(2 , konfig, 16#00000002, PLC_BA_DigIn_2 , PLC_BA_OK_2 , all_ok);
    BA_CheckSensor(3 , konfig, 16#00000004, PLC_BA_DigIn_3 , PLC_BA_OK_3 , all_ok);
    BA_CheckSensor(4 , konfig, 16#00000008, PLC_BA_DigIn_4 , PLC_BA_OK_4 , all_ok);
    BA_CheckSensor(5 , konfig, 16#00000010, PLC_BA_DigIn_5 , PLC_BA_OK_5 , all_ok);
    BA_CheckSensor(6 , konfig, 16#00000020, PLC_BA_DigIn_6 , PLC_BA_OK_6 , all_ok);
    BA_CheckSensor(7 , konfig, 16#00000040, PLC_BA_DigIn_7 , PLC_BA_OK_7 , all_ok);
    BA_CheckSensor(8 , konfig, 16#00000080, PLC_BA_DigIn_8 , PLC_BA_OK_8 , all_ok);
    BA_CheckSensor(9 , konfig, 16#00000100, PLC_BA_DigIn_9 , PLC_BA_OK_9 , all_ok);
    BA_CheckSensor(10, konfig, 16#00000200, PLC_BA_DigIn_10, PLC_BA_OK_10, all_ok);
    BA_CheckSensor(11, konfig, 16#00000400, PLC_BA_DigIn_11, PLC_BA_OK_11, all_ok);
    BA_CheckSensor(12, konfig, 16#00000800, PLC_BA_DigIn_12, PLC_BA_OK_12, all_ok);
    BA_CheckSensor(13, konfig, 16#00001000, PLC_BA_DigIn_13, PLC_BA_OK_13, all_ok);
    BA_CheckSensor(14, konfig, 16#00002000, PLC_BA_DigIn_14, PLC_BA_OK_14, all_ok);
    BA_CheckSensor(15, konfig, 16#00004000, PLC_BA_DigIn_15, PLC_BA_OK_15, all_ok);
    BA_CheckSensor(16, konfig, 16#00008000, PLC_BA_DigIn_16, PLC_BA_OK_16, all_ok);

    BA_CheckSensor(17, konfig, 16#00010000, PLC_BA_DigIn_17, PLC_BA_OK_17, all_ok);
    BA_CheckSensor(18, konfig, 16#00020000, PLC_BA_DigIn_18, PLC_BA_OK_18, all_ok);
    BA_CheckSensor(19, konfig, 16#00040000, PLC_BA_DigIn_19, PLC_BA_OK_19, all_ok);
    BA_CheckSensor(20, konfig, 16#00080000, PLC_BA_DigIn_20, PLC_BA_OK_20, all_ok);
    BA_CheckSensor(21, konfig, 16#00100000, PLC_BA_DigIn_21, PLC_BA_OK_21, all_ok);
    BA_CheckSensor(22, konfig, 16#00200000, PLC_BA_DigIn_22, PLC_BA_OK_22, all_ok);
    BA_CheckSensor(23, konfig, 16#00400000, PLC_BA_DigIn_23, PLC_BA_OK_23, all_ok);
    BA_CheckSensor(24, konfig, 16#00800000, PLC_BA_DigIn_24, PLC_BA_OK_24, all_ok);
    BA_CheckSensor(25, konfig, 16#01000000, PLC_BA_DigIn_25, PLC_BA_OK_25, all_ok);
    BA_CheckSensor(26, konfig, 16#02000000, PLC_BA_DigIn_26, PLC_BA_OK_26, all_ok);
    BA_CheckSensor(27, konfig, 16#04000000, PLC_BA_DigIn_27, PLC_BA_OK_27, all_ok);
    BA_CheckSensor(28, konfig, 16#08000000, PLC_BA_DigIn_28, PLC_BA_OK_28, all_ok);
    BA_CheckSensor(29, konfig, 16#10000000, PLC_BA_DigIn_29, PLC_BA_OK_29, all_ok);
    BA_CheckSensor(30, konfig, 16#20000000, PLC_BA_DigIn_30, PLC_BA_OK_30, all_ok);
    BA_CheckSensor(31, konfig, 16#40000000, PLC_BA_DigIn_31, PLC_BA_OK_31, all_ok);
    BA_CheckSensor(32, konfig, 16#80000000, PLC_BA_DigIn_32, PLC_BA_OK_32, all_ok);

	BA_CheckSensors := all_ok;

END_FUNCTION
