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
#include "page021.h"
#include "ui_page021.h"
#include "crosstable.h"

#include "automation.h"

page021::page021(QWidget *parent) :
    page(parent),
    ui(new Ui::page021)
{
    ui->setupUi(this);
    TRANSLATE_FONT_SIZE(this);
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));

    resetTimer_1(TimerValue_1);
    resetTimer_2(TimerValue_2);
    updateTimers();
    doWrite_PLC_buzzer_timer_1(false);
    doWrite_PLC_buzzer_timer_2(false);
}

void page021::reload()
{
    changeWidgets();
    updateWidgets();
}

void page021::changeWidgets()
{
    ui->headerPanel->changeWidgets(NULL, TM_PIXMAP, NULL, "page021: timer");
    updateTimers();
}

void page021::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();
    updateTimers();
    updateWidgets();
}

void page021::resetTimer_1(int value)
{
    if (TimerValue_1 != value) {
        doWrite_TimerValue_1(value);
    }
    ui->progressBar_1->setMinimum(0);
    ui->progressBar_1->setMaximum(value);

    value_1_ms = value;
    status_1 = IDLE;
    doWrite_PLC_buzzer_timer_1(false);

    ui->atcmButtonStartStop_1->blockSignals(true);
    ui->atcmButtonStartStop_1->setChecked(false);
    ui->atcmButtonStartStop_1->blockSignals(false);
}

void page021::resetTimer_2(int value)
{
    if (TimerValue_2 != value) {
        doWrite_TimerValue_2(value);
    }
    ui->progressBar_2->setMinimum(0);
    ui->progressBar_2->setMaximum(value);

    value_2_ms = value;
    status_2 = IDLE;
    doWrite_PLC_buzzer_timer_2(false);

    ui->atcmButtonStartStop_2->blockSignals(true);
    ui->atcmButtonStartStop_2->setChecked(false);
    ui->atcmButtonStartStop_2->blockSignals(false);
}

void page021::updateTimers()
{
    QTime time(0, 0, 0);

    // ----- 1 -----
    switch (status_1) {
    case RUNNING:
        value_1_ms -= timer_1.restart();
        if (value_1_ms < REFRESH_MS) {
            value_1_ms = TimerValue_1;
            status_1 = RINGING;
            doWrite_PLC_buzzer_timer_1(true);
        }
        // fall through
    case IDLE:
    case PAUSED:
        ui->pushButton_timer_1->setText(time.addMSecs(value_1_ms).toString("HH:mm:ss"));
        ui->progressBar_1->setValue(value_1_ms);
        break;
    case RINGING:
        value_1_ms += timer_1.restart();
        ui->pushButton_timer_1->setText(time.addMSecs(value_1_ms).toString("HH:mm:ss"));
        ui->progressBar_1->setValue(TimerValue_1);
        status_1 = RINGING_BIS;
        break;
    case RINGING_BIS:
        value_1_ms += timer_1.restart();
        ui->pushButton_timer_1->setText(time.addMSecs(value_1_ms).toString("HH:mm:ss"));
        ui->progressBar_1->setValue(0);
        status_1 = RINGING;
        break;
    default:
        ui->pushButton_timer_1->setText("xx:xx:xx");
        ui->progressBar_1->setValue(0);
    }

    // ----- 2 -----
    switch (status_2) {
    case RUNNING:
        value_2_ms -= timer_2.restart();
        if (value_2_ms < REFRESH_MS) {
            value_2_ms = TimerValue_2;
            status_2 = RINGING;
            doWrite_PLC_buzzer_timer_2(true);
        }
        // fall through
    case IDLE:
    case PAUSED:
        ui->pushButton_timer_2->setText(time.addMSecs(value_2_ms).toString("HH:mm:ss"));
        ui->progressBar_2->setValue(value_2_ms);
        break;
    case RINGING:
        value_2_ms += timer_2.restart();
        ui->pushButton_timer_2->setText(time.addMSecs(value_2_ms).toString("HH:mm:ss"));
        ui->progressBar_2->setValue(TimerValue_2);
        status_2 = RINGING_BIS;
        break;
    case RINGING_BIS:
        value_2_ms += timer_2.restart();
        ui->pushButton_timer_2->setText(time.addMSecs(value_2_ms).toString("HH:mm:ss"));
        ui->progressBar_2->setValue(0);
        status_2 = RINGING;
        break;
    default:
        ui->pushButton_timer_2->setText("xx:xx:xx");
        ui->progressBar_2->setValue(0);
    }
}

