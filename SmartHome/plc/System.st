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

PROGRAM System 
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR
	retval : WORD;
END_VAR

	if PLC_RELOAD_CONF then
		retval := EVT_Set(EVT_INITIALIZE);
		PLC_RELOAD_CONF := false;
		return;
	end_if;

	PLC_EP_isOK := PLC_Iam_EP or (NODE_01_STATUS = NODE_NODE_OK);
	PLC_T1_isOK := PLC_Iam_T1 or (NODE_02_STATUS = NODE_NODE_OK);
	PLC_T2_isOK := PLC_Iam_T2 or (NODE_03_STATUS = NODE_NODE_OK);
	PLC_T3_isOK := PLC_Iam_T3 or (NODE_04_STATUS = NODE_NODE_OK);
	PLC_T4_isOK := PLC_Iam_T4 or (NODE_05_STATUS = NODE_NODE_OK);
	PLC_T5_isOK := PLC_Iam_T5 or (NODE_06_STATUS = NODE_NODE_OK);
	PLC_T6_isOK := PLC_Iam_T6 or (NODE_07_STATUS = NODE_NODE_OK);
	PLC_BA_isOK := PLC_Iam_BA or (NODE_08_STATUS = NODE_NODE_OK);

	PLC_Tn_heating := (PLC_T1_heating and PLC_T1_control_type <> ControlType_15)
	               or (PLC_T2_heating and PLC_T2_control_type <> ControlType_15)
				   or (PLC_T3_heating and PLC_T3_control_type <> ControlType_15)
				   or (PLC_T4_heating and PLC_T4_control_type <> ControlType_15 and PLC_T4_control_type <> ControlType_6)
				   or (PLC_T5_heating and PLC_T5_control_type <> ControlType_15)
				   or (PLC_T6_heating and PLC_T6_control_type <> ControlType_15);

	PLC_time_bis := PLC_time + PLC_timeOffset;
	PLC_timeMin_bis := PLC_timeMin + PLC_timeOffset;
	PLC_timeMax_bis := PLC_timeMax + PLC_timeOffset;

END_PROGRAM
