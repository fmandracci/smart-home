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
#include "page101c.h"
#include "ui_page101c.h"
#include "crosstable.h"

#include "automation.h"
#include <QTime>

page101c::page101c(QWidget *parent) :
    page(parent),
    ui(new Ui::page101c)
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
}

void page101c::changeWidgets(const QString t, const QString name,
                             int Tn_temperature, bool Tn_nightime, int Tn_temperature_setpoint, int Tn_temperature_setpoint_nt,
                             int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color)
{
    QString offStyleSheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());

    // header
    ui->label_Tn->setText(t);
    ui->label_Tn->setStyleSheet(offStyleSheet);
    ui->label_Tn_temperature->setStyleSheet(offStyleSheet);;

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
    updateWidgets(Tn_temperature, Tn_nightime, Tn_temperature_setpoint, Tn_temperature_setpoint_nt,
                  enabled_sensors, Iam_Tn, Tn_isOK, Tn_heating_status, Tn_heating_timer, Tn_heating, color);
}

void page101c::reload()
{
    QSettings hmi_ini("/local/root/hmi.ini", QSettings::IniFormat);

    if (PLC_Tn_count >= 2) {
        ui->atcmButton_up->setPageName("page100");
    } else {
        currentThermostat = 1;
        ui->atcmButton_up->setPageName("HOME");
    }
    switch (currentThermostat) {
    case  1: changeWidgets(LABEL_01, hmi_ini.value("T1/name").toString(), PLC_T1_temperature, PLC_T1_nighttime, PLC_T1_temperature_setpoint, PLC_T1_temperature_setpoint_nt, PLC_T1_enabled_sensors, PLC_Iam_T1, PLC_T1_isOK, PLC_T1_heating_status, PLC_T1_heating_timer, PLC_T1_heating, COLOR_01); break;
    case  2: changeWidgets(LABEL_02, hmi_ini.value("T2/name").toString(), PLC_T2_temperature, PLC_T2_nighttime, PLC_T2_temperature_setpoint, PLC_T2_temperature_setpoint_nt, PLC_T2_enabled_sensors, PLC_Iam_T2, PLC_T2_isOK, PLC_T2_heating_status, PLC_T2_heating_timer, PLC_T2_heating, COLOR_02); break;
    case  3: changeWidgets(LABEL_03, hmi_ini.value("T3/name").toString(), PLC_T3_temperature, PLC_T3_nighttime, PLC_T3_temperature_setpoint, PLC_T3_temperature_setpoint_nt, PLC_T3_enabled_sensors, PLC_Iam_T3, PLC_T3_isOK, PLC_T3_heating_status, PLC_T3_heating_timer, PLC_T3_heating, COLOR_03); break;
    case  4: changeWidgets(LABEL_04, hmi_ini.value("T4/name").toString(), PLC_T4_temperature, PLC_T4_nighttime, PLC_T4_temperature_setpoint, PLC_T4_temperature_setpoint_nt, PLC_T4_enabled_sensors, PLC_Iam_T4, PLC_T4_isOK, PLC_T4_heating_status, PLC_T4_heating_timer, PLC_T4_heating, COLOR_04); break;
    case  5: changeWidgets(LABEL_05, hmi_ini.value("T5/name").toString(), PLC_T5_temperature, PLC_T5_nighttime, PLC_T5_temperature_setpoint, PLC_T5_temperature_setpoint_nt, PLC_T5_enabled_sensors, PLC_Iam_T5, PLC_T5_isOK, PLC_T5_heating_status, PLC_T5_heating_timer, PLC_T5_heating, COLOR_05); break;
    case  6: changeWidgets(LABEL_06, hmi_ini.value("T6/name").toString(), PLC_T6_temperature, PLC_T6_nighttime, PLC_T6_temperature_setpoint, PLC_T6_temperature_setpoint_nt, PLC_T6_enabled_sensors, PLC_Iam_T6, PLC_T6_isOK, PLC_T6_heating_status, PLC_T6_heating_timer, PLC_T6_heating, COLOR_06); break;
    default: changeWidgets("??"    , ""                                 , 0                 , 0              , 0                          , 0                             , 0                     , 0         , 0          , 0                    , 0                   , 0             , COLOR_01);
    }
}

