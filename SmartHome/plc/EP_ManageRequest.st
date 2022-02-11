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

FUNCTION EP_ManageRequest
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR_INPUT
	n : UINT;
	Tn_requested_W: UINT;
END_VAR
VAR_IN_OUT
	Tn_assigned_W: UINT;
	total_requested_W: UINT;
	total_assigned_W: UINT;
	last_assigned: UINT;
	first_refused: UINT;
END_VAR

	total_requested_W := total_requested_W + Tn_requested_W;

	if n > PLC_Tn_count or Tn_requested_W = 0 or PLC_EP_BlackoutDetected or PLC_EP_OverloadDetected then
		Tn_assigned_W := 0;

	elsif (total_assigned_W + Tn_requested_W) <= PLC_EP_max_assigned_W and (total_assigned_W + Tn_requested_W) <= PLC_EP_overload_W then
		Tn_assigned_W := Tn_requested_W;
		total_assigned_W := total_assigned_W + Tn_requested_W;
		last_assigned := n;

	else
		Tn_assigned_W := 0;
		if first_refused = 0 then
			first_refused := n;
		end_if;

	end_if;
	
END_FUNCTION
