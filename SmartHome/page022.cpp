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
#include "page022.h"
#include "ui_page022.h"
#include "crosstable.h"

#include "automation.h"

page022::page022(QWidget *parent) :
    page(parent),
    ui(new Ui::page022)
{
    ui->setupUi(this);
#ifndef QT_KNOWS_THE_DPI_VALUE
    translateFontSize(this);
#endif

    value_ms = 0;
    status = IDLE;
}

void page022::reload()
{
    updateTimer();
    updateWidgets();
}

void page022::updateTimer()
{
    QTime time(0, 0, 0);
    QString hhmmss;

    switch (status) {
    case RUNNING:
        value_ms += timer.restart();
        // no break;
    case IDLE:
    case PAUSED:
        hhmmss = time.addMSecs(value_ms).toString("HH:mm:ss");
        break;
    default:
        hhmmss = "xx:xx:xx";
    }
    ui->label_timer->setText(hhmmss);
}

void page022::updateWidgets()
{
    updateLedLabels(ui->label_EP, ui->label_BA, ui->label_green,
                    ui->label_T5, ui->label_T6, ui->label_red,
                    ui->label_T3, ui->label_T4, ui->label_yellow_1,
                    ui->label_T1, ui->label_T2, ui->label_yellow_2);
    ui->pushButton_time->setText(PLC_nighttime ? TIME_FMT_NIGHTTIME : TIME_FMT_DAYTIME);

    switch (status) {
    case IDLE:
        ui->atcmButton_StartPause->setVisible(true);
        ui->atcmButton_Reset->setVisible(false);
        break;
    case RUNNING:
        ui->atcmButton_StartPause->setVisible(true);
        ui->atcmButton_Reset->setVisible(false);
        break;
    case PAUSED:
        ui->atcmButton_StartPause->setVisible(true);
        ui->atcmButton_Reset->setVisible(true);
        break;
    default:
        ;
    }
}

void page022::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();

    updateTimer();
    updateWidgets();
}

void page022::timerEvent(QTimerEvent *event)
{
    qDebug() << "Timer ID:" << event->timerId();
}

void page022::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

page022::~page022()
{
    delete ui;
}

void page022::on_atcmButton_StartPause_toggled(bool checked)
{
    switch (status) {
    case IDLE:
        if (checked) {
            timer.restart();
            value_ms = 0;
            status = RUNNING;
        }
        break;
    case RUNNING:
        if (not checked) {
            status = PAUSED;
        }
        break;
    case PAUSED:
        if (checked) {
            timer.restart();
            status = RUNNING;
        }
        break;
    default:
        ;
    }
}

void page022::on_atcmButton_Reset_clicked()
{
    switch (status) {
    case IDLE:
        value_ms = 0;
        break;
    case RUNNING:
        timer.restart();
        value_ms = 0;
        break;
    case PAUSED:
        value_ms = 0;
        status = IDLE;
        break;
    default:
        ;
    }
}
