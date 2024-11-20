﻿/****************************************************************************
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
#include "page101a.h"
#include "ui_page101a.h"
#include "crosstable.h"

#include "automation.h"
#include <QTime>

page101a::page101a(QWidget *parent) :
    page(parent),
    ui(new Ui::page101a)
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
}

void page101a::changeWidgets(const QString t, const QString name, const QString T, const QString Tbis, const QString Text,
                             const QString Thumidity, const QString Thumidity_bis, const QString Thumidity_ext,
                             int Tn_max_request_W, const QString Tn_requested_W, const QString EP_Tn_assigned_W,
                             int daily_heating_s, int monthly_heating_s,
                             int Tn_temperature_setpoint, int Tn_temperature_setpoint_nt,
                             int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color)
{
    QString offStyleSheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());

    // header
    ui->label_Tn->setText(t);
    ui->label_Tn->setStyleSheet(offStyleSheet);
    ui->label_Tn_temperature_setpoint->setStyleSheet(offStyleSheet);

    // left margin
    ui->label_heating_status->setVisible(abs(enabled_sensors) > 0);
    ui->label_heating_status->setStyleSheet(offStyleSheet);
    ui->label_heating_timer->setVisible(abs(enabled_sensors) > 0);
    ui->label_heating_timer->setStyleSheet(offStyleSheet);
    ui->atcmButton_prev->setFontColor(color);

    // right margin
    ui->atcmButton_next->setFontColor(color);

    // footer
    ui->atcmButton_down->setEnabled(enabled_sensors < 0 and Iam_Tn);

    // center grid
    ui->label_name->setText(name);
    ui->label_name->setStyleSheet(offStyleSheet);

    ui->atcmLabel_Tn_temperature->setVisible(true); // (abs(enabled_sensors) >= 1);
    ui->atcmLabel_Tn_temperature->setVariable(T);
    ui->atcmLabel_Tn_temperature->setFontColor(color);
    ui->atcmLabel_Tn_temperature->setBorderColor(color);

    ui->atcmLabel_Tn_humidity->setVisible(enabled_sensors <= -1);
    ui->atcmLabel_Tn_humidity->setVariable(Thumidity);
    ui->atcmLabel_Tn_humidity->setFontColor(color);
    ui->atcmLabel_Tn_humidity->setBorderColor(color);

    ui->atcmLabel_Tn_temperature_bis->setVisible(abs(enabled_sensors) >= 2);
    ui->atcmLabel_Tn_temperature_bis->setVariable(Tbis);
    ui->atcmLabel_Tn_temperature_bis->setFontColor(color);
    ui->atcmLabel_Tn_temperature_bis->setBorderColor(color);

    ui->atcmLabel_Tn_humidity_bis->setVisible(enabled_sensors <= -2);
    ui->atcmLabel_Tn_humidity_bis->setVariable(Thumidity_bis);
    ui->atcmLabel_Tn_humidity_bis->setFontColor(color);
    ui->atcmLabel_Tn_humidity_bis->setBorderColor(color);

    ui->atcmLabel_Tn_temperature_ext->setVisible(abs(enabled_sensors) >= 3);
    ui->atcmLabel_Tn_temperature_ext->setVariable(Text);
    ui->atcmLabel_Tn_temperature_ext->setFontColor(color);

    ui->atcmLabel_Tn_humidity_ext->setVisible(enabled_sensors <= -3);
    ui->atcmLabel_Tn_humidity_ext->setVariable(Thumidity_ext);
    ui->atcmLabel_Tn_humidity_ext->setFontColor(color);

    ui->label_daily->setStyleSheet(offStyleSheet);
    ui->label_monthly->setStyleSheet(offStyleSheet);

    if (Tn_max_request_W > 0) {
        ui->atcmLabel_Tn_requested_W->setVariable(Tn_requested_W);
        ui->atcmLabel_Tn_requested_W->setFontColor(color);
        ui->atcmLabel_Tn_requested_W->setVisible(true);

        ui->atcmLabel_Tn_assigned_W->setVariable(EP_Tn_assigned_W);
        ui->atcmLabel_Tn_assigned_W->setFontColor(color);
        ui->atcmLabel_Tn_assigned_W->setVisible(true);
    } else {
        ui->atcmLabel_Tn_requested_W->setVisible(false);
        ui->atcmLabel_Tn_assigned_W->setVisible(false);
    }
    updateWidgets(daily_heating_s, monthly_heating_s, Tn_temperature_setpoint, Tn_temperature_setpoint_nt, enabled_sensors, Iam_Tn, Tn_isOK, Tn_heating_status, Tn_heating_timer, Tn_heating, color);
}

void page101a::reload()
{
    QSettings hmi_ini("/local/root/hmi.ini", QSettings::IniFormat);

    if (PLC_Tn_count >= 2) {
        ui->atcmButton_up->setPageName("page100");
    } else {
        currentThermostat = 1;
        ui->atcmButton_up->setPageName("HOME");
    }
    switch (currentThermostat) {
    case  1: changeWidgets(LABEL_01, hmi_ini.value("T1/name").toString(), "PLC_T1_temperature", "PLC_T1_temperature_bis", "PLC_T1_temperature_ext", "PLC_T1_humidity", "PLC_T1_humidity_bis", "PLC_T1_humidity_ext", PLC_T1_max_request_W, "PLC_T1_requested_W", "PLC_EP_T1_assigned_W", PLC_T1_daily_heating_s, PLC_T1_monthly_heating_s, PLC_T1_temperature_setpoint, PLC_T1_temperature_setpoint_nt, PLC_T1_enabled_sensors, PLC_Iam_T1, PLC_T1_isOK, PLC_T1_heating_status, PLC_T1_heating_timer, PLC_T1_heating, COLOR_01); break;
    case  2: changeWidgets(LABEL_02, hmi_ini.value("T2/name").toString(), "PLC_T2_temperature", "PLC_T2_temperature_bis", "PLC_T2_temperature_ext", "PLC_T2_humidity", "PLC_T2_humidity_bis", "PLC_T2_humidity_ext", PLC_T2_max_request_W, "PLC_T2_requested_W", "PLC_EP_T2_assigned_W", PLC_T2_daily_heating_s, PLC_T2_monthly_heating_s, PLC_T2_temperature_setpoint, PLC_T2_temperature_setpoint_nt, PLC_T2_enabled_sensors, PLC_Iam_T2, PLC_T2_isOK, PLC_T2_heating_status, PLC_T2_heating_timer, PLC_T2_heating, COLOR_02); break;
    case  3: changeWidgets(LABEL_03, hmi_ini.value("T3/name").toString(), "PLC_T3_temperature", "PLC_T3_temperature_bis", "PLC_T3_temperature_ext", "PLC_T3_humidity", "PLC_T3_humidity_bis", "PLC_T3_humidity_ext", PLC_T3_max_request_W, "PLC_T3_requested_W", "PLC_EP_T3_assigned_W", PLC_T3_daily_heating_s, PLC_T3_monthly_heating_s, PLC_T3_temperature_setpoint, PLC_T3_temperature_setpoint_nt, PLC_T3_enabled_sensors, PLC_Iam_T3, PLC_T3_isOK, PLC_T3_heating_status, PLC_T3_heating_timer, PLC_T3_heating, COLOR_03); break;
    case  4: changeWidgets(LABEL_04, hmi_ini.value("T4/name").toString(), "PLC_T4_temperature", "PLC_T4_temperature_bis", "PLC_T4_temperature_ext", "PLC_T4_humidity", "PLC_T4_humidity_bis", "PLC_T4_humidity_ext", PLC_T4_max_request_W, "PLC_T4_requested_W", "PLC_EP_T4_assigned_W", PLC_T4_daily_heating_s, PLC_T4_monthly_heating_s, PLC_T4_temperature_setpoint, PLC_T4_temperature_setpoint_nt, PLC_T4_enabled_sensors, PLC_Iam_T4, PLC_T4_isOK, PLC_T4_heating_status, PLC_T4_heating_timer, PLC_T4_heating, COLOR_04); break;
    case  5: changeWidgets(LABEL_05, hmi_ini.value("T5/name").toString(), "PLC_T5_temperature", "PLC_T5_temperature_bis", "PLC_T5_temperature_ext", "PLC_T5_humidity", "PLC_T5_humidity_bis", "PLC_T5_humidity_ext", PLC_T5_max_request_W, "PLC_T5_requested_W", "PLC_EP_T5_assigned_W", PLC_T5_daily_heating_s, PLC_T5_monthly_heating_s, PLC_T5_temperature_setpoint, PLC_T5_temperature_setpoint_nt, PLC_T5_enabled_sensors, PLC_Iam_T5, PLC_T5_isOK, PLC_T5_heating_status, PLC_T5_heating_timer, PLC_T5_heating, COLOR_05); break;
    case  6: changeWidgets(LABEL_06, hmi_ini.value("T6/name").toString(), "PLC_T6_temperature", "PLC_T6_temperature_bis", "PLC_T6_temperature_ext", "PLC_T6_humidity", "PLC_T6_humidity_bis", "PLC_T6_humidity_ext", PLC_T6_max_request_W, "PLC_T6_requested_W", "PLC_EP_T6_assigned_W", PLC_T6_daily_heating_s, PLC_T6_monthly_heating_s, PLC_T6_temperature_setpoint, PLC_T6_temperature_setpoint_nt, PLC_T6_enabled_sensors, PLC_Iam_T6, PLC_T6_isOK, PLC_T6_heating_status, PLC_T6_heating_timer, PLC_T6_heating, COLOR_06); break;
    default: changeWidgets("??"    , ""                                 , ""                  , ""                      , ""                      , ""               , ""                   , ""                   , 0                   , ""                  , ""                    , 0                     , 0                       , 0                          , 0                             , 0                     , 0         , 0          , 0                    , 0                   , 0             , COLOR_01);
    }
}

void page101a::updateWidgets(int daily_heating_s, int monthly_heating_s, int Tn_temperature_setpoint, int Tn_temperature_setpoint_nt,
                             int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color)
{
    QString offStylesheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());
    QString onStylesheet = QString("background-color: rgb(%1, %2, %3); color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());

    // header
    updateLedLabels(ui->label_EP, ui->label_BA, ui->label_green,
                    ui->label_T5, ui->label_T6, ui->label_red,
                    ui->label_T3, ui->label_T4, ui->label_yellow_1,
                    ui->label_T1, ui->label_T2, ui->label_yellow_2);
    ui->pushButton_time->setText(PLC_nighttime ? TIME_FMT_NIGHTTIME : TIME_FMT_DAYTIME);
    ui->label_Tn_temperature_setpoint->setText(QString("%1 %2%3\n%4 %5%6")
                                               .arg(LABEL_TRIANGLE).arg(Tn_temperature_setpoint/10.0, 3, 'f', 1).arg(LABEL_CELSIUS)
                                               .arg(LABEL_TRIANGLE).arg(Tn_temperature_setpoint_nt/10.0, 3, 'f', 1).arg(LABEL_CELSIUS));

    // left margin
    if (Iam_Tn or Tn_isOK) {
        ui->label_heating_status->setVisible(abs(enabled_sensors) >= 1);
        ui->label_heating_timer->setVisible(abs(enabled_sensors) >= 1);
        if (abs(enabled_sensors) >= 1) {
            ui->label_heating_status->setText(heating_name(Tn_heating_status));
            ui->label_heating_status->setStyleSheet(Tn_heating ? onStylesheet : offStylesheet);
            if (Tn_heating_status > HEATING_AUTO) {
                ui->label_heating_timer->setText(QTime().addSecs(Tn_heating_timer).toString("HH:mm\nss"));
            } else {
                ui->label_heating_timer->setText("");
            }
        }
    } else {
        ui->label_heating_status->setText(heating_name(-1)); // LABEL_MISSING);
        ui->label_heating_status->setStyleSheet(offStylesheet);
        ui->label_heating_timer->setText("");
        ui->label_heating_status->setVisible(true);
        ui->label_heating_timer->setVisible(true);
    }

    // right margin

    // footer

    // center grid
    ui->label_daily->setText(QString("day: %1h%2'").arg(daily_heating_s / 3600).arg((daily_heating_s % 3600) / 60));
    ui->label_monthly->setText(QString("month: %1h%2'").arg(monthly_heating_s / 3600).arg((monthly_heating_s % 3600) / 60));
}

void page101a::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();

    switch (currentThermostat) {
    case  1: updateWidgets(PLC_T1_daily_heating_s, PLC_T1_monthly_heating_s, PLC_T1_temperature_setpoint, PLC_T1_temperature_setpoint_nt, PLC_T1_enabled_sensors, PLC_Iam_T1, PLC_T1_isOK, PLC_T1_heating_status, PLC_T1_heating_timer, PLC_T1_heating, COLOR_01); break;
    case  2: updateWidgets(PLC_T2_daily_heating_s, PLC_T2_monthly_heating_s, PLC_T2_temperature_setpoint, PLC_T2_temperature_setpoint_nt, PLC_T2_enabled_sensors, PLC_Iam_T2, PLC_T2_isOK, PLC_T2_heating_status, PLC_T2_heating_timer, PLC_T2_heating, COLOR_02); break;
    case  3: updateWidgets(PLC_T3_daily_heating_s, PLC_T3_monthly_heating_s, PLC_T3_temperature_setpoint, PLC_T3_temperature_setpoint_nt, PLC_T3_enabled_sensors, PLC_Iam_T3, PLC_T3_isOK, PLC_T3_heating_status, PLC_T3_heating_timer, PLC_T3_heating, COLOR_03); break;
    case  4: updateWidgets(PLC_T4_daily_heating_s, PLC_T4_monthly_heating_s, PLC_T4_temperature_setpoint, PLC_T4_temperature_setpoint_nt, PLC_T4_enabled_sensors, PLC_Iam_T4, PLC_T4_isOK, PLC_T4_heating_status, PLC_T4_heating_timer, PLC_T4_heating, COLOR_04); break;
    case  5: updateWidgets(PLC_T5_daily_heating_s, PLC_T5_monthly_heating_s, PLC_T5_temperature_setpoint, PLC_T5_temperature_setpoint_nt, PLC_T5_enabled_sensors, PLC_Iam_T5, PLC_T5_isOK, PLC_T5_heating_status, PLC_T5_heating_timer, PLC_T5_heating, COLOR_05); break;
    case  6: updateWidgets(PLC_T6_daily_heating_s, PLC_T6_monthly_heating_s, PLC_T6_temperature_setpoint, PLC_T6_temperature_setpoint_nt, PLC_T6_enabled_sensors, PLC_Iam_T6, PLC_T6_isOK, PLC_T6_heating_status, PLC_T6_heating_timer, PLC_T6_heating, COLOR_06); break;
    default: updateWidgets(0                     , 0                       , 0                          , 0                             , 0                     , 0         , 0          , 0                    , 0                   , 0             , COLOR_01);
    }
}

void page101a::on_pushButton_plot_clicked()
{
    goto_page("page102", true);
}

void page101a::on_pushButton_trend_clicked()
{
    switch (currentThermostat) {
    case  1: goto_trend_page("trend_T1.csv") break;
    case  2: goto_trend_page("trend_T2.csv") break;
    case  3: goto_trend_page("trend_T3.csv") break;
    case  4: if (PLC_T4_control_type == ControlType_6) goto_trend_page("trend_T4puffer.csv") else goto_trend_page("trend_T4.csv") break;
    case  5: goto_trend_page("trend_T5.csv") break;
    case  6: goto_trend_page("trend_T6.csv") break;
    default: ;
    }
}

void page101a::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page101a::~page101a()
{
    delete ui;
}
