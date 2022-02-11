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

FUNCTION BA_ClearOK : UINT
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
    n : UINT;
END_VAR

	if PLC_BA_enabled_sensors >= n then
		BA_ClearOK := ALARM_SENSOR_IGNORED;
	else
		BA_ClearOK := ALARM_SENSOR_DISABLED;
	end_if;

END_FUNCTION
