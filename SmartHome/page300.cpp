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
#include "page300.h"
#include "ui_page300.h"
#include "crosstable.h"

#include "automation.h"

page300::page300(QWidget *parent) :
    page(parent),
    ui(new Ui::page300)
{
    ui->setupUi(this);
#ifndef QT_KNOWS_THE_DPI_VALUE
    translateFontSize(this);
#endif
}

void page300::setupRelay(QPushButton *button, QLabel *label, int n)
{
    button->setVisible(abs(PLC_EP_enabled_relays) >= n);
    label->setVisible(abs(PLC_EP_enabled_relays) >= n);
}

void page300::reload()
{
    QSettings hmi_ini("/local/root/hmi.ini", QSettings::IniFormat);

    if (PLC_EP_enabled_relays > 0) {
        ui->label->setText(QString("%1 n.o. relays, with manual activation / deactivation").arg(PLC_EP_enabled_relays));
    } else if (PLC_EP_enabled_relays < 0) {
        ui->label->setText(QString("%1 n.c. relays, with overload cutoff and manual rearm").arg(PLC_EP_enabled_relays));
    } else {
        ui->label->setText("no enabled relays");
    }

    ui->label_EP_relay_A->setText(hmi_ini.value("EP/relay_A").toString());
    ui->label_EP_relay_B->setText(hmi_ini.value("EP/relay_B").toString());
    ui->label_EP_relay_C->setText(hmi_ini.value("EP/relay_C").toString());
    ui->label_EP_relay_D->setText(hmi_ini.value("EP/relay_D").toString());

    ui->label_EP_relay_E->setText(hmi_ini.value("EP/relay_E").toString());
    ui->label_EP_relay_F->setText(hmi_ini.value("EP/relay_F").toString());
    ui->label_EP_relay_G->setText(hmi_ini.value("EP/relay_G").toString());
    ui->label_EP_relay_H->setText(hmi_ini.value("EP/relay_H").toString());

    setupRelay(ui->pushButton_EP_relay_A, ui->label_EP_relay_A, 1);
    setupRelay(ui->pushButton_EP_relay_B, ui->label_EP_relay_B, 2);
    setupRelay(ui->pushButton_EP_relay_C, ui->label_EP_relay_C, 3);
    setupRelay(ui->pushButton_EP_relay_D, ui->label_EP_relay_D, 4);
    ui->line_1->setVisible(abs(PLC_EP_enabled_relays) >= 5);
    setupRelay(ui->pushButton_EP_relay_E, ui->label_EP_relay_E, 5);
    setupRelay(ui->pushButton_EP_relay_F, ui->label_EP_relay_F, 6);
    setupRelay(ui->pushButton_EP_relay_G, ui->label_EP_relay_G, 7);
    setupRelay(ui->pushButton_EP_relay_H, ui->label_EP_relay_H, 8);
}

void page300::updateRelay(QPushButton *button, int n, int value)
{
    if (abs(PLC_EP_enabled_relays) >= n) {
        if (value != button->isChecked()) {
            bool x = button->blockSignals(true);
            {
                button->setChecked(value);
            }
            button->blockSignals(x);
        }
        button->setVisible(true);
    } else {
        button->setVisible(false);
    }
}

void page300::updateData()
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

    updateRelay(ui->pushButton_EP_relay_A, 1, PLC_EP_relay_A);
    updateRelay(ui->pushButton_EP_relay_B, 2, PLC_EP_relay_B);
    updateRelay(ui->pushButton_EP_relay_C, 3, PLC_EP_relay_C);
    updateRelay(ui->pushButton_EP_relay_D, 4, PLC_EP_relay_D);
    updateRelay(ui->pushButton_EP_relay_E, 5, PLC_EP_relay_E);
    updateRelay(ui->pushButton_EP_relay_F, 6, PLC_EP_relay_F);
    updateRelay(ui->pushButton_EP_relay_G, 7, PLC_EP_relay_G);
    updateRelay(ui->pushButton_EP_relay_H, 8, PLC_EP_relay_H);
}

void page300::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page300::~page300()
{
    delete ui;
}

