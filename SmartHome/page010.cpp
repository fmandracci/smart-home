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
#include "page010.h"
#include "ui_page010.h"
#include "crosstable.h"

#include "automation.h"

page010::page010(QWidget *parent) :
    page(parent),
    ui(new Ui::page010)
{
    ui->setupUi(this);
    TRANSLATE_FONT_SIZE(this);
}

void page010::reload()
{
    changeWidgets();
    updateWidgets();
}

void page010::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();
    updateWidgets();
}

void page010::changeWidgets()
{
    ui->header_leds->changeWidgets();

    modulor->scaleTripleButton(ui->atcmButton_mute);

    ui->pushButton_time->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(modulor->LARGEFont_px()));
    ui->pushButton_time->setMaximumHeight(modulor->tripleSize_px());

    ui->label_title->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_N(modulor->normalFont_px()));
    ui->label_title->setMaximumHeight(modulor->quadrupleSize_px());

    modulor->scaleTripleButton(ui->pushButton_home);

    ui->label_versions->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_N(modulor->smallFont_px()));
    ui->label_versions->setMinimumWidth(modulor->tripleSize_px());
    ui->label_versions->setMaximumWidth(modulor->tripleSize_px());

    if (PLC_ConfigPassword) {
        ui->atcmButton_settings->setPasswordVar("PLC_ConfigPassword");
    } else {
        ui->atcmButton_settings->setPasswordVar("");
    }
    if (PLC_BA_password) {
        ui->atcmButton_BA->setPasswordVar("PLC_BA_password");
    } else {
        ui->atcmButton_BA->setPasswordVar("");
    }

    modulor->scaleMainButton(ui->atcmButton_Tn_thermo);
    if (PLC_Tn_count >= 1) {
        ui->atcmButton_Tn_thermo->setEnabled(true);
        ui->atcmButton_Tn_thermo->setBorderColor(QColor(255,128,  0));
        if (PLC_Tn_count >= 2) {
            ui->atcmButton_Tn_thermo->setPageName("page100");
        } else {
            currentThermostat = 1;
            ui->atcmButton_Tn_thermo->setPageName("page101a");
        }
    } else {
        ui->atcmButton_Tn_thermo->setEnabled(false);
        ui->atcmButton_Tn_thermo->setBorderColor(QColor( 64, 64, 64));
    }

    modulor->scaleMainButton(ui->atcmButton_Tn_lamps);
    if (PLC_Tn_count >= 1 and (PLC_T1_enabled_lamps + PLC_T2_enabled_lamps + PLC_T3_enabled_lamps + PLC_T4_enabled_lamps + PLC_T5_enabled_lamps + PLC_T6_enabled_lamps) >= 1) {
        ui->atcmButton_Tn_lamps->setEnabled(true);
        ui->atcmButton_Tn_lamps->setBorderColor(QColor(  0,255,  0));
    } else {
        ui->atcmButton_Tn_lamps->setEnabled(false);
        ui->atcmButton_Tn_lamps->setBorderColor(QColor( 64, 64, 64));
    }

    modulor->scaleMainButton(ui->atcmButton_timers);

    modulor->scaleMainButton(ui->atcmButton_EP_wattmeters);
    if (PLC_EP_exists) {
        ui->atcmButton_EP_wattmeters->setEnabled(true);
        ui->atcmButton_EP_wattmeters->setBorderColor(QColor(255,  0,  0));
    } else {
        ui->atcmButton_EP_wattmeters->setEnabled(false);
        ui->atcmButton_EP_wattmeters->setBorderColor(QColor( 64, 64, 64));
    }

    modulor->scaleMainButton(ui->atcmButton_settings);

    modulor->scaleMainButton(ui->atcmButton_EP_relays);
    if (PLC_EP_exists and abs(PLC_EP_enabled_relays) >= 1) {
        ui->atcmButton_EP_relays->setEnabled(true);
        ui->atcmButton_EP_relays->setBorderColor(QColor(255,255,  0));
    } else {
        ui->atcmButton_EP_relays->setEnabled(false);
        ui->atcmButton_EP_relays->setBorderColor(QColor( 64, 64, 64));
    }

    modulor->scaleMainButton(ui->atcmButton_BA);
    if (PLC_BA_exists) {
        ui->atcmButton_BA->setEnabled(true);
        ui->atcmButton_BA->setBorderColor(QColor(128,  0,255));
    } else {
        ui->atcmButton_BA->setEnabled(false);
        ui->atcmButton_BA->setBorderColor(QColor( 64, 64, 64));
    }
}

void page010::updateWidgets()
{
    ui->header_leds->updateWidgets();
    ui->pushButton_time->setText(PLC_nighttime ? TIME_FMT_NIGHTTIME : TIME_FMT_DAYTIME);

    ui->label_versions->setText(QString("%1\n%2_%3\n%4_%5\n%6")
        .arg(PLC_PRODUCT_ID, 8, 16)
        .arg((PLC_HMI_Version / 100) / 10.0, 1, 'f', 1).arg(PLC_HMI_Version % 100, 2, 10, QLatin1Char('0'))
        .arg((PLC_PLC_Version / 100) / 10.0, 1, 'f', 1).arg(PLC_PLC_Version % 100, 2, 10, QLatin1Char('0'))
        .arg(PLC_control_type)
        .toUpper()
        );

    if (PLC_BA_BlackoutDetected || PLC_EP_BlackoutDetected) { // NB: no || PLC_EP_OverloadDetected
        ui->atcmButton_mute->setEnabled(true);
    } else {
        ui->atcmButton_mute->setEnabled(false);
        if (PLC_mute_BlackoutDetected) {
            doWrite_PLC_mute_BlackoutDetected(0);
        }
    }
}

void page010::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page010::~page010()
{
    delete ui;
}
