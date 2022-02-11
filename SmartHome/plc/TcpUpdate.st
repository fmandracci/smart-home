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

PROGRAM TcpUpdate 
#import "Crosstable.gvl"
#import "Resource1.gvl"
VAR
    heartbeat: UINT := 65535;
END_VAR

    if heartbeat = 65535 then
        heartbeat := 1; (* always non-zero heartbeat *)
    else
        heartbeat := heartbeat + 1;
    end_if;

(*
	SRV_heartbeat        := heartbeat           ;
	SRV_Iam_EP           := PLC_Iam_EP          ;
	SRV_Iam_T1           := PLC_Iam_T1          ;
	SRV_Iam_T2           := PLC_Iam_T2          ;
	SRV_Iam_T3           := PLC_Iam_T3          ;
	SRV_Iam_T4           := PLC_Iam_T4          ;
	SRV_Iam_T5           := PLC_Iam_T5          ;
	SRV_Iam_T6           := PLC_Iam_T6          ;
	SRV_Iam_BA           := PLC_Iam_BA          ;
	SRV_EP_exists        := PLC_EP_exists       ;
	SRV_Tn_count         := PLC_Tn_count        ;
	SRV_BA_exists        := PLC_BA_exists       ;
	SRV_sunrise          := PLC_sunrise         ;
	SRV_sunset           := PLC_sunset          ;
	SRV_day_brightness   := PLC_day_brightness  ;
	SRV_night_brightness := PLC_night_brightness;
	SRV_screensaver      := PLC_screensaver     ;
	SRV_nighttime        := PLC_nighttime       ;
*)
    if PLC_Iam_EP then
        SRV_EP_heartbeat          := heartbeat                ;
        SRV_EP_enabled_wattmeters := PLC_EP_enabled_wattmeters;
        SRV_EP_wattmeters_ok      := PLC_EP_wattmeters_ok     ;
        if PLC_EP_enabled_wattmeters >= 1 then
            SRV_EP_wattmeter_M_W      := PLC_EP_wattmeter_M_W     ;
            SRV_EP_wattmeter_M_var    := PLC_EP_wattmeter_M_var   ;
            SRV_EP_wattmeter_M_VA     := PLC_EP_wattmeter_M_VA    ;
            SRV_EP_wattmeter_M_pf     := PLC_EP_wattmeter_M_pf    ;
            SRV_EP_wattmeter_M_Hz     := PLC_EP_wattmeter_M_Hz    ;
            SRV_EP_wattmeter_M_V      := PLC_EP_wattmeter_M_V     ;
            SRV_EP_wattmeter_M_A      := PLC_EP_wattmeter_M_A     ;
            SRV_EP_wattmeter_M_kWh    := PLC_EP_wattmeter_M_kWh   ;
            SRV_EP_wattmeter_M_e_kWh  := PLC_EP_wattmeter_M_e_kWh ;
        end_if;
        if PLC_EP_enabled_wattmeters >= 2 then
            SRV_EP_wattmeter_F_W      := PLC_EP_wattmeter_F_W     ;
            SRV_EP_wattmeter_F_var    := PLC_EP_wattmeter_F_var   ;
            SRV_EP_wattmeter_F_VA     := PLC_EP_wattmeter_F_VA    ;
            SRV_EP_wattmeter_F_pf     := PLC_EP_wattmeter_F_pf    ;
            SRV_EP_wattmeter_F_Hz     := PLC_EP_wattmeter_F_Hz    ;
            SRV_EP_wattmeter_F_V      := PLC_EP_wattmeter_F_V     ;
            SRV_EP_wattmeter_F_A      := PLC_EP_wattmeter_F_A     ;
            SRV_EP_wattmeter_F_kWh    := PLC_EP_wattmeter_F_kWh   ;
            SRV_EP_wattmeter_F_e_kWh  := PLC_EP_wattmeter_F_e_kWh ;
        end_if;
        if PLC_EP_enabled_wattmeters >= 3 then
            SRV_EP_wattmeter01_W      := PLC_EP_wattmeter01_W     ;
            SRV_EP_wattmeter01_var    := PLC_EP_wattmeter01_var   ;
            SRV_EP_wattmeter01_VA     := PLC_EP_wattmeter01_VA    ;
            SRV_EP_wattmeter01_kWh    := PLC_EP_wattmeter01_kWh   ;
        end_if;
        if PLC_EP_enabled_wattmeters >= 4 then
            SRV_EP_wattmeter02_W      := PLC_EP_wattmeter02_W     ;
            SRV_EP_wattmeter02_var    := PLC_EP_wattmeter02_var   ;
            SRV_EP_wattmeter02_VA     := PLC_EP_wattmeter02_VA    ;
            SRV_EP_wattmeter02_kWh    := PLC_EP_wattmeter02_kWh   ;
        end_if;
        if PLC_EP_enabled_wattmeters >= 5 then
            SRV_EP_wattmeter03_W      := PLC_EP_wattmeter03_W     ;
            SRV_EP_wattmeter03_var    := PLC_EP_wattmeter03_var   ;
            SRV_EP_wattmeter03_VA     := PLC_EP_wattmeter03_VA    ;
            SRV_EP_wattmeter03_kWh    := PLC_EP_wattmeter03_kWh   ;
        end_if;
        if PLC_EP_enabled_wattmeters >= 6 then
            SRV_EP_wattmeter04_W      := PLC_EP_wattmeter04_W     ;
            SRV_EP_wattmeter04_var    := PLC_EP_wattmeter04_var   ;
            SRV_EP_wattmeter04_VA     := PLC_EP_wattmeter04_VA    ;
            SRV_EP_wattmeter04_kWh    := PLC_EP_wattmeter04_kWh   ;
        end_if;
        if PLC_EP_enabled_wattmeters >= 7 then
            SRV_EP_wattmeter05_W      := PLC_EP_wattmeter05_W     ;
            SRV_EP_wattmeter05_var    := PLC_EP_wattmeter05_var   ;
            SRV_EP_wattmeter05_VA     := PLC_EP_wattmeter05_VA    ;
            SRV_EP_wattmeter05_kWh    := PLC_EP_wattmeter05_kWh   ;
        end_if;
        if PLC_EP_enabled_wattmeters >= 8 then
            SRV_EP_wattmeter06_W      := PLC_EP_wattmeter06_W     ;
            SRV_EP_wattmeter06_var    := PLC_EP_wattmeter06_var   ;
            SRV_EP_wattmeter06_VA     := PLC_EP_wattmeter06_VA    ;
            SRV_EP_wattmeter06_kWh    := PLC_EP_wattmeter06_kWh   ;
        end_if;
        if PLC_EP_enabled_wattmeters >= 9 then
            SRV_EP_wattmeter07_W      := PLC_EP_wattmeter07_W     ;
            SRV_EP_wattmeter07_var    := PLC_EP_wattmeter07_var   ;
            SRV_EP_wattmeter07_VA     := PLC_EP_wattmeter07_VA    ;
            SRV_EP_wattmeter07_kWh    := PLC_EP_wattmeter07_kWh   ;
        end_if;
        if PLC_EP_enabled_wattmeters >= 10 then
            SRV_EP_wattmeter08_W      := PLC_EP_wattmeter08_W     ;
            SRV_EP_wattmeter08_var    := PLC_EP_wattmeter08_var   ;
            SRV_EP_wattmeter08_VA     := PLC_EP_wattmeter08_VA    ;
            SRV_EP_wattmeter08_kWh    := PLC_EP_wattmeter08_kWh   ;
        end_if;
        if PLC_EP_enabled_wattmeters >= 11 then
            SRV_EP_wattmeter09_W      := PLC_EP_wattmeter09_W     ;
            SRV_EP_wattmeter09_var    := PLC_EP_wattmeter09_var   ;
            SRV_EP_wattmeter09_VA     := PLC_EP_wattmeter09_VA    ;
            SRV_EP_wattmeter09_kWh    := PLC_EP_wattmeter09_kWh   ;
        end_if;
        if PLC_EP_enabled_wattmeters >= 12 then
            SRV_EP_wattmeter10_W      := PLC_EP_wattmeter10_W     ;
            SRV_EP_wattmeter10_var    := PLC_EP_wattmeter10_var   ;
            SRV_EP_wattmeter10_VA     := PLC_EP_wattmeter10_VA    ;
            SRV_EP_wattmeter10_kWh    := PLC_EP_wattmeter10_kWh   ;
        end_if;

        SRV_EP_BlackoutDetected   := PLC_EP_BlackoutDetected  ;
        SRV_EP_OverloadDetected   := PLC_EP_OverloadDetected  ;
        SRV_EP_enabled_relays     := PLC_EP_enabled_relays    ;
        if PLC_EP_enabled_relays > 0 or (PLC_EP_enabled_relays < 0 and not PLC_EP_OverloadDetected) then
