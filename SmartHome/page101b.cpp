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
#include "page101b.h"
#include "ui_page101b.h"
#include "crosstable.h"

#include "automation.h"
#include <QTime>

page101b::page101b(QWidget *parent) :
    page(parent),
    ui(new Ui::page101b),
    deltaT(5), //  0.5 °C
    deltaH(100) // 10.0 %
{
    ui->setupUi(this);
    TRANSLATE_FONT_SIZE(this);
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page101b::reload()
{
    QSettings home_ini(HOME_INI_FILE, QSettings::IniFormat);

    switch (currentThermostat) {
    case  1: changeWidgets(PLC_T1_sunrise, PLC_T1_sunset, LABEL_01, "trend_T1.csv", home_ini.value("T1/name").toString(), "PLC_T1_temperature_setpoint", "PLC_T1_temperature_setpoint_nt", "PLC_T1_humidity_setpoint", "PLC_T1_humidity_setpoint_nt", PLC_T1_temperature, PLC_T1_temperature_bis, PLC_T1_enabled_sensors, PLC_Iam_T1, PLC_T1_isOK, PLC_T1_heating_status, PLC_T1_heating_timer, PLC_T1_heating, COLOR_01); break;
    case  2: changeWidgets(PLC_T2_sunrise, PLC_T2_sunset, LABEL_02, "trend_T2.csv", home_ini.value("T2/name").toString(), "PLC_T2_temperature_setpoint", "PLC_T2_temperature_setpoint_nt", "PLC_T2_humidity_setpoint", "PLC_T2_humidity_setpoint_nt", PLC_T2_temperature, PLC_T2_temperature_bis, PLC_T2_enabled_sensors, PLC_Iam_T2, PLC_T2_isOK, PLC_T2_heating_status, PLC_T2_heating_timer, PLC_T2_heating, COLOR_02); break;
    case  3: changeWidgets(PLC_T3_sunrise, PLC_T3_sunset, LABEL_03, "trend_T3.csv", home_ini.value("T3/name").toString(), "PLC_T3_temperature_setpoint", "PLC_T3_temperature_setpoint_nt", "PLC_T3_humidity_setpoint", "PLC_T3_humidity_setpoint_nt", PLC_T3_temperature, PLC_T3_temperature_bis, PLC_T3_enabled_sensors, PLC_Iam_T3, PLC_T3_isOK, PLC_T3_heating_status, PLC_T3_heating_timer, PLC_T3_heating, COLOR_03); break;
    case  4:
        if (PLC_T4_control_type == ControlType_6)
             changeWidgets(PLC_T4_sunrise, PLC_T4_sunset, LABEL_04, "trend_T4puffer.csv", home_ini.value("T4/name").toString(), "PLC_T4_temperature_setpoint", "PLC_T4_temperature_setpoint_nt", "PLC_T4_humidity_setpoint", "PLC_T4_humidity_setpoint_nt", PLC_T4_temperature, PLC_T4_temperature_bis, PLC_T4_enabled_sensors, PLC_Iam_T4, PLC_T4_isOK, PLC_T4_heating_status, PLC_T4_heating_timer, PLC_T4_heating, COLOR_04);
        else
             changeWidgets(PLC_T4_sunrise, PLC_T4_sunset, LABEL_04, "trend_T4.csv", home_ini.value("T4/name").toString(), "PLC_T4_temperature_setpoint", "PLC_T4_temperature_setpoint_nt", "PLC_T4_humidity_setpoint", "PLC_T4_humidity_setpoint_nt", PLC_T4_temperature, PLC_T4_temperature_bis, PLC_T4_enabled_sensors, PLC_Iam_T4, PLC_T4_isOK, PLC_T4_heating_status, PLC_T4_heating_timer, PLC_T4_heating, COLOR_04);
        break;
    case  5: changeWidgets(PLC_T5_sunrise, PLC_T5_sunset, LABEL_05, "trend_T5.csv", home_ini.value("T5/name").toString(), "PLC_T5_temperature_setpoint", "PLC_T5_temperature_setpoint_nt", "PLC_T5_humidity_setpoint", "PLC_T5_humidity_setpoint_nt", PLC_T5_temperature, PLC_T5_temperature_bis, PLC_T5_enabled_sensors, PLC_Iam_T5, PLC_T5_isOK, PLC_T5_heating_status, PLC_T5_heating_timer, PLC_T5_heating, COLOR_05); break;
    case  6: changeWidgets(PLC_T6_sunrise, PLC_T6_sunset, LABEL_06, "trend_T6.csv", home_ini.value("T6/name").toString(), "PLC_T6_temperature_setpoint", "PLC_T6_temperature_setpoint_nt", "PLC_T6_humidity_setpoint", "PLC_T6_humidity_setpoint_nt", PLC_T6_temperature, PLC_T6_temperature_bis, PLC_T6_enabled_sensors, PLC_Iam_T6, PLC_T6_isOK, PLC_T6_heating_status, PLC_T6_heating_timer, PLC_T6_heating, COLOR_06); break;
    default: changeWidgets(0             , 0            , "??"    , NULL          , ""                                  , ""                           , ""                              , ""                        , ""                           , 0                 , 0                     , 0                     , 0         , 0          , 0                    , 0                   , 0             , COLOR_01);
    }
    // updateWidgets() called by changeWidgets()
}

void page101b::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();

    switch (currentThermostat) {
    case  1: updateWidgets(PLC_T1_sunrise, PLC_T1_sunset, LABEL_01, PLC_T1_temperature, PLC_T1_temperature_bis, PLC_T1_enabled_sensors, PLC_Iam_T1, PLC_T1_isOK, PLC_T1_heating_status, PLC_T1_heating_timer, PLC_T1_heating, COLOR_01); break;
    case  2: updateWidgets(PLC_T2_sunrise, PLC_T2_sunset, LABEL_02, PLC_T2_temperature, PLC_T2_temperature_bis, PLC_T2_enabled_sensors, PLC_Iam_T2, PLC_T2_isOK, PLC_T2_heating_status, PLC_T2_heating_timer, PLC_T2_heating, COLOR_02); break;
    case  3: updateWidgets(PLC_T3_sunrise, PLC_T3_sunset, LABEL_03, PLC_T3_temperature, PLC_T3_temperature_bis, PLC_T3_enabled_sensors, PLC_Iam_T3, PLC_T3_isOK, PLC_T3_heating_status, PLC_T3_heating_timer, PLC_T3_heating, COLOR_03); break;
    case  4: updateWidgets(PLC_T4_sunrise, PLC_T4_sunset, LABEL_04, PLC_T4_temperature, PLC_T4_temperature_bis, PLC_T4_enabled_sensors, PLC_Iam_T4, PLC_T4_isOK, PLC_T4_heating_status, PLC_T4_heating_timer, PLC_T4_heating, COLOR_04); break;
    case  5: updateWidgets(PLC_T5_sunrise, PLC_T5_sunset, LABEL_05, PLC_T5_temperature, PLC_T5_temperature_bis, PLC_T5_enabled_sensors, PLC_Iam_T5, PLC_T5_isOK, PLC_T5_heating_status, PLC_T5_heating_timer, PLC_T5_heating, COLOR_05); break;
    case  6: updateWidgets(PLC_T6_sunrise, PLC_T6_sunset, LABEL_06, PLC_T6_temperature, PLC_T6_temperature_bis, PLC_T6_enabled_sensors, PLC_Iam_T6, PLC_T6_isOK, PLC_T6_heating_status, PLC_T6_heating_timer, PLC_T6_heating, COLOR_06); break;
    default: updateWidgets(0             , 0            , "??"    , 0                 , 0                     , 0                     , 0         , 0          , 0                    , 0                   , 0             , COLOR_01);
    }
}

