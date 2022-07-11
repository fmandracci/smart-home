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

FUNCTION Tn_ReadSensors
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
	n  : UINT; (* Tn                     *)
    ES : INT;  (* PLC_Tn_enabled_sensors *)
END_VAR
VAR_IN_OUT
    T1 : INT;  (* PLC_Tn_temperature     *)
    T2 : INT;  (* PLC_Tn_temperature_bis *)
    T3 : INT;  (* PLC_Tn_temperature_ext *)

    H1 : INT;  (* PLC_Tn_humidity        *)
    H2 : INT;  (* PLC_Tn_humidity_bis    *)
    H3 : INT;  (* PLC_Tn_humidity_ext    *)
END_VAR

	(* INPUT: sensors *)
	if PLC_control_type = ControlType_3 or PLC_control_type = ControlType_4 or PLC_control_type = ControlType_15 then			
		(* TPAC1007_04_AD Local I/O AI1..3 on RTU3 *)
		if ES >= 1 then
			if NODE_31_STATUS = NODE_NODE_OK then
				SetAnIn_PT100R(PLC_AnInConf_1, PLC_AnIn1Filter);
				T1 := PLC_AnIn_1;
			else
				T1 := TemperatureErrorValue;
			end_if;
			H1 := 0;
		end_if;
		if ES >= 2 then
			if NODE_31_STATUS = NODE_NODE_OK then
				SetAnIn_PT100R(PLC_AnInConf_2, PLC_AnIn2Filter);
				T2 := PLC_AnIn_2;
			else
				T2 := TemperatureErrorValue;
			end_if;
			H2 := 0;
		end_if;
		if ES >= 3 then
			if NODE_31_STATUS = NODE_NODE_OK then
				SetAnIn_PT100R(PLC_AnInConf_3, PLC_AnIn3Filter);
				T3 := PLC_AnIn_3;
			else
				T3 := TemperatureErrorValue;
			end_if;
			H3 := 0;
		end_if;

	elsif (PLC_control_type = ControlType_13 and n <= 3) then			
		(* n=1..3 TPAC1007_04_AD Local I/O AI1..3 on RTU3 *)
		if ES >= 1 then
			if NODE_31_STATUS = NODE_NODE_OK then
				case n of
				1:
					SetAnIn_PT100R(PLC_AnInConf_1, PLC_AnIn1Filter);
					T1 := PLC_AnIn_1;
				2:
					SetAnIn_PT100R(PLC_AnInConf_2, PLC_AnIn2Filter);
					T1 := PLC_AnIn_2;
				3:
					SetAnIn_PT100R(PLC_AnInConf_3, PLC_AnIn3Filter);
					T1 := PLC_AnIn_3;
				else ;
				end_case;
			else
				T1 := TemperatureErrorValue;
			end_if;
			H1 := 0;
		end_if;

	elsif PLC_control_type = ControlType_5 or PLC_control_type = ControlType_8 or PLC_control_type = ControlType_12 then
		(* first, second and third (T,H) sensor on RTU3 *)
		if ES <= -1 then
			if NODE_28_STATUS = NODE_NODE_OK then
				T1 := RTU_temperature;
				H1 := RTU_humidity;
			else
				T1 := TemperatureErrorValue;
				H1 := HumidityErrorValue;
			end_if;
		end_if;
		if ES <= -2 then
			if NODE_29_STATUS = NODE_NODE_OK then
				T2 := RTU_temperature_bis;
				H2 := RTU_humidity_bis;
			else
				T2 := TemperatureErrorValue;
				H2 := HumidityErrorValue;
			end_if;
		end_if;
		if ES <= -3 then
			if NODE_30_STATUS = NODE_NODE_OK then
				T3 := RTU_temperature_bis;
				H3 := RTU_humidity_bis;
			else
				T3 := TemperatureErrorValue;
				H3 := HumidityErrorValue;
			end_if;
		end_if;

	elsif PLC_control_type = ControlType_6 then
		(* MPNC 4xAI4 on RTU0 1=C+6 2=B+7 3=A+8 4=base+5, bis,ext varies *)
		if NODE_27_STATUS = NODE_NODE_OK then
			case n of
			1:
				if MPNC_AnInConf_C <> AnIn_MPNCx4_Pt100R then MPNC_AnInConf_C := AnIn_MPNCx4_Pt100R; end_if;
				T1 := MPNC_AnIn_C_3; (* scala *)
				T2 := MPNC_AnIn_C_1; (* lavanderia *)
				T3 := MPNC_AnIn_C_2; (* cantina *)
			2:
				if MPNC_AnInConf_B <> AnIn_MPNCx4_Pt100R then MPNC_AnInConf_B := AnIn_MPNCx4_Pt100R; end_if;
				T1 := MPNC_AnIn_B_3; (* corridoio *)
				T2 := MPNC_AnIn_B_1; (* cucina *)
				T3 := MPNC_AnIn_B_2; (* soggiorno *)
			3:
				if MPNC_AnInConf_A <> AnIn_MPNCx4_Pt100R then MPNC_AnInConf_A := AnIn_MPNCx4_Pt100R; end_if;
				T1 := MPNC_AnIn_A_3; (* sopra sud *)
				T2 := MPNC_AnIn_A_2; (* sopra nord *)
				T3 := MPNC_AnIn_A_1; (* esterna *)
			4:
				if MPNC_AnInConf_1 <> AnIn_MPNC_Pt100R then MPNC_AnInConf_1 := AnIn_MPNC_Pt100R; end_if;
				if MPNC_AnInConf_2 <> AnIn_MPNC_Pt100R then MPNC_AnInConf_2 := AnIn_MPNC_Pt100R; end_if;
				T1 := MPNC_AnIn_1; (* puffer *)
				T2 := MPNC_AnIn_2; (* ritorno radiatori *)
				T3 := 0;
			else ;
			end_case;
		else 
			T1 := TemperatureErrorValue;
			T2 := TemperatureErrorValue;
			T3 := TemperatureErrorValue;
		end_if;
		H1 := 0;
		H2 := 0;
		H3 := 0;

	elsif PLC_control_type = ControlType_14 then
		(* MPNC 4xAI4 on RTU0 1=A 2=B 3=C 4=D _1=t _2=t_bis _3=t_ext *)
		if NODE_27_STATUS = NODE_NODE_OK then
			case n of
			1:
				if MPNC_AnInConf_A <> AnIn_MPNCx4_Pt100R then MPNC_AnInConf_A := AnIn_MPNCx4_Pt100R; end_if;
				T1 := MPNC_AnIn_A_1;
				T2 := MPNC_AnIn_A_2;
				T3 := MPNC_AnIn_A_3;
			2:
				if MPNC_AnInConf_B <> AnIn_MPNCx4_Pt100R then MPNC_AnInConf_B := AnIn_MPNCx4_Pt100R; end_if;
				T1 := MPNC_AnIn_B_1;
				T2 := MPNC_AnIn_B_2;
				T3 := MPNC_AnIn_B_3;
			3:
				if MPNC_AnInConf_C <> AnIn_MPNCx4_Pt100R then MPNC_AnInConf_C := AnIn_MPNCx4_Pt100R; end_if;
				T1 := MPNC_AnIn_C_1;
				T2 := MPNC_AnIn_C_2;
				T3 := MPNC_AnIn_C_3;
			4:
				if MPNC_AnInConf_D <> AnIn_MPNCx4_Pt100R then MPNC_AnInConf_D := AnIn_MPNCx4_Pt100R; end_if;
				T1 := MPNC_AnIn_D_1;
				T2 := MPNC_AnIn_D_2;
				T3 := MPNC_AnIn_D_3;
			else ;
			end_case;
		else 
			T1 := TemperatureErrorValue;
			T2 := TemperatureErrorValue;
			T3 := TemperatureErrorValue;
		end_if;
		H1 := 0;
		H2 := 0;
		H3 := 0;

	elsif PLC_control_type = ControlType_7 then
		(* n=1..4 MPNE_C AI1..4 on RTU0; n=5,6 T,H on RTU3 *)
		if n <= 4 then
			if ES >= 1 then
				if NODE_13_STATUS = NODE_NODE_OK then
					case n of
					1:
						SetAnIn_PT100R(MPNE_C_AnIn1Conf, MPNE_C_AnIn1Filter);
						T1 := MPNE_C_AnIn_1;
					2:
						SetAnIn_PT100R(MPNE_C_AnIn2Conf, MPNE_C_AnIn2Filter);
						T1 := MPNE_C_AnIn_2;
					3:
						SetAnIn_PT100R(MPNE_C_AnIn3Conf, MPNE_C_AnIn3Filter);
						T1 := MPNE_C_AnIn_3;
					4:
						SetAnIn_PT100R(MPNE_C_AnIn4Conf, MPNE_C_AnIn4Filter);
						T1 := MPNE_C_AnIn_4;
					else ;
					end_case;
				else 
					T1 := TemperatureErrorValue;
				end_if;
				H1 := 0;
			end_if;
		elsif (n = 5) and (ES <= -1) then
			if NODE_28_STATUS = NODE_NODE_OK then
				T1 := RTU_temperature;
				H1 := RTU_humidity;
			else
				T1 := TemperatureErrorValue;
				H1 := HumidityErrorValue;
			end_if;
		elsif (n = 6) and (ES <= -1) then
			if NODE_29_STATUS = NODE_NODE_OK then
				T1 := RTU_temperature_bis;
				H1 := RTU_humidity_bis;
			else
				T1 := TemperatureErrorValue;
				H1 := HumidityErrorValue;
			end_if;
		else
			T1 := TemperatureErrorValue;
			H1 := HumidityErrorValue;
		end_if;


	elsif PLC_control_type = ControlType_10 then
		(* MPNE_C AI1.2 on RTU0 *)
		if ES >= 1 then
			if NODE_13_STATUS = NODE_NODE_OK then
				SetAnIn_PT100R(MPNE_C_AnIn1Conf, MPNE_C_AnIn1Filter);
				T1 := MPNE_C_AnIn_1;
			else 
				T1 := TemperatureErrorValue;
			end_if;
			H1 := 0;
		end_if;
		if ES >= 2 then
			if NODE_13_STATUS = NODE_NODE_OK then
				SetAnIn_PT100R(MPNE_C_AnIn2Conf, MPNE_C_AnIn2Filter);
				T2 := MPNE_C_AnIn_2;
			else 
				T2 := TemperatureErrorValue;
			end_if;
			H2 := 0;
		end_if;

	elsif PLC_control_type = ControlType_11 then
		(* n=1..4: MPNE_C/D AI(1+2) .. (3+4) on RTU0 *)
		case n of
		1:
			SetAnIn_PT100R(MPNE_C_AnIn1Conf, MPNE_C_AnIn1Filter);
			SetAnIn_PT100R(MPNE_C_AnIn2Conf, MPNE_C_AnIn2Filter);
			T1 := MPNE_C_AnIn_1;
			T2 := MPNE_C_AnIn_2;
		2:
			SetAnIn_PT100R(MPNE_C_AnIn3Conf, MPNE_C_AnIn3Filter);
			SetAnIn_PT100R(MPNE_C_AnIn4Conf, MPNE_C_AnIn4Filter);
			T1 := MPNE_C_AnIn_3;
			T2 := MPNE_C_AnIn_4;
		3:
			SetAnIn_PT100R(MPNE_D_AnIn1Conf, MPNE_D_AnIn1Filter);
			SetAnIn_PT100R(MPNE_D_AnIn2Conf, MPNE_D_AnIn2Filter);
			T1 := MPNE_D_AnIn_1;
			T2 := MPNE_D_AnIn_2;
		4:
			SetAnIn_PT100R(MPNE_D_AnIn3Conf, MPNE_D_AnIn3Filter);
			SetAnIn_PT100R(MPNE_D_AnIn4Conf, MPNE_D_AnIn4Filter);
			T1 := MPNE_D_AnIn_3;
			T2 := MPNE_D_AnIn_4;
		else ;
		end_case;

	end_if;

	case n of
	1:
		if (T1 <> TemperatureErrorValue and ES >= 1) then T1 := T1 + T1_temperature_offset; end_if;
		if (T2 <> TemperatureErrorValue and ES >= 2) then T2 := T2 + T1_temperature_bis_offset; end_if;
		if (T3 <> TemperatureErrorValue and ES >= 3) then T3 := T3 + T1_temperature_ext_offset; end_if;
	2:
		if (T1 <> TemperatureErrorValue and ES >= 1) then T1 := T1 + T2_temperature_offset; end_if;
		if (T2 <> TemperatureErrorValue and ES >= 2) then T2 := T2 + T2_temperature_bis_offset; end_if;
		if (T3 <> TemperatureErrorValue and ES >= 3) then T3 := T3 + T2_temperature_ext_offset; end_if;
	3:
		if (T1 <> TemperatureErrorValue and ES >= 1) then T1 := T1 + T3_temperature_offset; end_if;
		if (T2 <> TemperatureErrorValue and ES >= 2) then T2 := T2 + T3_temperature_bis_offset; end_if;
		if (T3 <> TemperatureErrorValue and ES >= 3) then T3 := T3 + T3_temperature_ext_offset; end_if;
	4:
		if (T1 <> TemperatureErrorValue and ES >= 1) then T1 := T1 + T4_temperature_offset; end_if;
		if (T2 <> TemperatureErrorValue and ES >= 2) then T2 := T2 + T4_temperature_bis_offset; end_if;
		if (T3 <> TemperatureErrorValue and ES >= 3) then T3 := T3 + T4_temperature_ext_offset; end_if;
	5:
		if (T1 <> TemperatureErrorValue and ES >= 1) then T1 := T1 + T5_temperature_offset; end_if;
		if (T2 <> TemperatureErrorValue and ES >= 2) then T2 := T2 + T5_temperature_bis_offset; end_if;
		if (T3 <> TemperatureErrorValue and ES >= 3) then T3 := T3 + T5_temperature_ext_offset; end_if;
	6:
		if (T1 <> TemperatureErrorValue and ES >= 1) then T1 := T1 + T6_temperature_offset; end_if;
		if (T2 <> TemperatureErrorValue and ES >= 2) then T2 := T2 + T6_temperature_bis_offset; end_if;
		if (T3 <> TemperatureErrorValue and ES >= 3) then T3 := T3 + T6_temperature_ext_offset; end_if;
	else
		;
	end_case;
	
	
END_FUNCTION
