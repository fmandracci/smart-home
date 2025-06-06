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
#include "page500.h"
#include "ui_page500.h"
#include "crosstable.h"

#include "automation.h"
#include <QSettings>

page500::page500(QWidget *parent) :
    page(parent),
    ui(new Ui::page500)
{
    ui->setupUi(this);
    TRANSLATE_FONT_SIZE(this);
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));

    ui->pushButton_OFF->setEnabled(false);
    ui->pushButton_DAYTIME->setEnabled(false);
    ui->pushButton_NIGHTTIME->setEnabled(false);
    ui->pushButton_EVERYTHING->setEnabled(false);
    ui->pushButton_ENABLED->setEnabled(false);
    ui->pushButton_RINGING->setEnabled(false);
    ui->pushButton_MUTED->setEnabled(false);
    ui->pushButton_TESTING->setEnabled(false);
}

void page500::reload()
{
    changeWidgets();
    enableDisableCommands();
    updateWidgets();
}

void page500::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();
    enableDisableCommands();
    updateWidgets();
}

void page500::changeLabel(QLabel *label, const QString text)
{
    QString base_style = FONT_SS_N(modulor->normalFont_px()) + "background-color: rgb(0, 0, 0);";

    if (text.contains(LABEL_01))
        label->setStyleSheet(base_style + COLOR_SS(COLOR_01));
    else if (text.contains(LABEL_02))
        label->setStyleSheet(base_style + COLOR_SS(COLOR_02));
    else if (text.contains(LABEL_03))
        label->setStyleSheet(base_style + COLOR_SS(COLOR_03));
    else if (text.contains(LABEL_04))
        label->setStyleSheet(base_style + COLOR_SS(COLOR_04));
    else if (text.contains(LABEL_05))
        label->setStyleSheet(base_style + COLOR_SS(COLOR_05));
    else if (text.contains(LABEL_06))
        label->setStyleSheet(base_style + COLOR_SS(COLOR_06));
    else
        label->setStyleSheet(base_style + COLOR_SS(COLOR_00));

    label->setText(text);
}

