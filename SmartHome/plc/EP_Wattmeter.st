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

FUNCTION EP_Wattmeter
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
	n : UINT;
END_VAR
VAR_IN_OUT
	W    : INT;   (*  W  *)
	_var : INT;   (* var *)
	VA   : INT;   (* VA  *)    
	kWh  : DINT;  (* kWh *)
END_VAR

	if PLC_control_type <> ControlType_6 then

		case n of
		 1:
		 	W   := REAL_TO_INT  (RTU_EP_wattmeter_M_P             );
			_var:= REAL_TO_INT  (RTU_EP_wattmeter_M_Q             );
			VA  := REAL_TO_INT  (RTU_EP_wattmeter_M_S             );
			kWh := REAL_TO_DINT (RTU_EP_wattmeter_M_Ein  /  100.0) + PLC_EP_wattmeter_M_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 2: 
		 	W   := REAL_TO_INT  (RTU_EP_wattmeter_F_P             );
			_var:= REAL_TO_INT  (RTU_EP_wattmeter_F_Q             );
			VA  := REAL_TO_INT  (RTU_EP_wattmeter_F_S             );
			kWh := REAL_TO_DINT (RTU_EP_wattmeter_F_Ein  /  100.0) + PLC_EP_wattmeter_F_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 3:
		 	W   := REAL_TO_INT  (RTU_EP_wattmeter01_P             );
			_var:= REAL_TO_INT  (RTU_EP_wattmeter01_Q             );
			VA  := REAL_TO_INT  (RTU_EP_wattmeter01_S             );
			kWh := REAL_TO_DINT (RTU_EP_wattmeter01_Ein  /  100.0) + PLC_EP_wattmeter01_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 4:
		 	W   := REAL_TO_INT  (RTU_EP_wattmeter02_P             );
			_var:= REAL_TO_INT  (RTU_EP_wattmeter02_Q             );
			VA  := REAL_TO_INT  (RTU_EP_wattmeter02_S             );
			kWh := REAL_TO_DINT (RTU_EP_wattmeter02_Ein  /  100.0) + PLC_EP_wattmeter02_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 5:
		 	W   := REAL_TO_INT  (RTU_EP_wattmeter03_P             );
			_var:= REAL_TO_INT  (RTU_EP_wattmeter03_Q             );
			VA  := REAL_TO_INT  (RTU_EP_wattmeter03_S             );
			kWh := REAL_TO_DINT (RTU_EP_wattmeter03_Ein  /  100.0) + PLC_EP_wattmeter03_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 6:
		 	W   := REAL_TO_INT  (RTU_EP_wattmeter04_P             );
			_var:= REAL_TO_INT  (RTU_EP_wattmeter04_Q             );
			VA  := REAL_TO_INT  (RTU_EP_wattmeter04_S             );
			kWh := REAL_TO_DINT (RTU_EP_wattmeter04_Ein  /  100.0) + PLC_EP_wattmeter04_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 7:
		 	W   := REAL_TO_INT  (RTU_EP_wattmeter05_P             );
			_var:= REAL_TO_INT  (RTU_EP_wattmeter05_Q             );
			VA  := REAL_TO_INT  (RTU_EP_wattmeter05_S             );
			kWh := REAL_TO_DINT (RTU_EP_wattmeter05_Ein  /  100.0) + PLC_EP_wattmeter05_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 8:
		 	W   := REAL_TO_INT  (RTU_EP_wattmeter06_P             );
			_var:= REAL_TO_INT  (RTU_EP_wattmeter06_Q             );
			VA  := REAL_TO_INT  (RTU_EP_wattmeter06_S             );
			kWh := REAL_TO_DINT (RTU_EP_wattmeter06_Ein  /  100.0) + PLC_EP_wattmeter06_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 9:
		 	W   := REAL_TO_INT  (RTU_EP_wattmeter07_P             );
			_var:= REAL_TO_INT  (RTU_EP_wattmeter07_Q             );
			VA  := REAL_TO_INT  (RTU_EP_wattmeter07_S             );
			kWh := REAL_TO_DINT (RTU_EP_wattmeter07_Ein  /  100.0) + PLC_EP_wattmeter07_kWh_offset; (* wxyz Wh --> w.x kWh *)
		10:
		 	W   := REAL_TO_INT  (RTU_EP_wattmeter08_P             );
			_var:= REAL_TO_INT  (RTU_EP_wattmeter08_Q             );
			VA  := REAL_TO_INT  (RTU_EP_wattmeter08_S             );
			kWh := REAL_TO_DINT (RTU_EP_wattmeter08_Ein  /  100.0) + PLC_EP_wattmeter08_kWh_offset; (* wxyz Wh --> w.x kWh *)
		11:
		 	W   := REAL_TO_INT  (RTU_EP_wattmeter09_P             );
			_var:= REAL_TO_INT  (RTU_EP_wattmeter09_Q             );
			VA  := REAL_TO_INT  (RTU_EP_wattmeter09_S             );
			kWh := REAL_TO_DINT (RTU_EP_wattmeter09_Ein  /  100.0) + PLC_EP_wattmeter09_kWh_offset; (* wxyz Wh --> w.x kWh *)
		12:
		 	W   := REAL_TO_INT  (RTU_EP_wattmeter10_P             );
			_var:= REAL_TO_INT  (RTU_EP_wattmeter10_Q             );
			VA  := REAL_TO_INT  (RTU_EP_wattmeter10_S             );
			kWh := REAL_TO_DINT (RTU_EP_wattmeter10_Ein  /  100.0) + PLC_EP_wattmeter10_kWh_offset; (* wxyz Wh --> w.x kWh *)
		else ;
		end_case;

    elsif PLC_control_type = ControlType_6 then

		case n of
		 1:
		 	W   := REAL_TO_INT  (SysActivePower_0             );
			_var:= REAL_TO_INT  (SysReactivePower_0           );
			VA  := REAL_TO_INT  (SysApparentPower_0           );
			kWh := REAL_TO_DINT (SysImpActiveEnergy_0  / 100.0) + PLC_EP_wattmeter_M_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 2:
		 	W   := REAL_TO_INT  (SysActivePower_1             );
			_var:= REAL_TO_INT  (SysReactivePower_1           );
			VA  := REAL_TO_INT  (SysApparentPower_1           );
			kWh := REAL_TO_DINT (SysImpActiveEnergy_1  / 100.0) + PLC_EP_wattmeter_F_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 3:
		 	W   := REAL_TO_INT  (SysActivePower_2             );
			_var:= REAL_TO_INT  (SysReactivePower_2           );
			VA  := REAL_TO_INT  (SysApparentPower_2           );
			kWh := REAL_TO_DINT (SysImpActiveEnergy_2  / 100.0) + PLC_EP_wattmeter01_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 4:
		 	W   := REAL_TO_INT  (SysActivePower_3             );
			_var:= REAL_TO_INT  (SysReactivePower_3           );
			VA  := REAL_TO_INT  (SysApparentPower_3           );
			kWh := REAL_TO_DINT (SysImpActiveEnergy_3  / 100.0) + PLC_EP_wattmeter02_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 5:
		 	W   := REAL_TO_INT  (SysActivePower_4             );
			_var:= REAL_TO_INT  (SysReactivePower_4           );
			VA  := REAL_TO_INT  (SysApparentPower_4           );
			kWh := REAL_TO_DINT (SysImpActiveEnergy_4  / 100.0) + PLC_EP_wattmeter03_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 6:
		 	W   := REAL_TO_INT  (SysActivePower_5             );
			_var:= REAL_TO_INT  (SysReactivePower_5           );
			VA  := REAL_TO_INT  (SysApparentPower_5           );
			kWh := REAL_TO_DINT (SysImpActiveEnergy_5  / 100.0) + PLC_EP_wattmeter04_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 7:
		 	W   := REAL_TO_INT  (SysActivePower_6             );
			_var:= REAL_TO_INT  (SysReactivePower_6           );
			VA  := REAL_TO_INT  (SysApparentPower_6           );
			kWh := REAL_TO_DINT (SysImpActiveEnergy_6  / 100.0) + PLC_EP_wattmeter05_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 8:
		 	W   := REAL_TO_INT  (SysActivePower_7             );
			_var:= REAL_TO_INT  (SysReactivePower_7           );
			VA  := REAL_TO_INT  (SysApparentPower_7           );
			kWh := REAL_TO_DINT (SysImpActiveEnergy_7  / 100.0) + PLC_EP_wattmeter06_kWh_offset; (* wxyz Wh --> w.x kWh *)
		 9: 
		 	W   := REAL_TO_INT  (SysActivePower_8             );
			_var:= REAL_TO_INT  (SysReactivePower_8           );
			VA  := REAL_TO_INT  (SysApparentPower_8           );
			kWh := REAL_TO_DINT (SysImpActiveEnergy_8  / 100.0) + PLC_EP_wattmeter07_kWh_offset; (* wxyz Wh --> w.x kWh *)
		10:
		 	W   := REAL_TO_INT  (SysActivePower_9             );
			_var:= REAL_TO_INT  (SysReactivePower_9           );
			VA  := REAL_TO_INT  (SysApparentPower_9           );
			kWh := REAL_TO_DINT (SysImpActiveEnergy_9  / 100.0) + PLC_EP_wattmeter08_kWh_offset; (* wxyz Wh --> w.x kWh *)
		11:
		 	W   := REAL_TO_INT  (SysActivePower_10            );
			_var:= REAL_TO_INT  (SysReactivePower_10          );
			VA  := REAL_TO_INT  (SysApparentPower_10          );
			kWh := REAL_TO_DINT (SysImpActiveEnergy_10 / 100.0) + PLC_EP_wattmeter09_kWh_offset; (* wxyz Wh --> w.x kWh *)
		12:
		 	W   := REAL_TO_INT  (SysActivePower_11            );
			_var:= REAL_TO_INT  (SysReactivePower_11          );
			VA  := REAL_TO_INT  (SysApparentPower_11          );
			kWh := REAL_TO_DINT (SysImpActiveEnergy_11 / 100.0) + PLC_EP_wattmeter10_kWh_offset; (* wxyz Wh --> w.x kWh *)
		else ;
		end_case;

	end_if;

END_FUNCTION
