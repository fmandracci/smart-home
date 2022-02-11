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

FUNCTION Tn_Watchdog
#import "Crosstable.gvl"
#import "Resource1.gvl"

	if (PLC_control_type = ControlType_4) or (PLC_control_type = ControlType_5) or (PLC_control_type = ControlType_8) then
		if ARQ_Watchdog <> WatchDogTimeout_s and NODE_10_STATUS = NODE_NODE_OK then
			ARQ_Watchdog := WatchDogTimeout_s;
		end_if;
	end_if;

END_FUNCTION