void page500::changeWidgets()
{
    QSettings home_ini(HOME_INI_FILE, QSettings::IniFormat);
    home_ini.setIniCodec("UTF-8");

    ui->headerPanel->changeWidgets(NULL, BA_PIXMAP, NULL, "page500: BA");

    QString bf = FONT_SS_N(modulor->normalFont_px()); // STATUS/BUTTONS
    int minimum_height = modulor->normalFont_px() * 15 / 10;

    ACTIVE_StyleSheet  = bf + "background-color: rgb(255,  85,   0); color: rgb(  0,   0,   0); border: none; font: bold;";
    Possible_StyleSheet= bf + "background-color: rgb( 85,   0,   0); color: rgb(255, 255, 255); border: none;            ";
    inactive_StyleSheet= bf + "background-color: rgb(  0,   0,   0); color: rgb( 64,  64,  64); border: none;            ";

    ui->pushButton_OFF->setMinimumHeight(minimum_height);
    ui->pushButton_DAYTIME->setMinimumHeight(minimum_height);
    ui->pushButton_NIGHTTIME->setMinimumHeight(minimum_height);
    ui->pushButton_EVERYTHING->setMinimumHeight(minimum_height);
    ui->pushButton_ENABLED->setMinimumHeight(minimum_height);
    ui->pushButton_RINGING->setMinimumHeight(minimum_height);
    ui->pushButton_MUTED->setMinimumHeight(minimum_height);
    ui->pushButton_TESTING->setMinimumHeight(minimum_height);

    QSize labelSize(modulor->largeFont_px(), modulor->largeFont_px()); // sensor leds
    QString sf = FONT_SS_N(modulor->normalFont_px()); // sensor leds and sensor names

    WHITE_OVER_BLACK   = sf + "color: rgb(255, 255, 255); background-color: rgb(0, 0, 0);";
    GREY_OVER_BLACK    = sf + "color: rgb( 64,  64,  64); background-color: rgb(0, 0, 0);";
    GREEN_OVER_BLACK   = sf + "color: rgb(  0, 255,   0); background-color: rgb(0, 0, 0);";
    RED_OVER_BLACK     = sf + "color: rgb(255,   0,   0); background-color: rgb(0, 0, 0);";
    ORANGE_OVER_BLACK  = sf + "color: rgb(255, 128,   0); background-color: rgb(0, 0, 0);";
    MAGENTA_OVER_BLACK = sf + "color: rgb(255,   0, 255); background-color: rgb(0, 0, 0);";

    ui->label_BA_OK_01->setStyleSheet(sf); ui->label_BA_OK_01->setMaximumSize(labelSize);
    ui->label_BA_OK_02->setStyleSheet(sf); ui->label_BA_OK_02->setMaximumSize(labelSize);
    ui->label_BA_OK_03->setStyleSheet(sf); ui->label_BA_OK_03->setMaximumSize(labelSize);
    ui->label_BA_OK_04->setStyleSheet(sf); ui->label_BA_OK_04->setMaximumSize(labelSize);
    ui->label_BA_OK_05->setStyleSheet(sf); ui->label_BA_OK_05->setMaximumSize(labelSize);
    ui->label_BA_OK_06->setStyleSheet(sf); ui->label_BA_OK_06->setMaximumSize(labelSize);
    ui->label_BA_OK_07->setStyleSheet(sf); ui->label_BA_OK_07->setMaximumSize(labelSize);
    ui->label_BA_OK_08->setStyleSheet(sf); ui->label_BA_OK_08->setMaximumSize(labelSize);

    ui->label_BA_OK_09->setStyleSheet(sf); ui->label_BA_OK_09->setMaximumSize(labelSize);
    ui->label_BA_OK_10->setStyleSheet(sf); ui->label_BA_OK_10->setMaximumSize(labelSize);
    ui->label_BA_OK_11->setStyleSheet(sf); ui->label_BA_OK_11->setMaximumSize(labelSize);
    ui->label_BA_OK_12->setStyleSheet(sf); ui->label_BA_OK_12->setMaximumSize(labelSize);
    ui->label_BA_OK_13->setStyleSheet(sf); ui->label_BA_OK_13->setMaximumSize(labelSize);
    ui->label_BA_OK_14->setStyleSheet(sf); ui->label_BA_OK_14->setMaximumSize(labelSize);
    ui->label_BA_OK_15->setStyleSheet(sf); ui->label_BA_OK_15->setMaximumSize(labelSize);
    ui->label_BA_OK_16->setStyleSheet(sf); ui->label_BA_OK_16->setMaximumSize(labelSize);

    ui->label_BA_OK_17->setStyleSheet(sf); ui->label_BA_OK_17->setMaximumSize(labelSize);
    ui->label_BA_OK_18->setStyleSheet(sf); ui->label_BA_OK_18->setMaximumSize(labelSize);
    ui->label_BA_OK_19->setStyleSheet(sf); ui->label_BA_OK_19->setMaximumSize(labelSize);
    ui->label_BA_OK_20->setStyleSheet(sf); ui->label_BA_OK_20->setMaximumSize(labelSize);
    ui->label_BA_OK_21->setStyleSheet(sf); ui->label_BA_OK_21->setMaximumSize(labelSize);
    ui->label_BA_OK_22->setStyleSheet(sf); ui->label_BA_OK_22->setMaximumSize(labelSize);
    ui->label_BA_OK_23->setStyleSheet(sf); ui->label_BA_OK_23->setMaximumSize(labelSize);
    ui->label_BA_OK_24->setStyleSheet(sf); ui->label_BA_OK_24->setMaximumSize(labelSize);

    ui->label_BA_OK_25->setStyleSheet(sf); ui->label_BA_OK_25->setMaximumSize(labelSize);
    ui->label_BA_OK_26->setStyleSheet(sf); ui->label_BA_OK_26->setMaximumSize(labelSize);
    ui->label_BA_OK_27->setStyleSheet(sf); ui->label_BA_OK_27->setMaximumSize(labelSize);
    ui->label_BA_OK_28->setStyleSheet(sf); ui->label_BA_OK_28->setMaximumSize(labelSize);
    ui->label_BA_OK_29->setStyleSheet(sf); ui->label_BA_OK_29->setMaximumSize(labelSize);
    ui->label_BA_OK_30->setStyleSheet(sf); ui->label_BA_OK_30->setMaximumSize(labelSize);
    ui->label_BA_OK_31->setStyleSheet(sf); ui->label_BA_OK_31->setMaximumSize(labelSize);
    ui->label_BA_OK_32->setStyleSheet(sf); ui->label_BA_OK_32->setMaximumSize(labelSize);

    changeLabel(ui->label_sensor_01, home_ini.value("BA/sensor_01").toString());
    changeLabel(ui->label_sensor_02, home_ini.value("BA/sensor_02").toString());
    changeLabel(ui->label_sensor_03, home_ini.value("BA/sensor_03").toString());
    changeLabel(ui->label_sensor_04, home_ini.value("BA/sensor_04").toString());
    changeLabel(ui->label_sensor_05, home_ini.value("BA/sensor_05").toString());
    changeLabel(ui->label_sensor_06, home_ini.value("BA/sensor_06").toString());
    changeLabel(ui->label_sensor_07, home_ini.value("BA/sensor_07").toString());
    changeLabel(ui->label_sensor_08, home_ini.value("BA/sensor_08").toString());

    changeLabel(ui->label_sensor_09, home_ini.value("BA/sensor_09").toString());
    changeLabel(ui->label_sensor_10, home_ini.value("BA/sensor_10").toString());
    changeLabel(ui->label_sensor_11, home_ini.value("BA/sensor_11").toString());
    changeLabel(ui->label_sensor_12, home_ini.value("BA/sensor_12").toString());
    changeLabel(ui->label_sensor_13, home_ini.value("BA/sensor_13").toString());
    changeLabel(ui->label_sensor_14, home_ini.value("BA/sensor_14").toString());
    changeLabel(ui->label_sensor_15, home_ini.value("BA/sensor_15").toString());
    changeLabel(ui->label_sensor_16, home_ini.value("BA/sensor_16").toString());

    changeLabel(ui->label_sensor_17, home_ini.value("BA/sensor_17").toString());
    changeLabel(ui->label_sensor_18, home_ini.value("BA/sensor_18").toString());
    changeLabel(ui->label_sensor_19, home_ini.value("BA/sensor_19").toString());
    changeLabel(ui->label_sensor_20, home_ini.value("BA/sensor_20").toString());
    changeLabel(ui->label_sensor_21, home_ini.value("BA/sensor_21").toString());
    changeLabel(ui->label_sensor_22, home_ini.value("BA/sensor_22").toString());
    changeLabel(ui->label_sensor_23, home_ini.value("BA/sensor_23").toString());
    changeLabel(ui->label_sensor_24, home_ini.value("BA/sensor_24").toString());

    changeLabel(ui->label_sensor_25, home_ini.value("BA/sensor_25").toString());
    changeLabel(ui->label_sensor_26, home_ini.value("BA/sensor_26").toString());
    changeLabel(ui->label_sensor_27, home_ini.value("BA/sensor_27").toString());
    changeLabel(ui->label_sensor_28, home_ini.value("BA/sensor_28").toString());
    changeLabel(ui->label_sensor_29, home_ini.value("BA/sensor_29").toString());
    changeLabel(ui->label_sensor_30, home_ini.value("BA/sensor_30").toString());
    changeLabel(ui->label_sensor_31, home_ini.value("BA/sensor_31").toString());
    changeLabel(ui->label_sensor_32, home_ini.value("BA/sensor_32").toString());
}