void page101b::changeWidgets(int sunrise, int sunset,
                             const QString Tlabel, const char *trend, const QString title,
                             const QString Tsp, const QString Tsp_nt,
                             const QString Hsp, const QString Hsp_nt,
                             int Tn_temperature, int Tn_temperature_bis,
                             int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color)
{
    const QColor gray(64, 64, 64);
    const QColor white(255, 255, 255);
    const QColor blue(0, 0, 127);
    const QColor red(127, 0, 0);

    // header
    if (PLC_Tn_count >= 2) {
        ui->headerPanel->changeWidgets(trend, TH_PIXMAP, "page100", QString("page101b: Tn " + title).toLatin1().data());
    } else {
        currentThermostat = 1;
        ui->headerPanel->changeWidgets(trend, TH_PIXMAP, NULL, QString("page101b: Tn " + title).toLatin1().data());
    }

    int big_size_px = modulor->bodyHeight_px() / ((enabled_sensors < 0) ? 6 : 4) * 5 / 10; // ①;
    int medium_size_px = modulor->titleFont_px();
    int small_size_px = modulor->smallFont_px();
    int tiny_size_px = modulor->tinyFont_px();

    ui->label_Tn_temperature->setStyleSheet(COLOR_SS(color));

    // left margin
    ui->label_heating_status->setVisible(abs(enabled_sensors) > 0);
    ui->label_heating_status->setStyleSheet(                   COLOR_SS(color) +                    FONT_SS_B(medium_size_px));
    ui->label_heating_status->setMaximumWidth(modulor->ledsWidth_px());

    ui->label_heating_timer->setVisible(abs(enabled_sensors) > 0);
    ui->label_heating_timer->setStyleSheet(                    COLOR_SS(color) +                    FONT_SS_B(small_size_px));
    ui->label_heating_timer->setMaximumWidth(modulor->ledsWidth_px());

    ui->atcmButton_set_T_everywhere->setFontColor(color);

    // right margin
    ui->label_Tn->setText(Tlabel);
    ui->label_Tn->setStyleSheet(COLOR_SS(color) + FONT_SS_B(big_size_px));
    ui->label_Tn->setMaximumWidth(modulor->ledsWidth_px());

    // ui->atcmButton_next->setFontColor(color);
    ui->atcmButton_next->setMaximumWidth(modulor->ledsWidth_px());

    // footer
    ui->atcmButton_down->setEnabled(enabled_sensors < 0 and Iam_Tn);

    // center grid
    ui->pushButton_sunrise->setStyleSheet(                     COLOR_SS(color) + BORDER_SS(color) + FONT_SS_B(big_size_px));
    ui->pushButton_sunrise->setEnabled(Iam_Tn);

    ui->atcmButton_set_T_everywhere->setStyleSheet(            COLOR_SS(color) +                    FONT_SS_B(tiny_size_px));

    ui->pushButton_sunset->setStyleSheet(                      COLOR_SS(color) + BORDER_SS(color) + FONT_SS_B(big_size_px));
    ui->pushButton_sunset->setEnabled(Iam_Tn);

    ui->atcmLabel_Tn_temperature_setpoint->setVariable(Tsp);
    ui->atcmLabel_Tn_temperature_setpoint->setStyleSheet(      COLOR_SS(color) +                    FONT_SS_B(big_size_px));
    ui->label_Tn_temperature->setStyleSheet(                   COLOR_SS(color) +                    FONT_SS_B(small_size_px));
    ui->atcmLabel_Tn_temperature_setpoint_nt->setVariable(Tsp_nt);
    ui->atcmLabel_Tn_temperature_setpoint_nt->setStyleSheet(   COLOR_SS(color) +                    FONT_SS_B(big_size_px));

    ui->pushButton_Tdown->setStyleSheet(   BG_COLOR_SS(blue) + COLOR_SS(white) + BORDER_SS(white) + FONT_SS_B(big_size_px));
    ui->pushButton_Tup->setStyleSheet(     BG_COLOR_SS(red)  + COLOR_SS(white) + BORDER_SS(white) + FONT_SS_B(big_size_px));

    ui->pushButton_Tdown_nt->setStyleSheet(BG_COLOR_SS(blue) + COLOR_SS(white) + BORDER_SS(white) + FONT_SS_B(big_size_px));
    ui->pushButton_Tup_nt->setStyleSheet(  BG_COLOR_SS(red)  + COLOR_SS(white) + BORDER_SS(white) + FONT_SS_B(big_size_px));

    ui->pushButton_T_0->setStyleSheet(     BG_COLOR_SS(gray) + COLOR_SS(white) + BORDER_SS(white) + FONT_SS_B(big_size_px));
    ui->pushButton_T_1->setStyleSheet(     BG_COLOR_SS(gray) + COLOR_SS(white) + BORDER_SS(white) + FONT_SS_B(big_size_px));
    ui->pushButton_T_2->setStyleSheet(     BG_COLOR_SS(gray) + COLOR_SS(white) + BORDER_SS(white) + FONT_SS_B(big_size_px));
    ui->pushButton_T_3->setStyleSheet(     BG_COLOR_SS(gray) + COLOR_SS(white) + BORDER_SS(white) + FONT_SS_B(big_size_px));
    ui->pushButton_T_4->setStyleSheet(     BG_COLOR_SS(gray) + COLOR_SS(white) + BORDER_SS(white) + FONT_SS_B(big_size_px));

    ui->atcmLabel_Tn_humidity_setpoint->setVariable(Hsp);
    ui->atcmLabel_Tn_humidity_setpoint->setStyleSheet(         COLOR_SS(color) + FONT_SS_B(big_size_px));
    ui->atcmLabel_Tn_humidity_setpoint_nt->setVariable(Hsp_nt);
    ui->atcmLabel_Tn_humidity_setpoint_nt->setStyleSheet(      COLOR_SS(color) + FONT_SS_B(big_size_px));

    updateWidgets(sunrise, sunset, Tlabel,
                  Tn_temperature, Tn_temperature_bis,
                  enabled_sensors, Iam_Tn, Tn_isOK, Tn_heating_status, Tn_heating_timer, Tn_heating, color);
}

