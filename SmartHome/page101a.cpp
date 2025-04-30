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
#include "page101a.h"
#include "ui_page101a.h"
#include "crosstable.h"

#include "automation.h"
#include <QTime>

page101a::page101a(QWidget *parent) :
    page(parent),
    ui(new Ui::page101a),
    black(0, 0, 0)
{
    ui->setupUi(this);
    TRANSLATE_FONT_SIZE(this);
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page101a::reload()
{
    QSettings home_ini(HOME_INI_FILE, QSettings::IniFormat);

    switch (currentThermostat) {
    case  1: changeWidgets(LABEL_01, "trend_T1.csv", home_ini.value("T1/name").toString(), "PLC_T1_temperature", "PLC_T1_temperature_bis", "PLC_T1_temperature_ext", "PLC_T1_humidity", "PLC_T1_humidity_bis", "PLC_T1_humidity_ext", PLC_T1_max_request_W, "PLC_T1_requested_W", "PLC_EP_T1_assigned_W", PLC_T1_daily_heating_s, PLC_T1_monthly_heating_s, PLC_T1_temperature_setpoint, PLC_T1_temperature_setpoint_nt, PLC_T1_enabled_sensors, PLC_Iam_T1, PLC_T1_isOK, PLC_T1_heating_status, PLC_T1_heating_timer, PLC_T1_heating, COLOR_01); break;
    case  2: changeWidgets(LABEL_02, "trend_T2.csv", home_ini.value("T2/name").toString(), "PLC_T2_temperature", "PLC_T2_temperature_bis", "PLC_T2_temperature_ext", "PLC_T2_humidity", "PLC_T2_humidity_bis", "PLC_T2_humidity_ext", PLC_T2_max_request_W, "PLC_T2_requested_W", "PLC_EP_T2_assigned_W", PLC_T2_daily_heating_s, PLC_T2_monthly_heating_s, PLC_T2_temperature_setpoint, PLC_T2_temperature_setpoint_nt, PLC_T2_enabled_sensors, PLC_Iam_T2, PLC_T2_isOK, PLC_T2_heating_status, PLC_T2_heating_timer, PLC_T2_heating, COLOR_02); break;
    case  3: changeWidgets(LABEL_03, "trend_T3.csv", home_ini.value("T3/name").toString(), "PLC_T3_temperature", "PLC_T3_temperature_bis", "PLC_T3_temperature_ext", "PLC_T3_humidity", "PLC_T3_humidity_bis", "PLC_T3_humidity_ext", PLC_T3_max_request_W, "PLC_T3_requested_W", "PLC_EP_T3_assigned_W", PLC_T3_daily_heating_s, PLC_T3_monthly_heating_s, PLC_T3_temperature_setpoint, PLC_T3_temperature_setpoint_nt, PLC_T3_enabled_sensors, PLC_Iam_T3, PLC_T3_isOK, PLC_T3_heating_status, PLC_T3_heating_timer, PLC_T3_heating, COLOR_03); break;
    case  4:
        if (PLC_T4_control_type == ControlType_6)
             changeWidgets(LABEL_04, "trend_T4puffer.csv", home_ini.value("T4/name").toString(), "PLC_T4_temperature", "PLC_T4_temperature_bis", "PLC_T4_temperature_ext", "PLC_T4_humidity", "PLC_T4_humidity_bis", "PLC_T4_humidity_ext", PLC_T4_max_request_W, "PLC_T4_requested_W", "PLC_EP_T4_assigned_W", PLC_T4_daily_heating_s, PLC_T4_monthly_heating_s, PLC_T4_temperature_setpoint, PLC_T4_temperature_setpoint_nt, PLC_T4_enabled_sensors, PLC_Iam_T4, PLC_T4_isOK, PLC_T4_heating_status, PLC_T4_heating_timer, PLC_T4_heating, COLOR_04);
        else
             changeWidgets(LABEL_04, "trend_T4.csv", home_ini.value("T4/name").toString(), "PLC_T4_temperature", "PLC_T4_temperature_bis", "PLC_T4_temperature_ext", "PLC_T4_humidity", "PLC_T4_humidity_bis", "PLC_T4_humidity_ext", PLC_T4_max_request_W, "PLC_T4_requested_W", "PLC_EP_T4_assigned_W", PLC_T4_daily_heating_s, PLC_T4_monthly_heating_s, PLC_T4_temperature_setpoint, PLC_T4_temperature_setpoint_nt, PLC_T4_enabled_sensors, PLC_Iam_T4, PLC_T4_isOK, PLC_T4_heating_status, PLC_T4_heating_timer, PLC_T4_heating, COLOR_04);
        break;
    case  5: changeWidgets(LABEL_05, "trend_T5.csv", home_ini.value("T5/name").toString(), "PLC_T5_temperature", "PLC_T5_temperature_bis", "PLC_T5_temperature_ext", "PLC_T5_humidity", "PLC_T5_humidity_bis", "PLC_T5_humidity_ext", PLC_T5_max_request_W, "PLC_T5_requested_W", "PLC_EP_T5_assigned_W", PLC_T5_daily_heating_s, PLC_T5_monthly_heating_s, PLC_T5_temperature_setpoint, PLC_T5_temperature_setpoint_nt, PLC_T5_enabled_sensors, PLC_Iam_T5, PLC_T5_isOK, PLC_T5_heating_status, PLC_T5_heating_timer, PLC_T5_heating, COLOR_05); break;
    case  6: changeWidgets(LABEL_06, "trend_T6.csv", home_ini.value("T6/name").toString(), "PLC_T6_temperature", "PLC_T6_temperature_bis", "PLC_T6_temperature_ext", "PLC_T6_humidity", "PLC_T6_humidity_bis", "PLC_T6_humidity_ext", PLC_T6_max_request_W, "PLC_T6_requested_W", "PLC_EP_T6_assigned_W", PLC_T6_daily_heating_s, PLC_T6_monthly_heating_s, PLC_T6_temperature_setpoint, PLC_T6_temperature_setpoint_nt, PLC_T6_enabled_sensors, PLC_Iam_T6, PLC_T6_isOK, PLC_T6_heating_status, PLC_T6_heating_timer, PLC_T6_heating, COLOR_06); break;
    default: changeWidgets("??"    , NULL,           ""                                  , ""                  , ""                      , ""                      , ""               , ""                   , ""                   , 0                   , ""                  , ""                    , 0                     , 0                       , 0                          , 0                             , 0                     , 0         , 0          , 0                    , 0                   , 0             , COLOR_01);
    }
    // updateWidgets() called by changeWidgets()
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

void page101a::changeWidgets(const QString t, const char *trend, const QString title, const QString T, const QString Tbis, const QString Text,
                             const QString Thumidity, const QString Thumidity_bis, const QString Thumidity_ext,
                             int Tn_max_request_W, const QString Tn_requested_W, const QString EP_Tn_assigned_W,
                             int daily_heating_s, int monthly_heating_s,
                             int Tn_temperature_setpoint, int Tn_temperature_setpoint_nt,
                             int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color)
{
    QString offStyleSheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());

    // header
    if (PLC_Tn_count >= 2) {
        ui->headerPanel->changeWidgets(trend, TH_PIXMAP, "page100", QString("page101a: Tn " + title).toLatin1().data());
    } else {
        currentThermostat = 1;
        ui->headerPanel->changeWidgets(trend, TH_PIXMAP, NULL, QString("page101a: Tn " + title).toLatin1().data());
    }

    if (enabled_sensors < 0) {
        // (T,H)
        fontSize_t  = modulor->normalFont_px();
        fontSize_xx = modulor->tinyFont_px();
    } else {
        // (T)
        fontSize_t  = modulor->largeFont_px();
        fontSize_xx = modulor->normalFont_px();
    }

    // left margin
    ui->label_heating_status->setVisible(abs(enabled_sensors) > 0);
    ui->label_heating_status->setStyleSheet(                   COLOR_SS(color) +                    FONT_SS_B(fontSize_t));
    ui->label_heating_status->setMaximumWidth(modulor->tripleSize_px());

    ui->label_heating_timer->setVisible(abs(enabled_sensors) > 0);
    ui->label_heating_timer->setStyleSheet(                    COLOR_SS(color) +                    FONT_SS_B(fontSize_xx));
    ui->label_heating_timer->setMaximumWidth(modulor->tripleSize_px());

    modulor->scaleTripleButton(ui->atcmButton_prev);

    // right margin
    ui->label_Tn->setText(t);
    ui->label_Tn->setStyleSheet(                               COLOR_SS(color) +                    FONT_SS_B(modulor->LARGEFont_px()));
    ui->label_Tn->setMaximumWidth(modulor->tripleSize_px());

    // footer
    ui->atcmButton_down->setEnabled(enabled_sensors < 0 and Iam_Tn);

    // center grid
    ui->atcmLabel_Tn_temperature->setVisible(true); // (abs(enabled_sensors) >= 1);
    ui->atcmLabel_Tn_temperature->setVariable(T);
    ui->atcmLabel_Tn_temperature->setStyleSheet(                                                    FONT_SS_B(fontSize_t));
    ui->atcmLabel_Tn_temperature->setFontColor(color);
    ui->atcmLabel_Tn_temperature->setBorderColor(color);

    ui->label_Tn_temperature_setpoint->setStyleSheet(          COLOR_SS(color) +                    FONT_SS_B(fontSize_xx));
    //ui->label_Tn_temperature_setpoint->setMaximumWidth(modulor->tripleSize_px());

    ui->label_Tn_temperature_setpoint_nt->setStyleSheet(       COLOR_SS(color) +                    FONT_SS_B(fontSize_xx));
    //ui->label_Tn_temperature_setpoint_nt->setMaximumWidth(modulor->tripleSize_px());

    ui->atcmLabel_Tn_humidity->setVisible(enabled_sensors <= -1);
    ui->atcmLabel_Tn_humidity->setVariable(Thumidity);
    ui->atcmLabel_Tn_humidity->setStyleSheet(                                                       FONT_SS_B(fontSize_t));
    ui->atcmLabel_Tn_humidity->setFontColor(color);
    ui->atcmLabel_Tn_humidity->setBorderColor(color);

    ui->atcmLabel_Tn_temperature_bis->setVisible(abs(enabled_sensors) >= 2);
    ui->atcmLabel_Tn_temperature_bis->setVariable(Tbis);
    ui->atcmLabel_Tn_temperature_bis->setStyleSheet(                                                FONT_SS_B(fontSize_t));
    ui->atcmLabel_Tn_temperature_bis->setFontColor(color);
    ui->atcmLabel_Tn_temperature_bis->setBorderColor(color);

    ui->atcmLabel_Tn_humidity_bis->setVisible(enabled_sensors <= -2);
    ui->atcmLabel_Tn_humidity_bis->setVariable(Thumidity_bis);
    ui->atcmLabel_Tn_humidity_bis->setStyleSheet(                                                   FONT_SS_B(fontSize_t));
    ui->atcmLabel_Tn_humidity_bis->setFontColor(color);
    ui->atcmLabel_Tn_humidity_bis->setBorderColor(color);

    ui->atcmLabel_Tn_temperature_ext->setVisible(abs(enabled_sensors) >= 3);
    ui->atcmLabel_Tn_temperature_ext->setVariable(Text);
    ui->atcmLabel_Tn_temperature_ext->setStyleSheet(                                                FONT_SS_B(fontSize_t));
    ui->atcmLabel_Tn_temperature_ext->setFontColor(color);

    ui->atcmLabel_Tn_humidity_ext->setVisible(enabled_sensors <= -3);
    ui->atcmLabel_Tn_humidity_ext->setVariable(Thumidity_ext);
    ui->atcmLabel_Tn_humidity_ext->setStyleSheet(                                                   FONT_SS_B(fontSize_t));
    ui->atcmLabel_Tn_humidity_ext->setFontColor(color);

    ui->label_daily->setStyleSheet(                            COLOR_SS(color) +                    FONT_SS_B(fontSize_xx));
    ui->label_monthly->setStyleSheet(                          COLOR_SS(color) +                    FONT_SS_B(fontSize_xx));

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

void page101a::updateWidgets(int daily_heating_s, int monthly_heating_s, int Tn_temperature_setpoint, int Tn_temperature_setpoint_nt,
                             int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color)
{
    // header
    ui->headerPanel->updateWidgets();

    ui->label_Tn_temperature_setpoint->setText(QString("%1 %2%3")
                                               .arg(LABEL_TRIANGLE).arg(Tn_temperature_setpoint/10.0, 3, 'f', 1).arg(LABEL_CELSIUS));
    ui->label_Tn_temperature_setpoint_nt->setText(QString("%1 %2%3")
                                               .arg(LABEL_TRIANGLE).arg(Tn_temperature_setpoint_nt/10.0, 3, 'f', 1).arg(LABEL_CELSIUS));

    // left margin
    if (Iam_Tn or Tn_isOK) {
        ui->label_heating_status->setVisible(abs(enabled_sensors) >= 1);
        ui->label_heating_timer->setVisible(abs(enabled_sensors) >= 1);
        if (abs(enabled_sensors) >= 1) {
            ui->label_heating_status->setText(heating_name(Tn_heating_status));
            if (Tn_heating)
                ui->label_heating_status->setStyleSheet(BG_COLOR_SS(color) + COLOR_SS(black) + FONT_SS_B(fontSize_xx));
            else
                ui->label_heating_status->setStyleSheet(BG_COLOR_SS(black) + COLOR_SS(color) + FONT_SS_B(fontSize_xx));
            if (Tn_heating_status > HEATING_AUTO) {
                ui->label_heating_timer->setText(QTime().addSecs(Tn_heating_timer).toString("HH:mm\nss"));
            } else {
                ui->label_heating_timer->setText("");
            }
        }
    } else {
        ui->label_heating_status->setText(heating_name(-1)); // LABEL_MISSING);
        ui->label_heating_status->setStyleSheet(BG_COLOR_SS(black) + COLOR_SS(color) + FONT_SS_B(fontSize_xx));
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
