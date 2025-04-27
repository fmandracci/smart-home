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
    int pointSize_bt;
    int pointSize_ct;

    ui->headerPanel->changeWidgets("trend1.csv", XX_PIXMAP, NULL, "page011 settings");
    pointSize_bt = ui->headerPanel->ledSize_px();
    pointSize_ct = ui->headerPanel->titleFont_px();

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
    QString sn("background-color: rgb(0, 0, 0); color: rgb(255, 255, 255); border: 1px solid rgb(255, 255, 255); padding: 5px;" + FONT_SS_N(pointSize_bt));
    QString sb("background-color: rgb(0, 0, 0); color: rgb(255,  85,   0); border: 1px solid rgb(255,  85,   0); padding: 5px;" + FONT_SS_B(pointSize_bt));
    QString sx("background-color: rgb(0, 0, 0); color: rgb(127, 127, 127); border: 1px solid rgb(127, 127, 127); padding: 5px;" + FONT_SS_I(pointSize_bt));

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

void page011::highlightButton(QPushButton *button)
{
    int pointSize_bt = ui->headerPanel->ledSize_px();

    QString ss("background-color: rgb(255, 255, 0); color: rgb(0, 0, 0); border: 1px solid rgb(255, 255, 255); padding: 5px;" + FONT_SS_N(pointSize_bt));

    button->setStyleSheet(ss);
    button->repaint();
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

void page011::on_pushButton_set_home_clicked()  { highlightButton(ui->pushButton_set_home ); beep(100); reload(); }
void page011::on_pushButton_TPX_clicked()       { highlightButton(ui->pushButton_TPX      ); goto_page("page041" ); }
void page011::on_pushButton_TPAC1007_clicked()  { highlightButton(ui->pushButton_TPAC1007 ); goto_page("page048" ); }

void page011::on_pushButton_Config_clicked()    { highlightButton(ui->pushButton_Config   ); goto_page("page005" ); }
void page011::on_pushButton_Menu_clicked()      { highlightButton(ui->pushButton_Menu     ); goto_page("menu"    ); }
void page011::on_pushButton_EP_7M_clicked()     { highlightButton(ui->pushButton_EP_7M    ); goto_page("page043" ); }
void page011::on_pushButton_EP_7E_clicked()     { highlightButton(ui->pushButton_EP_7E    ); goto_page("page043e"); }

void page011::on_pushButton_DateTime_clicked()  { highlightButton(ui->pushButton_DateTime ); goto_page("time_set"); }
void page011::on_pushButton_Display_clicked()   { highlightButton(ui->pushButton_Display  ); goto_page("display_settings"); }
void page011::on_pushButton_Tn_ARQ01_clicked()  { highlightButton(ui->pushButton_Tn_ARQ01 ); goto_page("page044" ); }
void page011::on_pushButton_XX_MPNC_clicked()   { highlightButton(ui->pushButton_XX_MPNC  ); goto_page("page047" ); }

void page011::on_pushButton_NetConf_clicked()   { highlightButton(ui->pushButton_NetConf  ); goto_page("net_conf"); }
void page011::on_pushButton_Info_clicked()      { highlightButton(ui->pushButton_Info     ); goto_page("info"    ); }
void page011::on_pushButton_XX_MPNE_C_clicked() { highlightButton(ui->pushButton_XX_MPNE_C); goto_page("page049c" ); }
void page011::on_pushButton_XX_MPNE_D_clicked() { highlightButton(ui->pushButton_XX_MPNE_D); goto_page("page049d" ); }

void page011::on_pushButton_Fonts_clicked()     { highlightButton(ui->pushButton_Fonts    ); goto_page("page042" ); }
void page011::on_pushButton_BA_test_clicked()   { highlightButton(ui->pushButton_BA_test  ); goto_page("page046" ); }
void page011::on_pushButton_BA_MPNE_A_clicked() { highlightButton(ui->pushButton_BA_MPNE_A); goto_page("page045a" ); }
void page011::on_pushButton_BA_MPNE_B_clicked() { highlightButton(ui->pushButton_BA_MPNE_B); goto_page("page045b" ); }
void page011::on_pushButton_BA_MPNE_E_clicked() { highlightButton(ui->pushButton_BA_MPNE_E); goto_page("page045e" ); }

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
