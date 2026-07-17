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

PROGRAM EP_Relays
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR
	n : UINT := 0;
END_VAR;

    if not PLC_Iam_EP then
		return;
	end_if;

	if PLC_EP_enabled_relays > 0 then
		(* normally open relays, custom logic *)

		if PLC_EP_enabled_relays >= 1 then EP_SetDigOut_relay(1, PLC_EP_relay_A); end_if;
		if PLC_EP_enabled_relays >= 2 then EP_SetDigOut_relay(2, PLC_EP_relay_B); end_if;
		if PLC_EP_enabled_relays >= 3 then EP_SetDigOut_relay(3, PLC_EP_relay_C); end_if;
		if PLC_EP_enabled_relays >= 4 then EP_SetDigOut_relay(4, PLC_EP_relay_D); end_if;

		if PLC_EP_enabled_relays >= 5 then EP_SetDigOut_relay(5, PLC_EP_relay_E); end_if;
		if PLC_EP_enabled_relays >= 6 then EP_SetDigOut_relay(6, PLC_EP_relay_F); end_if;
		if PLC_EP_enabled_relays >= 7 then EP_SetDigOut_relay(7, PLC_EP_relay_G); end_if;
		if PLC_EP_enabled_relays >= 8 then EP_SetDigOut_relay(8, PLC_EP_relay_H); end_if;

	elsif PLC_EP_enabled_relays < 0 then
		(* normally closed relays, overload cutoff and manual rearm *)

	    if PLC_EP_OverloadDetected then
			(* overload cutoff (each n seconds) *)
			if n < 4 then
				n := n + 1;
			else
				n := 0;
				if    PLC_EP_enabled_relays <= -8 and not PLC_EP_relay_H then PLC_EP_relay_H := true; EP_SetDigOut_relay(8, true);
				elsif PLC_EP_enabled_relays <= -7 and not PLC_EP_relay_G then PLC_EP_relay_G := true; EP_SetDigOut_relay(7, true);
				elsif PLC_EP_enabled_relays <= -6 and not PLC_EP_relay_F then PLC_EP_relay_F := true; EP_SetDigOut_relay(6, true);
				elsif PLC_EP_enabled_relays <= -5 and not PLC_EP_relay_E then PLC_EP_relay_E := true; EP_SetDigOut_relay(5, true);
	
				elsif PLC_EP_enabled_relays <= -4 and not PLC_EP_relay_D then PLC_EP_relay_D := true; EP_SetDigOut_relay(4, true);
				elsif PLC_EP_enabled_relays <= -3 and not PLC_EP_relay_C then PLC_EP_relay_C := true; EP_SetDigOut_relay(3, true);
				elsif PLC_EP_enabled_relays <= -2 and not PLC_EP_relay_B then PLC_EP_relay_B := true; EP_SetDigOut_relay(2, true);
				elsif PLC_EP_enabled_relays <= -1 and not PLC_EP_relay_A then PLC_EP_relay_A := true; EP_SetDigOut_relay(1, true);
				end_if;
		    end_if;
		else
			(* manual rearm *)
			n:= 0;
			if PLC_EP_enabled_relays <= -1 then EP_SetDigOut_relay(1, PLC_EP_relay_A); end_if;
			if PLC_EP_enabled_relays <= -2 then EP_SetDigOut_relay(2, PLC_EP_relay_B); end_if;
			if PLC_EP_enabled_relays <= -3 then EP_SetDigOut_relay(3, PLC_EP_relay_C); end_if;
			if PLC_EP_enabled_relays <= -4 then EP_SetDigOut_relay(4, PLC_EP_relay_D); end_if;
	
			if PLC_EP_enabled_relays <= -5 then EP_SetDigOut_relay(5, PLC_EP_relay_E); end_if;
			if PLC_EP_enabled_relays <= -6 then EP_SetDigOut_relay(6, PLC_EP_relay_F); end_if;
			if PLC_EP_enabled_relays <= -7 then EP_SetDigOut_relay(7, PLC_EP_relay_G); end_if;
			if PLC_EP_enabled_relays <= -8 then EP_SetDigOut_relay(8, PLC_EP_relay_H); end_if;
		end_if;
	end_if;

END_PROGRAM
