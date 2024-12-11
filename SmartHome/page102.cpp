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
#include "page102.h"
#include "ui_page102.h"
#include "crosstable.h"

#include "automation.h"

page102::page102(QWidget *parent) :
    page(parent),
    ui(new Ui::page102)
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
}

void page102::changeWidgets(const QString t, const QString T, const QString Tbis, const QString Text, const QString Tsp,
                            int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color)
{
    QString offStylesheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());

    // header
    ui->label_Tn->setText(t);
    ui->label_Tn->setStyleSheet(offStylesheet);

    // left margin
    ui->label_heating_status->setVisible(abs(enabled_sensors) > 0);
    ui->label_heating_status->setStyleSheet(offStylesheet);
    ui->label_heating_timer->setVisible(abs(enabled_sensors) > 0);
    ui->label_heating_timer->setStyleSheet(offStylesheet);

    // right margin
    ui->atcmButton_next->setFontColor(color);

    // footer
    ui->atcmLabel_T->setVisible(abs(enabled_sensors) >= 1);
    ui->atcmLabel_Tsp->setVisible(abs(enabled_sensors) >= 1);
    if (abs(enabled_sensors) >= 1) {
        ui->atcmLabel_T->setVariable(T);
        ui->atcmLabel_Tsp->setVariable(Tsp);
        ui->atcmLabel_Tsp->setFontColor(color);
    }
    ui->atcmLabel_Tbis->setVisible(abs(enabled_sensors) >= 2);
    if (abs(enabled_sensors) >= 2) {
        ui->atcmLabel_Tbis->setVariable(Tbis);
    }
    ui->atcmLabel_Text->setVisible(abs(enabled_sensors) >= 3);
    if (abs(enabled_sensors) >= 3) {
        ui->atcmLabel_Text->setVariable(Text);
        ui->atcmLabel_Text->setFontColor(color);
        ui->atcmLabel_Text->setSuffix(" " + LABEL_CELSIUS);
    }

    // center
    if (abs(enabled_sensors) >= 1) {
        ui->atcmGraph->setY1Variable(T);
    } else {
        ui->atcmGraph->setY1Variable("");
    }
    if (abs(enabled_sensors) >= 2) {
        ui->atcmGraph->setY2Variable(Tbis);
    } else {
        ui->atcmGraph->setY2Variable("");
    }
    ui->atcmGraph->setY1Label(QString::fromUtf8("℃"));
    ui->atcmGraph->setY2Label(QString::fromUtf8("℃"));
    ui->atcmGraph->setToolTip("");
    ui->atcmGraph->setStyleSheet(offStylesheet);

    ui->atcmGraph->setY2Min("16.0");
    ui->atcmGraph->setY2Max("24.0");
    ui->atcmGraph->setY2Step(1.0);

    updateWidgets(enabled_sensors, Iam_Tn, Tn_isOK, Tn_heating_status, Tn_heating_timer, Tn_heating, color);
}