void page101b::updateWidgets(int sunrise, int sunset, const QString Tlabel, int Tn_temperature, int Tn_temperature_bis,
                             int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color)
{
    QString offStylesheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());
    QString onStylesheet = QString("background-color: rgb(%1, %2, %3); color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());
    bool x;

    ui->headerPanel->updateWidgets();

    QString tStr = Tn_temperature > TemperatureError ? QString("%1").arg(Tn_temperature / 10.0, 3, 'f', 1) : LABEL_NULL_T;
    if (enabled_sensors >= 2) {
        QString tBisStr = Tn_temperature_bis > TemperatureError ? QString("%1").arg(Tn_temperature_bis / 10.0, 3, 'f', 1) : LABEL_NULL_T;

        ui->label_Tn_temperature->setText(QString("%1%2\n%3%4").arg(tStr).arg(LABEL_CELSIUS).arg(tBisStr).arg(LABEL_CELSIUS));
    } else {
        ui->label_Tn_temperature->setText(QString("%1%2").arg(tStr).arg(LABEL_CELSIUS));
    }

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
    x = ui->pushButton_sunrise->blockSignals(true);
    ui->pushButton_sunrise->setText((Iam_Tn ? "" : Tlabel) + QTime().addSecs(3600 * (sunrise / 100) + 60 * (sunrise % 100)).toString("HH:mm ") + LABEL_WSUNRAYS);
    ui->pushButton_sunrise->blockSignals(x);
    x = ui->pushButton_sunset->blockSignals(true);
    ui->pushButton_sunset->setText((Iam_Tn ? "" : Tlabel) + QTime().addSecs(3600 * (sunset / 100) + 60 * (sunset % 100)).toString("HH:mm ") + LABEL_MOON);
    ui->pushButton_sunset->blockSignals(x);

    ui->atcmLabel_Tn_temperature_setpoint->setVisible(abs(enabled_sensors) >= 1);
    ui->atcmLabel_Tn_temperature_setpoint_nt->setVisible(abs(enabled_sensors) >= 1);
    ui->pushButton_Tup->setVisible(abs(enabled_sensors) >= 1);
    ui->pushButton_Tup_nt->setVisible(abs(enabled_sensors) >= 1);
    ui->pushButton_Tdown->setVisible(abs(enabled_sensors) >= 1);
    ui->pushButton_Tdown_nt->setVisible(abs(enabled_sensors) >= 1);

    ui->atcmLabel_Tn_humidity_setpoint->setVisible(enabled_sensors <= -1);
    ui->atcmLabel_Tn_humidity_setpoint_nt->setVisible(enabled_sensors <= -1);
    ui->pushButton_Hup->setVisible(enabled_sensors <= -1);
    ui->pushButton_Hup_nt->setVisible(enabled_sensors <= -1);
    ui->pushButton_Hdown->setVisible(enabled_sensors <= -1);
    ui->pushButton_Hdown_nt->setVisible(enabled_sensors <= -1);
}

