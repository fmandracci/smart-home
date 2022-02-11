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

PROGRAM EP_Wattmeters 
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR
	timer_blackout : TON;
	mask : UINT;
END_VAR;

    if not PLC_Iam_EP then
		return;
	end_if;

	(* --------------------- each second --------------------- *)

	mask := 0;

    if PLC_EP_enabled_wattmeters >= 1 then
		if (PLC_control_type = ControlType_6 and NODE_32_STATUS = NODE_NODE_OK) or (PLC_control_type <> ControlType_6 and NODE_15_STATUS = NODE_NODE_OK) then
			mask := mask + 1;
			EP_WattmeterFull(1, PLC_EP_wattmeter_M_W, PLC_EP_wattmeter_M_var, PLC_EP_wattmeter_M_VA,
			                 PLC_EP_wattmeter_M_pf, PLC_EP_wattmeter_M_Hz, PLC_EP_wattmeter_M_V,
							 PLC_EP_wattmeter_M_1_A, PLC_EP_wattmeter_M_2_A, PLC_EP_wattmeter_M_3_A, PLC_EP_wattmeter_M_A,
							 PLC_EP_wattmeter_M_kWh, PLC_EP_wattmeter_M_e_kWh);

			(* ------- blackout detection ------- *)
			if BlackoutDetected_enable then
				if PLC_EP_blackout_flag then
					(* NB: no delay *)
					PLC_EP_blackout_flag := false; (* --> falling PLC_EP_BlackoutDetected Alarm *)
					timer_blackout(IN := FALSE);
				end_if;
			end_if;

			(* ------- overload detection ------- *)
			if (PLC_EP_overload_W > 0) and (PLC_EP_wattmeter_M_W > UINT_TO_INT(PLC_EP_overload_W)) then
				PLC_EP_overload_flag := true; (* --> rising PLC_EP_OverloadDetected Alarm *)
			else
				if PLC_EP_overload_flag then PLC_EP_overload_flag := false; end_if; (* NB: avoid useless alarm checking in the plc engine *)
			end_if;

		else
			(* ------- blackout detection ------- *)
			if BlackoutDetected_enable then
				timer_blackout(IN := TRUE, PT := BlackoutDetected_delay); 
				if timer_blackout.Q then
					timer_blackout(IN := FALSE);
					PLC_EP_blackout_flag := true; (* --> rising PLC_EP_BlackoutDetected Alarm *)
					(* ------- overload detection ------- *)
					if PLC_EP_overload_flag then PLC_EP_overload_flag := false; end_if; (* NB: avoid useless alarm checking in the plc engine *)
				end_if;
			end_if;

		end_if;
    end_if;

    if PLC_EP_enabled_wattmeters >= 2 then
		if (PLC_control_type = ControlType_6 and NODE_33_STATUS = NODE_NODE_OK) or (PLC_control_type <> ControlType_6 and NODE_16_STATUS = NODE_NODE_OK)  then
			mask := mask + 2;
			EP_WattmeterFull(2, PLC_EP_wattmeter_F_W, PLC_EP_wattmeter_F_var, PLC_EP_wattmeter_F_VA,
			                 PLC_EP_wattmeter_F_pf, PLC_EP_wattmeter_F_Hz, PLC_EP_wattmeter_F_V,
							 PLC_EP_wattmeter_F_1_A, PLC_EP_wattmeter_F_2_A, PLC_EP_wattmeter_F_3_A, PLC_EP_wattmeter_F_A,
							 PLC_EP_wattmeter_F_kWh, PLC_EP_wattmeter_F_e_kWh);
	    else
			; (* TODO: timer? *)
		end_if;
    end_if;

    if PLC_EP_enabled_wattmeters >= 3 then
		if (PLC_control_type = ControlType_6 and NODE_34_STATUS = NODE_NODE_OK) or (PLC_control_type <> ControlType_6 and NODE_17_STATUS = NODE_NODE_OK)  then
			mask := mask + 4;
			EP_Wattmeter(3, PLC_EP_wattmeter01_W, PLC_EP_wattmeter01_var, PLC_EP_wattmeter01_VA,
						PLC_EP_wattmeter01_kWh);
	    else
			; (* TODO: timer? *)
		end_if;
    end_if;

    if PLC_EP_enabled_wattmeters >= 4 then
		if (PLC_control_type = ControlType_6 and NODE_35_STATUS = NODE_NODE_OK) or (PLC_control_type <> ControlType_6 and NODE_18_STATUS = NODE_NODE_OK)  then
			mask := mask + 8;
			EP_Wattmeter(4, PLC_EP_wattmeter02_W, PLC_EP_wattmeter02_var, PLC_EP_wattmeter02_VA,
						PLC_EP_wattmeter02_kWh);
	    else
			; (* TODO: timer? *)
		end_if;
    end_if;

    if PLC_EP_enabled_wattmeters >= 5 then
		if (PLC_control_type = ControlType_6 and NODE_36_STATUS = NODE_NODE_OK) or (PLC_control_type <> ControlType_6 and NODE_19_STATUS = NODE_NODE_OK)  then
			mask := mask + 16;
			EP_Wattmeter(5, PLC_EP_wattmeter03_W, PLC_EP_wattmeter03_var, PLC_EP_wattmeter03_VA,
						 PLC_EP_wattmeter03_kWh);
	    else
			; (* TODO: timer? *)
		end_if;
    end_if;

    if PLC_EP_enabled_wattmeters >= 6 then
		if (PLC_control_type = ControlType_6 and NODE_37_STATUS = NODE_NODE_OK) or (PLC_control_type <> ControlType_6 and NODE_20_STATUS = NODE_NODE_OK)  then
			mask := mask + 32;
			EP_Wattmeter(6, PLC_EP_wattmeter04_W, PLC_EP_wattmeter04_var, PLC_EP_wattmeter04_VA,
						 PLC_EP_wattmeter04_kWh);
	    else
			; (* TODO: timer? *)
		end_if;
    end_if;

    if PLC_EP_enabled_wattmeters >= 7 then
		if (PLC_control_type = ControlType_6 and NODE_38_STATUS = NODE_NODE_OK) or (PLC_control_type <> ControlType_6 and NODE_21_STATUS = NODE_NODE_OK)  then
			mask := mask + 64;
			EP_Wattmeter(7, PLC_EP_wattmeter05_W, PLC_EP_wattmeter05_var, PLC_EP_wattmeter05_VA,
						 PLC_EP_wattmeter05_kWh);
	    else
			; (* TODO: timer? *)
		end_if;
    end_if;

    if PLC_EP_enabled_wattmeters >= 8 then
		if (PLC_control_type = ControlType_6 and NODE_39_STATUS = NODE_NODE_OK) or (PLC_control_type <> ControlType_6 and NODE_22_STATUS = NODE_NODE_OK)  then
			mask := mask + 128;
			EP_Wattmeter(8, PLC_EP_wattmeter06_W, PLC_EP_wattmeter06_var, PLC_EP_wattmeter06_VA,
						 PLC_EP_wattmeter06_kWh);
	    else
			; (* TODO: timer? *)
		end_if;
    end_if;

    if PLC_EP_enabled_wattmeters >= 9 then
		if (PLC_control_type = ControlType_6 and NODE_40_STATUS = NODE_NODE_OK) or (PLC_control_type <> ControlType_6 and NODE_23_STATUS = NODE_NODE_OK)  then
			mask := mask + 256;
			EP_Wattmeter(9, PLC_EP_wattmeter07_W, PLC_EP_wattmeter07_var, PLC_EP_wattmeter07_VA,
						 PLC_EP_wattmeter07_kWh);
	    else
			; (* TODO: timer? *)
		end_if;
    end_if;

    if PLC_EP_enabled_wattmeters >= 10 then
		if (PLC_control_type = ControlType_6 and NODE_41_STATUS = NODE_NODE_OK) or (PLC_control_type <> ControlType_6 and NODE_24_STATUS = NODE_NODE_OK)  then
			mask := mask + 512;
			EP_Wattmeter(10, PLC_EP_wattmeter08_W, PLC_EP_wattmeter08_var, PLC_EP_wattmeter08_VA,
						 PLC_EP_wattmeter08_kWh);
	    else
			; (* TODO: timer? *)
		end_if;
    end_if;

    if PLC_EP_enabled_wattmeters >= 11 then
		if (PLC_control_type = ControlType_6 and NODE_42_STATUS = NODE_NODE_OK) or (PLC_control_type <> ControlType_6 and NODE_25_STATUS = NODE_NODE_OK)  then
			mask := mask + 1024;
			EP_Wattmeter(11, PLC_EP_wattmeter09_W, PLC_EP_wattmeter09_var, PLC_EP_wattmeter09_VA,
						 PLC_EP_wattmeter09_kWh);
	    else
			; (* TODO: timer? *)
		end_if;
    end_if;

    if PLC_EP_enabled_wattmeters >= 12 then
		if (PLC_control_type = ControlType_6 and NODE_43_STATUS = NODE_NODE_OK) or (PLC_control_type <> ControlType_6 and NODE_26_STATUS = NODE_NODE_OK)  then
			mask := mask + 2048;
			EP_Wattmeter(12, PLC_EP_wattmeter10_W, PLC_EP_wattmeter10_var, PLC_EP_wattmeter10_VA,
						 PLC_EP_wattmeter10_kWh);
	    else
			; (* TODO: timer? *)
		end_if;
    end_if;

	PLC_EP_wattmeters_ok := mask;

END_PROGRAM
