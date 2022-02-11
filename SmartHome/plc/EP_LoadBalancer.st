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

PROGRAM EP_LoadBalancer 
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR
	last_assigned : UINT := 0;
	first_refused : UINT := 0;
	i: UINT; 
	base: UINT;
	total_requested_W: UINT;
	total_assigned_W: UINT;
	tic_in_tac: UINT := 0;
END_VAR

	tic_in_tac := (tic_in_tac + 1) mod TacPeriod_s;

	if PLC_Tn_count > 0 then

		if (tic_in_tac = Decision_TicInTac) then (* the decision time has come ! *)		
			total_requested_W := 0;
			total_assigned_W := 0;

			if first_refused = 0 then
				base := last_assigned;     (* i.e. we start from the next one *)
			elsif first_refused = 1 then
				base := 6;                 (* i.e. we start from the first_refused *)
				first_refused := 0;
			else
				base := first_refused - 1; (* i.e. we start from the first_refused *)
				first_refused := 0;
			end_if;

			for i := 0 to 5 by 1 do
				case (((base + i) mod 6) + 1) of
				1: EP_ManageRequest(1, PLC_T1_requested_W, PLC_EP_T1_assigned_W, total_requested_W, total_assigned_W, last_assigned, first_refused);
				2: EP_ManageRequest(2, PLC_T2_requested_W, PLC_EP_T2_assigned_W, total_requested_W, total_assigned_W, last_assigned, first_refused);
				3: EP_ManageRequest(3, PLC_T3_requested_W, PLC_EP_T3_assigned_W, total_requested_W, total_assigned_W, last_assigned, first_refused);
				4: EP_ManageRequest(4, PLC_T4_requested_W, PLC_EP_T4_assigned_W, total_requested_W, total_assigned_W, last_assigned, first_refused);
				5: EP_ManageRequest(5, PLC_T5_requested_W, PLC_EP_T5_assigned_W, total_requested_W, total_assigned_W, last_assigned, first_refused);
				6: EP_ManageRequest(6, PLC_T6_requested_W, PLC_EP_T6_assigned_W, total_requested_W, total_assigned_W, last_assigned, first_refused);
				else ;
				end_case;
	 	    end_for;
	
			PLC_EP_requested_W := total_requested_W;
			PLC_EP_assigned_W := total_assigned_W;

	    end_if;

	else
		if PLC_EP_T1_assigned_W <> 0 then PLC_EP_T1_assigned_W := 0; end_if;
		if PLC_EP_T2_assigned_W <> 0 then PLC_EP_T2_assigned_W := 0; end_if;
		if PLC_EP_T3_assigned_W <> 0 then PLC_EP_T3_assigned_W := 0; end_if;
		if PLC_EP_T4_assigned_W <> 0 then PLC_EP_T4_assigned_W := 0; end_if;
		if PLC_EP_T5_assigned_W <> 0 then PLC_EP_T5_assigned_W := 0; end_if;
		if PLC_EP_T6_assigned_W <> 0 then PLC_EP_T6_assigned_W := 0; end_if;

		if PLC_EP_requested_W <> 0 then PLC_EP_requested_W := 0; end_if;
		if PLC_EP_assigned_W <> 0 then PLC_EP_assigned_W := 0; end_if;

	end_if;

	PLC_EP_tic_in_tac := tic_in_tac;
	
END_PROGRAM
