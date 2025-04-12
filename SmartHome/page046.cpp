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
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page046::reload()
{
    ui->headerPanel->changeWidgets(NULL, XX_PIXMAP, "BACK", "page046 BA test");
    if (PLC_Iam_BA) {
        ui->pushButton_Test->setText("TEST");
        ui->pushButton_Test->setEnabled(true);
    } else {
        ui->pushButton_Test->setText("(test)");
        ui->pushButton_Test->setEnabled(false);
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