void page500::updateWidgets()
{
    ui->headerPanel->updateWidgets();
    switch (PLC_BA_status) {
    case ALARM_STATUS_ZERO:
        ui->pushButton_OFF->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_DAYTIME->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_NIGHTTIME->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_EVERYTHING->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_ENABLED->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_RINGING->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_MUTED->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_TESTING->setStyleSheet(inactive_StyleSheet);
        break;
    case ALARM_STATUS_OFF:
        ui->pushButton_OFF->setStyleSheet(ACTIVE_StyleSheet);
        ui->pushButton_DAYTIME->setStyleSheet(Possible_StyleSheet);
        ui->pushButton_NIGHTTIME->setStyleSheet(Possible_StyleSheet);
        ui->pushButton_EVERYTHING->setStyleSheet(Possible_StyleSheet);
        ui->pushButton_ENABLED->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_RINGING->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_MUTED->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_TESTING->setStyleSheet(inactive_StyleSheet); // (PLC_Iam_BA ? Possible_StyleSheet : inactive_StyleSheet);
        break;
    case ALARM_STATUS_ARMED:
        ui->pushButton_OFF->setStyleSheet(Possible_StyleSheet);
        ui->pushButton_DAYTIME->setStyleSheet((PLC_BA_config_index == ALARM_CONFIG_INDEX_DAYTIME)? ACTIVE_StyleSheet : Possible_StyleSheet);
        ui->pushButton_NIGHTTIME->setStyleSheet((PLC_BA_config_index == ALARM_CONFIG_INDEX_NIGHTTIME)? ACTIVE_StyleSheet : Possible_StyleSheet);
        ui->pushButton_EVERYTHING->setStyleSheet((PLC_BA_config_index == ALARM_CONFIG_INDEX_EVERYTHING)? ACTIVE_StyleSheet : Possible_StyleSheet);
        ui->pushButton_ENABLED->setStyleSheet(Possible_StyleSheet);
        ui->pushButton_RINGING->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_MUTED->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_TESTING->setStyleSheet(inactive_StyleSheet); // (PLC_Iam_BA ? Possible_StyleSheet : inactive_StyleSheet);
        break;
    case ALARM_STATUS_ENABLED:
        ui->pushButton_OFF->setStyleSheet(Possible_StyleSheet);
        ui->pushButton_DAYTIME->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_NIGHTTIME->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_EVERYTHING->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_ENABLED->setStyleSheet(ACTIVE_StyleSheet);
        ui->pushButton_RINGING->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_MUTED->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_TESTING->setStyleSheet(inactive_StyleSheet); // (PLC_Iam_BA ? Possible_StyleSheet : inactive_StyleSheet);
        break;
    case ALARM_STATUS_RINGING:
        ui->pushButton_OFF->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_DAYTIME->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_NIGHTTIME->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_EVERYTHING->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_ENABLED->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_RINGING->setStyleSheet(ACTIVE_StyleSheet);
        ui->pushButton_MUTED->setStyleSheet(Possible_StyleSheet);
        ui->pushButton_TESTING->setStyleSheet(inactive_StyleSheet); // (PLC_Iam_BA ? Possible_StyleSheet : inactive_StyleSheet);
        break;
    case ALARM_STATUS_MUTED:
        ui->pushButton_OFF->setStyleSheet(Possible_StyleSheet);
        ui->pushButton_DAYTIME->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_NIGHTTIME->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_EVERYTHING->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_ENABLED->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_RINGING->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_MUTED->setStyleSheet(ACTIVE_StyleSheet);
        ui->pushButton_TESTING->setStyleSheet(inactive_StyleSheet); // (PLC_Iam_BA ? Possible_StyleSheet : inactive_StyleSheet);
        break;
    case ALARM_STATUS_TESTING:
        ui->pushButton_OFF->setStyleSheet(Possible_StyleSheet);
        ui->pushButton_DAYTIME->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_NIGHTTIME->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_EVERYTHING->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_ENABLED->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_RINGING->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_MUTED->setStyleSheet(inactive_StyleSheet);
        ui->pushButton_TESTING->setStyleSheet(ACTIVE_StyleSheet);
        break;
    default:
        ;
    }

    updateSensor( 1, PLC_BA_OK_1 , ui->label_BA_OK_01, ui->label_sensor_01);
    updateSensor( 2, PLC_BA_OK_2 , ui->label_BA_OK_02, ui->label_sensor_02);
    updateSensor( 3, PLC_BA_OK_3 , ui->label_BA_OK_03, ui->label_sensor_03);
    updateSensor( 4, PLC_BA_OK_4 , ui->label_BA_OK_04, ui->label_sensor_04);
    ui->line_4_5->setVisible(false); // PLC_BA_enabled_sensors >= 5);
    updateSensor( 5, PLC_BA_OK_5 , ui->label_BA_OK_05, ui->label_sensor_05);
    updateSensor( 6, PLC_BA_OK_6 , ui->label_BA_OK_06, ui->label_sensor_06);
    updateSensor( 7, PLC_BA_OK_7 , ui->label_BA_OK_07, ui->label_sensor_07);
    updateSensor( 8, PLC_BA_OK_8 , ui->label_BA_OK_08, ui->label_sensor_08);

    updateSensor( 9, PLC_BA_OK_9 , ui->label_BA_OK_09, ui->label_sensor_09);
    updateSensor(10, PLC_BA_OK_10, ui->label_BA_OK_10, ui->label_sensor_10);
    updateSensor(11, PLC_BA_OK_11, ui->label_BA_OK_11, ui->label_sensor_11);
    updateSensor(12, PLC_BA_OK_12, ui->label_BA_OK_12, ui->label_sensor_12);
    ui->line_12_13->setVisible(false); // PLC_BA_enabled_sensors >= 13);
    updateSensor(13, PLC_BA_OK_13, ui->label_BA_OK_13, ui->label_sensor_13);
    updateSensor(14, PLC_BA_OK_14, ui->label_BA_OK_14, ui->label_sensor_14);
    updateSensor(15, PLC_BA_OK_15, ui->label_BA_OK_15, ui->label_sensor_15);
    updateSensor(16, PLC_BA_OK_16, ui->label_BA_OK_16, ui->label_sensor_16);

    updateSensor(17, PLC_BA_OK_17, ui->label_BA_OK_17, ui->label_sensor_17);
    updateSensor(18, PLC_BA_OK_18, ui->label_BA_OK_18, ui->label_sensor_18);
    updateSensor(19, PLC_BA_OK_19, ui->label_BA_OK_19, ui->label_sensor_19);
    updateSensor(20, PLC_BA_OK_20, ui->label_BA_OK_20, ui->label_sensor_20);
    ui->line_20_21->setVisible(false); // PLC_BA_enabled_sensors >= 21);
    updateSensor(21, PLC_BA_OK_21, ui->label_BA_OK_21, ui->label_sensor_21);
    updateSensor(22, PLC_BA_OK_22, ui->label_BA_OK_22, ui->label_sensor_22);
    updateSensor(23, PLC_BA_OK_23, ui->label_BA_OK_23, ui->label_sensor_23);
    updateSensor(24, PLC_BA_OK_24, ui->label_BA_OK_24, ui->label_sensor_24);

    updateSensor(25, PLC_BA_OK_25, ui->label_BA_OK_25, ui->label_sensor_25);
    updateSensor(26, PLC_BA_OK_26, ui->label_BA_OK_26, ui->label_sensor_26);
    updateSensor(27, PLC_BA_OK_27, ui->label_BA_OK_27, ui->label_sensor_27);
    updateSensor(28, PLC_BA_OK_28, ui->label_BA_OK_28, ui->label_sensor_28);
    ui->line_28_29->setVisible(false); // PLC_BA_enabled_sensors >= 29);
    updateSensor(29, PLC_BA_OK_29, ui->label_BA_OK_29, ui->label_sensor_29);
    updateSensor(30, PLC_BA_OK_30, ui->label_BA_OK_30, ui->label_sensor_30);
    updateSensor(31, PLC_BA_OK_31, ui->label_BA_OK_31, ui->label_sensor_31);
    updateSensor(32, PLC_BA_OK_32, ui->label_BA_OK_32, ui->label_sensor_32);
}

