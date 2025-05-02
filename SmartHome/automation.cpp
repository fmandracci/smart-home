/****************************************************************************
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
****************************************************************************/

#include "crosstable.h"
#include "automation.h"

#include <QDebug>
#include <QSettings>

#if defined(MECT_SUITE_3_5)
#elif defined(MECT_SUITE_3_4)
int mectScreenWidth;
int mectScreenHeight;
float mectFontCorrector;
#else
#error
#endif

Modulor * modulor;

const char *status_names[HEATING_COUNT + 1] = {
    "OFF",
    "AUTO",
    "-2°C", // "--", // "ECO",
    "+2°C", // "++", // "COM-\nFORT",
    "BOOST",
    "???"
};

const QString heating_name(int heating_status)
{
    if (heating_status >= 0 and heating_status < HEATING_COUNT) {
        return QString::fromUtf8(status_names[heating_status]);
    } else {
        return QString::fromUtf8(status_names[HEATING_COUNT]);
    }
}

int currentThermostat = -1;
int currentWattmeter = -1;

void setup(void)
{
    qDebug() << HMIversion;

    // --------- engine ---------------------------------------------
    while (PLC_EngineStatus < 2) {
        fputc('*', stderr);
        sleep(1);
    }
    doWrite_PLC_HMI_Version(2005);

    // --------- system ---------------------------------------------
    doWrite_PLC_timeWin(300); // graph: 5'
    // NB: in system.ini "Trend Window [s]"
    // 108000 = 1d + 12h = 30h = { 4.3" = 5 colonne da 6 ore, 7.0" = 10 colonne da 3 ore }
    //  18000 =       5h =  5h = { 4.3" = 5 colonne da 1 ora, 7.0" = 10 colonne da ½ ora }

    if (TimerValue_1 <= 0) {
        doWrite_TimerValue_1(10*60*1000); // 10'
    }
    if (TimerValue_2 <= 0) {
        doWrite_TimerValue_2(20*60*1000); // 20'
    }
    doWrite_PLC_TOUCH_VOLUME(50); // 50%

    // vedi pages.cpp: SERIAL_PORT_3/baudrate=225000 in TPAC1007_04_A[ACD]

    // --------- EP + T1 + T2 + T3 + T4 + BA ---------------------------------------
    if (PLC_Iam_EP) {
        unsigned byte3 = (TCP0_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP0_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP0_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP0_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("sudo ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_T1) {
        unsigned byte3 = (TCP1_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP1_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP1_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP1_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("sudo ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_T2) {
        unsigned byte3 = (TCP2_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP2_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP2_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP2_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("sudo ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_T3) {
        unsigned byte3 = (TCP3_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP3_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP3_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP3_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("sudo ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_T4) {
        unsigned byte3 = (TCP4_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP4_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP4_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP4_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("sudo ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_T5) {
        unsigned byte3 = (TCP5_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP5_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP5_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP5_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("sudo ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_T6) {
        unsigned byte3 = (TCP6_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP6_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP6_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP6_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("sudo ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_BA) {
        unsigned byte3 = (TCP7_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP7_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP7_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP7_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("sudo ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }

    // --------- MectSuite + sMily logs ---------------------------------------------
    logStart();
}

void loop(void)
{
    // --------- system ---------------------------------------------
//    switch (PLC_EngineStatus) {
//    }
}

void resetPLC_timeOffset()
{
    if (PLC_timeMax_bis < 86400.0) {
        doWrite_PLC_timeOffset(PLC_timeMax_bis + PLC_timeWin);
    } else {
        doWrite_PLC_timeOffset(- PLC_time);
    }
}