void page101c::updateWidgets(int Tn_temperature, bool Tn_nightime, int Tn_temperature_setpoint, int Tn_temperature_setpoint_nt,
                             int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color)
{
    QString offStylesheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());
    QString onStylesheet = QString("background-color: rgb(%1, %2, %3); color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());

    QString disabledBorderStylesheet = QString("color: rgb(64, 64, 64); background-color: rgb(0, 0, 0); border: 1px solid rgb(64, 64, 64);");
    QString inactiveBorderStylesheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0); border: 1px solid rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue());
    QString activeBorderStylesheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0); border: 3px solid rgb(255, 255, 255);").arg(color.red()).arg(color.green()).arg(color.blue());

    // header
    updateLedLabels(ui->label_EP, ui->label_BA, ui->label_green,
                    ui->label_T5, ui->label_T6, ui->label_red,
                    ui->label_T3, ui->label_T4, ui->label_yellow_1,
                    ui->label_T1, ui->label_T2, ui->label_yellow_2);
    ui->pushButton_time->setText(PLC_nighttime ? TIME_FMT_NIGHTTIME : TIME_FMT_DAYTIME);

    QString tStr = Tn_temperature > TemperatureError ? QString("%1").arg(Tn_temperature / 10.0, 3, 'f', 1) : LABEL_NULL_T;
    QString tspStr;

    if (Tn_nightime) {
        tspStr = QString("%1").arg(Tn_temperature_setpoint_nt / 10.0, 3, 'f', 1);
    } else {
        tspStr = QString("%1").arg(Tn_temperature_setpoint / 10.0, 3, 'f', 1);
    }
    ui->label_Tn_temperature->setText(QString("%1%2\n%3 %4%5")
                                         .arg(tStr).arg(LABEL_CELSIUS)
                                         .arg(LABEL_TRIANGLE).arg(tspStr).arg(LABEL_CELSIUS));

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
    ui->pushButton_off->setStyleSheet((Tn_heating_status == HEATING_OFF) ? activeBorderStylesheet : inactiveBorderStylesheet);
    ui->pushButton_ON->setStyleSheet((Tn_heating_status == HEATING_AUTO) ? activeBorderStylesheet : inactiveBorderStylesheet);

    ui->pushButton_ECO->setStyleSheet((Tn_heating_status == HEATING_ECONOMY) ? activeBorderStylesheet : inactiveBorderStylesheet);
    ui->pushButton_COMFORT->setStyleSheet((Tn_heating_status == HEATING_COMFORT) ? activeBorderStylesheet : inactiveBorderStylesheet);
    ui->pushButton_BOOST->setStyleSheet((Tn_heating_status == HEATING_BOOST) ? activeBorderStylesheet : inactiveBorderStylesheet);

    ui->pushButton_20m->setStyleSheet((Tn_heating_status > HEATING_AUTO) ? inactiveBorderStylesheet : disabledBorderStylesheet);
    ui->pushButton_20m->setEnabled(Tn_heating_status > HEATING_AUTO);
    ui->pushButton_40m->setStyleSheet((Tn_heating_status > HEATING_AUTO) ? inactiveBorderStylesheet : disabledBorderStylesheet);
    ui->pushButton_40m->setEnabled(Tn_heating_status > HEATING_AUTO);
    ui->pushButton_60m->setStyleSheet((Tn_heating_status > HEATING_AUTO) ? inactiveBorderStylesheet : disabledBorderStylesheet);
    ui->pushButton_60m->setEnabled(Tn_heating_status > HEATING_AUTO);

    ui->pushButton_2h->setStyleSheet((Tn_heating_status > HEATING_AUTO) ? inactiveBorderStylesheet : disabledBorderStylesheet);
    ui->pushButton_2h->setEnabled(Tn_heating_status > HEATING_AUTO);
    ui->pushButton_5h->setStyleSheet((Tn_heating_status > HEATING_AUTO) ? inactiveBorderStylesheet : disabledBorderStylesheet);
    ui->pushButton_5h->setEnabled(Tn_heating_status > HEATING_AUTO);
    ui->pushButton_8h->setStyleSheet((Tn_heating_status > HEATING_AUTO) ? inactiveBorderStylesheet : disabledBorderStylesheet);
    ui->pushButton_8h->setEnabled(Tn_heating_status > HEATING_AUTO);
}

