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

#include "headerpanel.h"
#include "ui_headerpanel.h"

#include "automation.h"
#include "crosstable.h"

HeaderPanel::HeaderPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderPanel),
    pparent((page *)parent),
    trend()
{
    ui->setupUi(this);
    TRANSLATE_FONT_SIZE(this);
}

bool HeaderPanel::goto_page(const char *page, bool remember)
{
    emit newPage(page, remember);
    return true;
}

void HeaderPanel::changeWidgets(const char *trend, const char *icon, const char *back, const char *title)
{
    ui->header_leds->changeWidgets();

    ui->header_leds->scaleButton(ui->pushButton_mute);
    ui->header_leds->scaleButton(ui->pushButton_trend);

    ui->pushButton_time->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(ui->header_leds->timeFont_px()));
    ui->pushButton_time->setMaximumHeight(ui->header_leds->timeHeight_px());

    ui->label_title->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_N(ui->header_leds->titleFont_px()));
    ui->label_title->setMaximumHeight(ui->header_leds->titleHeight_px());

    ui->header_leds->scaleIconLabel(ui->label_icon);
    ui->header_leds->scaleButton(ui->atcmButton_back);

    ui->atcmButton_home->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(ui->header_leds->timeFont_px()));
    ui->atcmButton_home->setMaximumWidth(ui->header_leds->ledsWidth_px());
    ui->atcmButton_home->setMaximumHeight(ui->header_leds->ledsHeight_px());

    if (trend)
        HeaderPanel::trend = trend;
    else
        ui->pushButton_trend->setVisible(false);
    if (icon)
        ui->label_icon->setPixmap(QPixmap(icon));
    else
        ui->label_icon->setVisible(false);
    if (back)
        ui->atcmButton_back->setPageName(back);
    else
        ui->atcmButton_back->setVisible(false);
    if (title)
        ui->label_title->setText(title);
    else
        ui->label_title->setVisible(false);
}

void HeaderPanel::updateWidgets(const QString datetime)
{
    ui->header_leds->updateWidgets();

    if (datetime != NULL)
        ui->pushButton_time->setText(datetime);
    else
        ui->pushButton_time->setText(PLC_nighttime ? TIME_FMT_NIGHTTIME : TIME_FMT_DAYTIME);

    if (PLC_BA_BlackoutDetected || PLC_EP_BlackoutDetected) { // NB: no || PLC_EP_OverloadDetected
        ui->pushButton_mute->setVisible(true);
    } else {
        ui->pushButton_mute->setVisible(false);
        if (ui->pushButton_mute->isChecked()) {
            ui->pushButton_mute->setChecked(false);
        }
        if (PLC_mute_BlackoutDetected) {
            doWrite_PLC_mute_BlackoutDetected(0);
        }
    }
}

void HeaderPanel::on_pushButton_mute_toggled(bool checked)
{
    if (checked) {
        doWrite_PLC_mute_BlackoutDetected(1);
    } else {
        doWrite_PLC_mute_BlackoutDetected(0);
    }
}

HeaderPanel::~HeaderPanel()
{
    delete ui;
}