void page102::reload()
{
    changeHeader(ui->pushButton_time, ui->atcmButton_home);
    ui->atcmGraph->RunStop();
    resetPLC_timeOffset();
    switch (currentThermostat) {
    case  1: changeWidgets(LABEL_01, "PLC_T1_temperature", "PLC_T1_temperature_bis", "PLC_T1_temperature_ext", "PLC_T1_temperature_setpoint", PLC_T1_enabled_sensors, PLC_Iam_T1, PLC_T1_isOK, PLC_T1_heating_status, PLC_T1_heating_timer, PLC_T1_heating, COLOR_01); break;
    case  2: changeWidgets(LABEL_02, "PLC_T2_temperature", "PLC_T2_temperature_bis", "PLC_T2_temperature_ext", "PLC_T2_temperature_setpoint", PLC_T2_enabled_sensors, PLC_Iam_T2, PLC_T2_isOK, PLC_T2_heating_status, PLC_T2_heating_timer, PLC_T2_heating, COLOR_02); break;
    case  3: changeWidgets(LABEL_03, "PLC_T3_temperature", "PLC_T3_temperature_bis", "PLC_T3_temperature_ext", "PLC_T3_temperature_setpoint", PLC_T3_enabled_sensors, PLC_Iam_T3, PLC_T3_isOK, PLC_T3_heating_status, PLC_T3_heating_timer, PLC_T3_heating, COLOR_03); break;
    case  4: changeWidgets(LABEL_04, "PLC_T4_temperature", "PLC_T4_temperature_bis", "PLC_T4_temperature_ext", "PLC_T4_temperature_setpoint", PLC_T4_enabled_sensors, PLC_Iam_T4, PLC_T4_isOK, PLC_T4_heating_status, PLC_T4_heating_timer, PLC_T4_heating, COLOR_04); break;
    case  5: changeWidgets(LABEL_05, "PLC_T5_temperature", "PLC_T5_temperature_bis", "PLC_T5_temperature_ext", "PLC_T5_temperature_setpoint", PLC_T5_enabled_sensors, PLC_Iam_T5, PLC_T5_isOK, PLC_T5_heating_status, PLC_T5_heating_timer, PLC_T5_heating, COLOR_05); break;
    case  6: changeWidgets(LABEL_06, "PLC_T6_temperature", "PLC_T6_temperature_bis", "PLC_T6_temperature_ext", "PLC_T6_temperature_setpoint", PLC_T6_enabled_sensors, PLC_Iam_T6, PLC_T6_isOK, PLC_T6_heating_status, PLC_T6_heating_timer, PLC_T6_heating, COLOR_06); break;
    default: changeWidgets("??"    , ""                  , ""                      , ""                      , ""                           , 0                     , 0         , 0          , 0                    , 0                   , 0             , COLOR_01);
    }
    ui->atcmGraph->RunStop();
}

void page102::updateWidgets(int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color)
{
    QString offStylesheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());
    QString onStylesheet = QString("background-color: rgb(%1, %2, %3); color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());

    // header
    updateLedLabels(ui->label_EP, ui->label_BA, ui->label_green,
                    ui->label_T5, ui->label_T6, ui->label_red,
                    ui->label_T3, ui->label_T4, ui->label_yellow_1,
                    ui->label_T1, ui->label_T2, ui->label_yellow_2);
    ui->pushButton_time->setText(PLC_nighttime ? TIME_FMT_NIGHTTIME : TIME_FMT_DAYTIME);

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

    // center
}

void page102::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();

    switch (currentThermostat) {
    case  1: updateWidgets(PLC_T1_enabled_sensors, PLC_Iam_T1, PLC_T1_isOK, PLC_T1_heating_status, PLC_T1_heating_timer, PLC_T1_heating, COLOR_01); break;
    case  2: updateWidgets(PLC_T2_enabled_sensors, PLC_Iam_T2, PLC_T2_isOK, PLC_T2_heating_status, PLC_T2_heating_timer, PLC_T2_heating, COLOR_02); break;
    case  3: updateWidgets(PLC_T3_enabled_sensors, PLC_Iam_T3, PLC_T3_isOK, PLC_T3_heating_status, PLC_T3_heating_timer, PLC_T3_heating, COLOR_03); break;
    case  4: updateWidgets(PLC_T4_enabled_sensors, PLC_Iam_T4, PLC_T4_isOK, PLC_T4_heating_status, PLC_T4_heating_timer, PLC_T4_heating, COLOR_04); break;
    case  5: updateWidgets(PLC_T5_enabled_sensors, PLC_Iam_T5, PLC_T5_isOK, PLC_T5_heating_status, PLC_T5_heating_timer, PLC_T5_heating, COLOR_05); break;
    case  6: updateWidgets(PLC_T6_enabled_sensors, PLC_Iam_T6, PLC_T6_isOK, PLC_T6_heating_status, PLC_T6_heating_timer, PLC_T6_heating, COLOR_06); break;
    default: updateWidgets(0                     , 0         , 0          , 0                    , 0                   , 0             , COLOR_01);
    }
}

void page102::on_pushButton_trend_clicked()
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

void page102::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page102::~page102()
{
    delete ui;
}