void page101b::on_pushButton_sunrise_clicked()
{
    numpad * numPad;
    int minValue = 0000;
    int maxValue = 2359;
    int value, hh, mm;

    value = PLC_sunrise;

    numPad = new numpad(&value, value, minValue, maxValue);
    numPad->showFullScreen();
    if (numPad->exec() == QDialog::Accepted) {
        hh = value / 100;
        mm = value % 100;
        if (hh > 23) {
            hh = 23;
        }
        if (mm > 59) {
            mm = 59;
        }
        value = hh * 100 + mm;
        doWrite_PLC_sunrise(value);
    }
}

void page101b::on_pushButton_sunset_clicked()
{
    numpad * numPad;
    int minValue = 0000;
    int maxValue = 2359;
    int value, hh, mm;

    value = PLC_sunset;

    numPad = new numpad(&value, value, minValue, maxValue);
    numPad->showFullScreen();
    if (numPad->exec() == QDialog::Accepted) {
        hh = value / 100;
        mm = value % 100;
        if (hh > 23) {
            hh = 23;
        }
        if (mm > 59) {
            mm = 59;
        }
        value = hh * 100 + mm;
        doWrite_PLC_sunset(value);
    }
}

int page101b::checkTvalue(int value, int diff)
{
    int retval = (value + diff) / deltaT * deltaT;

    if (retval < TemperatureSetPoint_min) {
        retval = TemperatureSetPoint_min;
    } else if (retval > TemperatureSetPoint_max) {
        retval = TemperatureSetPoint_max;
    }
    return retval;
}