void page500::updateSensor(int i, unsigned status, QLabel *label_ok, QLabel *label_sensor)
{
    if (PLC_BA_isOK) {
        if (PLC_BA_enabled_sensors >= i) {
                switch (status) {
                case ALARM_SENSOR_IGNORED:  label_ok->setStyleSheet(GREY_OVER_BLACK); break;
                case ALARM_SENSOR_STILL_NG: label_ok->setStyleSheet(RED_OVER_BLACK); break;
                case ALARM_SENSOR_GOOD:     label_ok->setStyleSheet(GREEN_OVER_BLACK); break;
                case ALARM_SENSOR_NOT_GOOD: label_ok->setStyleSheet(RED_OVER_BLACK); break;
                case ALARM_SENSOR_WAS_NG:   label_ok->setStyleSheet(ORANGE_OVER_BLACK); break;
                default: ;
                }
            label_ok->setVisible(true);
            label_sensor->setVisible(true);
        } else {
            label_ok->setVisible(false);
            label_sensor->setVisible(false);
        }
    } else {
        label_ok->setVisible(true);
        label_sensor->setVisible(true);
        label_ok->setStyleSheet(MAGENTA_OVER_BLACK);
    }
}

void page500::enableDisableCommands()
{
    switch (PLC_BA_status) {
    case ALARM_STATUS_ZERO:
        ui->pushButton_OFF->setEnabled(false);
        ui->pushButton_DAYTIME->setEnabled(false);
        ui->pushButton_NIGHTTIME->setEnabled(false);
        ui->pushButton_EVERYTHING->setEnabled(false);
        ui->pushButton_ENABLED->setEnabled(false);
        ui->pushButton_RINGING->setEnabled(false);
        ui->pushButton_MUTED->setEnabled(false);
        ui->pushButton_TESTING->setEnabled(false);
        break;
    case ALARM_STATUS_OFF:
        ui->pushButton_OFF->setEnabled(false);
        ui->pushButton_DAYTIME->setEnabled(true);     // ---> ARMED+DAYTIME
        ui->pushButton_NIGHTTIME->setEnabled(true);   // ---> ARMED+NIGHTIME
        ui->pushButton_EVERYTHING->setEnabled(true);  // ---> ARMED+EVERYTHING
        ui->pushButton_ENABLED->setEnabled(false);
        ui->pushButton_RINGING->setEnabled(false);
        ui->pushButton_MUTED->setEnabled(false);
        ui->pushButton_TESTING->setEnabled(false); // (PLC_Iam_BA);    // ---> TESTING
        break;
    case ALARM_STATUS_ARMED:
        ui->pushButton_OFF->setEnabled(true);        // disarm --> IDLE
        ui->pushButton_DAYTIME->setEnabled(true);     // ---> ARMED+DAYTIME
        ui->pushButton_NIGHTTIME->setEnabled(true);   // ---> ARMED+NIGHTIME
        ui->pushButton_EVERYTHING->setEnabled(true);  // ---> ARMED+EVERYTHING
        ui->pushButton_ENABLED->setEnabled(true);     // ---> ENABLED
        ui->pushButton_RINGING->setEnabled(false);
        ui->pushButton_MUTED->setEnabled(false);
        ui->pushButton_TESTING->setEnabled(false); // (PLC_Iam_BA);    // ---> TESTING
        break;
    case ALARM_STATUS_ENABLED:
        ui->pushButton_OFF->setEnabled(true);          // disable ---> IDLE
        ui->pushButton_DAYTIME->setEnabled(false);
        ui->pushButton_NIGHTTIME->setEnabled(false);
        ui->pushButton_EVERYTHING->setEnabled(false);
        ui->pushButton_ENABLED->setEnabled(false);
        ui->pushButton_RINGING->setEnabled(false);
        ui->pushButton_MUTED->setEnabled(false);
        ui->pushButton_TESTING->setEnabled(false); // (PLC_Iam_BA);
        break;
    case ALARM_STATUS_RINGING:
        ui->pushButton_OFF->setEnabled(false);
        ui->pushButton_DAYTIME->setEnabled(false);
        ui->pushButton_NIGHTTIME->setEnabled(false);
        ui->pushButton_EVERYTHING->setEnabled(false);
        ui->pushButton_ENABLED->setEnabled(false);
        ui->pushButton_RINGING->setEnabled(false);
        ui->pushButton_MUTED->setEnabled(true);     // ack     --> MUTED
        ui->pushButton_TESTING->setEnabled(false); // (PLC_Iam_BA);
        break;
    case ALARM_STATUS_MUTED:
        ui->pushButton_OFF->setEnabled(true);  // disable --> IDLE
        ui->pushButton_DAYTIME->setEnabled(false);
        ui->pushButton_NIGHTTIME->setEnabled(false);
        ui->pushButton_EVERYTHING->setEnabled(false);
        ui->pushButton_ENABLED->setEnabled(false);
        ui->pushButton_RINGING->setEnabled(false);
        ui->pushButton_MUTED->setEnabled(false);
        ui->pushButton_TESTING->setEnabled(false); // (PLC_Iam_BA);
        break;
    case ALARM_STATUS_TESTING:
        ui->pushButton_OFF->setEnabled(true);
        ui->pushButton_DAYTIME->setEnabled(false);
        ui->pushButton_NIGHTTIME->setEnabled(false);
        ui->pushButton_EVERYTHING->setEnabled(false);
        ui->pushButton_ENABLED->setEnabled(false);
        ui->pushButton_RINGING->setEnabled(false);
        ui->pushButton_MUTED->setEnabled(false);
        ui->pushButton_TESTING->setEnabled(false); // (PLC_Iam_BA);
        break;
    default:
        ;
    }
}

