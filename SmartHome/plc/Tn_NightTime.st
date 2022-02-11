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

PROGRAM Tn_NightTime 
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR
	hhmm : UINT;
	nighttime : BOOL;
END_VAR

	hhmm := PLC_Hours * 100 + PLC_Minutes;

	if PLC_sunrise < PLC_sunset then
		nighttime := hhmm < PLC_sunrise or PLC_sunset <= hhmm;
	elsif PLC_sunrise = PLC_sunset then
		nighttime := false;
	else
		nighttime := PLC_sunset <= hhmm and hhmm < PLC_sunrise;
	end_if;

	PLC_nighttime := nighttime;
	if PLC_Iam_T1 then
		PLC_T1_nighttime := nighttime;
    end_if;
	if PLC_Iam_T2 then
		PLC_T2_nighttime := nighttime;
    end_if;
	if PLC_Iam_T3 then
		PLC_T3_nighttime := nighttime;
    end_if;
	if PLC_Iam_T4 then
		PLC_T4_nighttime := nighttime;
    end_if;
	if PLC_Iam_T5 then
		PLC_T5_nighttime := nighttime;
    end_if;
	if PLC_Iam_T6 then
		PLC_T6_nighttime := nighttime;
    end_if;

END_PROGRAM
