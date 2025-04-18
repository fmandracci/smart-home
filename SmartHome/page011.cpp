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
#include "page011.h"
#include "ui_page011.h"
#include "crosstable.h"

#include "automation.h"

page011::page011(QWidget *parent) :
    page(parent),
    ui(new Ui::page011)
{
    ui->setupUi(this);
    TRANSLATE_FONT_SIZE(this);
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page011::reload()
{
    changeWidgets();
    updateWidgets();
}

void page011::changeWidgets()
{
    int pointSize_ct;
    int pointSize_bt;

    if (mectScreenWidth >= 1280) {
        pointSize_ct = 16;
        pointSize_bt = 24;
    } else if (mectScreenWidth >= 800) {
        pointSize_ct = 14;
        pointSize_bt = 18;
    } else {
        pointSize_ct = 10;
        pointSize_bt = 10;
    }
    ui->headerPanel->changeWidgets("trend1.csv", XX_PIXMAP, NULL, "page011 settings");

    if ((PLC_PRODUCT_ID & 0xF0000000) == 0x40000000) {
        ui->atcmLabel_cpu_temp->setVisible(true);
        ui->atcmLabel_status->setVisible(true);
        ui->atcmLabel_errors->setVisible(true);
        ui->atcmLabel_mask->setVisible(true);
    } else {
        ui->atcmLabel_cpu_temp->setVisible(false);
        ui->atcmLabel_status->setVisible(false);
        ui->atcmLabel_errors->setVisible(false);
        ui->atcmLabel_mask->setVisible(false);
    }
    QString sn("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255); border: 1px solid rgb(255, 255, 255);" + FONT_SS_B(pointSize_bt));
    QString sb("background-color: rgb(0, 0, 0); color: rgb(255,  85,   0); border: 1px solid rgb(255,  85,   0);" + FONT_SS_B(pointSize_bt));
    QString sx("background-color: rgb(0, 0, 0); color: rgb(127, 127, 127); border: 1px solid rgb(127, 127, 127);" + FONT_SS_B(pointSize_bt));

    ui->pushButton_set_home->setStyleSheet(sn);
    ui->pushButton_TPX->setStyleSheet(sx);
    ui->pushButton_TPAC1007->setStyleSheet(sx);

    ui->pushButton_Config->setStyleSheet(sn);
    ui->pushButton_Menu->setStyleSheet(sn);
    ui->pushButton_EP_7M->setStyleSheet(sx);
    ui->pushButton_EP_7E->setStyleSheet(sx);

    ui->pushButton_DateTime->setStyleSheet(sb);
    ui->pushButton_Display->setStyleSheet(sb);
    ui->pushButton_Tn_ARQ01->setStyleSheet(sx);
    ui->pushButton_XX_MPNC->setStyleSheet(sx);

    ui->pushButton_NetConf->setStyleSheet(sn);
    ui->pushButton_Info->setStyleSheet(sn);
    ui->pushButton_XX_MPNE_C->setStyleSheet(sx);
    ui->pushButton_XX_MPNE_D->setStyleSheet(sx);

    ui->pushButton_Fonts->setStyleSheet(sx);
    ui->pushButton_BA_test->setStyleSheet(sx);
    ui->pushButton_BA_MPNE_A->setStyleSheet(sx);
    ui->pushButton_BA_MPNE_B->setStyleSheet(sx);
    ui->pushButton_BA_MPNE_E->setStyleSheet(sx);

    QString cn("background-color: rgb(0, 0, 0); color: rgb(255,  85,   0);" + FONT_SS_N(pointSize_ct));
    ui->atcmLabel_cpu_temp->setStyleSheet(cn);
    ui->atcmLabel_status->setStyleSheet(cn);
    ui->atcmLabel_errors->setStyleSheet(cn);
    ui->atcmLabel_mask->setStyleSheet(cn);
}

void page011::updateWidgets()
{
    ui->headerPanel->updateWidgets();
}

void page011::updateData()
{
    if (this->isVisible() == false)
    {
        return;
    }
    page::updateData();
    updateWidgets();
}

void page011::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page011::~page011()
{
    delete ui;
}
