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
    doWrite_PLC_HMI_Version(1205);

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
        QString command = QString("ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_T1) {
        unsigned byte3 = (TCP1_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP1_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP1_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP1_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_T2) {
        unsigned byte3 = (TCP2_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP2_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP2_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP2_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_T3) {
        unsigned byte3 = (TCP3_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP3_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP3_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP3_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_T4) {
        unsigned byte3 = (TCP4_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP4_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP4_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP4_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_T5) {
        unsigned byte3 = (TCP5_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP5_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP5_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP5_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_T6) {
        unsigned byte3 = (TCP6_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP6_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP6_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP6_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

        qDebug() << command;
        system(command.toLatin1().data());
    }
    if (PLC_Iam_BA) {
        unsigned byte3 = (TCP7_IP_ADDRESS & 0xFF000000) >> 24;
        unsigned byte2 = (TCP7_IP_ADDRESS & 0x00FF0000) >> 16;
        unsigned byte1 = (TCP7_IP_ADDRESS & 0x0000FF00) >>  8;
        unsigned byte0 = (TCP7_IP_ADDRESS & 0x000000FF) >>  0;
        QString command = QString("ip addr add %1.%2.%3.%4/24 dev eth0").arg(byte3).arg(byte2).arg(byte1).arg(byte0);

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

void changeHeader(QWidget *time_button, QWidget *home_button,
                  QLabel *label_EP, QLabel *label_BA, QLabel *label_green,
                  QLabel *label_T5, QLabel *label_T6, QLabel *label_red,
                  QLabel *label_T3, QLabel *label_T4, QLabel *label_yellow_1,
                  QLabel *label_T1, QLabel *label_T2, QLabel *label_yellow_2)
{
    int pointSize_t;
    int pointSize_h;
    int pixelSize_xy;

    if (mectScreenWidth >= 1280) {
        pointSize_t = 42;
        pointSize_h = 32;
        pixelSize_xy = 20;
    } else if (mectScreenWidth >= 800) {
        pointSize_t = 32;
        pointSize_h = 28;
        pixelSize_xy = 15;
    } else {
        pointSize_t = 28;
        pointSize_h = 24;
        pixelSize_xy = 15;
    }

    if (time_button)
        time_button->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(pointSize_t));
    if (home_button)
        home_button->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(pointSize_h));

    QSize labelSize(pixelSize_xy, pixelSize_xy);
    if (label_EP)
        label_EP->setMaximumSize(labelSize);
    if (label_BA)
        label_BA->setMaximumSize(labelSize);
    if (label_green)
        label_green->setMaximumSize(labelSize);
    if (label_T5)
        label_T5->setMaximumSize(labelSize);
    if (label_T6)
        label_T6->setMaximumSize(labelSize);
    if (label_red)
        label_red->setMaximumSize(labelSize);
    if (label_T3)
        label_T3->setMaximumSize(labelSize);
    if (label_T4)
        label_T4->setMaximumSize(labelSize);
    if (label_yellow_1)
        label_yellow_1->setMaximumSize(labelSize);
    if (label_T1)
        label_T1->setMaximumSize(labelSize);
    if (label_T2)
        label_T2->setMaximumSize(labelSize);
    if (label_yellow_2)
        label_yellow_2->setMaximumSize(labelSize);
}

void updateLedLabels(QLabel *label_EP, QLabel *label_BA, QLabel *label_green,
                     QLabel *label_T5, QLabel *label_T6, QLabel *label_red,
                     QLabel *label_T3, QLabel *label_T4, QLabel *label_yellow_1,
                     QLabel *label_T1, QLabel *label_T2, QLabel *label_yellow_2)
{
    const QString     RED_OVER_BLACK("color: rgb(255,   0,   0); background-color: rgb(0, 0, 0);");
    const QString   GREEN_OVER_BLACK("color: rgb(  0, 255,   0); background-color: rgb(0, 0, 0);");
    const QString  YELLOW_OVER_BLACK("color: rgb(255, 255,   0); background-color: rgb(0, 0, 0);");
    const QString    GREY_OVER_BLACK("color: rgb( 64,  64,  64); background-color: rgb(0, 0, 0);");
    const QString MAGENTA_OVER_BLACK("color: rgb(255,   0, 255); background-color: rgb(0, 0, 0);");
    const QString    CYAN_OVER_BLACK("color: rgb(  0, 255, 255); background-color: rgb(0, 0, 0);");

    const QString YELLOW_OVER_BLACK_BORDER = YELLOW_OVER_BLACK + "border: 1px solid rgb(255, 255,   0);";
  //const QString  GREEN_OVER_BLACK_BORDER = GREEN_OVER_BLACK  + "border: 1px solid rgb(  0, 255,   0);";
    const QString   CYAN_OVER_BLACK_BORDER = CYAN_OVER_BLACK   + "border: 1px solid rgb(  0, 255, 255);";

    const QPixmap Error_png(":/systemicons/Error.png");
    const QPixmap Danger_png(":/systemicons/Danger.png");
    const QPixmap Alert_png(":/systemicons/Alert.png");

    label_EP->setVisible(PLC_EP_exists);
    if (PLC_EP_exists) {
        if (PLC_EP_BlackoutDetected) { // vedi plc/TcpUpdate.st
            label_EP->setPixmap(Danger_png);
        } else if (PLC_EP_OverloadDetected) { // vedi plc/TcpUpdate.st
            label_EP->setPixmap(Alert_png);
        } else {
            label_EP->setText(LABEL_EP);
            if (not PLC_EP_isOK) {
                label_EP->setPixmap(Error_png);
            } else if (PLC_Iam_EP) {
                label_EP->setStyleSheet(CYAN_OVER_BLACK_BORDER);
            } else  {
                label_EP->setStyleSheet(GREEN_OVER_BLACK);
            }
        }
    }

    label_BA->setVisible(PLC_BA_exists);
    if (PLC_BA_exists) {
        if (PLC_BA_AlarmRinging) { // vedi plc/TcpUpdate.st
            label_BA->setPixmap(Alert_png);
        } else if (PLC_BA_BlackoutDetected) { // vedi plc/TcpUpdate.st
            label_BA->setPixmap(Danger_png);
        } else {
            label_BA->setText(LABEL_BA);
            if (not PLC_BA_isOK) {
                label_BA->setPixmap(Error_png);
            } else if (PLC_Iam_BA) {
                label_BA->setStyleSheet(CYAN_OVER_BLACK_BORDER);
            } else {
                label_BA->setStyleSheet(GREEN_OVER_BLACK);
            }
        }
    }

    label_green->setVisible(PLC_BA_exists);
    if (PLC_BA_exists) {
        label_green->setText(LABEL_B_CIRCLE);
        if (not PLC_BA_isOK) {
            label_green->setStyleSheet(MAGENTA_OVER_BLACK);
        } else if (PLC_BA_led_green) {
            label_green->setStyleSheet(GREEN_OVER_BLACK);
        } else {
            label_green->setStyleSheet(GREY_OVER_BLACK);
        }
    }

    label_red->setVisible(PLC_BA_exists);
    if (PLC_BA_exists) {
        label_red->setText(LABEL_B_CIRCLE);
        if (not PLC_BA_isOK) {
            label_red->setStyleSheet(MAGENTA_OVER_BLACK);
        } else if (PLC_BA_led_red) {
            label_red->setStyleSheet(RED_OVER_BLACK);
        } else {
            label_red->setStyleSheet(GREY_OVER_BLACK);
        }
    }

    label_yellow_1->setVisible(PLC_BA_exists);
    if (PLC_BA_exists) {
        label_yellow_1->setText(LABEL_B_CIRCLE);
        if (not PLC_BA_isOK) {
            label_yellow_1->setStyleSheet(MAGENTA_OVER_BLACK);
        } else if (PLC_BA_led_yellow1) {
            label_yellow_1->setStyleSheet(YELLOW_OVER_BLACK);
        } else {
            label_yellow_1->setStyleSheet(GREY_OVER_BLACK);
        }
    }

    label_yellow_2->setVisible(PLC_BA_exists);
    if (PLC_BA_exists) {
        label_yellow_2->setText(LABEL_B_CIRCLE);
        if (not PLC_BA_isOK) {
            label_yellow_2->setStyleSheet(MAGENTA_OVER_BLACK);
        } else if (PLC_BA_led_yellow2) {
            label_yellow_2->setStyleSheet(YELLOW_OVER_BLACK);
        } else {
            label_yellow_2->setStyleSheet(GREY_OVER_BLACK);
        }
    }

    label_T1->setVisible(PLC_Tn_count >= 1);
    if (PLC_Tn_count >= 1) {
        label_T1->setText(PLC_T1_heating ? LABEL_01_ON : LABEL_01);
        if (not PLC_T1_isOK) {
            label_T1->setPixmap(Error_png);
        } else if (PLC_Iam_T1) {
            label_T1->setStyleSheet(PLC_T1_heating ? YELLOW_OVER_BLACK_BORDER : CYAN_OVER_BLACK_BORDER);
        } else {
            label_T1->setStyleSheet(PLC_T1_heating ? YELLOW_OVER_BLACK : GREEN_OVER_BLACK);
        }
    }

    label_T2->setVisible(PLC_Tn_count >= 2);
    if (PLC_Tn_count >= 2) {
        label_T2->setText(PLC_T2_heating ? LABEL_02_ON : LABEL_02);
        if (not PLC_T2_isOK) {
            label_T2->setPixmap(Error_png);
        } else if (PLC_Iam_T2) {
            label_T2->setStyleSheet(PLC_T2_heating ? YELLOW_OVER_BLACK_BORDER : CYAN_OVER_BLACK_BORDER);
        } else {
            label_T2->setStyleSheet(PLC_T2_heating ? YELLOW_OVER_BLACK : GREEN_OVER_BLACK);
        }
    }

    label_T3->setVisible(PLC_Tn_count >= 3);
    if (PLC_Tn_count >= 3) {
        label_T3->setText(PLC_T3_heating ? LABEL_03_ON : LABEL_03);
        if (not PLC_T3_isOK) {
            label_T3->setPixmap(Error_png);
        } else if (PLC_Iam_T3) {
            label_T3->setStyleSheet(PLC_T3_heating ? YELLOW_OVER_BLACK_BORDER : CYAN_OVER_BLACK_BORDER);
        } else {
            label_T3->setStyleSheet(PLC_T3_heating ? YELLOW_OVER_BLACK : GREEN_OVER_BLACK);
        }
    }

    label_T4->setVisible(PLC_Tn_count >= 4);
    if (PLC_Tn_count >= 4) {
        label_T4->setText(PLC_T4_heating ? LABEL_04_ON : LABEL_04);
        if (not PLC_T4_isOK) {
            label_T4->setPixmap(Error_png);
        } else if (PLC_Iam_T4) {
            label_T4->setStyleSheet(PLC_T4_heating ? YELLOW_OVER_BLACK_BORDER : CYAN_OVER_BLACK_BORDER);
        } else {
            label_T4->setStyleSheet(PLC_T4_heating ? YELLOW_OVER_BLACK : GREEN_OVER_BLACK);
        }
    }

    label_T5->setVisible(PLC_Tn_count >= 5);
    if (PLC_Tn_count >= 5) {
        label_T5->setText(PLC_T5_heating ? LABEL_05_ON : LABEL_05);
        if (not PLC_T5_isOK) {
            label_T5->setPixmap(Error_png);
        } else if (PLC_Iam_T5) {
            label_T5->setStyleSheet(PLC_T5_heating ? YELLOW_OVER_BLACK_BORDER : CYAN_OVER_BLACK_BORDER);
        } else {
            label_T5->setStyleSheet(PLC_T5_heating ? YELLOW_OVER_BLACK : GREEN_OVER_BLACK);
        }
    }

    label_T6->setVisible(PLC_Tn_count >= 6);
    if (PLC_Tn_count >= 6) {
        label_T6->setText(PLC_T6_heating ? LABEL_06_ON : LABEL_06);
        if (not PLC_T6_isOK) {
            label_T6->setPixmap(Error_png);
        } else if (PLC_Iam_T6) {
            label_T6->setStyleSheet(PLC_T6_heating ? YELLOW_OVER_BLACK_BORDER : CYAN_OVER_BLACK_BORDER);
        } else {
            label_T6->setStyleSheet(PLC_T6_heating ? YELLOW_OVER_BLACK : GREEN_OVER_BLACK);
        }
    }
}

void resetPLC_timeOffset()
{
    if (PLC_timeMax_bis < 86400.0) {
        doWrite_PLC_timeOffset(PLC_timeMax_bis + PLC_timeWin);
    } else {
        doWrite_PLC_timeOffset(- PLC_time);
    }
}