void page021::updateWidgets()
{
    ui->headerPanel->updateWidgets();

    // ----- 1 -----
    switch (status_1) {
    case IDLE:
        ui->atcmButtonStartStop_1->setVisible(true);
        ui->pushButton_timer_1->setEnabled(true);
        ui->atcmButtonReset_1->setVisible(false);
        break;
    case RUNNING:
        ui->atcmButtonStartStop_1->setVisible(true);
        ui->pushButton_timer_1->setEnabled(false);
        ui->atcmButtonReset_1->setVisible(false);
        break;
    case PAUSED:
        ui->atcmButtonStartStop_1->setVisible(true);
        ui->pushButton_timer_1->setEnabled(true);
        ui->atcmButtonReset_1->setVisible(true);
        break;
    case RINGING:
    case RINGING_BIS:
        ui->atcmButtonStartStop_1->setVisible(false);
        ui->pushButton_timer_1->setEnabled(false);
        ui->atcmButtonReset_1->setVisible(true);
        break;
    default:
        ;
    }

    // ----- 2 -----
    switch (status_2) {
    case IDLE:
        ui->atcmButtonStartStop_2->setVisible(true);
        ui->pushButton_timer_2->setEnabled(true);
        ui->atcmButtonReset_2->setVisible(false);
        break;
    case RUNNING:
        ui->atcmButtonStartStop_2->setVisible(true);
        ui->pushButton_timer_2->setEnabled(false);
        ui->atcmButtonReset_2->setVisible(false);
        break;
    case PAUSED:
        ui->atcmButtonStartStop_2->setVisible(true);
        ui->pushButton_timer_2->setEnabled(true);
        ui->atcmButtonReset_2->setVisible(true);
        break;
    case RINGING:
    case RINGING_BIS:
        ui->atcmButtonStartStop_2->setVisible(false);
        ui->pushButton_timer_2->setEnabled(false);
        ui->atcmButtonReset_2->setVisible(true);\
        break;
    default:
        ;
    }
}

void page021::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

page021::~page021()
{
    delete ui;
}

void page021::on_atcmButtonStartStop_1_toggled(bool checked)
{
    switch (status_1) {
    case IDLE:
        if (checked) {
            timer_1.restart();
            value_1_ms = TimerValue_1;
            status_1 = RUNNING;
        }
        break;
    case RUNNING:
        if (not checked) {
            status_1 = PAUSED;
        }
        break;
    case PAUSED:
        if (checked) {
            timer_1.restart();
            status_1 = RUNNING;
        }
        break;
    case RINGING:
    case RINGING_BIS:
    default:
        ;
    }
}

void page021::on_atcmButtonStartStop_2_toggled(bool checked)
{
    switch (status_2) {
    case IDLE:
        if (checked) {
            timer_2.restart();
            value_2_ms = TimerValue_2;
            status_2 = RUNNING;
        }
        break;
    case RUNNING:
        if (not checked) {
            status_2 = PAUSED;
        }
        break;
    case PAUSED:
        if (checked) {
            timer_2.restart();
            status_2 = RUNNING;
        }
        break;
    case RINGING:
    case RINGING_BIS:
    default:
        ;
    }
}

void page021::on_atcmButtonReset_1_clicked()
{
    switch (status_1) {
    case RUNNING:
        value_1_ms = TimerValue_1;
        timer_1.restart();
        break;
    case IDLE:
    case PAUSED:
    case RINGING:
    case RINGING_BIS:
        resetTimer_1(TimerValue_1);
        break;
    default:
        ;
    }
}

void page021::on_atcmButtonReset_2_clicked()
{
    switch (status_2) {
    case RUNNING:
        value_2_ms = TimerValue_2;
        timer_2.restart();
        break;
    case IDLE:
    case PAUSED:
    case RINGING:
    case RINGING_BIS:
        resetTimer_2(TimerValue_2);
        break;
    default:
        ;
    }
}

void page021::on_pushButton_timer_1_clicked()
{
    numpad * numPad;
    int minValue = 1;
    int maxValue = 235959;
    int value = value_1_ms / 1000; // not TimerValue_1
    int hh = value / 3600;
    int mm = (value % 3600) / 60;
    int ss = (value % 3600) % 60;
    int defvalue = hh * 10000 + mm * 100 + ss;

    numPad = new numpad(&value, defvalue, minValue, maxValue);
    numPad->showFullScreen();
    if (numPad->exec() == QDialog::Accepted) {
        hh = value / 10000;
        mm = (value % 10000) / 100;
        ss = (value % 10000) % 100;

        if (hh > 23) {
            hh = 23;
        }
        if (mm > 59) {
            mm = 59;
        }
        if (ss > 59) {
            ss = 59;
        }
        resetTimer_1((hh * 3600 + mm * 60 + ss) * 1000);
        updateTimers();
    }
}

void page021::on_pushButton_timer_2_clicked()
{
    numpad * numPad;
    int minValue = 1;
    int maxValue = 235959;
    int value = value_2_ms / 1000; // not TimerValue_2
    int hh = value / 3600;
    int mm = (value % 3600) / 60;
    int ss = (value % 3600) % 60;
    int defvalue = hh * 10000 + mm * 100 + ss;

    numPad = new numpad(&value, defvalue, minValue, maxValue);
    numPad->showFullScreen();
    if (numPad->exec() == QDialog::Accepted) {
        hh = value / 10000;
        mm = (value % 10000) / 100;
        ss = (value % 10000) % 100;

        if (hh > 23) {
            hh = 23;
        }
        if (mm > 59) {
            mm = 59;
        }
        if (ss > 59) {
            ss = 59;
        }
        resetTimer_2((hh * 3600 + mm * 60 + ss) * 1000);
        updateTimers();
    }
}
