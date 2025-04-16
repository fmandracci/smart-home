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
    TRANSLATE_FONT_SIZE(this);
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page402::reload()
{
    ui->atcmGraph->RunStop();
    resetPLC_timeOffset();
    ui->atcmGraph->RunStop();

    ui->atcmLabel_M_W->setVariable("PLC_EP_wattmeter_M_W");
    ui->atcmLabel_M_W->setPrefix(LABEL__M + " ");

    switch (currentWattmeter) {
    case  1: changeWidgets("trend_W-M.csv", LABEL__M, "PLC_EP_wattmeter_M_W", ""                    , COLOR_01); break;
    case  2: changeWidgets("trend_W-F.csv", LABEL__F, "PLC_EP_wattmeter_F_W", "PLC_EP_wattmeter_M_W", COLOR_02); break;
    case  3: changeWidgets("trend_W01.csv", LABEL_01, "PLC_EP_wattmeter01_W", "PLC_EP_wattmeter_M_W", COLOR_03); break;
    case  4: changeWidgets("trend_W02.csv", LABEL_02, "PLC_EP_wattmeter02_W", "PLC_EP_wattmeter_M_W", COLOR_04); break;
    case  5: changeWidgets("trend_W03.csv", LABEL_03, "PLC_EP_wattmeter03_W", "PLC_EP_wattmeter_M_W", COLOR_05); break;
    case  6: changeWidgets("trend_W04.csv", LABEL_04, "PLC_EP_wattmeter04_W", "PLC_EP_wattmeter_M_W", COLOR_06); break;
    case  7: changeWidgets("trend_W05.csv", LABEL_05, "PLC_EP_wattmeter05_W", "PLC_EP_wattmeter_M_W", COLOR_07); break;
    case  8: changeWidgets("trend_W06.csv", LABEL_06, "PLC_EP_wattmeter06_W", "PLC_EP_wattmeter_M_W", COLOR_08); break;
    case  9: changeWidgets("trend_W07.csv", LABEL_07, "PLC_EP_wattmeter07_W", "PLC_EP_wattmeter_M_W", COLOR_09); break;
    case 10: changeWidgets("trend_W08.csv", LABEL_08, "PLC_EP_wattmeter08_W", "PLC_EP_wattmeter_M_W", COLOR_10); break;
    case 11: changeWidgets("trend_W09.csv", LABEL_09, "PLC_EP_wattmeter09_W", "PLC_EP_wattmeter_M_W", COLOR_11); break;
    case 12: changeWidgets("trend_W10.csv", LABEL_10, "PLC_EP_wattmeter10_W", "PLC_EP_wattmeter_M_W", COLOR_12); break;
    default: changeWidgets(NULL           ,     "??", "PLC_EP_wattmeter_M_W", "PLC_EP_wattmeter_M_W", COLOR_01);
    }
}

void page402::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();
    ui->headerPanel->updateWidgets();
}

void page402::changeWidgets(const char *trend, const QString t, const QString W, const QString M_W, const QColor color)
{
    QString colorStylesheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());

    ui->headerPanel->changeWidgets(trend, EP_PIXMAP, "page401", QString("page402: EP W " + t).toLatin1().data());

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
