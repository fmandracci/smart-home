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
#include "page400.h"
#include "ui_page400.h"
#include "crosstable.h"
#include "automation.h"

#include <QScreen>

page400::page400(QWidget *parent) :
    page(parent),
    ui(new Ui::page400)
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif

    pointSize = 9;
}

void page400::reload()
{
#ifdef Q_WS_QWS
    if (mectScreenWidth >= 800) {
        pointSize = 14;
    } else {
        pointSize = 9;
    }
#else
    pointSize = 14;
#endif
    changeWidgets();
    updateWidgets();
}

void page400::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();

    updateWidgets();
}

void page400::changeWidgets()
{
    QSettings hmi_ini("/local/root/hmi.ini", QSettings::IniFormat);

    changeHeader(ui->pushButton_time, ui->atcmButton_home);

    changeWattmeterCommon(ui->label_max_assigned_W, ui->label_overload_W, ui->label_M_V, ui->label_M_Hz);
    changeWattmeterFull(QString::fromUtf8(hmi_ini.value("EP/meter__M").toByteArray()),  1, COLOR_01, ui->pushButton_M_W,
                        ui->label_M_pf, ui->label_M_var, ui->label_M_VA);

    ui->line->setVisible(PLC_EP_enabled_wattmeters >= 2);
    changeWattmeterFull(QString::fromUtf8(hmi_ini.value("EP/meter__F").toByteArray()),  2, COLOR_02, ui->pushButton_F_W,
                        ui->label_F_pf, ui->label_F_var, ui->label_F_VA);

    changeWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_01").toByteArray()),  3, COLOR_03, ui->pushButton01_W);
    changeWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_02").toByteArray()),  4, COLOR_04, ui->pushButton02_W);
    changeWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_03").toByteArray()),  5, COLOR_05, ui->pushButton03_W);
    changeWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_04").toByteArray()),  6, COLOR_06, ui->pushButton04_W);
    changeWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_05").toByteArray()),  7, COLOR_07, ui->pushButton05_W);

    changeWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_06").toByteArray()),  8, COLOR_08, ui->pushButton06_W);
    changeWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_07").toByteArray()),  9, COLOR_09, ui->pushButton07_W);
    changeWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_08").toByteArray()), 10, COLOR_10, ui->pushButton08_W);
    changeWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_09").toByteArray()), 11, COLOR_11, ui->pushButton09_W);
    changeWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_10").toByteArray()), 12, COLOR_12, ui->pushButton10_W);
}

void page400::changeWattmeterCommon(QLabel *label_max_assigned_W, QLabel *label_overload_W, QLabel *label_V, QLabel *label_Hz)
{
    if (PLC_EP_enabled_wattmeters >= 1) {
        label_max_assigned_W->setStyleSheet(COLOR_SS(COLOR_01) + FONT_SS_N(pointSize));
        label_overload_W->setStyleSheet(COLOR_SS(COLOR_01) + FONT_SS_N(pointSize));
        label_V->setStyleSheet(COLOR_SS(COLOR_01) + FONT_SS_N(pointSize));
        label_Hz->setStyleSheet(COLOR_SS(COLOR_01) + FONT_SS_N(pointSize));

        label_max_assigned_W->setVisible(true);
        label_overload_W->setVisible(true);
        label_V->setVisible(true);
        label_Hz->setVisible(true);
    } else {
        label_max_assigned_W->setVisible(false);
        label_overload_W->setVisible(false);
        label_V->setVisible(false);
        label_Hz->setVisible(false);
    }
}

void page400::changeWattmeterFull(QString label, int n, const QColor color,
                                  QPushButton *pushButton_W, QLabel *label_pf, QLabel *label_var, QLabel *label_VA)
{
    changeWattmeter(label, n, color, pushButton_W);
    if (PLC_EP_enabled_wattmeters >= n) {
        label_pf->setStyleSheet(COLOR_SS(color) + FONT_SS_N(pointSize));
        label_var->setStyleSheet(COLOR_SS(color) + FONT_SS_N(pointSize));
        label_VA->setStyleSheet(COLOR_SS(color) + FONT_SS_N(pointSize));

        label_pf->setVisible(true);
        label_var->setVisible(true);
        label_VA->setVisible(true);
    } else {
        label_pf->setVisible(false);
        label_var->setVisible(false);
        label_VA->setVisible(false);
    }
}

void page400::changeWattmeter(const QString label, int n, const QColor color, QPushButton *pushButton_W)
{
    if (PLC_EP_enabled_wattmeters >= n) {
        if (n <= 2) {
            pushButton_W->setStyleSheet(COLOR_SS(color) + FONT_SS_B(pointSize) + BORDER_SS(color));
        } else {
            pushButton_W->setStyleSheet(COLOR_SS(color) + FONT_SS_N(pointSize) + BORDER_SS(color));
        }
        pushButton_W->setText(QString("%1\n%2 W").arg(label).arg(LABEL_NULL_W));
        pushButton_W->setVisible(true);
    } else {
        pushButton_W->setVisible(false);
    }
}

