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
#include "page046.h"
#include "ui_page046.h"
#include "crosstable.h"

#include "automation.h"

page046::page046(QWidget *parent) :
    page(parent),
    ui(new Ui::page046)
{
    ui->setupUi(this);
    TRANSLATE_FONT_SIZE(this);
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page046::reload()
{
    ui->headerPanel->changeWidgets(NULL, XX_PIXMAP, "BACK", "page046 BA test");

    QString atcmss = QString("QLabel, ATCMcombobox, ATCMlabel, ATCMbutton { %1 }\n").arg(FONT_SS_N(modulor->normalFont_px()))
                   + QString("ATCMled { %1 }\n").arg(FONT_SS_N(modulor->normalFont_px()));
    ui->frame->setStyleSheet(atcmss);

    if (PLC_Iam_BA) {
        ui->pushButton_Test->setText("TEST");
        ui->pushButton_Test->setEnabled(true);
    } else {
        ui->pushButton_Test->setText("(test)");
        ui->pushButton_Test->setEnabled(false);
    }

    QSize iconSize(modulor->normalFont_px(), modulor->normalFont_px());
    ui->atcmButton_BA_led_green->setIconSize(iconSize);
    ui->atcmButton_BA_led_red->setIconSize(iconSize);
    ui->atcmButton_BA_led_yellow1->setIconSize(iconSize);
    ui->atcmButton_BA_led_yellow2->setIconSize(iconSize);
    ui->atcmButton_BA_siren->setIconSize(iconSize);
    ui->atcmButton_BA_relay_A->setIconSize(iconSize);
    ui->atcmButton_BA_relay_B->setIconSize(iconSize);
    ui->atcmButton_BA_relay_C->setIconSize(iconSize);

    setSensor(ui->atcmButton_DO_1, 1);
    setSensor(ui->atcmButton_DO_2, 2);
    setSensor(ui->atcmButton_DO_3, 3);
    setSensor(ui->atcmButton_DO_4, 4);
    setSensor(ui->atcmButton_DO_5, 5);
    setSensor(ui->atcmButton_DO_6, 6);
    setSensor(ui->atcmButton_DO_7, 7);
    setSensor(ui->atcmButton_DO_8, 8);

    setSensor(ui->atcmButton_DO_9, 9);
    setSensor(ui->atcmButton_DO_10, 10);
    setSensor(ui->atcmButton_DO_11, 11);
    setSensor(ui->atcmButton_DO_12, 12);
    setSensor(ui->atcmButton_DO_13, 13);
    setSensor(ui->atcmButton_DO_14, 14);
    setSensor(ui->atcmButton_DO_15, 15);
    setSensor(ui->atcmButton_DO_16, 16);

    setSensor(ui->atcmButton_DO_17, 17);
    setSensor(ui->atcmButton_DO_18, 18);
    setSensor(ui->atcmButton_DO_19, 19);
    setSensor(ui->atcmButton_DO_20, 20);
    setSensor(ui->atcmButton_DO_21, 21);
    setSensor(ui->atcmButton_DO_22, 22);
    setSensor(ui->atcmButton_DO_23, 23);
    setSensor(ui->atcmButton_DO_24, 24);

    setSensor(ui->atcmButton_DO_25, 25);
    setSensor(ui->atcmButton_DO_26, 26);
    setSensor(ui->atcmButton_DO_27, 27);
    setSensor(ui->atcmButton_DO_28, 28);
    setSensor(ui->atcmButton_DO_29, 29);
    setSensor(ui->atcmButton_DO_30, 30);
    setSensor(ui->atcmButton_DO_31, 31);
    setSensor(ui->atcmButton_DO_32, 32);
}

void page046::setSensor(ATCMbutton *button, int n)
{
    if (PLC_BA_enabled_sensors >= n)
    {
        button->setEnabled(true);
        button->setBgColor(QColor(230,230,230));
    } else {
        button->setEnabled(false);
        button->setBgColor(QColor( 32, 32, 32));
    }
}

void page046::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();
    ui->headerPanel->updateWidgets();
}

void page046::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page046::~page046()
{
    delete ui;
}


void page046::on_pushButton_Test_toggled(bool checked)
{
    if (PLC_Iam_BA) {
        beginWrite();
        if (checked) {
            addWrite_PLC_BA_command(ALARM_COMMAND_TEST);
            addWrite_SRV_BA_command(ALARM_COMMAND_TEST);
            ui->pushButton_Test->setText("OFF");
        } else {
            addWrite_PLC_BA_command(ALARM_COMMAND_DISABLE);
            addWrite_SRV_BA_command(ALARM_COMMAND_DISABLE);
            ui->pushButton_Test->setText("TEST");
        }
        endWrite();
    } else {
        if (checked)
            ui->pushButton_Test->setChecked(false);
    }
}