int page101b::checkHvalue(int value, int diff)
{
    int retval = (value + diff) / deltaH * deltaH;

    if (retval < HumiditySetPoint_min) {
        retval = HumiditySetPoint_min;
    } else if (retval > HumiditySetPoint_max) {
        retval = HumiditySetPoint_max;
    }
    return retval;
}

void page101b::temperature_valueAbsolute(int value)
{
    beginWrite();
    {
        switch (currentThermostat) {
        case 1:
            if (PLC_Iam_T1) {
                addWrite_PLC_T1_temperature_setpoint(value);
                addWrite_PLC_T1_temperature_setpoint_nt(value);
                addWrite_SRV_T1_temperature_setpoint(value);
                addWrite_SRV_T1_temperature_setpoint_nt(value);
            } else {
                addWrite_TCP_T1_temperature_setpoint(value);
                addWrite_TCP_T1_temperature_setpoint_nt(value);
            }
            break;
        case 2:
            if (PLC_Iam_T2) {
                addWrite_PLC_T2_temperature_setpoint(value);
                addWrite_PLC_T2_temperature_setpoint_nt(value);
                addWrite_SRV_T2_temperature_setpoint(value);
                addWrite_SRV_T2_temperature_setpoint_nt(value);
            } else {
                addWrite_TCP_T2_temperature_setpoint(value);
                addWrite_TCP_T2_temperature_setpoint_nt(value);
            }
            break;
        case 3:
            if (PLC_Iam_T3) {
                addWrite_PLC_T3_temperature_setpoint(value);
                addWrite_PLC_T3_temperature_setpoint_nt(value);
                addWrite_SRV_T3_temperature_setpoint(value);
                addWrite_SRV_T3_temperature_setpoint_nt(value);
            } else {
                addWrite_TCP_T3_temperature_setpoint(value);
                addWrite_TCP_T3_temperature_setpoint_nt(value);
            }
            break;
        case 4:
            if (PLC_Iam_T4) {
                addWrite_PLC_T4_temperature_setpoint(value);
                addWrite_PLC_T4_temperature_setpoint_nt(value);
                addWrite_SRV_T4_temperature_setpoint(value);
                addWrite_SRV_T4_temperature_setpoint_nt(value);
            } else {
                addWrite_TCP_T4_temperature_setpoint(value);
                addWrite_TCP_T4_temperature_setpoint_nt(value);
            }
            break;
        case 5:
            if (PLC_Iam_T5) {
                addWrite_PLC_T5_temperature_setpoint(value);
                addWrite_PLC_T5_temperature_setpoint_nt(value);
                addWrite_SRV_T5_temperature_setpoint(value);
                addWrite_SRV_T5_temperature_setpoint_nt(value);
            } else {
                addWrite_TCP_T5_temperature_setpoint(value);
                addWrite_TCP_T5_temperature_setpoint_nt(value);
            }
            break;
        case 6:
            if (PLC_Iam_T6) {
                addWrite_PLC_T6_temperature_setpoint(value);
                addWrite_PLC_T6_temperature_setpoint_nt(value);
                addWrite_SRV_T6_temperature_setpoint(value);
                addWrite_SRV_T6_temperature_setpoint_nt(value);
            } else {
                addWrite_TCP_T6_temperature_setpoint(value);
                addWrite_TCP_T6_temperature_setpoint_nt(value);
            }
            break;
        default:
            ;
        }
    }
    endWrite();
}

