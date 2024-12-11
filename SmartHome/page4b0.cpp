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
#include "page4b0.h"
#include "ui_page4b0.h"
#include "crosstable.h"
#include "automation.h"

page4b0::page4b0(QWidget *parent) :
    page(parent),
    ui(new Ui::page4b0),
    tic_0(QString::fromUtf8(" ")),
    tic_1(QString::fromUtf8("⚋")),
    tic_2(QString::fromUtf8("⚏")),
    tic_3(QString::fromUtf8("☷")),
    tic_4(QString::fromUtf8("☰")),
    tic_5(QString::fromUtf8("⚌")),
    tic_6(QString::fromUtf8("⚊"))
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
}

void page4b0::reload()
{
    changeWidgets();
    updateWidgets();
}

void page4b0::changeWidgets()
{
    QSettings hmi_ini("/local/root/hmi.ini", QSettings::IniFormat);

    changeHeader(ui->pushButton_time, ui->atcmButton_home);
    changeThermostat(1, COLOR_01, ui->label_1, QString::fromUtf8(hmi_ini.value("T1/name").toByteArray()));
    changeThermostat(2, COLOR_02, ui->label_2, QString::fromUtf8(hmi_ini.value("T2/name").toByteArray()));
    changeThermostat(3, COLOR_03, ui->label_3, QString::fromUtf8(hmi_ini.value("T3/name").toByteArray()));
    changeThermostat(4, COLOR_04, ui->label_4, QString::fromUtf8(hmi_ini.value("T4/name").toByteArray()));
    changeThermostat(5, COLOR_05, ui->label_5, QString::fromUtf8(hmi_ini.value("T5/name").toByteArray()));
    changeThermostat(6, COLOR_06, ui->label_6, QString::fromUtf8(hmi_ini.value("T6/name").toByteArray()));
}

void page4b0::changeThermostat(int n, const QColor color, QLabel *label_n, const QString label)
{
    int ps;

    if (mectScreenWidth >= 800) {
        ps = 18;
    } else {
        ps = 12;
    }
    if (PLC_Tn_count >= n) {
        // ①
        label_n->setText(label);
        label_n->setStyleSheet(COLOR_SS(color) + FONT_SS_N(ps));
        label_n->setVisible(true);
    } else {
        label_n->setVisible(false);
    }
}

void page4b0::updateValues(int n, const QColor color,
                          QLabel *label_r_W, QLabel *label_a_W,
                          int value_r_W, int value_a_W)
{
    int ps;

    if (mectScreenWidth >= 800) {
        ps = 18;
    } else {
        ps = 12;
    }
    if (PLC_Tn_count >= n) {
        // requested W
        label_r_W->setText(QString("%1 W").arg(value_r_W));
        label_r_W->setStyleSheet(COLOR_SS(color) + FONT_SS_N(ps));
        label_r_W->setVisible(true);

        // assigned W
        label_a_W->setText(QString("%1 W").arg(value_a_W));
        label_a_W->setStyleSheet(COLOR_SS(color) + FONT_SS_N(ps));
        label_a_W->setVisible(true);
    } else {
        label_r_W->setVisible(false);
        label_a_W->setVisible(false);
    }
}

void page4b0::updateWidgets()
{
    updateValues(1, COLOR_01, ui->label_requested_W_1, ui->label_assigned_W_1, PLC_T1_requested_W, PLC_EP_T1_assigned_W);
    updateValues(2, COLOR_02, ui->label_requested_W_2, ui->label_assigned_W_2, PLC_T2_requested_W, PLC_EP_T2_assigned_W);
    updateValues(3, COLOR_03, ui->label_requested_W_3, ui->label_assigned_W_3, PLC_T3_requested_W, PLC_EP_T3_assigned_W);
    updateValues(4, COLOR_04, ui->label_requested_W_4, ui->label_assigned_W_4, PLC_T4_requested_W, PLC_EP_T4_assigned_W);
    updateValues(5, COLOR_05, ui->label_requested_W_5, ui->label_assigned_W_5, PLC_T5_requested_W, PLC_EP_T5_assigned_W);
    updateValues(6, COLOR_06, ui->label_requested_W_6, ui->label_assigned_W_6, PLC_T6_requested_W, PLC_EP_T6_assigned_W);

    ui->label_requested_W->setText(QString("%1 %2 W").arg(LABEL_SUM).arg(PLC_EP_requested_W));
    ui->label_assigned_W->setText(QString("%1 %2 W").arg(LABEL_SUM).arg(PLC_EP_assigned_W));
    ui->label_max_assigned_W->setText(QString("%1 %2 W").arg(LABEL_LESS_OR_EQ).arg(PLC_EP_max_assigned_W));

    ui->label_actual_W->setText(QString("%1 W").arg(PLC_EP_wattmeter_M_W));
    ui->label_overload_W->setText(QString("%1 %2 W").arg(LABEL_LESS_OR_EQ).arg(PLC_EP_overload_W));

    switch (PLC_EP_tic_in_tac) {
    case 0: ui->label_seconds->setText(tic_0); break;
    case 1: ui->label_seconds->setText(tic_1); break;
    case 2: ui->label_seconds->setText(tic_2); break;
    case 3: ui->label_seconds->setText(tic_3); break;
    case 4: ui->label_seconds->setText(tic_4); break;
    case 5: ui->label_seconds->setText(tic_5); break;
    case 6: ui->label_seconds->setText(tic_6); break;
    default:;
    }

    ui->progressBar->setRange(0, (PLC_EP_overload_W * 133 / 100)); // 3300W --> 4500W
    ui->progressBar->setValue(PLC_EP_wattmeter_M_W);
    if (PLC_EP_wattmeter_M_W >= PLC_EP_overload_W) {
        ui->progressBar->setStyleSheet("QProgressBar { border: 2px solid black; background-color: black; } "
                                       "QProgressBar::chunk { background-color: red; height: 10px; margin: 1px; } ");
    } else if (PLC_EP_wattmeter_M_W >= (PLC_EP_overload_W * 91 / 100)) { // 3300W --> 3000W
        ui->progressBar->setStyleSheet("QProgressBar { border: 2px solid black; background-color: black; } "
                                       "QProgressBar::chunk { background-color: yellow; height: 10px; margin: 1px; } ");
    } else {
        ui->progressBar->setStyleSheet("QProgressBar { border: 2px solid black; background-color: black; } "
                                       "QProgressBar::chunk { background-color: green; height: 10px; margin: 1px; } ");
    }
}

void page4b0::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();

    updateLedLabels(ui->label_EP, ui->label_BA, ui->label_green,
                    ui->label_T5, ui->label_T6, ui->label_red,
                    ui->label_T3, ui->label_T4, ui->label_yellow_1,
                    ui->label_T1, ui->label_T2, ui->label_yellow_2);
    ui->pushButton_time->setText(PLC_nighttime ? TIME_FMT_NIGHTTIME : TIME_FMT_DAYTIME);

    if (PLC_EP_BlackoutDetected or PLC_BA_BlackoutDetected) {
        ui->label_alarm->setText("BLACKOUT");
        ui->label_alarm->setVisible(true);
    } else if (PLC_EP_OverloadDetected) {
        ui->label_alarm->setText("OVERLOAD");
        ui->label_alarm->setVisible(true);
    } else {
        ui->label_alarm->setVisible(false);
    }

    updateWidgets();
}

void page4b0::on_pushButton_trend_clicked()
{
    goto_trend_page("trend_Wall");
}

void page4b0::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page4b0::~page4b0()
{
    delete ui;
}
