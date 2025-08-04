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

FUNCTION EP_WattmeterFull
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
	n : UINT;
END_VAR
VAR_IN_OUT
	W     : INT;   (*  W  *)
	_var  : INT;   (* var *)
	VA    : INT;   (* VA  *)    
	pf    : INT;   (*  .  *)
	Hz    : INT;   (*  Hz *)
	V     : INT;   (*  V  *)
	A1    : INT;   (*  A  *)
	A2    : INT;   (*  A  *)
	A3    : INT;   (*  A  *)
	A     : INT;   (*  A  *)
	kWh   : DINT;  (* kWh *)
	e_kWh : DINT;  (* kWh *)
END_VAR

    if PLC_control_type = ControlType_6 then
        case n of
        1:
            EP_Wattmeter(n, W, _var, VA, kWh);
            pf    := REAL_TO_INT  (SysPowerFactor_0     * 1000.0);
            Hz    := REAL_TO_INT  (Frequency_0          *  100.0);
            V     := REAL_TO_INT  (SystemVoltage_0      *  100.0);
            A     := REAL_TO_INT  (SystemCurrent_0      * 1000.0);
            e_kWh := REAL_TO_DINT(SysExpActiveEnergy_0 /  100.0) + PLC_EP_wattmeter_M_e_kWh_offset; (* wxyz Wh --> w.x kWh *)
        2:
            EP_Wattmeter(n, W, _var, VA, kWh);
            pf    := REAL_TO_INT  (SysPowerFactor_1     * 1000.0);
         (* Hz    := REAL_TO_INT  (Frequency_1          *  100.0); *)
         (* V     := REAL_TO_INT  (SystemVoltage_1      *  100.0); *)
            A     := REAL_TO_INT  (SystemCurrent_1      * 1000.0);
            e_kWh := REAL_TO_DINT (SysExpActiveEnergy_1 /  100.0) + PLC_EP_wattmeter_F_e_kWh_offset; (* wxyz Wh --> w.x kWh *)
        else ;
        end_case;

    elsif PLC_control_type = ControlType_16 then
        case n of
        1:
            EP_Wattmeter(n, W, _var, VA, kWh);
            pf    := QcPm_PowerFactor_0      ;
            Hz    := QcPm_Frequency_0   *  10;
            V     := QcPm_Voltage_0     *  10;
            A     := QcPm_Current_0     *  10;
            e_kWh :=                        0; 
        else ;
        end_case;

    else
        case n of
        1:
            EP_Wattmeter(n, W, _var, VA, kWh);
            pf    := REAL_TO_INT  (RTU_EP_wattmeter_M_C  * 1000.0);
            Hz    := REAL_TO_INT  (RTU_EP_wattmeter_M_F  *  100.0);
            V     := REAL_TO_INT  (RTU_EP_wattmeter_M_U  *  100.0);
            A1    := REAL_TO_INT  (RTU_EP_wattmeter_M_I1 * 1000.0);
            A2    := REAL_TO_INT  (RTU_EP_wattmeter_M_I2 * 1000.0);
            A3    := REAL_TO_INT  (RTU_EP_wattmeter_M_I3 * 1000.0);
            A     := REAL_TO_INT  (RTU_EP_wattmeter_M_I  * 1000.0);
            e_kWh := REAL_TO_DINT (RTU_EP_wattmeter_M_Eout /  100.0) + PLC_EP_wattmeter_M_e_kWh_offset; (* wxyz Wh --> w.x kWh *)
        2:
            EP_Wattmeter(n, W, _var, VA, kWh);
            pf    := REAL_TO_INT  (RTU_EP_wattmeter_F_C  * 1000.0);
            Hz    := REAL_TO_INT  (RTU_EP_wattmeter_F_F  *  100.0);
            V     := REAL_TO_INT  (RTU_EP_wattmeter_F_U  *  100.0);
            A1    := REAL_TO_INT  (RTU_EP_wattmeter_F_I1 * 1000.0);
            A2    := REAL_TO_INT  (RTU_EP_wattmeter_F_I2 * 1000.0);
            A3    := REAL_TO_INT  (RTU_EP_wattmeter_F_I3 * 1000.0);
            A     := REAL_TO_INT  (RTU_EP_wattmeter_F_I  * 1000.0);
            e_kWh := REAL_TO_DINT (RTU_EP_wattmeter_F_Eout /  100.0) + PLC_EP_wattmeter_F_e_kWh_offset; (* wxyz Wh --> w.x kWh *)
        else ;
        end_case;

    end_if;

END_FUNCTION