void page101b::temperature_valueChanged(int diff)
{
    int value;

    beginWrite();
    {
        switch (currentThermostat) {
        case 1:
            value = checkTvalue(PLC_T1_temperature_setpoint, diff);
            if (PLC_Iam_T1) {
                addWrite_PLC_T1_temperature_setpoint(value);
                addWrite_SRV_T1_temperature_setpoint(value);
            } else {
                addWrite_TCP_T1_temperature_setpoint(value);
            }
            break;
        case 2:
            value = checkTvalue(PLC_T2_temperature_setpoint, diff);
            if (PLC_Iam_T2) {
                addWrite_PLC_T2_temperature_setpoint(value);
                addWrite_SRV_T2_temperature_setpoint(value);
            } else {
                addWrite_TCP_T2_temperature_setpoint(value);
            }
            break;
        case 3:
            value = checkTvalue(PLC_T3_temperature_setpoint, diff);
            if (PLC_Iam_T3) {
                addWrite_PLC_T3_temperature_setpoint(value);
                addWrite_SRV_T3_temperature_setpoint(value);
            } else {
                addWrite_TCP_T3_temperature_setpoint(value);
            }
            break;
        case 4:
            value = checkTvalue(PLC_T4_temperature_setpoint, diff);
            if (PLC_Iam_T4) {
                addWrite_PLC_T4_temperature_setpoint(value);
                addWrite_SRV_T4_temperature_setpoint(value);
            } else {
                addWrite_TCP_T4_temperature_setpoint(value);
            }
            break;
        case 5:
            value = checkTvalue(PLC_T5_temperature_setpoint, diff);
            if (PLC_Iam_T5) {
                addWrite_PLC_T5_temperature_setpoint(value);
                addWrite_SRV_T5_temperature_setpoint(value);
            } else {
                addWrite_TCP_T5_temperature_setpoint(value);
            }
            break;
        case 6:
            value = checkTvalue(PLC_T6_temperature_setpoint, diff);
            if (PLC_Iam_T6) {
                addWrite_PLC_T6_temperature_setpoint(value);
                addWrite_SRV_T6_temperature_setpoint(value);
            } else {
                addWrite_TCP_T6_temperature_setpoint(value);
            }
            break;
        default:
            ;
        }
    }
    endWrite();
}

void page101b::temperature_nt_valueChanged(int diff)
{
    int value;

    beginWrite();
    {
        switch (currentThermostat) {
        case 1:
            value = checkTvalue(PLC_T1_temperature_setpoint_nt, diff);
            if (PLC_Iam_T1) {
                addWrite_PLC_T1_temperature_setpoint_nt(value);
                addWrite_SRV_T1_temperature_setpoint_nt(value);
            } else {
                addWrite_TCP_T1_temperature_setpoint_nt(value);
            }
            break;
        case 2:
            value = checkTvalue(PLC_T2_temperature_setpoint_nt, diff);
            if (PLC_Iam_T2) {
                addWrite_PLC_T2_temperature_setpoint_nt(value);
                addWrite_SRV_T2_temperature_setpoint_nt(value);
            } else {
                addWrite_TCP_T2_temperature_setpoint_nt(value);
            }
            break;
        case 3:
            value = checkTvalue(PLC_T3_temperature_setpoint_nt, diff);
            if (PLC_Iam_T3) {
                addWrite_PLC_T3_temperature_setpoint_nt(value);
                addWrite_SRV_T3_temperature_setpoint_nt(value);
            } else {
                addWrite_TCP_T3_temperature_setpoint_nt(value);
            }
            break;
        case 4:
            value = checkTvalue(PLC_T4_temperature_setpoint_nt, diff);
            if (PLC_Iam_T4) {
                addWrite_PLC_T4_temperature_setpoint_nt(value);
                addWrite_SRV_T4_temperature_setpoint_nt(value);
            } else {
                addWrite_TCP_T4_temperature_setpoint_nt(value);
            }
            break;
        case 5:
            value = checkTvalue(PLC_T5_temperature_setpoint_nt, diff);
            if (PLC_Iam_T5) {
                addWrite_PLC_T5_temperature_setpoint_nt(value);
                addWrite_SRV_T5_temperature_setpoint_nt(value);
            } else {
                addWrite_TCP_T5_temperature_setpoint_nt(value);
            }
            break;
        case 6:
            value = checkTvalue(PLC_T6_temperature_setpoint_nt, diff);
            if (PLC_Iam_T6) {
                addWrite_PLC_T6_temperature_setpoint_nt(value);
                addWrite_SRV_T6_temperature_setpoint_nt(value);
            } else {
                addWrite_TCP_T6_temperature_setpoint_nt(value);
            }
            break;
        default:
            ;
        }
    }
    endWrite();
}

