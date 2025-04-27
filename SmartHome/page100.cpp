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

#include "app_logprint.h"
#include "atcmplugin.h"
#include "main.h"
#include "page100.h"
#include "ui_page100.h"
#include "crosstable.h"

#include "automation.h"

page100::page100(QWidget *parent) :
    page(parent),
    ui(new Ui::page100)
{
    ui->setupUi(this);
    TRANSLATE_FONT_SIZE(this);
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page100::reload()
{
    changeWidgets();
    updateWidgets();
}

void page100::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();
    updateWidgets();
}

void page100::changeWidgets()
{
    ui->headerPanel->changeWidgets("trend_Tall.csv", TH_PIXMAP, NULL, "page100: Tn");

    changeTemperature(ui->label_1, ui->pushButton_SP_1, ui->pushButton_status_1, ui->pushButton_1, ui->label_ext_1, 1, COLOR_01);
    changeTemperature(ui->label_2, ui->pushButton_SP_2, ui->pushButton_status_2, ui->pushButton_2, ui->label_ext_2, 2, COLOR_02);
    changeTemperature(ui->label_3, ui->pushButton_SP_3, ui->pushButton_status_3, ui->pushButton_3, ui->label_ext_3, 3, COLOR_03);
    changeTemperature(ui->label_4, ui->pushButton_SP_4, ui->pushButton_status_4, ui->pushButton_4, ui->label_ext_4, 4, COLOR_04);
    changeTemperature(ui->label_5, ui->pushButton_SP_5, ui->pushButton_status_5, ui->pushButton_5, ui->label_ext_5, 5, COLOR_05);
    changeTemperature(ui->label_6, ui->pushButton_SP_6, ui->pushButton_status_6, ui->pushButton_6, ui->label_ext_6, 6, COLOR_06);
}

void page100::updateWidgets()
{
    ui->headerPanel->updateWidgets();

    updateTemperature(ui->label_1, LABEL_01_ON, LABEL_01, ui->pushButton_SP_1, ui->pushButton_status_1, ui->pushButton_1, ui->label_ext_1, 1, PLC_T1_enabled_sensors, PLC_T1_temperature_setpoint, PLC_T1_temperature_setpoint_nt, PLC_T1_temperature, PLC_T1_temperature_bis, PLC_T1_temperature_ext, PLC_T1_humidity, PLC_Iam_T1, PLC_T1_isOK, PLC_T1_heating_status, PLC_T1_heating);
    updateTemperature(ui->label_2, LABEL_02_ON, LABEL_02, ui->pushButton_SP_2, ui->pushButton_status_2, ui->pushButton_2, ui->label_ext_2, 2, PLC_T2_enabled_sensors, PLC_T2_temperature_setpoint, PLC_T2_temperature_setpoint_nt, PLC_T2_temperature, PLC_T2_temperature_bis, PLC_T2_temperature_ext, PLC_T2_humidity, PLC_Iam_T2, PLC_T2_isOK, PLC_T2_heating_status, PLC_T2_heating);
    updateTemperature(ui->label_3, LABEL_03_ON, LABEL_03, ui->pushButton_SP_3, ui->pushButton_status_3, ui->pushButton_3, ui->label_ext_3, 3, PLC_T3_enabled_sensors, PLC_T3_temperature_setpoint, PLC_T3_temperature_setpoint_nt, PLC_T3_temperature, PLC_T3_temperature_bis, PLC_T3_temperature_ext, PLC_T3_humidity, PLC_Iam_T3, PLC_T3_isOK, PLC_T3_heating_status, PLC_T3_heating);
    updateTemperature(ui->label_4, LABEL_04_ON, LABEL_04, ui->pushButton_SP_4, ui->pushButton_status_4, ui->pushButton_4, ui->label_ext_4, 4, PLC_T4_enabled_sensors, PLC_T4_temperature_setpoint, PLC_T4_temperature_setpoint_nt, PLC_T4_temperature, PLC_T4_temperature_bis, PLC_T4_temperature_ext, PLC_T4_humidity, PLC_Iam_T4, PLC_T4_isOK, PLC_T4_heating_status, PLC_T4_heating);
    updateTemperature(ui->label_5, LABEL_05_ON, LABEL_05, ui->pushButton_SP_5, ui->pushButton_status_5, ui->pushButton_5, ui->label_ext_5, 5, PLC_T5_enabled_sensors, PLC_T5_temperature_setpoint, PLC_T5_temperature_setpoint_nt, PLC_T5_temperature, PLC_T5_temperature_bis, PLC_T5_temperature_ext, PLC_T5_humidity, PLC_Iam_T5, PLC_T5_isOK, PLC_T5_heating_status, PLC_T5_heating);
    updateTemperature(ui->label_6, LABEL_06_ON, LABEL_06, ui->pushButton_SP_6, ui->pushButton_status_6, ui->pushButton_6, ui->label_ext_6, 6, PLC_T6_enabled_sensors, PLC_T6_temperature_setpoint, PLC_T6_temperature_setpoint_nt, PLC_T6_temperature, PLC_T6_temperature_bis, PLC_T6_temperature_ext, PLC_T6_humidity, PLC_Iam_T6, PLC_T6_isOK, PLC_T6_heating_status, PLC_T6_heating);
}