void page500::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page500::~page500()
{
    delete ui;
}

void page500::sendCommand(uint32_t command)
{
    beginWrite();
    {
        if (PLC_Iam_BA) {
            addWrite_PLC_BA_command(command);
            addWrite_SRV_BA_command(command);
        } else {
            addWrite_TCP_BA_command(command);
        }
    }
    endWrite();
}

void page500::on_pushButton_OFF_clicked()
{
    ui->pushButton_OFF->setStyleSheet(ACTIVE_StyleSheet);
    sendCommand(ALARM_COMMAND_DISABLE);
}

void page500::on_pushButton_DAYTIME_clicked()
{
    ui->pushButton_DAYTIME->setStyleSheet(ACTIVE_StyleSheet);
    sendCommand(ALARM_COMMAND_DAYTIME);
}

void page500::on_pushButton_NIGHTTIME_clicked()
{
    ui->pushButton_NIGHTTIME->setStyleSheet(ACTIVE_StyleSheet);
    sendCommand(ALARM_COMMAND_NIGHTTIME);
}

void page500::on_pushButton_EVERYTHING_clicked()
{
    ui->pushButton_EVERYTHING->setStyleSheet(ACTIVE_StyleSheet);
    sendCommand(ALARM_COMMAND_EVERYTHING);
}

void page500::on_pushButton_TESTING_clicked()
{
    //sendCommand(ALARM_COMMAND_TEST);
    goto_page("page046");
}

void page500::on_pushButton_ENABLED_clicked()
{
    ui->pushButton_ENABLED->setStyleSheet(ACTIVE_StyleSheet);
    sendCommand(ALARM_COMMAND_ENABLE);
}

void page500::on_pushButton_RINGING_clicked()
{
}

void page500::on_pushButton_MUTED_clicked()
{
    ui->pushButton_MUTED->setStyleSheet(ACTIVE_StyleSheet);
    sendCommand(ALARM_COMMAND_ACK);
}
