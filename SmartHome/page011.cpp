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
        pointSize_ct = 12;
        pointSize_bt = 24;
    } else if (mectScreenWidth >= 800) {
        pointSize_ct = 10;
        pointSize_bt = 20;
    } else {
        pointSize_ct =  9;
        pointSize_bt = 18;
    }
    ui->label_cputemp->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(pointSize_ct));

    changeHeader(ui->pushButton_time, ui->atcmButton_home,
                 ui->label_EP, ui->label_BA, ui->label_green,
                 ui->label_T5, ui->label_T6, ui->label_red,
                 ui->label_T3, ui->label_T4, ui->label_yellow_1,
                 ui->label_T1, ui->label_T2, ui->label_yellow_2);
//    ui->headerLeds->changeHeader();
//    changeHeader(ui->pushButton_time, ui->atcmButton_home,
//                 NULL, NULL, NULL,
//                 NULL, NULL, NULL,
//                 NULL, NULL, NULL,
//                 NULL, NULL, NULL);

    QString sn("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255); border: 1px solid rgb(255, 255, 255);" + FONT_SS_N(pointSize_bt));
    QString sb("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255); border: 1px solid rgb(255, 255, 255);" + FONT_SS_B(pointSize_bt));

    ui->pushButton_11_Config->setStyleSheet(sn);
    ui->pushButton_12_Menu->setStyleSheet(sn);
    ui->pushButton_13_7M->setStyleSheet(sn);
    ui->pushButton_14_7E->setStyleSheet(sn);

    ui->pushButton_21_DST->setStyleSheet(sb);
    ui->pushButton_22_SS->setStyleSheet(sb);
    ui->pushButton_23_ARQ01->setStyleSheet(sn);
    ui->pushButton_24_MPNC->setStyleSheet(sn);

    ui->pushButton_31_DateTime->setStyleSheet(sn);
    ui->pushButton_32_Display->setStyleSheet(sn);
    ui->pushButton_33_BA->setStyleSheet(sn);
    ui->pushButton_34_MPNE_AB->setStyleSheet(sn);

    ui->pushButton_41_NetConf->setStyleSheet(sn);
    ui->pushButton_42_Info->setStyleSheet(sn);
    ui->pushButton_43_Fonts->setStyleSheet(sn);
    ui->pushButton_44_MPNE_CD->setStyleSheet(sn);

    ui->pushButton_51->setStyleSheet(sn);
    ui->pushButton_52->setStyleSheet(sn);
    ui->pushButton_53->setStyleSheet(sn);
    ui->pushButton_54_TPAC1007->setStyleSheet(sn);
}

void page011::updateWidgets()
{
    updateLedLabels(ui->label_EP, ui->label_BA, ui->label_green,
                    ui->label_T5, ui->label_T6, ui->label_red,
                    ui->label_T3, ui->label_T4, ui->label_yellow_1,
                    ui->label_T1, ui->label_T2, ui->label_yellow_2);
    ui->label_cputemp->setText(TEMP_FMT);
    ui->pushButton_time->setText(PLC_nighttime ? TIME_FMT_NIGHTTIME : TIME_FMT_DAYTIME);
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

void page011::on_pushButton_trend_clicked()
{
    goto_trend_page("trend1.csv");
}
