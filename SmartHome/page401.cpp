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
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
}

void page401::changeWidgets(int n, const QString t, const QString name, const QColor color,
                            const QString W, const QString var, const QString VA,
                            const QString kWh)
{
    QString colorStylesheet = QString("color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue());

    // name
    ui->label_name->setText(name);
    ui->label_name->setStyleSheet(colorStylesheet);

    // left
    ui->atcmButton_prev->setFontColor(color);

    // right
    ui->label_wattmeterN->setText(t);
    ui->label_wattmeterN->setStyleSheet(colorStylesheet);
    ui->atcmButton_next->setFontColor(color);

    // center
    ui->atcmLabel_EP_wattmeterN_W->setVariable(W);
    ui->atcmLabel_EP_wattmeterN_W->setFontColor(color);
    ui->atcmLabel_EP_wattmeterN_W->setBorderColor(color);

    ui->atcmLabel_EP_wattmeterN_var->setVariable(var);
    ui->atcmLabel_EP_wattmeterN_var->setFontColor(color);

    if (n == 1) {
        ui->atcmLabel_EP_wattmeterN_A->setVariable("PLC_EP_wattmeter_M_A");
        ui->atcmLabel_EP_wattmeterN_A->setFontColor(color);
        ui->atcmLabel_EP_wattmeterN_A->setVisible(true);

        ui->atcmLabel_EP_wattmeterN_A_1->setVariable("PLC_EP_wattmeter_M_1_A");
        ui->atcmLabel_EP_wattmeterN_A_1->setFontColor(color);
        ui->atcmLabel_EP_wattmeterN_A_1->setVisible(true);

        ui->atcmLabel_EP_wattmeterN_A_2->setVariable("PLC_EP_wattmeter_M_2_A");
        ui->atcmLabel_EP_wattmeterN_A_2->setFontColor(color);
        ui->atcmLabel_EP_wattmeterN_A_2->setVisible(true);

        ui->atcmLabel_EP_wattmeterN_A_3->setVariable("PLC_EP_wattmeter_M_3_A");
        ui->atcmLabel_EP_wattmeterN_A_3->setFontColor(color);
        ui->atcmLabel_EP_wattmeterN_A_3->setVisible(true);

    } else if (n == 2) {
        ui->atcmLabel_EP_wattmeterN_A->setVariable("PLC_EP_wattmeter_F_A");
        ui->atcmLabel_EP_wattmeterN_A->setFontColor(color);
        ui->atcmLabel_EP_wattmeterN_A->setVisible(true);

        ui->atcmLabel_EP_wattmeterN_A_1->setVariable("PLC_EP_wattmeter_F_1_A");
        ui->atcmLabel_EP_wattmeterN_A_1->setFontColor(color);
        ui->atcmLabel_EP_wattmeterN_A_1->setVisible(true);

        ui->atcmLabel_EP_wattmeterN_A_2->setVariable("PLC_EP_wattmeter_F_2_A");
        ui->atcmLabel_EP_wattmeterN_A_2->setFontColor(color);
        ui->atcmLabel_EP_wattmeterN_A_2->setVisible(true);

        ui->atcmLabel_EP_wattmeterN_A_3->setVariable("PLC_EP_wattmeter_F_3_A");
        ui->atcmLabel_EP_wattmeterN_A_3->setFontColor(color);
        ui->atcmLabel_EP_wattmeterN_A_3->setVisible(true);

    } else {
        ui->atcmLabel_EP_wattmeterN_A->setVisible(false);
        ui->atcmLabel_EP_wattmeterN_A_1->setVisible(false);
        ui->atcmLabel_EP_wattmeterN_A_2->setVisible(false);
        ui->atcmLabel_EP_wattmeterN_A_3->setVisible(false);
    }

    ui->atcmLabel_EP_wattmeterN_VA->setVariable(VA);
    ui->atcmLabel_EP_wattmeterN_VA->setFontColor(color);

    ui->atcmLabel_EP_wattmeterN_kWh->setVariable(kWh);
    ui->atcmLabel_EP_wattmeterN_kWh->setFontColor(color);
    ui->atcmLabel_EP_wattmeterN_kWh->setBorderColor(color);

    if (n == 1) {
        ui->atcmLabel_EP_wattmeterN_e_kWh->setVariable("PLC_EP_wattmeter_M_e_kWh");
        ui->atcmLabel_EP_wattmeterN_e_kWh->setFontColor(color);
        ui->atcmLabel_EP_wattmeterN_e_kWh->setBorderColor(color);
        ui->atcmLabel_EP_wattmeterN_e_kWh->setVisible(true);
    } else if (n == 2) {
        ui->atcmLabel_EP_wattmeterN_e_kWh->setVariable("PLC_EP_wattmeter_F_e_kWh");
        ui->atcmLabel_EP_wattmeterN_e_kWh->setFontColor(color);
        ui->atcmLabel_EP_wattmeterN_e_kWh->setBorderColor(color);
        ui->atcmLabel_EP_wattmeterN_e_kWh->setVisible(true);
    } else {
        ui->atcmLabel_EP_wattmeterN_e_kWh->setVisible(false);
    }
}

void page401::reload()
{
    QSettings hmi_ini("/local/root/hmi.ini", QSettings::IniFormat);

    changeHeader(ui->pushButton_time, ui->atcmButton_home);
    switch (currentWattmeter) {
    case  1: changeWidgets( 1, LABEL__M, QString::fromUtf8(hmi_ini.value("EP/meter__M").toByteArray()), COLOR_01, "PLC_EP_wattmeter_M_W", "PLC_EP_wattmeter_M_var", "PLC_EP_wattmeter_M_VA", "PLC_EP_wattmeter_M_kWh"); break;
    case  2: changeWidgets( 2, LABEL__F, QString::fromUtf8(hmi_ini.value("EP/meter__F").toByteArray()), COLOR_02, "PLC_EP_wattmeter_F_W", "PLC_EP_wattmeter_F_var", "PLC_EP_wattmeter_F_VA", "PLC_EP_wattmeter_F_kWh"); break;
    case  3: changeWidgets( 3, LABEL_01, QString::fromUtf8(hmi_ini.value("EP/meter_01").toByteArray()), COLOR_03, "PLC_EP_wattmeter01_W", "PLC_EP_wattmeter01_var", "PLC_EP_wattmeter01_VA", "PLC_EP_wattmeter01_kWh"); break;
    case  4: changeWidgets( 4, LABEL_02, QString::fromUtf8(hmi_ini.value("EP/meter_02").toByteArray()), COLOR_04, "PLC_EP_wattmeter02_W", "PLC_EP_wattmeter02_var", "PLC_EP_wattmeter02_VA", "PLC_EP_wattmeter02_kWh"); break;
    case  5: changeWidgets( 5, LABEL_03, QString::fromUtf8(hmi_ini.value("EP/meter_03").toByteArray()), COLOR_05, "PLC_EP_wattmeter03_W", "PLC_EP_wattmeter03_var", "PLC_EP_wattmeter03_VA", "PLC_EP_wattmeter03_kWh"); break;
    case  6: changeWidgets( 6, LABEL_04, QString::fromUtf8(hmi_ini.value("EP/meter_04").toByteArray()), COLOR_06, "PLC_EP_wattmeter04_W", "PLC_EP_wattmeter04_var", "PLC_EP_wattmeter04_VA", "PLC_EP_wattmeter04_kWh"); break;
    case  7: changeWidgets( 7, LABEL_05, QString::fromUtf8(hmi_ini.value("EP/meter_05").toByteArray()), COLOR_07, "PLC_EP_wattmeter05_W", "PLC_EP_wattmeter05_var", "PLC_EP_wattmeter05_VA", "PLC_EP_wattmeter05_kWh"); break;
    case  8: changeWidgets( 8, LABEL_06, QString::fromUtf8(hmi_ini.value("EP/meter_06").toByteArray()), COLOR_08, "PLC_EP_wattmeter06_W", "PLC_EP_wattmeter06_var", "PLC_EP_wattmeter06_VA", "PLC_EP_wattmeter06_kWh"); break;
    case  9: changeWidgets( 9, LABEL_07, QString::fromUtf8(hmi_ini.value("EP/meter_07").toByteArray()), COLOR_09, "PLC_EP_wattmeter07_W", "PLC_EP_wattmeter07_var", "PLC_EP_wattmeter07_VA", "PLC_EP_wattmeter07_kWh"); break;
    case  0: changeWidgets(10, LABEL_08, QString::fromUtf8(hmi_ini.value("EP/meter_08").toByteArray()), COLOR_10, "PLC_EP_wattmeter08_W", "PLC_EP_wattmeter08_var", "PLC_EP_wattmeter08_VA", "PLC_EP_wattmeter08_kWh"); break;
    case 11: changeWidgets(11, LABEL_09, QString::fromUtf8(hmi_ini.value("EP/meter_09").toByteArray()), COLOR_11, "PLC_EP_wattmeter09_W", "PLC_EP_wattmeter09_var", "PLC_EP_wattmeter09_VA", "PLC_EP_wattmeter09_kWh"); break;
    case 12: changeWidgets(12, LABEL_10, QString::fromUtf8(hmi_ini.value("EP/meter_10").toByteArray()), COLOR_12, "PLC_EP_wattmeter10_W", "PLC_EP_wattmeter10_var", "PLC_EP_wattmeter10_VA", "PLC_EP_wattmeter10_kWh"); break;
    default: ;
    }
}

void page401::updateData()
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

void page401::on_pushButton_plot_clicked()
{
    goto_page("page402", true);
}

void page401::on_pushButton_trend_clicked()
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

