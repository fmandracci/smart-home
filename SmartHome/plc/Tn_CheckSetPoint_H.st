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

FUNCTION Tn_CheckSetPoint_H : INT
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_IN_OUT
    setpoint : INT;
END_VAR
VAR
	x : INT;
END_VAR;

	if setpoint <= 0 then
 	    x := HumiditySetPoint_max;
	else
		x := MIN(setpoint, HumiditySetPoint_max);
	end_if;
	x := MAX(x, HumiditySetPoint_min);

	if setpoint <> x then
		setpoint := x;
	end_if;

	Tn_CheckSetPoint_H := x;

END_FUNCTION