void page101c::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();

    switch (currentThermostat) {
    case  1: updateWidgets(PLC_T1_temperature, PLC_T1_nighttime, PLC_T1_temperature_setpoint, PLC_T1_temperature_setpoint_nt, PLC_T1_enabled_sensors, PLC_Iam_T1, PLC_T1_isOK, PLC_T1_heating_status, PLC_T1_heating_timer, PLC_T1_heating, COLOR_01); break;
    case  2: updateWidgets(PLC_T2_temperature, PLC_T2_nighttime, PLC_T2_temperature_setpoint, PLC_T2_temperature_setpoint_nt, PLC_T2_enabled_sensors, PLC_Iam_T2, PLC_T2_isOK, PLC_T2_heating_status, PLC_T2_heating_timer, PLC_T2_heating, COLOR_02); break;
    case  3: updateWidgets(PLC_T3_temperature, PLC_T3_nighttime, PLC_T3_temperature_setpoint, PLC_T3_temperature_setpoint_nt, PLC_T3_enabled_sensors, PLC_Iam_T3, PLC_T3_isOK, PLC_T3_heating_status, PLC_T3_heating_timer, PLC_T3_heating, COLOR_03); break;
    case  4: updateWidgets(PLC_T4_temperature, PLC_T4_nighttime, PLC_T4_temperature_setpoint, PLC_T4_temperature_setpoint_nt, PLC_T4_enabled_sensors, PLC_Iam_T4, PLC_T4_isOK, PLC_T4_heating_status, PLC_T4_heating_timer, PLC_T4_heating, COLOR_04); break;
    case  5: updateWidgets(PLC_T5_temperature, PLC_T5_nighttime, PLC_T5_temperature_setpoint, PLC_T5_temperature_setpoint_nt, PLC_T5_enabled_sensors, PLC_Iam_T5, PLC_T5_isOK, PLC_T5_heating_status, PLC_T5_heating_timer, PLC_T5_heating, COLOR_05); break;
    case  6: updateWidgets(PLC_T6_temperature, PLC_T6_nighttime, PLC_T6_temperature_setpoint, PLC_T6_temperature_setpoint_nt, PLC_T6_enabled_sensors, PLC_Iam_T6, PLC_T6_isOK, PLC_T6_heating_status, PLC_T6_heating_timer, PLC_T6_heating, COLOR_06); break;
    default: updateWidgets(0                 , 0              , 0                          , 0                             , 0                     , 0         , 0          , 0                    , 0                   , 0             , COLOR_01);
    }
}

void page101c::changeStatus(int status)
{
    int default_timer = 20 * 60;

    beginWrite();
    {
        switch (currentThermostat) {
        case 1:
            if (PLC_Iam_T1) {
                addWrite_PLC_T1_heating_status(status);
                addWrite_SRV_T1_heating_status(status);
                if (PLC_T1_heating_timer == 0) {
                    addWrite_PLC_T1_heating_timer(default_timer);
                    addWrite_SRV_T1_heating_timer(default_timer);
                }
            } else {
                addWrite_TCP_T1_heating_status(status);
                if (PLC_T1_heating_timer == 0) {
                    addWrite_TCP_T1_heating_timer(default_timer);
                }
            }
            break;
        case 2:
            if (PLC_Iam_T2) {
                addWrite_PLC_T2_heating_status(status);
                addWrite_SRV_T2_heating_status(status);
                if (PLC_T2_heating_timer == 0) {
                    addWrite_PLC_T2_heating_timer(default_timer);
                    addWrite_SRV_T2_heating_timer(default_timer);
                }
            } else {
                addWrite_TCP_T2_heating_status(status);
                if (PLC_T2_heating_timer == 0) {
                    addWrite_TCP_T2_heating_timer(default_timer);
                }
            }
            break;
        case 3:
            if (PLC_Iam_T3) {
                addWrite_PLC_T3_heating_status(status);
                addWrite_SRV_T3_heating_status(status);
                if (PLC_T3_heating_timer == 0) {
                    addWrite_PLC_T3_heating_timer(default_timer);
                    addWrite_SRV_T3_heating_timer(default_timer);
                }
            } else {
                addWrite_TCP_T3_heating_status(status);
                if (PLC_T3_heating_timer == 0) {
                    addWrite_TCP_T3_heating_timer(default_timer);
                }
            }
            break;
        case 4:
            if (PLC_Iam_T4) {
                addWrite_PLC_T4_heating_status(status);
                addWrite_SRV_T4_heating_status(status);
                if (PLC_T4_heating_timer == 0) {
                    addWrite_PLC_T4_heating_timer(default_timer);
                    addWrite_SRV_T4_heating_timer(default_timer);
                }
            } else {
                addWrite_TCP_T4_heating_status(status);
                if (PLC_T4_heating_timer == 0) {
                    addWrite_TCP_T4_heating_timer(default_timer);
                }
            }
            break;
        case 5:
            if (PLC_Iam_T5) {
                addWrite_PLC_T5_heating_status(status);
                addWrite_SRV_T5_heating_status(status);
                if (PLC_T5_heating_timer == 0) {
                    addWrite_PLC_T5_heating_timer(default_timer);
                    addWrite_SRV_T5_heating_timer(default_timer);
                }
            } else {
                addWrite_TCP_T5_heating_status(status);
                if (PLC_T5_heating_timer == 0) {
                    addWrite_TCP_T5_heating_timer(default_timer);
                }
            }
            break;
        case 6:
            if (PLC_Iam_T6) {
                addWrite_PLC_T6_heating_status(status);
                addWrite_SRV_T6_heating_status(status);
                if (PLC_T6_heating_timer == 0) {
                    addWrite_PLC_T6_heating_timer(default_timer);
                    addWrite_SRV_T6_heating_timer(default_timer);
                }
            } else {
                addWrite_TCP_T6_heating_status(status);
                if (PLC_T6_heating_timer == 0) {
                    addWrite_TCP_T6_heating_timer(default_timer);
                }
            }
            break;
        default:
            ;
        }
    }
    endWrite();
}

