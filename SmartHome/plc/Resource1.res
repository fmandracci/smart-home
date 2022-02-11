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

RESOURCE Resource1
    #IMPORT "Crosstable.gvl"
    #IMPORT "Resource1.gvl"
        TASK Task0_Init(EVENT:='4,12,23', PRIORITY:=0, AUTOSTART:=TRUE);
        TASK Task1_Alarms(EVENT:='28', PRIORITY:=1, AUTOSTART:=TRUE);
        TASK Task2_Events(EVENT:='27', PRIORITY:=2, AUTOSTART:=TRUE);
        TASK Task3_System_100ms(INTERVAL:=T#100ms, PRIORITY:=3, AUTOSTART:=TRUE);
        TASK Task4_Normal_500ms(INTERVAL:=T#500ms, PRIORITY:=4, AUTOSTART:=TRUE);
        TASK Task5_Slow_1000ms(INTERVAL:=T#1000ms, PRIORITY:=5, AUTOSTART:=TRUE);
        
        PROGRAM Init            WITH  Task0_Init        : Init;
        PROGRAM Alarms          WITH  Task1_Alarms      : Alarms;
        PROGRAM Events          WITH  Task2_Events      : Events;

        PROGRAM Buzzer          WITH  Task3_System_100ms: Buzzer;

        PROGRAM System          WITH  Task4_Normal_500ms: System;
        PROGRAM BA_main         WITH  Task4_Normal_500ms: BA_main;
        PROGRAM Tn_Lamps        WITH  Task4_Normal_500ms: Tn_Lamps;

        PROGRAM EP_Relays       WITH  Task5_Slow_1000ms : EP_Relays;
        PROGRAM EP_Wattmeters   WITH  Task5_Slow_1000ms : EP_Wattmeters;
        PROGRAM EP_LoadBalancer WITH  Task5_Slow_1000ms: EP_LoadBalancer;
        PROGRAM Tn_Thermo       WITH  Task5_Slow_1000ms : Tn_Thermo;
        PROGRAM Tn_NightTime    WITH  Task5_Slow_1000ms : Tn_NightTime;
        PROGRAM TcpUpdate       WITH  Task5_Slow_1000ms : TcpUpdate;
       
END_RESOURCE

