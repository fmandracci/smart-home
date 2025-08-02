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

FUNCTION BA_ReadSensorsReady : BOOL
#import "Crosstable.gvl"
#import "Resource1.gvl"

	if PLC_control_type = ControlType_2 then
		(* MPNE_A, MPNE_B on RTU0 *)

		if PLC_BA_enabled_sensors <= 16 then
			BA_ReadSensorsReady := (NODE_11_STATUS = NODE_NODE_OK);
		else
			BA_ReadSensorsReady := (NODE_11_STATUS = NODE_NODE_OK) and (NODE_12_STATUS = NODE_NODE_OK);
		end_if;

	elsif PLC_control_type = ControlType_7 then
		(* Fast I/O on GPIO *)
		BA_ReadSensorsReady := true;

	elsif PLC_control_type = ControlType_9 then
		(* MPNE_E on RTU3 *)
		BA_ReadSensorsReady :=  (NODE_45_STATUS = NODE_NODE_OK);

	elsif PLC_control_type = ControlType_12 then
		(* Fast I/O on GPIO *)
		BA_ReadSensorsReady := true;

	elsif PLC_control_type = ControlType_13 then
		(* TPAC1007_04_AD Local I/O on RTU3 *)
		BA_ReadSensorsReady := (NODE_31_STATUS = NODE_NODE_OK);

	elsif PLC_control_type = ControlType_16 then
		(* TPAC1007_04_AD Local I/O on RTU3 *)
		BA_ReadSensorsReady := (NODE_31_STATUS = NODE_NODE_OK);

	elsif PLC_control_type = ControlType_14 or PLC_control_type = ControlType_6 then
		(* MPNC DI16 "A,B" + DO16 "A,B" on RTU0 *)
		BA_ReadSensorsReady := (NODE_27_STATUS = NODE_NODE_OK);

	else
		BA_ReadSensorsReady := false;

	end_if;

END_FUNCTION
