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
#include "page401.h"
#include "ui_page401.h"
#include "crosstable.h"

#include "automation.h"

page401::page401(QWidget *parent) :
    page(parent),
    ui(new Ui::page401)
{
    ui->setupUi(this);
    TRANSLATE_FONT_SIZE(this);
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page401::reload()
{
    QSettings home_ini(HOME_INI_FILE, QSettings::IniFormat);
    home_ini.setIniCodec("UTF-8");

    switch (currentWattmeter) {
    case  1: changeWidgets( 1, LABEL__M, "trend_W-M.csv", home_ini.value("EP/meter__M").toString(), COLOR_01, "PLC_EP_wattmeter_M_W", "PLC_EP_wattmeter_M_var", "PLC_EP_wattmeter_M_VA", "PLC_EP_wattmeter_M_kWh"); break;
    case  2: changeWidgets( 2, LABEL__F, "trend_W-F.csv", home_ini.value("EP/meter__F").toString(), COLOR_02, "PLC_EP_wattmeter_F_W", "PLC_EP_wattmeter_F_var", "PLC_EP_wattmeter_F_VA", "PLC_EP_wattmeter_F_kWh"); break;
    case  3: changeWidgets( 3, LABEL_01, "trend_W01.csv", home_ini.value("EP/meter_01").toString(), COLOR_03, "PLC_EP_wattmeter01_W", "PLC_EP_wattmeter01_var", "PLC_EP_wattmeter01_VA", "PLC_EP_wattmeter01_kWh"); break;
    case  4: changeWidgets( 4, LABEL_02, "trend_W02.csv", home_ini.value("EP/meter_02").toString(), COLOR_04, "PLC_EP_wattmeter02_W", "PLC_EP_wattmeter02_var", "PLC_EP_wattmeter02_VA", "PLC_EP_wattmeter02_kWh"); break;
    case  5: changeWidgets( 5, LABEL_03, "trend_W03.csv", home_ini.value("EP/meter_03").toString(), COLOR_05, "PLC_EP_wattmeter03_W", "PLC_EP_wattmeter03_var", "PLC_EP_wattmeter03_VA", "PLC_EP_wattmeter03_kWh"); break;
    case  6: changeWidgets( 6, LABEL_04, "trend_W04.csv", home_ini.value("EP/meter_04").toString(), COLOR_06, "PLC_EP_wattmeter04_W", "PLC_EP_wattmeter04_var", "PLC_EP_wattmeter04_VA", "PLC_EP_wattmeter04_kWh"); break;
    case  7: changeWidgets( 7, LABEL_05, "trend_W05.csv", home_ini.value("EP/meter_05").toString(), COLOR_07, "PLC_EP_wattmeter05_W", "PLC_EP_wattmeter05_var", "PLC_EP_wattmeter05_VA", "PLC_EP_wattmeter05_kWh"); break;
    case  8: changeWidgets( 8, LABEL_06, "trend_W06.csv", home_ini.value("EP/meter_06").toString(), COLOR_08, "PLC_EP_wattmeter06_W", "PLC_EP_wattmeter06_var", "PLC_EP_wattmeter06_VA", "PLC_EP_wattmeter06_kWh"); break;
    case  9: changeWidgets( 9, LABEL_07, "trend_W07.csv", home_ini.value("EP/meter_07").toString(), COLOR_09, "PLC_EP_wattmeter07_W", "PLC_EP_wattmeter07_var", "PLC_EP_wattmeter07_VA", "PLC_EP_wattmeter07_kWh"); break;
    case 10: changeWidgets(10, LABEL_08, "trend_W08.csv", home_ini.value("EP/meter_08").toString(), COLOR_10, "PLC_EP_wattmeter08_W", "PLC_EP_wattmeter08_var", "PLC_EP_wattmeter08_VA", "PLC_EP_wattmeter08_kWh"); break;
    case 11: changeWidgets(11, LABEL_09, "trend_W09.csv", home_ini.value("EP/meter_09").toString(), COLOR_11, "PLC_EP_wattmeter09_W", "PLC_EP_wattmeter09_var", "PLC_EP_wattmeter09_VA", "PLC_EP_wattmeter09_kWh"); break;
    case 12: changeWidgets(12, LABEL_10, "trend_W10.csv", home_ini.value("EP/meter_10").toString(), COLOR_12, "PLC_EP_wattmeter10_W", "PLC_EP_wattmeter10_var", "PLC_EP_wattmeter10_VA", "PLC_EP_wattmeter10_kWh"); break;
    default: ;
    }
}

void page401::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();
    ui->headerPanel->updateWidgets();
}