void page101b::humidity_valueChanged(int diff)
{
    int value;

    beginWrite();
    {
        switch (currentThermostat) {
        case 1:
            value = checkHvalue(PLC_T1_humidity_setpoint, diff);
            if (PLC_Iam_T1) {
                addWrite_PLC_T1_humidity_setpoint(value);
                addWrite_SRV_T1_humidity_setpoint(value);
            } else {
                addWrite_TCP_T1_humidity_setpoint(value);
            }
            break;
        case 2:
            value = checkHvalue(PLC_T2_humidity_setpoint, diff);
            if (PLC_Iam_T2) {
                addWrite_PLC_T2_humidity_setpoint(value);
                addWrite_SRV_T2_humidity_setpoint(value);
            } else {
                addWrite_TCP_T2_humidity_setpoint(value);
            }
            break;
        case 3:
            value = checkHvalue(PLC_T3_humidity_setpoint, diff);
            if (PLC_Iam_T3) {
                addWrite_PLC_T3_humidity_setpoint(value);
                addWrite_SRV_T3_humidity_setpoint(value);
            } else {
                addWrite_TCP_T3_humidity_setpoint(value);
            }
            break;
        case 4:
            value = checkHvalue(PLC_T4_humidity_setpoint, diff);
            if (PLC_Iam_T4) {
                addWrite_PLC_T4_humidity_setpoint(value);
                addWrite_SRV_T4_humidity_setpoint(value);
            } else {
                addWrite_TCP_T4_humidity_setpoint(value);
            }
            break;
        case 5:
            value = checkHvalue(PLC_T5_humidity_setpoint, diff);
            if (PLC_Iam_T5) {
                addWrite_PLC_T5_humidity_setpoint(value);
                addWrite_SRV_T5_humidity_setpoint(value);
            } else {
                addWrite_TCP_T5_humidity_setpoint(value);
            }
            break;
        case 6:
            value = checkHvalue(PLC_T6_humidity_setpoint, diff);
            if (PLC_Iam_T6) {
                addWrite_PLC_T6_humidity_setpoint(value);
                addWrite_SRV_T6_humidity_setpoint(value);
            } else {
                addWrite_TCP_T6_humidity_setpoint(value);
            }
            break;
        default:
            ;
        }
    }
    endWrite();
}

void page101b::humidity_nt_valueChanged(int diff)
{
    int value;

    beginWrite();
    {
        switch (currentThermostat) {
        case 1:
            value = checkHvalue(PLC_T1_humidity_setpoint_nt, diff);
            if (PLC_Iam_T1) {
                addWrite_PLC_T1_humidity_setpoint_nt(value);
                addWrite_SRV_T1_humidity_setpoint_nt(value);
            } else {
                addWrite_TCP_T1_humidity_setpoint_nt(value);
            }
            break;
        case 2:
            value = checkHvalue(PLC_T2_humidity_setpoint_nt, diff);
            if (PLC_Iam_T2) {
                addWrite_PLC_T2_humidity_setpoint_nt(value);
                addWrite_SRV_T2_humidity_setpoint_nt(value);
            } else {
                addWrite_TCP_T2_humidity_setpoint_nt(value);
            }
            break;
        case 3:
            value = checkHvalue(PLC_T3_humidity_setpoint_nt, diff);
            if (PLC_Iam_T3) {
                addWrite_PLC_T3_humidity_setpoint_nt(value);
                addWrite_SRV_T3_humidity_setpoint_nt(value);
            } else {
                addWrite_TCP_T3_humidity_setpoint_nt(value);
            }
            break;
        case 4:
            value = checkHvalue(PLC_T4_humidity_setpoint_nt, diff);
            if (PLC_Iam_T4) {
                addWrite_PLC_T4_humidity_setpoint_nt(value);
                addWrite_SRV_T4_humidity_setpoint_nt(value);
            } else {
                addWrite_TCP_T4_humidity_setpoint_nt(value);
            }
            break;
        case 5:
            value = checkHvalue(PLC_T5_humidity_setpoint_nt, diff);
            if (PLC_Iam_T5) {
                addWrite_PLC_T5_humidity_setpoint_nt(value);
                addWrite_SRV_T5_humidity_setpoint_nt(value);
            } else {
                addWrite_TCP_T5_humidity_setpoint_nt(value);
            }
            break;
        case 6:
            value = checkHvalue(PLC_T6_humidity_setpoint_nt, diff);
            if (PLC_Iam_T6) {
                addWrite_PLC_T6_humidity_setpoint_nt(value);
                addWrite_SRV_T6_humidity_setpoint_nt(value);
            } else {
                addWrite_TCP_T6_humidity_setpoint_nt(value);
            }
            break;
        default:
            ;
        }
    }
    endWrite();
}