void page100::changeTemperature(QLabel *label_n, QPushButton *pushButton_setpoint,
                                QPushButton *pushButton_status, QPushButton *pushButton, QLabel *label_ext,
                                int n, const QColor color)
{
    if (n <= PLC_Tn_count) {
        int zoom;
        switch (PLC_Tn_count) {
        case 6: zoom = 100; break;
        case 5: zoom = 116; break;
        case 4: zoom = 133; break;
        case 3: zoom = 150; break;
        case 2: zoom = 166; break;
        case 1: zoom = 183; break;
        default: zoom = 99;
        }
        int pointSize_n  = (mectScreenHeight - ui->headerPanel->ledsHeight_px()) / 7 * zoom / 100; // ①
        int pointSize_sp = ui->headerPanel->tinyFont_px() * zoom / 100; // Set Point
        int pointSize_s  = ui->headerPanel->titleFont_px() * zoom / 100; // status
        int pointSize_t  = ui->headerPanel->titleFont_px() * zoom / 100; // xx.x°C xx.x°C
        int pointSize_e  = ui->headerPanel->titleFont_px() * zoom / 100; // xx.x°C

        // label_n  ①
        label_n->setStyleSheet(COLOR_SS(color) + FONT_SS_N(pointSize_n));
        label_n->setVisible(true);

        // pushButton_setpoint
        pushButton_setpoint->setStyleSheet(COLOR_SS(color) + FONT_SS_B(pointSize_sp) + BORDER_SS(color));
        pushButton_setpoint->setVisible(true);

        // pushButton_status "AUTO"
        pushButton_status->setStyleSheet(COLOR_SS(color) + FONT_SS_B(pointSize_s) + BORDER_SS(color));
        pushButton_status->setVisible(true);

        // pushButton xx.x°C xx.x°C
        pushButton->setStyleSheet(COLOR_SS(color) + FONT_SS_B(pointSize_t) + BORDER_SS(color));
        pushButton->setVisible(true);

        // label_ext  "-2.5°C"
        label_ext->setStyleSheet(COLOR_SS(color) + FONT_SS_BI(pointSize_e));
        label_ext->setVisible(true);

    } else {
        label_n->setVisible(false);
        pushButton_setpoint->setVisible(false);
        pushButton_status->setVisible(false);
        pushButton->setVisible(false);
        label_ext->setVisible(false);
    }
}