void page400::updateWidgets()
{
    QSettings hmi_ini("/local/root/hmi.ini", QSettings::IniFormat);

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

    updateWattmeterCommon(ui->label_max_assigned_W, ui->label_overload_W, ui->label_M_V, ui->label_M_Hz, PLC_EP_max_assigned_W, PLC_EP_overload_W, PLC_EP_wattmeter_M_V, PLC_EP_wattmeter_M_Hz);
    updateWattmeterFull(QString::fromUtf8(hmi_ini.value("EP/meter__M").toByteArray()),  1, ui->pushButton_M_W, ui->label_M_pf, ui->label_M_var, ui->label_M_VA, PLC_EP_wattmeter_M_W, PLC_EP_wattmeter_M_pf, PLC_EP_wattmeter_M_var, PLC_EP_wattmeter_M_VA);

    updateWattmeterFull(QString::fromUtf8(hmi_ini.value("EP/meter__F").toByteArray()),  2, ui->pushButton_F_W, ui->label_F_pf, ui->label_F_var, ui->label_F_VA, PLC_EP_wattmeter_F_W, PLC_EP_wattmeter_F_pf, PLC_EP_wattmeter_F_var, PLC_EP_wattmeter_F_VA);

    updateWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_01").toByteArray()),  3, ui->pushButton01_W, PLC_EP_wattmeter01_W);
    updateWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_02").toByteArray()),  4, ui->pushButton02_W, PLC_EP_wattmeter02_W);
    updateWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_03").toByteArray()),  5, ui->pushButton03_W, PLC_EP_wattmeter03_W);
    updateWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_04").toByteArray()),  6, ui->pushButton04_W, PLC_EP_wattmeter04_W);
    updateWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_05").toByteArray()),  7, ui->pushButton05_W, PLC_EP_wattmeter05_W);

    updateWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_06").toByteArray()),  8, ui->pushButton06_W, PLC_EP_wattmeter06_W);
    updateWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_07").toByteArray()),  9, ui->pushButton07_W, PLC_EP_wattmeter07_W);
    updateWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_08").toByteArray()), 10, ui->pushButton08_W, PLC_EP_wattmeter08_W);
    updateWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_09").toByteArray()), 11, ui->pushButton09_W, PLC_EP_wattmeter09_W);
    updateWattmeter(QString::fromUtf8(hmi_ini.value("EP/meter_10").toByteArray()), 12, ui->pushButton10_W, PLC_EP_wattmeter10_W);
}

void page400::updateWattmeterCommon(QLabel *label_max_assigned_W, QLabel *label_overload_W, QLabel *label_V, QLabel *label_Hz,
                             int value_max_assigned_W, int value_overload_W, int value_V, int value_Hz)
{
    if (PLC_EP_enabled_wattmeters >= 1) {
        label_max_assigned_W->setText(QString("%1 %2 W").arg(LABEL_LESS_OR_EQ).arg(value_max_assigned_W));
        label_overload_W->setText(QString("%1 %2 W").arg(LABEL_LESS_OR_EQ).arg(value_overload_W));
        label_V->setText(QString("%1 V").arg(value_V/100.0, 5, 'f', 2));
        label_Hz->setText(QString("%1 Hz").arg(value_Hz/100.0, 5, 'f', 2));
    }
}

void page400::updateWattmeterFull(QString label, int n,
                                  QPushButton *pushButton_W, QLabel *label_pf, QLabel *label_var, QLabel *label_VA,
                                  int value_W, int value_pf, int value_var, int value_VA)
{
    updateWattmeter(label, n, pushButton_W, value_W);
    if (PLC_EP_enabled_wattmeters >= n) {
        label_pf->setText(QString("p.f. %1").arg(value_pf/1000.0, 5, 'f', 3));
        label_var->setText(QString("%1 var").arg(value_var));
        label_VA->setText(QString("%1 VA").arg(value_VA));
    }
}

void page400::updateWattmeter(const QString label, int n,
                              QPushButton *pushButton_W, int value_W)
{
    if (PLC_EP_enabled_wattmeters >= n) {
        if (PLC_EP_wattmeters_ok & (1 << (n - 1))) {
            pushButton_W->setText(QString("%1\n%2%3 W").arg(label).arg(LABEL_M_SPACE).arg(value_W, 5));
        } else {
            pushButton_W->setText(QString("%1\n%2%3 W").arg(label).arg(LABEL_WARNING).arg(LABEL_NULL_W));
        }
    }
}

void page400::on_pushButton_trend_clicked()
{
    goto_trend_page("trend_Wall");
}

void page400::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page400::~page400()
{
    delete ui;
}
