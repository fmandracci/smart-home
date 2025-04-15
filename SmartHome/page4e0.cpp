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
#include "page4e0.h"
#include "ui_page4e0.h"
#include "crosstable.h"
#include "automation.h"

page4e0::page4e0(QWidget *parent) :
    page(parent),
    ui(new Ui::page4e0)
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    HeaderLeds::translateFontSize(this);
#endif
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page4e0::reload()
{
    changeWidgets();
    updateWidgets();
}

void page4e0::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();
    updateWidgets();
}

void page4e0::changeWidgets()
{
    ui->headerPanel->changeWidgets("trend_Wall.csv", EP_PIXMAP, NULL, "page4e0: EP kWh");
}

int page4e0::pointSize()
{
    int retval;

    if (mectScreenWidth >= 800) {
        retval = 14;
    } else {
        retval = 9;
    }
    return retval;
}

void page4e0::updateWattmeter(QPushButton *pushButton_kWh, const QString label, int n, int value_kWh, const QColor color)
{
    int ps = pointSize();

    if (PLC_EP_enabled_wattmeters >= n) {
        if (PLC_EP_wattmeters_ok & (1 << (n - 1))) {
            pushButton_kWh->setText(QString("%1 %2 kWh").arg(label).arg(value_kWh/10.0, 9, 'f', 1));
        } else {
            pushButton_kWh->setText(QString("%1 %2%3 kWh").arg(label).arg(LABEL_WARNING).arg(LABEL_NULL_kWh));
        }
        if (n == 1) {
            pushButton_kWh->setStyleSheet(COLOR_SS(color) + FONT_SS_B(ps) + BORDER_SS(color));
        } else {
            pushButton_kWh->setStyleSheet(COLOR_SS(color) + FONT_SS_N(ps) + BORDER_SS(color));
        }
        pushButton_kWh->setVisible(true);
    } else {
        pushButton_kWh->setVisible(false);
    }
}

void page4e0::updateWidgets()
{
    ui->headerPanel->updateWidgets();

    updateWattmeter(ui->pushButton_M  , LABEL__M,  1, PLC_EP_wattmeter_M_kWh,   COLOR_01);
    updateWattmeter(ui->pushButton_M_e, LABEL__M,  1, PLC_EP_wattmeter_M_e_kWh, COLOR_01);

    updateWattmeter(ui->pushButton_F  , LABEL__F,  2, PLC_EP_wattmeter_F_kWh,   COLOR_02);
    updateWattmeter(ui->pushButton_F_e, LABEL__F,  2, PLC_EP_wattmeter_F_e_kWh, COLOR_02);

    ui->line_3->setVisible(PLC_EP_enabled_wattmeters >= 3);

    updateWattmeter(ui->pushButton_1  , LABEL_01,  3, PLC_EP_wattmeter01_kWh,   COLOR_03);
    updateWattmeter(ui->pushButton_2  , LABEL_02,  4, PLC_EP_wattmeter02_kWh,   COLOR_04);
    updateWattmeter(ui->pushButton_3  , LABEL_03,  5, PLC_EP_wattmeter03_kWh,   COLOR_05);
    updateWattmeter(ui->pushButton_4  , LABEL_04,  6, PLC_EP_wattmeter04_kWh,   COLOR_06);
    updateWattmeter(ui->pushButton_5  , LABEL_05,  7, PLC_EP_wattmeter05_kWh,   COLOR_07);

    updateWattmeter(ui->pushButton_6  , LABEL_06,  8, PLC_EP_wattmeter06_kWh,   COLOR_08);
    updateWattmeter(ui->pushButton_7  , LABEL_07,  9, PLC_EP_wattmeter07_kWh,   COLOR_09);
    updateWattmeter(ui->pushButton_8  , LABEL_08, 10, PLC_EP_wattmeter08_kWh,   COLOR_10);
    updateWattmeter(ui->pushButton_9  , LABEL_09, 11, PLC_EP_wattmeter09_kWh,   COLOR_11);
    updateWattmeter(ui->pushButton_10 , LABEL_10, 12, PLC_EP_wattmeter10_kWh,   COLOR_12);
}

void page4e0::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page4e0::~page4e0()
{
    delete ui;
}