void page100::updateTemperature(QLabel *label_n, const QString label_on, const QString label_off, QPushButton *pushButton_setpoint,
                                QPushButton *pushButton_status, QPushButton *pushButton, QLabel *label_ext,
                                int n, int sensors,
                                int tsp, int tsp_nt, int t, int t_bis, int t_ext, int h,
                                int Iam_Tn, bool Tn_isOK, int Tn_heating_status, bool Tn_heating)
{
    if (n <= PLC_Tn_count) {
        int fieldWidth = 0;

        // label_n  ①
        label_n->setText(Tn_heating ? label_on : label_off);

        // pushButton_setpoint
        if (Iam_Tn or Tn_isOK) {
            pushButton_setpoint->setText(QString("%1%3\n%2%3") .arg(tsp/10.0, 3, 'f', 1) .arg(tsp_nt/10.0, 3, 'f', 1) .arg(LABEL_CELSIUS));
        } else {
            pushButton_setpoint->setText(heating_name(-1));
        }

        // pushButton_status "AUTO"
        if (Iam_Tn or Tn_isOK) {
            pushButton_status->setText(" " + heating_name(Tn_heating_status) + " ");
        } else {
            pushButton_status->setText(heating_name(-1));
        }

        // pushButton xx.x°C xx.x°C
        if (t >= 1000) {
            fieldWidth = 3;
        } else if (t >= 100) {
            fieldWidth = 3;
        } else if (t >= 10) {
            fieldWidth = 4;
        } else if (t >= 0) {
            fieldWidth = 5;
        } else if (t >= -10) {
            fieldWidth = 3;
        } else if (t >= -100) {
            fieldWidth = 2;
        }
        if (Tn_isOK) {
            QString tStr    = t > TemperatureError     ? QString("%1") .arg(t    /10.0, fieldWidth, 'f', 1) : LABEL_NULL_T;
            QString tBisStr = t_bis > TemperatureError ? QString("%1") .arg(t_bis/10.0, fieldWidth, 'f', 1) : LABEL_NULL_T;
            QString hStr    = h > HumidityError        ? QString("%1") .arg(h    /10.0, fieldWidth, 'f', 1) : LABEL_NULL_H;

            if (abs(sensors) >= 3) {
                // three temperatures (don't display humidity)
                pushButton->setText(QString(" %1%2 %3%4 ").arg(tStr).arg(LABEL_CELSIUS).arg(tBisStr).arg(LABEL_CELSIUS));
            } else if (abs(sensors) == 2) {
                // two temperatures (don't display humidity)
                pushButton->setText(QString(" %1%2 %3%4 ").arg(tStr).arg(LABEL_CELSIUS).arg(tBisStr).arg(LABEL_CELSIUS));
            } else if (sensors == -1) {
                // temperature and humidity
                pushButton->setText(QString(" %1%2 %3% ").arg(tStr).arg(LABEL_CELSIUS).arg(hStr));
            } else if (sensors == 1) {
                // one temperature
                pushButton->setText(QString("%1%2").arg(tStr).arg(LABEL_CELSIUS));
            } else {
                pushButton->setText(QString("%1%2").arg(LABEL_NULL_T).arg(LABEL_CELSIUS));
            }
        } else {
            pushButton->setText(QString("%1%2").arg(LABEL_NULL_T).arg(LABEL_CELSIUS));
        }

        // label_ext  "-2.5°C"
        if (abs(sensors) >= 3) {
                QString tExtStr = t_ext > TemperatureError ? QString("%1").arg(t_ext/10.0, fieldWidth, 'f', 1): LABEL_NULL_T;
                label_ext->setText(QString("%1%2").arg(tExtStr).arg(LABEL_CELSIUS));
        } else {
                label_ext->setText("");
        }

    } else {
        label_n->setVisible(false);
        pushButton_setpoint->setVisible(false);
        pushButton_status->setVisible(false);
        pushButton->setVisible(false);
        label_ext->setVisible(false);
    }
}

void page100::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

page100::~page100()
{
    delete ui;
}
