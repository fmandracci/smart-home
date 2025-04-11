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
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
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
        pointSize_bt = 20;
    } else {
        pointSize_ct = 10;
        pointSize_bt = 12;
    }
    ui->headerPanel->changeWidgets("trend1.csv", NULL, NULL, "page011");

    QString sn("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255); border: 1px solid rgb(255, 255, 255);" + FONT_SS_N(pointSize_bt));
    QString sb("background-color: rgb(0, 0, 0); color: rgb(255,  85,   0); border: 1px solid rgb(255, 255, 255);" + FONT_SS_B(pointSize_bt));

    ui->pushButton_11_set_home->setStyleSheet(sn);
    ui->pushButton_12_set_tp->setStyleSheet(sn);
    ui->pushButton_13_7M->setStyleSheet(sn);
    ui->pushButton_14_7E->setStyleSheet(sn);

    ui->pushButton_21_Config->setStyleSheet(sn);
    ui->pushButton_22_Menu->setStyleSheet(sn);
    ui->pushButton_23_ARQ01->setStyleSheet(sn);
    ui->pushButton_24_MPNC->setStyleSheet(sn);

    ui->pushButton_31_DST->setStyleSheet(sb);
    ui->pushButton_32_SS->setStyleSheet(sb);
    ui->pushButton_33_BA->setStyleSheet(sn);
    ui->pushButton_34_MPNE_AB->setStyleSheet(sn);

    ui->pushButton_41_DateTime->setStyleSheet(sn);
    ui->pushButton_42_Display->setStyleSheet(sn);
    ui->pushButton_43_Fonts->setStyleSheet(sn);
    ui->pushButton_44_MPNE_CD->setStyleSheet(sn);

    ui->pushButton_51_NetConf->setStyleSheet(sn);
    ui->pushButton_52_Info->setStyleSheet(sn);
    ui->pushButton_53_TPX->setStyleSheet(sn);
    ui->pushButton_54_TPAC1007->setStyleSheet(sn);

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