void page101b::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page101b::~page101b()
{
    delete ui;
}

void page101b::on_atcmButton_set_T_everywhere_clicked()
{
    int setpoint = TemperatureSetPoint_min, setpoint_nt = TemperatureSetPoint_min;

    switch (currentThermostat) {
    case 1:
        setpoint = PLC_T1_temperature_setpoint;
        setpoint_nt = PLC_T1_temperature_setpoint_nt;
        break;
    case 2:
        setpoint = PLC_T2_temperature_setpoint;
        setpoint_nt = PLC_T2_temperature_setpoint_nt;
        break;
    case 3:
        setpoint = PLC_T3_temperature_setpoint;
        setpoint_nt = PLC_T3_temperature_setpoint_nt;
        break;
    case 4:
        setpoint = PLC_T4_temperature_setpoint;
        setpoint_nt = PLC_T4_temperature_setpoint_nt;
        break;
    case 5:
        setpoint = PLC_T5_temperature_setpoint;
        setpoint_nt = PLC_T5_temperature_setpoint_nt;
        break;
    case 6:
        setpoint = PLC_T6_temperature_setpoint;
        setpoint_nt = PLC_T6_temperature_setpoint_nt;
        break;
    default:
        ;
    }

    beginWrite();
    {
        if (PLC_Iam_T1) {
            addWrite_PLC_T1_temperature_setpoint(setpoint);
            addWrite_SRV_T1_temperature_setpoint(setpoint);
            addWrite_PLC_T1_temperature_setpoint_nt(setpoint_nt);
            addWrite_SRV_T1_temperature_setpoint_nt(setpoint_nt);
        } else {
            addWrite_TCP_T1_temperature_setpoint(setpoint);
            addWrite_TCP_T1_temperature_setpoint_nt(setpoint_nt);
        }
        if (PLC_Iam_T2) {
            addWrite_PLC_T2_temperature_setpoint(setpoint);
            addWrite_SRV_T2_temperature_setpoint(setpoint);
            addWrite_PLC_T2_temperature_setpoint_nt(setpoint_nt);
            addWrite_SRV_T2_temperature_setpoint_nt(setpoint_nt);
        } else {
            addWrite_TCP_T2_temperature_setpoint(setpoint);
            addWrite_TCP_T2_temperature_setpoint_nt(setpoint_nt);
        }
        if (PLC_Iam_T3) {
            addWrite_PLC_T3_temperature_setpoint(setpoint);
            addWrite_SRV_T3_temperature_setpoint(setpoint);
            addWrite_PLC_T3_temperature_setpoint_nt(setpoint_nt);
            addWrite_SRV_T3_temperature_setpoint_nt(setpoint_nt);
        } else {
            addWrite_TCP_T3_temperature_setpoint(setpoint);
            addWrite_TCP_T3_temperature_setpoint_nt(setpoint_nt);
        }
        if (PLC_Iam_T4) {
            addWrite_PLC_T4_temperature_setpoint(setpoint);
            addWrite_SRV_T4_temperature_setpoint(setpoint);
            addWrite_PLC_T4_temperature_setpoint_nt(setpoint_nt);
            addWrite_SRV_T4_temperature_setpoint_nt(setpoint_nt);
        } else {
            addWrite_TCP_T4_temperature_setpoint(setpoint);
            addWrite_TCP_T4_temperature_setpoint_nt(setpoint_nt);
        }
        if (PLC_Iam_T5) {
            addWrite_PLC_T5_temperature_setpoint(setpoint);
            addWrite_SRV_T5_temperature_setpoint(setpoint);
            addWrite_PLC_T5_temperature_setpoint_nt(setpoint_nt);
            addWrite_SRV_T5_temperature_setpoint_nt(setpoint_nt);
        } else {
            addWrite_TCP_T5_temperature_setpoint(setpoint);
            addWrite_TCP_T5_temperature_setpoint_nt(setpoint_nt);
        }
        if (PLC_Iam_T6) {
            addWrite_PLC_T6_temperature_setpoint(setpoint);
            addWrite_SRV_T6_temperature_setpoint(setpoint);
            addWrite_PLC_T6_temperature_setpoint_nt(setpoint_nt);
            addWrite_SRV_T6_temperature_setpoint_nt(setpoint_nt);
        } else {
            addWrite_TCP_T6_temperature_setpoint(setpoint);
            addWrite_TCP_T6_temperature_setpoint_nt(setpoint_nt);
        }
    }
    endWrite();
}
