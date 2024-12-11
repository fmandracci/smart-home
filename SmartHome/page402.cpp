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
#include "page402.h"
#include "ui_page402.h"
#include "crosstable.h"

#include "automation.h"

page402::page402(QWidget *parent) :
    page(parent),
    ui(new Ui::page402)
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
}

void page402::changeWidgets(const QString t, const QString W, const QString M_W, const QColor color)
{
    QString colorStylesheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());

    // left
    ui->label_wattmeterN->setText(t);
    ui->label_wattmeterN->setStyleSheet(colorStylesheet);
    ui->atcmButton_next->setFontColor(color);

    // center
    ui->atcmGraph->setY1Variable(W);
    ui->atcmGraph->setY2Variable(M_W);
    ui->atcmGraph->setY1Label("W");
    ui->atcmGraph->setY2Label("W");
    ui->atcmGraph->setStyleSheet(colorStylesheet);
    ui->atcmGraph->setToolTip("");

    // bottom
    ui->atcmLabel_W->setVariable(W);
    ui->atcmLabel_W->setPrefix(t + " ");
    ui->atcmLabel_M_W->setVariable(M_W);
}

void page402::reload()
{
    changeHeader(ui->pushButton_time, ui->atcmButton_home);
    ui->atcmGraph->RunStop();
    resetPLC_timeOffset();
    ui->atcmGraph->RunStop();

    ui->atcmLabel_M_W->setVariable("PLC_EP_wattmeter_M_W");
    ui->atcmLabel_M_W->setPrefix(LABEL__M + " ");

    switch (currentWattmeter) {
    case  1: changeWidgets(LABEL__M, "PLC_EP_wattmeter_M_W", ""                    , COLOR_01); break;
    case  2: changeWidgets(LABEL__F, "PLC_EP_wattmeter_F_W", "PLC_EP_wattmeter_M_W", COLOR_02); break;
    case  3: changeWidgets(LABEL_01, "PLC_EP_wattmeter01_W", "PLC_EP_wattmeter_M_W", COLOR_03); break;
    case  4: changeWidgets(LABEL_02, "PLC_EP_wattmeter02_W", "PLC_EP_wattmeter_M_W", COLOR_04); break;
    case  5: changeWidgets(LABEL_03, "PLC_EP_wattmeter03_W", "PLC_EP_wattmeter_M_W", COLOR_05); break;
    case  6: changeWidgets(LABEL_04, "PLC_EP_wattmeter04_W", "PLC_EP_wattmeter_M_W", COLOR_06); break;
    case  7: changeWidgets(LABEL_05, "PLC_EP_wattmeter05_W", "PLC_EP_wattmeter_M_W", COLOR_07); break;
    case  8: changeWidgets(LABEL_06, "PLC_EP_wattmeter06_W", "PLC_EP_wattmeter_M_W", COLOR_08); break;
    case  9: changeWidgets(LABEL_07, "PLC_EP_wattmeter07_W", "PLC_EP_wattmeter_M_W", COLOR_09); break;
    case 10: changeWidgets(LABEL_08, "PLC_EP_wattmeter08_W", "PLC_EP_wattmeter_M_W", COLOR_10); break;
    case 11: changeWidgets(LABEL_09, "PLC_EP_wattmeter09_W", "PLC_EP_wattmeter_M_W", COLOR_11); break;
    case 12: changeWidgets(LABEL_10, "PLC_EP_wattmeter10_W", "PLC_EP_wattmeter_M_W", COLOR_12); break;
    default: changeWidgets(    "??", "PLC_EP_wattmeter_M_W", "PLC_EP_wattmeter_M_W", COLOR_01);
    }
}

void page402::updateData()
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
}

void page402::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page402::~page402()
{
    delete ui;
}

void page402::on_pushButton_trend_clicked()
{
    switch (currentWattmeter) {
    case  1: goto_trend_page("trend_W-M.csv"); break;
    case  2: goto_trend_page("trend_W-F.csv"); break;
    case  3: goto_trend_page("trend_W01.csv"); break;
    case  4: goto_trend_page("trend_W02.csv"); break;
    case  5: goto_trend_page("trend_W03.csv"); break;
    case  6: goto_trend_page("trend_W04.csv"); break;
    case  7: goto_trend_page("trend_W05.csv"); break;
    case  8: goto_trend_page("trend_W06.csv"); break;
    case  9: goto_trend_page("trend_W07.csv"); break;
    case 10: goto_trend_page("trend_W08.csv"); break;
    case 11: goto_trend_page("trend_W09.csv"); break;
    case 12: goto_trend_page("trend_W10.csv"); break;
    default: ;
    }
}