(*!*)       PLC_EP_relay_A            := SRV_EP_relay_A       ;
(*!*)       PLC_EP_relay_B            := SRV_EP_relay_B       ;
(*!*)       PLC_EP_relay_C            := SRV_EP_relay_C       ;
(*!*)       PLC_EP_relay_D            := SRV_EP_relay_D       ;
(*!*)       PLC_EP_relay_E            := SRV_EP_relay_E       ;
(*!*)       PLC_EP_relay_F            := SRV_EP_relay_F       ;
(*!*)       PLC_EP_relay_G            := SRV_EP_relay_G       ;
(*!*)       PLC_EP_relay_H            := SRV_EP_relay_H       ;
		elsif PLC_EP_enabled_relays < 0 then
            SRV_EP_relay_A            := PLC_EP_relay_A       ;
            SRV_EP_relay_B            := PLC_EP_relay_B       ;
            SRV_EP_relay_C            := PLC_EP_relay_C       ;
            SRV_EP_relay_D            := PLC_EP_relay_D       ;
            SRV_EP_relay_E            := PLC_EP_relay_E       ;
            SRV_EP_relay_F            := PLC_EP_relay_F       ;
            SRV_EP_relay_G            := PLC_EP_relay_G       ;
            SRV_EP_relay_H            := PLC_EP_relay_H       ;
        end_if;

        SRV_EP_overload_W         := PLC_EP_overload_W        ;
        SRV_EP_max_assigned_W     := PLC_EP_max_assigned_W    ;
        SRV_EP_tic_in_tac         := PLC_EP_tic_in_tac        ;
        SRV_EP_requested_W        := PLC_EP_requested_W       ;
        SRV_EP_T1_assigned_W      := PLC_EP_T1_assigned_W     ;
        SRV_EP_T2_assigned_W      := PLC_EP_T2_assigned_W     ;
        SRV_EP_T3_assigned_W      := PLC_EP_T3_assigned_W     ;
        SRV_EP_T4_assigned_W      := PLC_EP_T4_assigned_W     ;
        SRV_EP_T5_assigned_W      := PLC_EP_T5_assigned_W     ;
        SRV_EP_T6_assigned_W      := PLC_EP_T6_assigned_W     ;
        SRV_EP_assigned_W         := PLC_EP_assigned_W        ;

        SRV_EP_control_type       := PLC_control_type         ;
        PLC_EP_control_type       := PLC_control_type         ;

    elsif PLC_EP_exists then

        PLC_EP_enabled_wattmeters := TCP_EP_enabled_wattmeters;
        PLC_EP_wattmeters_ok      := TCP_EP_wattmeters_ok     ;
        if TCP_EP_enabled_wattmeters >= 1 then
            PLC_EP_wattmeter_M_W      := TCP_EP_wattmeter_M_W     ;
            PLC_EP_wattmeter_M_var    := TCP_EP_wattmeter_M_var   ;
            PLC_EP_wattmeter_M_VA     := TCP_EP_wattmeter_M_VA    ;
            PLC_EP_wattmeter_M_pf     := TCP_EP_wattmeter_M_pf    ;
            PLC_EP_wattmeter_M_Hz     := TCP_EP_wattmeter_M_Hz    ;
            PLC_EP_wattmeter_M_V      := TCP_EP_wattmeter_M_V     ;
            PLC_EP_wattmeter_M_A      := TCP_EP_wattmeter_M_A     ;
            PLC_EP_wattmeter_M_kWh    := TCP_EP_wattmeter_M_kWh   ;
            PLC_EP_wattmeter_M_e_kWh  := TCP_EP_wattmeter_M_e_kWh ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 2 then
            PLC_EP_wattmeter_F_W      := TCP_EP_wattmeter_F_W     ;
            PLC_EP_wattmeter_F_var    := TCP_EP_wattmeter_F_var   ;
            PLC_EP_wattmeter_F_VA     := TCP_EP_wattmeter_F_VA    ;
            PLC_EP_wattmeter_F_pf     := TCP_EP_wattmeter_F_pf    ;
            PLC_EP_wattmeter_F_Hz     := TCP_EP_wattmeter_F_Hz    ;
            PLC_EP_wattmeter_F_V      := TCP_EP_wattmeter_F_V     ;
            PLC_EP_wattmeter_F_A      := TCP_EP_wattmeter_F_A     ;
            PLC_EP_wattmeter_F_kWh    := TCP_EP_wattmeter_F_kWh   ;
            PLC_EP_wattmeter_F_e_kWh  := TCP_EP_wattmeter_F_e_kWh ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 3 then
            PLC_EP_wattmeter01_W      := TCP_EP_wattmeter01_W     ;
            PLC_EP_wattmeter01_var    := TCP_EP_wattmeter01_var   ;
            PLC_EP_wattmeter01_VA     := TCP_EP_wattmeter01_VA    ;
            PLC_EP_wattmeter01_kWh    := TCP_EP_wattmeter01_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 4 then
            PLC_EP_wattmeter02_W      := TCP_EP_wattmeter02_W     ;
            PLC_EP_wattmeter02_var    := TCP_EP_wattmeter02_var   ;
            PLC_EP_wattmeter02_VA     := TCP_EP_wattmeter02_VA    ;
            PLC_EP_wattmeter02_kWh    := TCP_EP_wattmeter02_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 5 then
            PLC_EP_wattmeter03_W      := TCP_EP_wattmeter03_W     ;
            PLC_EP_wattmeter03_var    := TCP_EP_wattmeter03_var   ;
            PLC_EP_wattmeter03_VA     := TCP_EP_wattmeter03_VA    ;
            PLC_EP_wattmeter03_kWh    := TCP_EP_wattmeter03_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 6 then
            PLC_EP_wattmeter04_W      := TCP_EP_wattmeter04_W     ;
            PLC_EP_wattmeter04_var    := TCP_EP_wattmeter04_var   ;
            PLC_EP_wattmeter04_VA     := TCP_EP_wattmeter04_VA    ;
            PLC_EP_wattmeter04_kWh    := TCP_EP_wattmeter04_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 7 then
            PLC_EP_wattmeter05_W      := TCP_EP_wattmeter05_W     ;
            PLC_EP_wattmeter05_var    := TCP_EP_wattmeter05_var   ;
            PLC_EP_wattmeter05_VA     := TCP_EP_wattmeter05_VA    ;
            PLC_EP_wattmeter05_kWh    := TCP_EP_wattmeter05_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 8 then
            PLC_EP_wattmeter06_W      := TCP_EP_wattmeter06_W     ;
            PLC_EP_wattmeter06_var    := TCP_EP_wattmeter06_var   ;
            PLC_EP_wattmeter06_VA     := TCP_EP_wattmeter06_VA    ;
            PLC_EP_wattmeter06_kWh    := TCP_EP_wattmeter06_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 9 then
            PLC_EP_wattmeter07_W      := TCP_EP_wattmeter07_W     ;
            PLC_EP_wattmeter07_var    := TCP_EP_wattmeter07_var   ;
            PLC_EP_wattmeter07_VA     := TCP_EP_wattmeter07_VA    ;
            PLC_EP_wattmeter07_kWh    := TCP_EP_wattmeter07_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 10 then
            PLC_EP_wattmeter08_W      := TCP_EP_wattmeter08_W     ;
            PLC_EP_wattmeter08_var    := TCP_EP_wattmeter08_var   ;
            PLC_EP_wattmeter08_VA     := TCP_EP_wattmeter08_VA    ;
            PLC_EP_wattmeter08_kWh    := TCP_EP_wattmeter08_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 11 then
            PLC_EP_wattmeter09_W      := TCP_EP_wattmeter09_W     ;
            PLC_EP_wattmeter09_var    := TCP_EP_wattmeter09_var   ;
            PLC_EP_wattmeter09_VA     := TCP_EP_wattmeter09_VA    ;
            PLC_EP_wattmeter09_kWh    := TCP_EP_wattmeter09_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 12 then
            PLC_EP_wattmeter10_W      := TCP_EP_wattmeter10_W     ;
            PLC_EP_wattmeter10_var    := TCP_EP_wattmeter10_var   ;
            PLC_EP_wattmeter10_VA     := TCP_EP_wattmeter10_VA    ;
            PLC_EP_wattmeter10_kWh    := TCP_EP_wattmeter10_kWh   ;
        end_if;

        PLC_EP_blackout_flag        := TCP_EP_BlackoutDetected; (* --> PLC_EP_BlackoutDetected Alarm *)
        PLC_EP_overload_flag        := TCP_EP_OverloadDetected; (* --> PLC_EP_OverloadDetected Alarm *)
        PLC_EP_enabled_relays       := TCP_EP_enabled_relays  ;

		PLC_EP_relay_A            := TCP_EP_relay_A       ;
        PLC_EP_relay_B            := TCP_EP_relay_B       ;
        PLC_EP_relay_C            := TCP_EP_relay_C       ;
        PLC_EP_relay_D            := TCP_EP_relay_D       ;
        PLC_EP_relay_E            := TCP_EP_relay_E       ;
        PLC_EP_relay_F            := TCP_EP_relay_F       ;
        PLC_EP_relay_G            := TCP_EP_relay_G       ;
        PLC_EP_relay_H            := TCP_EP_relay_H       ;

        PLC_EP_overload_W         := TCP_EP_overload_W        ;
        PLC_EP_max_assigned_W     := TCP_EP_max_assigned_W    ;
        PLC_EP_tic_in_tac         := TCP_EP_tic_in_tac        ;
        PLC_EP_requested_W        := TCP_EP_requested_W       ;
        PLC_EP_T1_assigned_W      := TCP_EP_T1_assigned_W     ;
        PLC_EP_T2_assigned_W      := TCP_EP_T2_assigned_W     ;
        PLC_EP_T3_assigned_W      := TCP_EP_T3_assigned_W     ;
        PLC_EP_T4_assigned_W      := TCP_EP_T4_assigned_W     ;
        PLC_EP_T5_assigned_W      := TCP_EP_T5_assigned_W     ;
        PLC_EP_T6_assigned_W      := TCP_EP_T6_assigned_W     ;
        PLC_EP_assigned_W         := TCP_EP_assigned_W        ;

        PLC_EP_control_type       := TCP_EP_control_type      ;

        (* extra copy for the Android App *)
        SRV_EP_heartbeat          := TCP_EP_heartbeat         ;
        SRV_EP_enabled_wattmeters := TCP_EP_enabled_wattmeters;
        SRV_EP_wattmeters_ok      := TCP_EP_wattmeters_ok     ;
        if TCP_EP_enabled_wattmeters >= 1 then
            SRV_EP_wattmeter_M_W      := TCP_EP_wattmeter_M_W     ;
            SRV_EP_wattmeter_M_var    := TCP_EP_wattmeter_M_var   ;
            SRV_EP_wattmeter_M_VA     := TCP_EP_wattmeter_M_VA    ;
            SRV_EP_wattmeter_M_pf     := TCP_EP_wattmeter_M_pf    ;
            SRV_EP_wattmeter_M_Hz     := TCP_EP_wattmeter_M_Hz    ;
            SRV_EP_wattmeter_M_V      := TCP_EP_wattmeter_M_V     ;
            SRV_EP_wattmeter_M_A      := TCP_EP_wattmeter_M_A     ;
            SRV_EP_wattmeter_M_kWh    := TCP_EP_wattmeter_M_kWh   ;
            SRV_EP_wattmeter_M_e_kWh  := TCP_EP_wattmeter_M_e_kWh ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 2 then
            SRV_EP_wattmeter_F_W      := TCP_EP_wattmeter_F_W     ;
            SRV_EP_wattmeter_F_var    := TCP_EP_wattmeter_F_var   ;
            SRV_EP_wattmeter_F_VA     := TCP_EP_wattmeter_F_VA    ;
            SRV_EP_wattmeter_F_pf     := TCP_EP_wattmeter_F_pf    ;
            SRV_EP_wattmeter_F_Hz     := TCP_EP_wattmeter_F_Hz    ;
            SRV_EP_wattmeter_F_V      := TCP_EP_wattmeter_F_V     ;
            SRV_EP_wattmeter_F_A      := TCP_EP_wattmeter_F_A     ;
            SRV_EP_wattmeter_F_kWh    := TCP_EP_wattmeter_F_kWh   ;
            SRV_EP_wattmeter_F_e_kWh  := TCP_EP_wattmeter_F_e_kWh ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 3 then
            SRV_EP_wattmeter01_W      := TCP_EP_wattmeter01_W     ;
            SRV_EP_wattmeter01_var    := TCP_EP_wattmeter01_var   ;
            SRV_EP_wattmeter01_VA     := TCP_EP_wattmeter01_VA    ;
            SRV_EP_wattmeter01_kWh    := TCP_EP_wattmeter01_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 4 then
            SRV_EP_wattmeter02_W      := TCP_EP_wattmeter02_W     ;
            SRV_EP_wattmeter02_var    := TCP_EP_wattmeter02_var   ;
            SRV_EP_wattmeter02_VA     := TCP_EP_wattmeter02_VA    ;
            SRV_EP_wattmeter02_kWh    := TCP_EP_wattmeter02_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 5 then
            SRV_EP_wattmeter03_W      := TCP_EP_wattmeter03_W     ;
            SRV_EP_wattmeter03_var    := TCP_EP_wattmeter03_var   ;
            SRV_EP_wattmeter03_VA     := TCP_EP_wattmeter03_VA    ;
            SRV_EP_wattmeter03_kWh    := TCP_EP_wattmeter03_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 6 then
            SRV_EP_wattmeter04_W      := TCP_EP_wattmeter04_W     ;
            SRV_EP_wattmeter04_var    := TCP_EP_wattmeter04_var   ;
            SRV_EP_wattmeter04_VA     := TCP_EP_wattmeter04_VA    ;
            SRV_EP_wattmeter04_kWh    := TCP_EP_wattmeter04_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 7 then
            SRV_EP_wattmeter05_W      := TCP_EP_wattmeter05_W     ;
            SRV_EP_wattmeter05_var    := TCP_EP_wattmeter05_var   ;
            SRV_EP_wattmeter05_VA     := TCP_EP_wattmeter05_VA    ;
            SRV_EP_wattmeter05_kWh    := TCP_EP_wattmeter05_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 8 then
            SRV_EP_wattmeter06_W      := TCP_EP_wattmeter06_W     ;
            SRV_EP_wattmeter06_var    := TCP_EP_wattmeter06_var   ;
            SRV_EP_wattmeter06_VA     := TCP_EP_wattmeter06_VA    ;
            SRV_EP_wattmeter06_kWh    := TCP_EP_wattmeter06_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 9 then
            SRV_EP_wattmeter07_W      := TCP_EP_wattmeter07_W     ;
            SRV_EP_wattmeter07_var    := TCP_EP_wattmeter07_var   ;
            SRV_EP_wattmeter07_VA     := TCP_EP_wattmeter07_VA    ;
            SRV_EP_wattmeter07_kWh    := TCP_EP_wattmeter07_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 10 then
            SRV_EP_wattmeter08_W      := TCP_EP_wattmeter08_W     ;
            SRV_EP_wattmeter08_var    := TCP_EP_wattmeter08_var   ;
            SRV_EP_wattmeter08_VA     := TCP_EP_wattmeter08_VA    ;
            SRV_EP_wattmeter08_kWh    := TCP_EP_wattmeter08_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 11 then
            SRV_EP_wattmeter09_W      := TCP_EP_wattmeter09_W     ;
            SRV_EP_wattmeter09_var    := TCP_EP_wattmeter09_var   ;
            SRV_EP_wattmeter09_VA     := TCP_EP_wattmeter09_VA    ;
            SRV_EP_wattmeter09_kWh    := TCP_EP_wattmeter09_kWh   ;
        end_if;
        if TCP_EP_enabled_wattmeters >= 12 then
            SRV_EP_wattmeter10_W      := TCP_EP_wattmeter10_W     ;
            SRV_EP_wattmeter10_var    := TCP_EP_wattmeter10_var   ;
            SRV_EP_wattmeter10_VA     := TCP_EP_wattmeter10_VA    ;
            SRV_EP_wattmeter10_kWh    := TCP_EP_wattmeter10_kWh   ;
        end_if;

        SRV_EP_BlackoutDetected   := TCP_EP_BlackoutDetected  ;
        SRV_EP_OverloadDetected   := TCP_EP_OverloadDetected  ;
        SRV_EP_enabled_relays     := TCP_EP_enabled_relays    ;
        if abs(TCP_EP_enabled_relays) >= 1 then
            SRV_EP_relay_A        := TCP_EP_relay_A           ;
            SRV_EP_relay_B        := TCP_EP_relay_B           ;
            SRV_EP_relay_C        := TCP_EP_relay_C           ;
            SRV_EP_relay_D        := TCP_EP_relay_D           ;
            SRV_EP_relay_E        := TCP_EP_relay_E           ;
            SRV_EP_relay_F        := TCP_EP_relay_F           ;
            SRV_EP_relay_G        := TCP_EP_relay_G           ;
            SRV_EP_relay_H        := TCP_EP_relay_H           ;
        end_if;

        SRV_EP_overload_W         := TCP_EP_overload_W        ;
        SRV_EP_max_assigned_W     := TCP_EP_max_assigned_W    ;
        SRV_EP_tic_in_tac         := TCP_EP_tic_in_tac        ;
        SRV_EP_requested_W        := TCP_EP_requested_W       ;
        SRV_EP_T1_assigned_W      := TCP_EP_T1_assigned_W     ;
        SRV_EP_T2_assigned_W      := TCP_EP_T2_assigned_W     ;
        SRV_EP_T3_assigned_W      := TCP_EP_T3_assigned_W     ;
        SRV_EP_T4_assigned_W      := TCP_EP_T4_assigned_W     ;
        SRV_EP_T5_assigned_W      := TCP_EP_T5_assigned_W     ;
        SRV_EP_T6_assigned_W      := TCP_EP_T6_assigned_W     ;
        SRV_EP_assigned_W         := TCP_EP_assigned_W        ;

        SRV_EP_control_type       := TCP_EP_control_type      ;
    end_if;

    if PLC_Iam_T1 then
        SRV_T1_heartbeat            := heartbeat                  ;

        SRV_T1_enabled_sensors      := PLC_T1_enabled_sensors     ;
        SRV_T1_temperature          := PLC_T1_temperature         ;
        SRV_T1_temperature_bis      := PLC_T1_temperature_bis     ;
        SRV_T1_temperature_ext      := PLC_T1_temperature_ext     ;
        SRV_T1_humidity             := PLC_T1_humidity            ;

 (*!*)  PLC_T1_temperature_setpoint := SRV_T1_temperature_setpoint;
 (*!*)  PLC_T1_humidity_setpoint    := SRV_T1_humidity_setpoint   ;

        SRV_T1_enabled_lamps        := PLC_T1_enabled_lamps       ;
 (*!*)  PLC_T1_lamp_1               := SRV_T1_lamp_1              ;
 (*!*)  PLC_T1_lamp_2               := SRV_T1_lamp_2              ;
 (*!*)  PLC_T1_lamp_3               := SRV_T1_lamp_3              ;
 (*!*)  PLC_T1_lamp_4               := SRV_T1_lamp_4              ;
 (*!*)  PLC_T1_lamp_5               := SRV_T1_lamp_5              ;

        SRV_T1_max_request_W        := PLC_T1_max_request_W  ;
        SRV_T1_heating              := PLC_T1_heating             ;
        SRV_T1_nighttime            := PLC_T1_nighttime           ;
 (*!*)  PLC_T1_heating_status       := SRV_T1_heating_status      ;
 (*!*)  PLC_T1_heating_timer        := SRV_T1_heating_timer       ;

        SRV_T1_sunrise              := PLC_sunrise             ;
        SRV_T1_sunset               := PLC_sunset              ;
        PLC_T1_sunrise              := PLC_sunrise             ;
        PLC_T1_sunset               := PLC_sunset              ;
 (*!*)  PLC_T1_temperature_setpoint_nt := SRV_T1_temperature_setpoint_nt;
 (*!*)  PLC_T1_humidity_setpoint_nt    := SRV_T1_humidity_setpoint_nt   ;

        SRV_T1_lamp_feedback_1      := PLC_T1_lamp_feedback_1     ;
        SRV_T1_lamp_feedback_2      := PLC_T1_lamp_feedback_2     ;
        SRV_T1_lamp_feedback_3      := PLC_T1_lamp_feedback_3     ;
        SRV_T1_lamp_feedback_4      := PLC_T1_lamp_feedback_4     ;
        SRV_T1_lamp_feedback_5      := PLC_T1_lamp_feedback_5     ;

		SRV_T1_control_type         := PLC_control_type           ;
		PLC_T1_control_type         := PLC_control_type           ;

		SRV_T1_daily_heating_s      := PLC_T1_daily_heating_s     ;
		SRV_T1_monthly_heating_s    := PLC_T1_monthly_heating_s   ;

     elsif PLC_Tn_count >= 1 then
        PLC_T1_enabled_sensors      := TCP_T1_enabled_sensors     ;
        PLC_T1_temperature          := TCP_T1_temperature         ;
        PLC_T1_temperature_bis      := TCP_T1_temperature_bis     ;
        PLC_T1_temperature_ext      := TCP_T1_temperature_ext     ;
        PLC_T1_humidity             := TCP_T1_humidity            ;

        PLC_T1_temperature_setpoint := TCP_T1_temperature_setpoint;
        PLC_T1_humidity_setpoint    := TCP_T1_humidity_setpoint   ;

        PLC_T1_enabled_lamps        := TCP_T1_enabled_lamps       ;
        PLC_T1_lamp_1               := TCP_T1_lamp_1              ;
        PLC_T1_lamp_2               := TCP_T1_lamp_2              ;
        PLC_T1_lamp_3               := TCP_T1_lamp_3              ;
        PLC_T1_lamp_4               := TCP_T1_lamp_4              ;
        PLC_T1_lamp_5               := TCP_T1_lamp_5              ;

        PLC_T1_max_request_W   := TCP_T1_max_request_W  ;
        PLC_T1_heating              := TCP_T1_heating             ;
        PLC_T1_nighttime            := TCP_T1_nighttime           ;
        PLC_T1_heating_status       := TCP_T1_heating_status      ;
        PLC_T1_heating_timer        := TCP_T1_heating_timer       ;

        PLC_T1_sunrise                 := TCP_T1_sunrise                ;
        PLC_T1_sunset                  := TCP_T1_sunset                 ;
        PLC_T1_temperature_setpoint_nt := TCP_T1_temperature_setpoint_nt;
        PLC_T1_humidity_setpoint_nt    := TCP_T1_humidity_setpoint_nt   ;

        PLC_T1_lamp_feedback_1      := TCP_T1_lamp_feedback_1     ;
        PLC_T1_lamp_feedback_2      := TCP_T1_lamp_feedback_2     ;
        PLC_T1_lamp_feedback_3      := TCP_T1_lamp_feedback_3     ;
        PLC_T1_lamp_feedback_4      := TCP_T1_lamp_feedback_4     ;
        PLC_T1_lamp_feedback_5      := TCP_T1_lamp_feedback_5     ;

        PLC_T1_requested_W          := TCP_T1_requested_W         ;
		PLC_T1_control_type         := TCP_T1_control_type        ;
        
		PLC_T1_daily_heating_s      := TCP_T1_daily_heating_s     ;
		PLC_T1_monthly_heating_s    := TCP_T1_monthly_heating_s   ;

		(* extra copy for the Android App *)
        SRV_T1_heartbeat            := TCP_T1_heartbeat           ;

        SRV_T1_enabled_sensors      := TCP_T1_enabled_sensors     ;
        SRV_T1_temperature          := TCP_T1_temperature         ;
        SRV_T1_temperature_bis      := TCP_T1_temperature_bis     ;
        SRV_T1_temperature_ext      := TCP_T1_temperature_ext     ;
        SRV_T1_humidity             := TCP_T1_humidity            ;

        SRV_T1_temperature_setpoint := TCP_T1_temperature_setpoint;
        SRV_T1_humidity_setpoint    := TCP_T1_humidity_setpoint   ;

        SRV_T1_enabled_lamps        := TCP_T1_enabled_lamps       ;
        SRV_T1_lamp_1               := TCP_T1_lamp_1              ;
        SRV_T1_lamp_2               := TCP_T1_lamp_2              ;
        SRV_T1_lamp_3               := TCP_T1_lamp_3              ;
        SRV_T1_lamp_4               := TCP_T1_lamp_4              ;
        SRV_T1_lamp_5               := TCP_T1_lamp_5              ;

        SRV_T1_max_request_W   := TCP_T1_max_request_W  ;
        SRV_T1_heating              := TCP_T1_heating             ;
        SRV_T1_nighttime            := TCP_T1_nighttime           ;
        SRV_T1_heating_status       := TCP_T1_heating_status      ;
        SRV_T1_heating_timer        := TCP_T1_heating_timer       ;

        SRV_T1_sunrise                 := TCP_T1_sunrise                ;
        SRV_T1_sunset                  := TCP_T1_sunset                 ;
        SRV_T1_temperature_setpoint_nt := TCP_T1_temperature_setpoint_nt;
        SRV_T1_humidity_setpoint_nt    := TCP_T1_humidity_setpoint_nt   ;

        SRV_T1_lamp_feedback_1      := TCP_T1_lamp_feedback_1     ;
        SRV_T1_lamp_feedback_2      := TCP_T1_lamp_feedback_2     ;
        SRV_T1_lamp_feedback_3      := TCP_T1_lamp_feedback_3     ;
        SRV_T1_lamp_feedback_4      := TCP_T1_lamp_feedback_4     ;
        SRV_T1_lamp_feedback_5      := TCP_T1_lamp_feedback_5     ;

        SRV_T1_requested_W          := TCP_T1_requested_W         ;
		SRV_T1_control_type         := TCP_T1_control_type        ;

		SRV_T1_daily_heating_s      := TCP_T1_daily_heating_s     ;
		SRV_T1_monthly_heating_s    := TCP_T1_monthly_heating_s   ;
		end_if;

    if PLC_Iam_T2 then
        SRV_T2_heartbeat            := heartbeat                  ;

        SRV_T2_enabled_sensors      := PLC_T2_enabled_sensors     ;
        SRV_T2_temperature          := PLC_T2_temperature         ;
        SRV_T2_temperature_bis      := PLC_T2_temperature_bis     ;
        SRV_T2_temperature_ext      := PLC_T2_temperature_ext     ;
        SRV_T2_humidity             := PLC_T2_humidity            ;

 (*!*)  PLC_T2_temperature_setpoint := SRV_T2_temperature_setpoint;
 (*!*)  PLC_T2_humidity_setpoint    := SRV_T2_humidity_setpoint   ;

        SRV_T2_enabled_lamps        := PLC_T2_enabled_lamps       ;
 (*!*)  PLC_T2_lamp_1               := SRV_T2_lamp_1              ;
 (*!*)  PLC_T2_lamp_2               := SRV_T2_lamp_2              ;
 (*!*)  PLC_T2_lamp_3               := SRV_T2_lamp_3              ;
 (*!*)  PLC_T2_lamp_4               := SRV_T2_lamp_4              ;
 (*!*)  PLC_T2_lamp_5               := SRV_T2_lamp_5              ;

        SRV_T2_max_request_W   := PLC_T2_max_request_W  ;
        SRV_T2_heating              := PLC_T2_heating             ;
        SRV_T2_nighttime            := PLC_T2_nighttime           ;
 (*!*)  PLC_T2_heating_status       := SRV_T2_heating_status      ;
 (*!*)  PLC_T2_heating_timer        := SRV_T2_heating_timer       ;

        SRV_T2_sunrise              := PLC_sunrise             ;
        SRV_T2_sunset               := PLC_sunset              ;
        PLC_T2_sunrise              := PLC_sunrise             ;
        PLC_T2_sunset               := PLC_sunset              ;
 (*!*)  PLC_T2_temperature_setpoint_nt := SRV_T2_temperature_setpoint_nt;
 (*!*)  PLC_T2_humidity_setpoint_nt    := SRV_T2_humidity_setpoint_nt   ;

        SRV_T2_lamp_feedback_1      := PLC_T2_lamp_feedback_1     ;
        SRV_T2_lamp_feedback_2      := PLC_T2_lamp_feedback_2     ;
        SRV_T2_lamp_feedback_3      := PLC_T2_lamp_feedback_3     ;
        SRV_T2_lamp_feedback_4      := PLC_T2_lamp_feedback_4     ;
        SRV_T2_lamp_feedback_5      := PLC_T2_lamp_feedback_5     ;

		SRV_T2_control_type         := PLC_control_type           ;
		PLC_T2_control_type         := PLC_control_type           ;

		SRV_T2_daily_heating_s      := PLC_T2_daily_heating_s     ;
		SRV_T2_monthly_heating_s    := PLC_T2_monthly_heating_s   ;

	elsif PLC_Tn_count >= 2 then
        PLC_T2_enabled_sensors      := TCP_T2_enabled_sensors     ;
        PLC_T2_temperature          := TCP_T2_temperature         ;
        PLC_T2_temperature_bis      := TCP_T2_temperature_bis     ;
        PLC_T2_temperature_ext      := TCP_T2_temperature_ext     ;
        PLC_T2_humidity             := TCP_T2_humidity            ;

        PLC_T2_temperature_setpoint := TCP_T2_temperature_setpoint;
        PLC_T2_humidity_setpoint    := TCP_T2_humidity_setpoint   ;

        PLC_T2_enabled_lamps        := TCP_T2_enabled_lamps       ;
        PLC_T2_lamp_1               := TCP_T2_lamp_1              ;
        PLC_T2_lamp_2               := TCP_T2_lamp_2              ;
        PLC_T2_lamp_3               := TCP_T2_lamp_3              ;
        PLC_T2_lamp_4               := TCP_T2_lamp_4              ;
        PLC_T2_lamp_5               := TCP_T2_lamp_5              ;

        PLC_T2_max_request_W   := TCP_T2_max_request_W  ;
        PLC_T2_heating              := TCP_T2_heating             ;
        PLC_T2_nighttime            := TCP_T2_nighttime           ;
        PLC_T2_heating_status       := TCP_T2_heating_status      ;
        PLC_T2_heating_timer        := TCP_T2_heating_timer       ;

        PLC_T2_sunrise                 := TCP_T2_sunrise                ;
        PLC_T2_sunset                  := TCP_T2_sunset                 ;
        PLC_T2_temperature_setpoint_nt := TCP_T2_temperature_setpoint_nt;
        PLC_T2_humidity_setpoint_nt    := TCP_T2_humidity_setpoint_nt   ;

        PLC_T2_lamp_feedback_1      := TCP_T2_lamp_feedback_1     ;
        PLC_T2_lamp_feedback_2      := TCP_T2_lamp_feedback_2     ;
        PLC_T2_lamp_feedback_3      := TCP_T2_lamp_feedback_3     ;
        PLC_T2_lamp_feedback_4      := TCP_T2_lamp_feedback_4     ;
        PLC_T2_lamp_feedback_5      := TCP_T2_lamp_feedback_5     ;

        PLC_T2_requested_W          := TCP_T2_requested_W         ;
		PLC_T2_control_type         := TCP_T2_control_type        ;

		PLC_T2_daily_heating_s      := TCP_T2_daily_heating_s     ;
		PLC_T2_monthly_heating_s    := TCP_T2_monthly_heating_s   ;

        (* extra copy for the Android App *)
        SRV_T2_heartbeat            := TCP_T2_heartbeat           ;

        SRV_T2_enabled_sensors      := TCP_T2_enabled_sensors     ;
        SRV_T2_temperature          := TCP_T2_temperature         ;
        SRV_T2_temperature_bis      := TCP_T2_temperature_bis     ;
        SRV_T2_temperature_ext      := TCP_T2_temperature_ext     ;
        SRV_T2_humidity             := TCP_T2_humidity            ;

        SRV_T2_temperature_setpoint := TCP_T2_temperature_setpoint;
        SRV_T2_humidity_setpoint    := TCP_T2_humidity_setpoint   ;

        SRV_T2_enabled_lamps        := TCP_T2_enabled_lamps       ;
        SRV_T2_lamp_1               := TCP_T2_lamp_1              ;
        SRV_T2_lamp_2               := TCP_T2_lamp_2              ;
        SRV_T2_lamp_3               := TCP_T2_lamp_3              ;
        SRV_T2_lamp_4               := TCP_T2_lamp_4              ;
        SRV_T2_lamp_5               := TCP_T2_lamp_5              ;

        SRV_T2_max_request_W   := TCP_T2_max_request_W  ;
        SRV_T2_heating              := TCP_T2_heating             ;
        SRV_T2_nighttime            := TCP_T2_nighttime           ;
        SRV_T2_heating_status       := TCP_T2_heating_status      ;
        SRV_T2_heating_timer        := TCP_T2_heating_timer       ;

        SRV_T2_sunrise                 := TCP_T2_sunrise                ;
        SRV_T2_sunset                  := TCP_T2_sunset                 ;
        SRV_T2_temperature_setpoint_nt := TCP_T2_temperature_setpoint_nt;
        SRV_T2_humidity_setpoint_nt    := TCP_T2_humidity_setpoint_nt   ;

        SRV_T2_lamp_feedback_1      := TCP_T2_lamp_feedback_1     ;
        SRV_T2_lamp_feedback_2      := TCP_T2_lamp_feedback_2     ;
        SRV_T2_lamp_feedback_3      := TCP_T2_lamp_feedback_3     ;
        SRV_T2_lamp_feedback_4      := TCP_T2_lamp_feedback_4     ;
        SRV_T2_lamp_feedback_5      := TCP_T2_lamp_feedback_5     ;

        SRV_T2_requested_W          := TCP_T2_requested_W         ;
		SRV_T2_control_type         := TCP_T2_control_type        ;

		SRV_T2_daily_heating_s      := TCP_T2_daily_heating_s     ;
		SRV_T1_monthly_heating_s    := TCP_T2_monthly_heating_s   ;
    end_if;

    if PLC_Iam_T3 then
        SRV_T3_heartbeat            := heartbeat                  ;

        SRV_T3_enabled_sensors      := PLC_T3_enabled_sensors     ;
        SRV_T3_temperature          := PLC_T3_temperature         ;
        SRV_T3_temperature_bis      := PLC_T3_temperature_bis     ;
        SRV_T3_temperature_ext      := PLC_T3_temperature_ext     ;
        SRV_T3_humidity             := PLC_T3_humidity            ;

 (*!*)  PLC_T3_temperature_setpoint := SRV_T3_temperature_setpoint;
 (*!*)  PLC_T3_humidity_setpoint    := SRV_T3_humidity_setpoint   ;

        SRV_T3_enabled_lamps        := PLC_T3_enabled_lamps       ;
 (*!*)  PLC_T3_lamp_1               := SRV_T3_lamp_1              ;
 (*!*)  PLC_T3_lamp_2               := SRV_T3_lamp_2              ;
 (*!*)  PLC_T3_lamp_3               := SRV_T3_lamp_3              ;
 (*!*)  PLC_T3_lamp_4               := SRV_T3_lamp_4              ;
 (*!*)  PLC_T3_lamp_5               := SRV_T3_lamp_5              ;

        SRV_T3_max_request_W   := PLC_T3_max_request_W  ;
        SRV_T3_heating              := PLC_T3_heating             ;
        SRV_T3_nighttime            := PLC_T3_nighttime           ;
 (*!*)  PLC_T3_heating_status       := SRV_T3_heating_status      ;
 (*!*)  PLC_T3_heating_timer        := SRV_T3_heating_timer       ;

        SRV_T3_sunrise              := PLC_sunrise             ;
        SRV_T3_sunset               := PLC_sunset              ;
        PLC_T3_sunrise              := PLC_sunrise             ;
        PLC_T3_sunset               := PLC_sunset              ;
 (*!*)  PLC_T3_temperature_setpoint_nt := SRV_T3_temperature_setpoint_nt;
 (*!*)  PLC_T3_humidity_setpoint_nt    := SRV_T3_humidity_setpoint_nt   ;

        SRV_T3_lamp_feedback_1      := PLC_T3_lamp_feedback_1     ;
        SRV_T3_lamp_feedback_2      := PLC_T3_lamp_feedback_2     ;
        SRV_T3_lamp_feedback_3      := PLC_T3_lamp_feedback_3     ;
        SRV_T3_lamp_feedback_4      := PLC_T3_lamp_feedback_4     ;
        SRV_T3_lamp_feedback_5      := PLC_T3_lamp_feedback_5     ;

		SRV_T3_control_type         := PLC_control_type           ;
		PLC_T3_control_type         := PLC_control_type           ;

		SRV_T3_daily_heating_s      := PLC_T3_daily_heating_s     ;
		SRV_T3_monthly_heating_s    := PLC_T3_monthly_heating_s   ;

     elsif PLC_Tn_count >= 3 then
        PLC_T3_enabled_sensors      := TCP_T3_enabled_sensors     ;
        PLC_T3_temperature          := TCP_T3_temperature         ;
        PLC_T3_temperature_bis      := TCP_T3_temperature_bis     ;
        PLC_T3_temperature_ext      := TCP_T3_temperature_ext     ;
        PLC_T3_humidity             := TCP_T3_humidity            ;

        PLC_T3_temperature_setpoint := TCP_T3_temperature_setpoint;
        PLC_T3_humidity_setpoint    := TCP_T3_humidity_setpoint   ;

        PLC_T3_enabled_lamps        := TCP_T3_enabled_lamps       ;
        PLC_T3_lamp_1               := TCP_T3_lamp_1              ;
        PLC_T3_lamp_2               := TCP_T3_lamp_2              ;
        PLC_T3_lamp_3               := TCP_T3_lamp_3              ;
        PLC_T3_lamp_4               := TCP_T3_lamp_4              ;
        PLC_T3_lamp_5               := TCP_T3_lamp_5              ;

        PLC_T3_max_request_W   := TCP_T3_max_request_W  ;
        PLC_T3_heating              := TCP_T3_heating             ;
        PLC_T3_nighttime            := TCP_T3_nighttime           ;
        PLC_T3_heating_status       := TCP_T3_heating_status      ;
        PLC_T3_heating_timer        := TCP_T3_heating_timer       ;

        PLC_T3_sunrise                 := TCP_T3_sunrise                ;
        PLC_T3_sunset                  := TCP_T3_sunset                 ;
        PLC_T3_temperature_setpoint_nt := TCP_T3_temperature_setpoint_nt;
        PLC_T3_humidity_setpoint_nt    := TCP_T3_humidity_setpoint_nt   ;

        PLC_T3_lamp_feedback_1      := TCP_T3_lamp_feedback_1     ;
        PLC_T3_lamp_feedback_2      := TCP_T3_lamp_feedback_2     ;
        PLC_T3_lamp_feedback_3      := TCP_T3_lamp_feedback_3     ;
        PLC_T3_lamp_feedback_4      := TCP_T3_lamp_feedback_4     ;
        PLC_T3_lamp_feedback_5      := TCP_T3_lamp_feedback_5     ;

        PLC_T3_requested_W          := TCP_T3_requested_W         ;
		PLC_T3_control_type         := TCP_T3_control_type        ;

		PLC_T3_daily_heating_s      := TCP_T3_daily_heating_s     ;
		PLC_T3_monthly_heating_s    := TCP_T3_monthly_heating_s   ;

        (* extra copy for the Android App *)
        SRV_T3_heartbeat            := TCP_T3_heartbeat           ;

        SRV_T3_enabled_sensors      := TCP_T3_enabled_sensors     ;
        SRV_T3_temperature          := TCP_T3_temperature         ;
        SRV_T3_temperature_bis      := TCP_T3_temperature_bis     ;
        SRV_T3_temperature_ext      := TCP_T3_temperature_ext     ;
        SRV_T3_humidity             := TCP_T3_humidity            ;

        SRV_T3_temperature_setpoint := TCP_T3_temperature_setpoint;
        SRV_T3_humidity_setpoint    := TCP_T3_humidity_setpoint   ;

        SRV_T3_enabled_lamps        := TCP_T3_enabled_lamps       ;
        SRV_T3_lamp_1               := TCP_T3_lamp_1              ;
        SRV_T3_lamp_2               := TCP_T3_lamp_2              ;
        SRV_T3_lamp_3               := TCP_T3_lamp_3              ;
        SRV_T3_lamp_4               := TCP_T3_lamp_4              ;
        SRV_T3_lamp_5               := TCP_T3_lamp_5              ;

        SRV_T3_max_request_W   := TCP_T3_max_request_W  ;
        SRV_T3_heating              := TCP_T3_heating             ;
        SRV_T3_nighttime            := TCP_T3_nighttime           ;
        SRV_T3_heating_status       := TCP_T3_heating_status      ;
        SRV_T3_heating_timer        := TCP_T3_heating_timer       ;

        SRV_T3_sunrise                 := TCP_T3_sunrise                ;
        SRV_T3_sunset                  := TCP_T3_sunset                 ;
        SRV_T3_temperature_setpoint_nt := TCP_T3_temperature_setpoint_nt;
        SRV_T3_humidity_setpoint_nt    := TCP_T3_humidity_setpoint_nt   ;

        SRV_T3_lamp_feedback_1      := TCP_T3_lamp_feedback_1     ;
        SRV_T3_lamp_feedback_2      := TCP_T3_lamp_feedback_2     ;
        SRV_T3_lamp_feedback_3      := TCP_T3_lamp_feedback_3     ;
        SRV_T3_lamp_feedback_4      := TCP_T3_lamp_feedback_4     ;
        SRV_T3_lamp_feedback_5      := TCP_T3_lamp_feedback_5     ;

        SRV_T3_requested_W          := TCP_T3_requested_W         ;
		SRV_T3_control_type         := TCP_T3_control_type        ;

		SRV_T3_daily_heating_s      := TCP_T3_daily_heating_s     ;
		SRV_T3_monthly_heating_s    := TCP_T3_monthly_heating_s   ;
    end_if;

    if PLC_Iam_T4 then
        SRV_T4_heartbeat            := heartbeat                  ;

        SRV_T4_enabled_sensors      := PLC_T4_enabled_sensors     ;
        SRV_T4_temperature          := PLC_T4_temperature         ;
        SRV_T4_temperature_bis      := PLC_T4_temperature_bis     ;
        SRV_T4_temperature_ext      := PLC_T4_temperature_ext     ;
        SRV_T4_humidity             := PLC_T4_humidity            ;

 (*!*)  PLC_T4_temperature_setpoint := SRV_T4_temperature_setpoint;
 (*!*)  PLC_T4_humidity_setpoint    := SRV_T4_humidity_setpoint   ;

        SRV_T4_enabled_lamps        := PLC_T4_enabled_lamps       ;
 (*!*)  PLC_T4_lamp_1               := SRV_T4_lamp_1              ;
 (*!*)  PLC_T4_lamp_2               := SRV_T4_lamp_2              ;
 (*!*)  PLC_T4_lamp_3               := SRV_T4_lamp_3              ;
 (*!*)  PLC_T4_lamp_4               := SRV_T4_lamp_4              ;
 (*!*)  PLC_T4_lamp_5               := SRV_T4_lamp_5              ;

        SRV_T4_max_request_W   := PLC_T4_max_request_W  ;
        SRV_T4_heating              := PLC_T4_heating             ;
        SRV_T4_nighttime            := PLC_T4_nighttime           ;
 (*!*)  PLC_T4_heating_status       := SRV_T4_heating_status      ;
 (*!*)  PLC_T4_heating_timer        := SRV_T4_heating_timer       ;

        SRV_T4_sunrise              := PLC_sunrise             ;
        SRV_T4_sunset               := PLC_sunset              ;
        PLC_T4_sunrise              := PLC_sunrise             ;
        PLC_T4_sunset               := PLC_sunset              ;
 (*!*)  PLC_T4_temperature_setpoint_nt := SRV_T4_temperature_setpoint_nt;
 (*!*)  PLC_T4_humidity_setpoint_nt    := SRV_T4_humidity_setpoint_nt   ;

        SRV_T4_lamp_feedback_1      := PLC_T4_lamp_feedback_1     ;
        SRV_T4_lamp_feedback_2      := PLC_T4_lamp_feedback_2     ;
        SRV_T4_lamp_feedback_3      := PLC_T4_lamp_feedback_3     ;
        SRV_T4_lamp_feedback_4      := PLC_T4_lamp_feedback_4     ;
        SRV_T4_lamp_feedback_5      := PLC_T4_lamp_feedback_5     ;

		SRV_T4_control_type         := PLC_control_type           ;
		PLC_T4_control_type         := PLC_control_type           ;

		SRV_T4_daily_heating_s      := PLC_T4_daily_heating_s     ;
		SRV_T4_monthly_heating_s    := PLC_T4_monthly_heating_s   ;

    elsif PLC_Tn_count >= 4 then
        PLC_T4_enabled_sensors      := TCP_T4_enabled_sensors     ;
        PLC_T4_temperature          := TCP_T4_temperature         ;
        PLC_T4_temperature_bis      := TCP_T4_temperature_bis     ;
        PLC_T4_temperature_ext      := TCP_T4_temperature_ext     ;
        PLC_T4_humidity             := TCP_T4_humidity            ;

        PLC_T4_temperature_setpoint := TCP_T4_temperature_setpoint;
        PLC_T4_humidity_setpoint    := TCP_T4_humidity_setpoint   ;

        PLC_T4_enabled_lamps        := TCP_T4_enabled_lamps       ;
        PLC_T4_lamp_1               := TCP_T4_lamp_1              ;
        PLC_T4_lamp_2               := TCP_T4_lamp_2              ;
        PLC_T4_lamp_3               := TCP_T4_lamp_3              ;
        PLC_T4_lamp_4               := TCP_T4_lamp_4              ;
        PLC_T4_lamp_5               := TCP_T4_lamp_5              ;

        PLC_T4_max_request_W   := TCP_T4_max_request_W  ;
        PLC_T4_heating              := TCP_T4_heating             ;
        PLC_T4_nighttime            := TCP_T4_nighttime           ;
        PLC_T4_heating_status       := TCP_T4_heating_status      ;
        PLC_T4_heating_timer        := TCP_T4_heating_timer       ;

        PLC_T4_sunrise                 := TCP_T4_sunrise                ;
        PLC_T4_sunset                  := TCP_T4_sunset                 ;
        PLC_T4_temperature_setpoint_nt := TCP_T4_temperature_setpoint_nt;
        PLC_T4_humidity_setpoint_nt    := TCP_T4_humidity_setpoint_nt   ;

        PLC_T4_lamp_feedback_1      := TCP_T4_lamp_feedback_1     ;
        PLC_T4_lamp_feedback_2      := TCP_T4_lamp_feedback_2     ;
        PLC_T4_lamp_feedback_3      := TCP_T4_lamp_feedback_3     ;
        PLC_T4_lamp_feedback_4      := TCP_T4_lamp_feedback_4     ;
        PLC_T4_lamp_feedback_5      := TCP_T4_lamp_feedback_5     ;

        PLC_T4_requested_W          := TCP_T4_requested_W         ;
		PLC_T4_control_type         := TCP_T4_control_type        ;

		PLC_T4_daily_heating_s      := TCP_T4_daily_heating_s     ;
		PLC_T4_monthly_heating_s    := TCP_T4_monthly_heating_s   ;

        (* extra copy for the Android App *)
        SRV_T4_heartbeat            := TCP_T4_heartbeat           ;

        SRV_T4_enabled_sensors      := TCP_T4_enabled_sensors     ;
        SRV_T4_temperature          := TCP_T4_temperature         ;
        SRV_T4_temperature_bis      := TCP_T4_temperature_bis     ;
        SRV_T4_temperature_ext      := TCP_T4_temperature_ext     ;
        SRV_T4_humidity             := TCP_T4_humidity            ;

        SRV_T4_temperature_setpoint := TCP_T4_temperature_setpoint;
        SRV_T4_humidity_setpoint    := TCP_T4_humidity_setpoint   ;

        SRV_T4_enabled_lamps        := TCP_T4_enabled_lamps       ;
        SRV_T4_lamp_1               := TCP_T4_lamp_1              ;
        SRV_T4_lamp_2               := TCP_T4_lamp_2              ;
        SRV_T4_lamp_3               := TCP_T4_lamp_3              ;
        SRV_T4_lamp_4               := TCP_T4_lamp_4              ;
        SRV_T4_lamp_5               := TCP_T4_lamp_5              ;

        SRV_T4_max_request_W   := TCP_T4_max_request_W  ;
        SRV_T4_heating              := TCP_T4_heating             ;
        SRV_T4_nighttime            := TCP_T4_nighttime           ;
        SRV_T4_heating_status       := TCP_T4_heating_status      ;
        SRV_T4_heating_timer        := TCP_T4_heating_timer       ;

        SRV_T4_sunrise                 := TCP_T4_sunrise                ;
        SRV_T4_sunset                  := TCP_T4_sunset                 ;
        SRV_T4_temperature_setpoint_nt := TCP_T4_temperature_setpoint_nt;
        SRV_T4_humidity_setpoint_nt    := TCP_T4_humidity_setpoint_nt   ;

        SRV_T4_lamp_feedback_1      := TCP_T4_lamp_feedback_1     ;
        SRV_T4_lamp_feedback_2      := TCP_T4_lamp_feedback_2     ;
        SRV_T4_lamp_feedback_3      := TCP_T4_lamp_feedback_3     ;
        SRV_T4_lamp_feedback_4      := TCP_T4_lamp_feedback_4     ;
        SRV_T4_lamp_feedback_5      := TCP_T4_lamp_feedback_5     ;

        SRV_T4_requested_W          := TCP_T4_requested_W         ;
		SRV_T4_control_type         := TCP_T4_control_type        ;

		SRV_T4_daily_heating_s      := TCP_T4_daily_heating_s     ;
		SRV_T4_monthly_heating_s    := TCP_T4_monthly_heating_s   ;
    end_if;

    if PLC_Iam_T5 then
        SRV_T5_heartbeat            := heartbeat                  ;

        SRV_T5_enabled_sensors      := PLC_T5_enabled_sensors     ;
        SRV_T5_temperature          := PLC_T5_temperature         ;
        SRV_T5_temperature_bis      := PLC_T5_temperature_bis     ;
        SRV_T5_temperature_ext      := PLC_T5_temperature_ext     ;
        SRV_T5_humidity             := PLC_T5_humidity            ;

 (*!*)  PLC_T5_temperature_setpoint := SRV_T5_temperature_setpoint;
 (*!*)  PLC_T5_humidity_setpoint    := SRV_T5_humidity_setpoint   ;

        SRV_T5_enabled_lamps        := PLC_T5_enabled_lamps       ;
 (*!*)  PLC_T5_lamp_1               := SRV_T5_lamp_1              ;
 (*!*)  PLC_T5_lamp_2               := SRV_T5_lamp_2              ;
 (*!*)  PLC_T5_lamp_3               := SRV_T5_lamp_3              ;
 (*!*)  PLC_T5_lamp_4               := SRV_T5_lamp_4              ;
 (*!*)  PLC_T5_lamp_5               := SRV_T5_lamp_5              ;

        SRV_T5_max_request_W   := PLC_T5_max_request_W  ;
        SRV_T5_heating              := PLC_T5_heating             ;
        SRV_T5_nighttime            := PLC_T5_nighttime           ;
 (*!*)  PLC_T5_heating_status       := SRV_T5_heating_status      ;
 (*!*)  PLC_T5_heating_timer        := SRV_T5_heating_timer       ;

        SRV_T5_sunrise              := PLC_sunrise             ;
        SRV_T5_sunset               := PLC_sunset              ;
        PLC_T5_sunrise              := PLC_sunrise             ;
        PLC_T5_sunset               := PLC_sunset              ;
 (*!*)  PLC_T5_temperature_setpoint_nt := SRV_T5_temperature_setpoint_nt;
 (*!*)  PLC_T5_humidity_setpoint_nt    := SRV_T5_humidity_setpoint_nt   ;

        SRV_T5_lamp_feedback_1      := PLC_T5_lamp_feedback_1     ;
        SRV_T5_lamp_feedback_2      := PLC_T5_lamp_feedback_2     ;
        SRV_T5_lamp_feedback_3      := PLC_T5_lamp_feedback_3     ;
        SRV_T5_lamp_feedback_4      := PLC_T5_lamp_feedback_4     ;
        SRV_T5_lamp_feedback_5      := PLC_T5_lamp_feedback_5     ;

		SRV_T5_control_type         := PLC_control_type           ;
		PLC_T5_control_type         := PLC_control_type           ;

		SRV_T5_daily_heating_s      := PLC_T5_daily_heating_s     ;
		SRV_T5_monthly_heating_s    := PLC_T5_monthly_heating_s   ;

     elsif PLC_Tn_count >= 5 then
        PLC_T5_enabled_sensors      := TCP_T5_enabled_sensors     ;
        PLC_T5_temperature          := TCP_T5_temperature         ;
        PLC_T5_temperature_bis      := TCP_T5_temperature_bis     ;
        PLC_T5_temperature_ext      := TCP_T5_temperature_ext     ;
        PLC_T5_humidity             := TCP_T5_humidity            ;

        PLC_T5_temperature_setpoint := TCP_T5_temperature_setpoint;
        PLC_T5_humidity_setpoint    := TCP_T5_humidity_setpoint   ;

        PLC_T5_enabled_lamps        := TCP_T5_enabled_lamps       ;
        PLC_T5_lamp_1               := TCP_T5_lamp_1              ;
        PLC_T5_lamp_2               := TCP_T5_lamp_2              ;
        PLC_T5_lamp_3               := TCP_T5_lamp_3              ;
        PLC_T5_lamp_4               := TCP_T5_lamp_4              ;
        PLC_T5_lamp_5               := TCP_T5_lamp_5              ;

        PLC_T5_max_request_W   := TCP_T5_max_request_W  ;
        PLC_T5_heating              := TCP_T5_heating             ;
        PLC_T5_nighttime            := TCP_T5_nighttime           ;
        PLC_T5_heating_status       := TCP_T5_heating_status      ;
        PLC_T5_heating_timer        := TCP_T5_heating_timer       ;

        PLC_T5_sunrise                 := TCP_T5_sunrise                ;
        PLC_T5_sunset                  := TCP_T5_sunset                 ;
        PLC_T5_temperature_setpoint_nt := TCP_T5_temperature_setpoint_nt;
        PLC_T5_humidity_setpoint_nt    := TCP_T5_humidity_setpoint_nt   ;

        PLC_T5_lamp_feedback_1      := TCP_T5_lamp_feedback_1     ;
        PLC_T5_lamp_feedback_2      := TCP_T5_lamp_feedback_2     ;
        PLC_T5_lamp_feedback_3      := TCP_T5_lamp_feedback_3     ;
        PLC_T5_lamp_feedback_4      := TCP_T5_lamp_feedback_4     ;
        PLC_T5_lamp_feedback_5      := TCP_T5_lamp_feedback_5     ;

        PLC_T5_requested_W          := TCP_T5_requested_W         ;
		PLC_T5_control_type         := TCP_T5_control_type        ;

		PLC_T5_daily_heating_s      := TCP_T5_daily_heating_s     ;
		PLC_T5_monthly_heating_s    := TCP_T5_monthly_heating_s   ;

        (* extra copy for the Android App *)
        SRV_T5_heartbeat            := TCP_T5_heartbeat           ;

        SRV_T5_enabled_sensors      := TCP_T5_enabled_sensors     ;
        SRV_T5_temperature          := TCP_T5_temperature         ;
        SRV_T5_temperature_bis      := TCP_T5_temperature_bis     ;
        SRV_T5_temperature_ext      := TCP_T5_temperature_ext     ;
        SRV_T5_humidity             := TCP_T5_humidity            ;

        SRV_T5_temperature_setpoint := TCP_T5_temperature_setpoint;
        SRV_T5_humidity_setpoint    := TCP_T5_humidity_setpoint   ;

        SRV_T5_enabled_lamps        := TCP_T5_enabled_lamps       ;
        SRV_T5_lamp_1               := TCP_T5_lamp_1              ;
        SRV_T5_lamp_2               := TCP_T5_lamp_2              ;
        SRV_T5_lamp_3               := TCP_T5_lamp_3              ;
        SRV_T5_lamp_4               := TCP_T5_lamp_4              ;
        SRV_T5_lamp_5               := TCP_T5_lamp_5              ;

        SRV_T5_max_request_W   := TCP_T5_max_request_W  ;
        SRV_T5_heating              := TCP_T5_heating             ;
        SRV_T5_nighttime            := TCP_T5_nighttime           ;
        SRV_T5_heating_status       := TCP_T5_heating_status      ;
        SRV_T5_heating_timer        := TCP_T5_heating_timer       ;

        SRV_T5_sunrise                 := TCP_T5_sunrise                ;
        SRV_T5_sunset                  := TCP_T5_sunset                 ;
        SRV_T5_temperature_setpoint_nt := TCP_T5_temperature_setpoint_nt;
        SRV_T5_humidity_setpoint_nt    := TCP_T5_humidity_setpoint_nt   ;

        SRV_T5_lamp_feedback_1      := TCP_T5_lamp_feedback_1     ;
        SRV_T5_lamp_feedback_2      := TCP_T5_lamp_feedback_2     ;
        SRV_T5_lamp_feedback_3      := TCP_T5_lamp_feedback_3     ;
        SRV_T5_lamp_feedback_4      := TCP_T5_lamp_feedback_4     ;
        SRV_T5_lamp_feedback_5      := TCP_T5_lamp_feedback_5     ;

        SRV_T5_requested_W          := TCP_T5_requested_W         ;
		SRV_T5_control_type         := TCP_T5_control_type        ;

		SRV_T5_daily_heating_s      := TCP_T5_daily_heating_s     ;
		SRV_T5_monthly_heating_s    := TCP_T5_monthly_heating_s   ;
    end_if;

    if PLC_Iam_T6 then
        SRV_T6_heartbeat            := heartbeat                  ;

        SRV_T6_enabled_sensors      := PLC_T6_enabled_sensors     ;
        SRV_T6_temperature          := PLC_T6_temperature         ;
        SRV_T6_temperature_bis      := PLC_T6_temperature_bis     ;
        SRV_T6_temperature_ext      := PLC_T6_temperature_ext     ;
        SRV_T6_humidity             := PLC_T6_humidity            ;

 (*!*)  PLC_T6_temperature_setpoint := SRV_T6_temperature_setpoint;
 (*!*)  PLC_T6_humidity_setpoint    := SRV_T6_humidity_setpoint   ;

        SRV_T6_enabled_lamps        := PLC_T6_enabled_lamps       ;
 (*!*)  PLC_T6_lamp_1               := SRV_T6_lamp_1              ;
 (*!*)  PLC_T6_lamp_2               := SRV_T6_lamp_2              ;
 (*!*)  PLC_T6_lamp_3               := SRV_T6_lamp_3              ;
 (*!*)  PLC_T6_lamp_4               := SRV_T6_lamp_4              ;
 (*!*)  PLC_T6_lamp_5               := SRV_T6_lamp_5              ;

        SRV_T6_max_request_W   := PLC_T6_max_request_W  ;
        SRV_T6_heating              := PLC_T6_heating             ;
        SRV_T6_nighttime            := PLC_T6_nighttime           ;
 (*!*)  PLC_T6_heating_status       := SRV_T6_heating_status      ;
 (*!*)  PLC_T6_heating_timer        := SRV_T6_heating_timer       ;

        SRV_T6_sunrise              := PLC_sunrise             ;
        SRV_T6_sunset               := PLC_sunset              ;
        PLC_T6_sunrise              := PLC_sunrise             ;
        PLC_T6_sunset               := PLC_sunset              ;
 (*!*)  PLC_T6_temperature_setpoint_nt := SRV_T6_temperature_setpoint_nt;
 (*!*)  PLC_T6_humidity_setpoint_nt    := SRV_T6_humidity_setpoint_nt   ;

        SRV_T6_lamp_feedback_1      := PLC_T6_lamp_feedback_1     ;
        SRV_T6_lamp_feedback_2      := PLC_T6_lamp_feedback_2     ;
        SRV_T6_lamp_feedback_3      := PLC_T6_lamp_feedback_3     ;
        SRV_T6_lamp_feedback_4      := PLC_T6_lamp_feedback_4     ;
        SRV_T6_lamp_feedback_5      := PLC_T6_lamp_feedback_5     ;

		SRV_T6_control_type         := PLC_control_type           ;
		PLC_T6_control_type         := PLC_control_type           ;

		SRV_T6_daily_heating_s      := PLC_T6_daily_heating_s     ;
		SRV_T6_monthly_heating_s    := PLC_T6_monthly_heating_s   ;

    elsif PLC_Tn_count >= 6 then
        PLC_T6_enabled_sensors      := TCP_T6_enabled_sensors     ;
        PLC_T6_temperature          := TCP_T6_temperature         ;
        PLC_T6_temperature_bis      := TCP_T6_temperature_bis     ;
        PLC_T6_temperature_ext      := TCP_T6_temperature_ext     ;
        PLC_T6_humidity             := TCP_T6_humidity            ;

        PLC_T6_temperature_setpoint := TCP_T6_temperature_setpoint;
        PLC_T6_humidity_setpoint    := TCP_T6_humidity_setpoint   ;

        PLC_T6_enabled_lamps        := TCP_T6_enabled_lamps       ;
        PLC_T6_lamp_1               := TCP_T6_lamp_1              ;
        PLC_T6_lamp_2               := TCP_T6_lamp_2              ;
        PLC_T6_lamp_3               := TCP_T6_lamp_3              ;
        PLC_T6_lamp_4               := TCP_T6_lamp_4              ;
        PLC_T6_lamp_5               := TCP_T6_lamp_5              ;

        PLC_T6_max_request_W   := TCP_T6_max_request_W  ;
        PLC_T6_heating              := TCP_T6_heating             ;
        PLC_T6_nighttime            := TCP_T6_nighttime           ;
        PLC_T6_heating_status       := TCP_T6_heating_status      ;
        PLC_T6_heating_timer        := TCP_T6_heating_timer       ;

        PLC_T6_sunrise                 := TCP_T6_sunrise                ;
        PLC_T6_sunset                  := TCP_T6_sunset                 ;
        PLC_T6_temperature_setpoint_nt := TCP_T6_temperature_setpoint_nt;
        PLC_T6_humidity_setpoint_nt    := TCP_T6_humidity_setpoint_nt   ;

        PLC_T6_lamp_feedback_1      := TCP_T6_lamp_feedback_1     ;
        PLC_T6_lamp_feedback_2      := TCP_T6_lamp_feedback_2     ;
        PLC_T6_lamp_feedback_3      := TCP_T6_lamp_feedback_3     ;
        PLC_T6_lamp_feedback_4      := TCP_T6_lamp_feedback_4     ;
        PLC_T6_lamp_feedback_5      := TCP_T6_lamp_feedback_5     ;

        PLC_T6_requested_W      := TCP_T6_requested_W    ;
		PLC_T6_control_type     := TCP_T6_control_type    ;

		PLC_T6_daily_heating_s      := TCP_T6_daily_heating_s     ;
		PLC_T6_monthly_heating_s    := TCP_T6_monthly_heating_s   ;

        (* extra copy for the Android App *)
        SRV_T6_heartbeat            := TCP_T6_heartbeat           ;

        SRV_T6_enabled_sensors      := TCP_T6_enabled_sensors     ;
        SRV_T6_temperature          := TCP_T6_temperature         ;
        SRV_T6_temperature_bis      := TCP_T6_temperature_bis     ;
        SRV_T6_temperature_ext      := TCP_T6_temperature_ext     ;
        SRV_T6_humidity             := TCP_T6_humidity            ;

        SRV_T6_temperature_setpoint := TCP_T6_temperature_setpoint;
        SRV_T6_humidity_setpoint    := TCP_T6_humidity_setpoint   ;

        SRV_T6_enabled_lamps        := TCP_T6_enabled_lamps       ;
        SRV_T6_lamp_1               := TCP_T6_lamp_1              ;
        SRV_T6_lamp_2               := TCP_T6_lamp_2              ;
        SRV_T6_lamp_3               := TCP_T6_lamp_3              ;
        SRV_T6_lamp_4               := TCP_T6_lamp_4              ;
        SRV_T6_lamp_5               := TCP_T6_lamp_5              ;

        SRV_T6_max_request_W   := TCP_T6_max_request_W  ;
        SRV_T6_heating              := TCP_T6_heating             ;
        SRV_T6_nighttime            := TCP_T6_nighttime           ;
        SRV_T6_heating_status       := TCP_T6_heating_status      ;
        SRV_T6_heating_timer        := TCP_T6_heating_timer       ;

        SRV_T6_sunrise                 := TCP_T6_sunrise                ;
        SRV_T6_sunset                  := TCP_T6_sunset                 ;
        SRV_T6_temperature_setpoint_nt := TCP_T6_temperature_setpoint_nt;
        SRV_T6_humidity_setpoint_nt    := TCP_T6_humidity_setpoint_nt   ;

        SRV_T6_lamp_feedback_1      := TCP_T6_lamp_feedback_1     ;
        SRV_T6_lamp_feedback_2      := TCP_T6_lamp_feedback_2     ;
        SRV_T6_lamp_feedback_3      := TCP_T6_lamp_feedback_3     ;
        SRV_T6_lamp_feedback_4      := TCP_T6_lamp_feedback_4     ;
        SRV_T6_lamp_feedback_5      := TCP_T6_lamp_feedback_5     ;

        SRV_T6_requested_W          := TCP_T6_requested_W         ;
		SRV_T6_control_type         := TCP_T6_control_type        ;

		SRV_T6_daily_heating_s      := TCP_T6_daily_heating_s     ;
		SRV_T6_monthly_heating_s    := TCP_T6_monthly_heating_s   ;
    end_if;

    if PLC_Iam_BA then
        SRV_BA_heartbeat        := heartbeat              ;
        SRV_BA_enabled_sensors  := PLC_BA_enabled_sensors ;
        SRV_BA_status           := PLC_BA_status          ;
        SRV_BA_config_index     := PLC_BA_config_index    ;
        SRV_BA_config_mask      := PLC_BA_config_mask     ;

		(*
		 * vedi BA_WriteLeds()
         * SRV_BA_led_green        := PLC_BA_led_green       ;
         * SRV_BA_led_red          := PLC_BA_led_red         ;
         * SRV_BA_led_yellow1      := PLC_BA_led_yellow1     ;
         * SRV_BA_led_yellow2      := PLC_BA_led_yellow2     ;
		 *)

        SRV_BA_siren            := PLC_BA_siren           ;
        SRV_BA_relay_A          := PLC_BA_relay_A         ;
        SRV_BA_relay_B          := PLC_BA_relay_B         ;
        SRV_BA_relay_C          := PLC_BA_relay_C         ;
        SRV_BA_input_9          := PLC_BA_input_9         ;
        SRV_BA_input_10         := PLC_BA_input_10        ;
        SRV_BA_input_11         := PLC_BA_input_11        ;
        SRV_BA_input_12         := PLC_BA_input_12        ;
        SRV_BA_BlackoutDetected := PLC_BA_BlackoutDetected;

 (*!*)  PLC_BA_command          := SRV_BA_command         ;

        SRV_BA_OK_1             := PLC_BA_OK_1            ;
        SRV_BA_OK_2             := PLC_BA_OK_2            ;
        SRV_BA_OK_3             := PLC_BA_OK_3            ;
        SRV_BA_OK_4             := PLC_BA_OK_4            ;
        SRV_BA_OK_5             := PLC_BA_OK_5            ;
        SRV_BA_OK_6             := PLC_BA_OK_6            ;
        SRV_BA_OK_7             := PLC_BA_OK_7            ;
        SRV_BA_OK_8             := PLC_BA_OK_8            ;
        SRV_BA_OK_9             := PLC_BA_OK_9            ;
        SRV_BA_OK_10            := PLC_BA_OK_10           ;
        SRV_BA_OK_11            := PLC_BA_OK_11           ;
        SRV_BA_OK_12            := PLC_BA_OK_12           ;
        SRV_BA_OK_13            := PLC_BA_OK_13           ;
        SRV_BA_OK_14            := PLC_BA_OK_14           ;
        SRV_BA_OK_15            := PLC_BA_OK_15           ;
        SRV_BA_OK_16            := PLC_BA_OK_16           ;
        SRV_BA_OK_17            := PLC_BA_OK_17           ;
        SRV_BA_OK_18            := PLC_BA_OK_18           ;
        SRV_BA_OK_19            := PLC_BA_OK_19           ;
        SRV_BA_OK_20            := PLC_BA_OK_20           ;
        SRV_BA_OK_21            := PLC_BA_OK_21           ;
        SRV_BA_OK_22            := PLC_BA_OK_22           ;
        SRV_BA_OK_23            := PLC_BA_OK_23           ;
        SRV_BA_OK_24            := PLC_BA_OK_24           ;
        SRV_BA_OK_25            := PLC_BA_OK_25           ;
        SRV_BA_OK_26            := PLC_BA_OK_26           ;
        SRV_BA_OK_27            := PLC_BA_OK_27           ;
        SRV_BA_OK_28            := PLC_BA_OK_28           ;
        SRV_BA_OK_29            := PLC_BA_OK_29           ;
        SRV_BA_OK_30            := PLC_BA_OK_30           ;
        SRV_BA_OK_31            := PLC_BA_OK_31           ;
        SRV_BA_OK_32            := PLC_BA_OK_32           ;

		SRV_BA_control_type     := PLC_control_type       ;
		PLC_BA_control_type     := PLC_control_type       ;

    elsif PLC_BA_exists then
        PLC_BA_enabled_sensors  := TCP_BA_enabled_sensors ;
        PLC_BA_status           := TCP_BA_status          ;
        PLC_BA_config_index     := TCP_BA_config_index    ;
        PLC_BA_config_mask      := TCP_BA_config_mask     ;

		if PLC_BA_isOK and TCP_BA_status = ALARM_STATUS_RINGING then
			if not PLC_BA_ringing_flag then PLC_BA_ringing_flag := true; end_if;
		else
			if PLC_BA_ringing_flag then PLC_BA_ringing_flag := false; end_if;
		end_if;

        PLC_BA_led_green        := TCP_BA_led_green       ;
        PLC_BA_led_red          := TCP_BA_led_red         ;
        PLC_BA_led_yellow1      := TCP_BA_led_yellow1     ;
        PLC_BA_led_yellow2      := TCP_BA_led_yellow2     ;
        PLC_BA_siren            := TCP_BA_siren           ;
        PLC_BA_relay_A          := TCP_BA_relay_A         ;
        PLC_BA_relay_B          := TCP_BA_relay_B         ;
        PLC_BA_relay_C          := TCP_BA_relay_C         ;
        PLC_BA_input_9          := TCP_BA_input_9         ;
        PLC_BA_input_10         := TCP_BA_input_10        ;
        PLC_BA_input_11         := TCP_BA_input_11        ;
        PLC_BA_input_12         := TCP_BA_input_12        ;
		if PLC_BA_isOK then
	        (* NB: PLC_BA_BlackoutDetected Alarm condition is "FALLING" *)
			PLC_BA_blackout_digin := not TCP_BA_BlackoutDetected;
		elsif not PLC_BA_blackout_digin then
			(* avoid alarm when connection fails *)
			PLC_BA_blackout_digin := true;
		end_if;

        PLC_BA_command          := TCP_BA_command         ;

        PLC_BA_OK_1             := TCP_BA_OK_1            ;
        PLC_BA_OK_2             := TCP_BA_OK_2            ;
        PLC_BA_OK_3             := TCP_BA_OK_3            ;
        PLC_BA_OK_4             := TCP_BA_OK_4            ;
        PLC_BA_OK_5             := TCP_BA_OK_5            ;
        PLC_BA_OK_6             := TCP_BA_OK_6            ;
        PLC_BA_OK_7             := TCP_BA_OK_7            ;
        PLC_BA_OK_8             := TCP_BA_OK_8            ;
        PLC_BA_OK_9             := TCP_BA_OK_9            ;
        PLC_BA_OK_10            := TCP_BA_OK_10           ;
        PLC_BA_OK_11            := TCP_BA_OK_11           ;
        PLC_BA_OK_12            := TCP_BA_OK_12           ;
        PLC_BA_OK_13            := TCP_BA_OK_13           ;
        PLC_BA_OK_14            := TCP_BA_OK_14           ;
        PLC_BA_OK_15            := TCP_BA_OK_15           ;
        PLC_BA_OK_16            := TCP_BA_OK_16           ;
        PLC_BA_OK_17            := TCP_BA_OK_17           ;
        PLC_BA_OK_18            := TCP_BA_OK_18           ;
        PLC_BA_OK_19            := TCP_BA_OK_19           ;
        PLC_BA_OK_20            := TCP_BA_OK_20           ;
        PLC_BA_OK_21            := TCP_BA_OK_21           ;
        PLC_BA_OK_22            := TCP_BA_OK_22           ;
        PLC_BA_OK_23            := TCP_BA_OK_23           ;
        PLC_BA_OK_24            := TCP_BA_OK_24           ;
        PLC_BA_OK_25            := TCP_BA_OK_25           ;
        PLC_BA_OK_26            := TCP_BA_OK_26           ;
        PLC_BA_OK_27            := TCP_BA_OK_27           ;
        PLC_BA_OK_28            := TCP_BA_OK_28           ;
        PLC_BA_OK_29            := TCP_BA_OK_29           ;
        PLC_BA_OK_30            := TCP_BA_OK_30           ;
        PLC_BA_OK_31            := TCP_BA_OK_31           ;
        PLC_BA_OK_32            := TCP_BA_OK_32           ;

		PLC_BA_control_type     := TCP_BA_control_type    ;

        (* extra copy for the Android App *)
        SRV_BA_heartbeat        := TCP_BA_heartbeat       ;

        SRV_BA_enabled_sensors  := TCP_BA_enabled_sensors ;
        SRV_BA_status           := TCP_BA_status          ;
        SRV_BA_config_index     := TCP_BA_config_index    ;
        SRV_BA_config_mask      := TCP_BA_config_mask     ;

        SRV_BA_led_green        := TCP_BA_led_green       ;
        SRV_BA_led_red          := TCP_BA_led_red         ;
        SRV_BA_led_yellow1      := TCP_BA_led_yellow1     ;
        SRV_BA_led_yellow2      := TCP_BA_led_yellow2     ;
        SRV_BA_siren            := TCP_BA_siren           ;
        SRV_BA_relay_A          := TCP_BA_relay_A         ;
        SRV_BA_relay_B          := TCP_BA_relay_B         ;
        SRV_BA_relay_C          := TCP_BA_relay_C         ;
        SRV_BA_input_9          := TCP_BA_input_9         ;
        SRV_BA_input_10         := TCP_BA_input_10        ;
        SRV_BA_input_11         := TCP_BA_input_11        ;
        SRV_BA_input_12         := TCP_BA_input_12        ;
        SRV_BA_BlackoutDetected := TCP_BA_BlackoutDetected;

        SRV_BA_command          := TCP_BA_command         ;

        SRV_BA_OK_1             := TCP_BA_OK_1            ;
        SRV_BA_OK_2             := TCP_BA_OK_2            ;
        SRV_BA_OK_3             := TCP_BA_OK_3            ;
        SRV_BA_OK_4             := TCP_BA_OK_4            ;
        SRV_BA_OK_5             := TCP_BA_OK_5            ;
        SRV_BA_OK_6             := TCP_BA_OK_6            ;
        SRV_BA_OK_7             := TCP_BA_OK_7            ;
        SRV_BA_OK_8             := TCP_BA_OK_8            ;
        SRV_BA_OK_9             := TCP_BA_OK_9            ;
        SRV_BA_OK_10            := TCP_BA_OK_10           ;
        SRV_BA_OK_11            := TCP_BA_OK_11           ;
        SRV_BA_OK_12            := TCP_BA_OK_12           ;
        SRV_BA_OK_13            := TCP_BA_OK_13           ;
        SRV_BA_OK_14            := TCP_BA_OK_14           ;
        SRV_BA_OK_15            := TCP_BA_OK_15           ;
        SRV_BA_OK_16            := TCP_BA_OK_16           ;
        SRV_BA_OK_17            := TCP_BA_OK_17           ;
        SRV_BA_OK_18            := TCP_BA_OK_18           ;
        SRV_BA_OK_19            := TCP_BA_OK_19           ;
        SRV_BA_OK_20            := TCP_BA_OK_20           ;
        SRV_BA_OK_21            := TCP_BA_OK_21           ;
        SRV_BA_OK_22            := TCP_BA_OK_22           ;
        SRV_BA_OK_23            := TCP_BA_OK_23           ;
        SRV_BA_OK_24            := TCP_BA_OK_24           ;
        SRV_BA_OK_25            := TCP_BA_OK_25           ;
        SRV_BA_OK_26            := TCP_BA_OK_26           ;
        SRV_BA_OK_27            := TCP_BA_OK_27           ;
        SRV_BA_OK_28            := TCP_BA_OK_28           ;
        SRV_BA_OK_29            := TCP_BA_OK_29           ;
        SRV_BA_OK_30            := TCP_BA_OK_30           ;
        SRV_BA_OK_31            := TCP_BA_OK_31           ;
        SRV_BA_OK_32            := TCP_BA_OK_32           ;

		SRV_BA_control_type     := TCP_BA_control_type    ;
    end_if;

END_PROGRAM
