/****************************************************************************
**
** Copyright (C) 2021-2025 Francesco Mandracci
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
****************************************************************************/

#include "crosstable.h"
#include "automation.h"


void setup(void)
{
    qDebug() << HMIversion;

    // --------- engine ---------------------------------------------
    while (PLC_EngineStatus < 2) {
        fputc('*', stderr);
        sleep(1);
    }
    doWrite_PLC_HMI_Version(1205);

    // --------- system ---------------------------------------------
    // TPX4120 FastIO Configuration
    doWrite_PLC_FastIO_Ena(0x000000FF);
    doWrite_PLC_FastIO_Dir(0x000000F0);
    // Insert your start-up code here
    // .....
    doWrite_PLC_timeWin(300); // 5 minutes
    logStart();
}

/* put here the operation made every 100ms */
void loop(void)
{
    // --------- system ---------------------------------------------
//    switch (PLC_EngineStatus) {
//    }
}