void page401::changeWidgets(int n, const QString t, const char *trend, const QString name, const QColor color,
                            const QString W, const QString var, const QString VA,
                            const QString kWh)
{
    // name
    ui->headerPanel->changeWidgets(trend, EP_PIXMAP, "page400", QString("page401: EP W: " + name).toLatin1().data());

    // left

    // right
    ui->label_wattmeterN->setText(t);
    ui->label_wattmeterN->setStyleSheet(QString(COLOR_SS(color) + FONT_SS_B(modulor->LARGEFont_px())));
    ui->label_wattmeterN->setMaximumWidth(modulor->tripleSize_px());

    modulor->scaleTripleButton(ui->atcmButton_next);

    // center
    ui->atcmLabel_EP_wattmeterN_W->setVariable(W);
    ui->atcmLabel_EP_wattmeterN_W->setStyleSheet(QString(FONT_SS_B(modulor->LargeFont_px())));
    ui->atcmLabel_EP_wattmeterN_W->setFontColor(color);
    ui->atcmLabel_EP_wattmeterN_W->setBorderColor(color);

    ui->atcmLabel_EP_wattmeterN_var->setVariable(var);
    ui->atcmLabel_EP_wattmeterN_var->setStyleSheet(QString(FONT_SS_B(modulor->normalFont_px())));
    ui->atcmLabel_EP_wattmeterN_var->setFontColor(color);

    ui->atcmLabel_EP_wattmeterN_A->setFontColor(color);
    ui->atcmLabel_EP_wattmeterN_A->setStyleSheet(QString(FONT_SS_B(modulor->normalFont_px())));
    ui->atcmLabel_EP_wattmeterN_A_1->setFontColor(color);
    ui->atcmLabel_EP_wattmeterN_A_1->setStyleSheet(QString(FONT_SS_B(modulor->normalFont_px())));
    ui->atcmLabel_EP_wattmeterN_A_2->setFontColor(color);
    ui->atcmLabel_EP_wattmeterN_A_2->setStyleSheet(QString(FONT_SS_B(modulor->normalFont_px())));
    ui->atcmLabel_EP_wattmeterN_A_3->setFontColor(color);
    ui->atcmLabel_EP_wattmeterN_A_3->setStyleSheet(QString(FONT_SS_B(modulor->normalFont_px())));
    if (n == 1) {
        ui->atcmLabel_EP_wattmeterN_A->setVariable("PLC_EP_wattmeter_M_A");
        ui->atcmLabel_EP_wattmeterN_A->setVisible(true);

        ui->atcmLabel_EP_wattmeterN_A_1->setVariable("PLC_EP_wattmeter_M_1_A");
        ui->atcmLabel_EP_wattmeterN_A_1->setVisible(true);

        ui->atcmLabel_EP_wattmeterN_A_2->setVariable("PLC_EP_wattmeter_M_2_A");
        ui->atcmLabel_EP_wattmeterN_A_2->setVisible(true);

        ui->atcmLabel_EP_wattmeterN_A_3->setVariable("PLC_EP_wattmeter_M_3_A");
        ui->atcmLabel_EP_wattmeterN_A_3->setVisible(true);

    } else if (n == 2) {
        ui->atcmLabel_EP_wattmeterN_A->setVariable("PLC_EP_wattmeter_F_A");
        ui->atcmLabel_EP_wattmeterN_A->setVisible(true);

        ui->atcmLabel_EP_wattmeterN_A_1->setVariable("PLC_EP_wattmeter_F_1_A");
        ui->atcmLabel_EP_wattmeterN_A_1->setVisible(true);

        ui->atcmLabel_EP_wattmeterN_A_2->setVariable("PLC_EP_wattmeter_F_2_A");
        ui->atcmLabel_EP_wattmeterN_A_2->setVisible(true);

        ui->atcmLabel_EP_wattmeterN_A_3->setVariable("PLC_EP_wattmeter_F_3_A");
        ui->atcmLabel_EP_wattmeterN_A_3->setVisible(true);

    } else {
        ui->atcmLabel_EP_wattmeterN_A->setVisible(false);
        ui->atcmLabel_EP_wattmeterN_A_1->setVisible(false);
        ui->atcmLabel_EP_wattmeterN_A_2->setVisible(false);
        ui->atcmLabel_EP_wattmeterN_A_3->setVisible(false);
    }

    ui->atcmLabel_EP_wattmeterN_VA->setVariable(VA);
    ui->atcmLabel_EP_wattmeterN_VA->setStyleSheet(QString(FONT_SS_B(modulor->normalFont_px())));
    ui->atcmLabel_EP_wattmeterN_VA->setFontColor(color);

    ui->atcmLabel_EP_wattmeterN_kWh->setVariable(kWh);
    ui->atcmLabel_EP_wattmeterN_kWh->setStyleSheet(QString(FONT_SS_B(modulor->largeFont_px())));
    ui->atcmLabel_EP_wattmeterN_kWh->setFontColor(color);
    ui->atcmLabel_EP_wattmeterN_kWh->setBorderColor(color);

    ui->atcmLabel_EP_wattmeterN_e_kWh->setStyleSheet(QString(FONT_SS_B(modulor->largeFont_px())));
    ui->atcmLabel_EP_wattmeterN_e_kWh->setFontColor(color);
    ui->atcmLabel_EP_wattmeterN_e_kWh->setBorderColor(color);
    if (n == 1) {
        ui->atcmLabel_EP_wattmeterN_e_kWh->setVariable("PLC_EP_wattmeter_M_e_kWh");
        ui->atcmLabel_EP_wattmeterN_e_kWh->setVisible(true);
    } else if (n == 2) {
        ui->atcmLabel_EP_wattmeterN_e_kWh->setVariable("PLC_EP_wattmeter_F_e_kWh");
        ui->atcmLabel_EP_wattmeterN_e_kWh->setVisible(true);
    } else {
        ui->atcmLabel_EP_wattmeterN_e_kWh->setVisible(false);
    }
}

void page401::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page401::~page401()
{
    delete ui;
}