void page101c::changeTimer(int timer)
{
    beginWrite();
    {
        switch (currentThermostat) {
        case 1:
            if (PLC_Iam_T1) {
                addWrite_PLC_T1_heating_timer(timer);
                addWrite_SRV_T1_heating_timer(timer);
            } else {
                addWrite_TCP_T1_heating_timer(timer);
            }
            break;
        case 2:
            if (PLC_Iam_T2) {
                addWrite_PLC_T2_heating_timer(timer);
                addWrite_SRV_T2_heating_timer(timer);
            } else {
                addWrite_TCP_T2_heating_timer(timer);
            }
            break;
        case 3:
            if (PLC_Iam_T3) {
                addWrite_PLC_T3_heating_timer(timer);
                addWrite_SRV_T3_heating_timer(timer);
            } else {
                addWrite_TCP_T3_heating_timer(timer);
            }
            break;
        case 4:
            if (PLC_Iam_T4) {
                addWrite_PLC_T4_heating_timer(timer);
                addWrite_SRV_T4_heating_timer(timer);
            } else {
                addWrite_TCP_T4_heating_timer(timer);
            }
            break;
        case 5:
            if (PLC_Iam_T5) {
                addWrite_PLC_T5_heating_timer(timer);
                addWrite_SRV_T5_heating_timer(timer);
            } else {
                addWrite_TCP_T5_heating_timer(timer);
            }
            break;
        case 6:
            if (PLC_Iam_T6) {
                addWrite_PLC_T6_heating_timer(timer);
                addWrite_SRV_T6_heating_timer(timer);
            } else {
                addWrite_TCP_T6_heating_timer(timer);
            }
            break;
        default:
            ;
        }
    }
    endWrite();
}

void page101c::on_pushButton_20m_clicked() { ui->pushButton_20m->setStyleSheet("color: rgb(255,255,255); background-color: rgb(0,0,0);"); changeTimer( 20 * 60); }
void page101c::on_pushButton_40m_clicked() { ui->pushButton_40m->setStyleSheet("color: rgb(255,255,255); background-color: rgb(0,0,0);"); changeTimer( 40 * 60); }
void page101c::on_pushButton_60m_clicked() { ui->pushButton_60m->setStyleSheet("color: rgb(255,255,255); background-color: rgb(0,0,0);"); changeTimer( 60 * 60); }
void page101c::on_pushButton_2h_clicked()  {  ui->pushButton_2h->setStyleSheet("color: rgb(255,255,255); background-color: rgb(0,0,0);"); changeTimer(120 * 60); }
void page101c::on_pushButton_5h_clicked()  {  ui->pushButton_5h->setStyleSheet("color: rgb(255,255,255); background-color: rgb(0,0,0);"); changeTimer(300 * 60); }
void page101c::on_pushButton_8h_clicked()  {  ui->pushButton_8h->setStyleSheet("color: rgb(255,255,255); background-color: rgb(0,0,0);"); changeTimer(480 * 60); }

void page101c::on_pushButton_plot_clicked()
{
    goto_page("page102", true);
}

void page101c::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page101c::~page101c()
{
    delete ui;
}

