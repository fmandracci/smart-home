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
#include "page200.h"
#include "ui_page200.h"
#include "crosstable.h"

#include "automation.h"

page200::page200(QWidget *parent) :
    page(parent),
    ui(new Ui::page200),
    LampOffIcon(QPixmap(":/icons/icons/Lamp.png")),
    LampPressIcon(QPixmap(":/icons/icons/LampGreen.png")),
    LampOnIcon(QPixmap(":/icons/icons/LampOn.png")),
    LampWarningIcon(QPixmap(":/systemicons/Error.png"))
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page200::reload()
{
    changeWidgets();
    updateWidgets();
}

void page200::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();

    updateWidgets();
}

void page200::changeWidgets()
{
    QSettings home_ini(HOME_INI_FILE, QSettings::IniFormat);

    ui->headerPanel->changeWidgets(NULL, ":/icons/icons/LampIcon.png", NULL, "page200: Tn lamps");

    changeLamps(1, COLOR_01, home_ini.value("T1/name").toString(),
                ui->label_Tn_1, PLC_T1_enabled_lamps,
                ui->pushButton_T1_lamp_1, ui->pushButton_T1_lamp_2, ui->pushButton_T1_lamp_3, ui->pushButton_T1_lamp_4, ui->pushButton_T1_lamp_5,
                ui->label_T1_1, ui->label_T1_2, ui->label_T1_3, ui->label_T1_4, ui->label_T1_5,
                home_ini.value("T1/lamp_1").toString(), home_ini.value("T1/lamp_2").toString(), home_ini.value("T1/lamp_3").toString(), home_ini.value("T1/lamp_4").toString(), home_ini.value("T1/lamp_5").toString());
    changeLamps(2, COLOR_02, home_ini.value("T2/name").toString(),
                ui->label_Tn_2, PLC_T2_enabled_lamps,
                ui->pushButton_T2_lamp_1, ui->pushButton_T2_lamp_2, ui->pushButton_T2_lamp_3, ui->pushButton_T2_lamp_4, ui->pushButton_T2_lamp_5,
                ui->label_T2_1, ui->label_T2_2, ui->label_T2_3, ui->label_T2_4, ui->label_T2_5,
                home_ini.value("T2/lamp_1").toString(), home_ini.value("T2/lamp_2").toString(), home_ini.value("T2/lamp_3").toString(), home_ini.value("T2/lamp_4").toString(), home_ini.value("T2/lamp_5").toString());
    changeLamps(3, COLOR_03, home_ini.value("T3/name").toString(),
                ui->label_Tn_3, PLC_T3_enabled_lamps,
                ui->pushButton_T3_lamp_1, ui->pushButton_T3_lamp_2, ui->pushButton_T3_lamp_3, ui->pushButton_T3_lamp_4, ui->pushButton_T3_lamp_5,
                ui->label_T3_1, ui->label_T3_2, ui->label_T3_3, ui->label_T3_4, ui->label_T3_5,
                home_ini.value("T3/lamp_1").toString(), home_ini.value("T3/lamp_2").toString(), home_ini.value("T3/lamp_3").toString(), home_ini.value("T3/lamp_4").toString(), home_ini.value("T3/lamp_5").toString());
    changeLamps(4, COLOR_04, home_ini.value("T4/name").toString(),
                ui->label_Tn_4, PLC_T4_enabled_lamps,
                ui->pushButton_T4_lamp_1, ui->pushButton_T4_lamp_2, ui->pushButton_T4_lamp_3, ui->pushButton_T4_lamp_4, ui->pushButton_T4_lamp_5,
                ui->label_T4_1, ui->label_T4_2, ui->label_T4_3, ui->label_T4_4, ui->label_T4_5,
                home_ini.value("T4/lamp_1").toString(), home_ini.value("T4/lamp_2").toString(), home_ini.value("T4/lamp_3").toString(), home_ini.value("T4/lamp_4").toString(), home_ini.value("T4/lamp_5").toString());
    changeLamps(5, COLOR_05, home_ini.value("T5/name").toString(),
                ui->label_Tn_5, PLC_T5_enabled_lamps,
                ui->pushButton_T5_lamp_1, ui->pushButton_T5_lamp_2, ui->pushButton_T5_lamp_3, ui->pushButton_T5_lamp_4, ui->pushButton_T5_lamp_5,
                ui->label_T5_1, ui->label_T5_2, ui->label_T5_3, ui->label_T5_4, ui->label_T5_5,
                home_ini.value("T5/lamp_1").toString(), home_ini.value("T5/lamp_2").toString(), home_ini.value("T5/lamp_3").toString(), home_ini.value("T5/lamp_4").toString(), home_ini.value("T5/lamp_5").toString());
    changeLamps(6, COLOR_06, home_ini.value("T6/name").toString(),
                ui->label_Tn_6, PLC_T6_enabled_lamps,
                ui->pushButton_T6_lamp_1, ui->pushButton_T6_lamp_2, ui->pushButton_T6_lamp_3, ui->pushButton_T6_lamp_4, ui->pushButton_T6_lamp_5,
                ui->label_T6_1, ui->label_T6_2, ui->label_T6_3, ui->label_T6_4, ui->label_T6_5,
                home_ini.value("T6/lamp_1").toString(), home_ini.value("T6/lamp_2").toString(), home_ini.value("T6/lamp_3").toString(), home_ini.value("T6/lamp_4").toString(), home_ini.value("T6/lamp_5").toString());

}

void page200::changeLamps(int t, const QColor color, const QString name,
                          QLabel *label_n, int enabled_lamps_t,
                          QPushButton *button_t_1, QPushButton *button_t_2, QPushButton *button_t_3, QPushButton *button_t_4, QPushButton *button_t_5,
                          QLabel *label_t_1, QLabel *label_t_2, QLabel *label_t_3, QLabel *label_t_4, QLabel *label_t_5,
                          const QString name_t_1, const QString name_t_2, const QString name_t_3, const QString name_t_4, const QString name_t_5)
{
    QString offStyleSheet = QString("color: rgb(%1, %2, %3); background-color: rgb(0, 0, 0);").arg(color.red()).arg(color.green()).arg(color.blue());

    if (t <= PLC_Tn_count and enabled_lamps_t > 0) {
        label_n->setText(name);
        label_n->setStyleSheet(offStyleSheet);
        label_n->setVisible(true);

        changeLamp(t, offStyleSheet, enabled_lamps_t, 1, button_t_1, label_t_1, name_t_1);
        changeLamp(t, offStyleSheet, enabled_lamps_t, 2, button_t_2, label_t_2, name_t_2);
        changeLamp(t, offStyleSheet, enabled_lamps_t, 3, button_t_3, label_t_3, name_t_3);
        changeLamp(t, offStyleSheet, enabled_lamps_t, 4, button_t_4, label_t_4, name_t_4);
        changeLamp(t, offStyleSheet, enabled_lamps_t, 5, button_t_5, label_t_5, name_t_5);

    } else {
        label_n->setVisible(false);
        button_t_1->setVisible(false);
        button_t_2->setVisible(false);
        button_t_3->setVisible(false);
        button_t_4->setVisible(false);
        button_t_5->setVisible(false);
        label_t_1->setVisible(false);
        label_t_2->setVisible(false);
        label_t_3->setVisible(false);
        label_t_4->setVisible(false);
        label_t_5->setVisible(false);
    }
}

void page200::changeLamp(int t, const QString colorSS, int enabled_lamps_t, int n, QPushButton *button_t_n, QLabel *label_t_n, const QString name_t_n)
{
    if (t <= PLC_Tn_count and n <= enabled_lamps_t) {
        button_t_n->setVisible(true);
        label_t_n->setStyleSheet(colorSS);
        label_t_n->setText(name_t_n);
        label_t_n->setVisible(true);
    } else {
        button_t_n->setVisible(false);
        label_t_n->setVisible(false);
    }
}

void page200::updateLamp(int t, bool isOK, int enabled_lamps_t, int n, QPushButton *button, bool feedback)
{
    if (t <= PLC_Tn_count and n <= enabled_lamps_t) {
        if (isOK) {
            button->setIcon(feedback ? LampOnIcon : LampOffIcon);
        } else {
            button->setIcon(LampWarningIcon);
        }
    }
}

void page200::updateWidgets()
{
    ui->headerPanel->updateWidgets();

    updateLamp(1, PLC_T1_isOK, PLC_T1_enabled_lamps, 1, ui->pushButton_T1_lamp_1, PLC_T1_lamp_feedback_1);
    updateLamp(1, PLC_T1_isOK, PLC_T1_enabled_lamps, 2, ui->pushButton_T1_lamp_2, PLC_T1_lamp_feedback_2);
    updateLamp(1, PLC_T1_isOK, PLC_T1_enabled_lamps, 3, ui->pushButton_T1_lamp_3, PLC_T1_lamp_feedback_3);
    updateLamp(1, PLC_T1_isOK, PLC_T1_enabled_lamps, 4, ui->pushButton_T1_lamp_4, PLC_T1_lamp_feedback_4);
    updateLamp(1, PLC_T1_isOK, PLC_T1_enabled_lamps, 5, ui->pushButton_T1_lamp_5, PLC_T1_lamp_feedback_5);

    updateLamp(2, PLC_T2_isOK, PLC_T2_enabled_lamps, 1, ui->pushButton_T2_lamp_1, PLC_T2_lamp_feedback_1);
    updateLamp(2, PLC_T2_isOK, PLC_T2_enabled_lamps, 2, ui->pushButton_T2_lamp_2, PLC_T2_lamp_feedback_2);
    updateLamp(2, PLC_T2_isOK, PLC_T2_enabled_lamps, 3, ui->pushButton_T2_lamp_3, PLC_T2_lamp_feedback_3);
    updateLamp(2, PLC_T2_isOK, PLC_T2_enabled_lamps, 4, ui->pushButton_T2_lamp_4, PLC_T2_lamp_feedback_4);
    updateLamp(2, PLC_T2_isOK, PLC_T2_enabled_lamps, 5, ui->pushButton_T2_lamp_5, PLC_T2_lamp_feedback_5);

    updateLamp(3, PLC_T2_isOK, PLC_T3_enabled_lamps, 1, ui->pushButton_T3_lamp_1, PLC_T3_lamp_feedback_1);
    updateLamp(3, PLC_T2_isOK, PLC_T3_enabled_lamps, 2, ui->pushButton_T3_lamp_2, PLC_T3_lamp_feedback_2);
    updateLamp(3, PLC_T2_isOK, PLC_T3_enabled_lamps, 3, ui->pushButton_T3_lamp_3, PLC_T3_lamp_feedback_3);
    updateLamp(3, PLC_T2_isOK, PLC_T3_enabled_lamps, 4, ui->pushButton_T3_lamp_4, PLC_T3_lamp_feedback_4);
    updateLamp(3, PLC_T2_isOK, PLC_T3_enabled_lamps, 5, ui->pushButton_T3_lamp_5, PLC_T3_lamp_feedback_5);

    updateLamp(4, PLC_T4_isOK, PLC_T4_enabled_lamps, 1, ui->pushButton_T4_lamp_1, PLC_T4_lamp_feedback_1);
    updateLamp(4, PLC_T4_isOK, PLC_T4_enabled_lamps, 2, ui->pushButton_T4_lamp_2, PLC_T4_lamp_feedback_2);
    updateLamp(4, PLC_T4_isOK, PLC_T4_enabled_lamps, 3, ui->pushButton_T4_lamp_3, PLC_T4_lamp_feedback_3);
    updateLamp(4, PLC_T4_isOK, PLC_T4_enabled_lamps, 4, ui->pushButton_T4_lamp_4, PLC_T4_lamp_feedback_4);
    updateLamp(4, PLC_T4_isOK, PLC_T4_enabled_lamps, 5, ui->pushButton_T4_lamp_5, PLC_T4_lamp_feedback_5);

    updateLamp(5, PLC_T5_isOK, PLC_T5_enabled_lamps, 1, ui->pushButton_T5_lamp_1, PLC_T5_lamp_feedback_1);
    updateLamp(5, PLC_T5_isOK, PLC_T5_enabled_lamps, 2, ui->pushButton_T5_lamp_2, PLC_T5_lamp_feedback_2);
    updateLamp(5, PLC_T5_isOK, PLC_T5_enabled_lamps, 3, ui->pushButton_T5_lamp_3, PLC_T5_lamp_feedback_3);
    updateLamp(5, PLC_T5_isOK, PLC_T5_enabled_lamps, 4, ui->pushButton_T5_lamp_4, PLC_T5_lamp_feedback_4);
    updateLamp(5, PLC_T5_isOK, PLC_T5_enabled_lamps, 5, ui->pushButton_T5_lamp_5, PLC_T5_lamp_feedback_5);

    updateLamp(6, PLC_T6_isOK, PLC_T6_enabled_lamps, 1, ui->pushButton_T6_lamp_1, PLC_T6_lamp_feedback_1);
    updateLamp(6, PLC_T6_isOK, PLC_T6_enabled_lamps, 2, ui->pushButton_T6_lamp_2, PLC_T6_lamp_feedback_2);
    updateLamp(6, PLC_T6_isOK, PLC_T6_enabled_lamps, 3, ui->pushButton_T6_lamp_3, PLC_T6_lamp_feedback_3);
    updateLamp(6, PLC_T6_isOK, PLC_T6_enabled_lamps, 4, ui->pushButton_T6_lamp_4, PLC_T6_lamp_feedback_4);
    updateLamp(6, PLC_T6_isOK, PLC_T6_enabled_lamps, 5, ui->pushButton_T6_lamp_5, PLC_T6_lamp_feedback_5);
}

void page200::on_pushButton_T1_lamp_1_clicked() { beginWrite(); if (PLC_Iam_T1) { addWrite_PLC_T1_lamp_1(true); addWrite_SRV_T1_lamp_1(true); } else { addWrite_TCP_T1_lamp_1(true); } endWrite(); ui->pushButton_T1_lamp_1->setIcon(LampPressIcon); }
void page200::on_pushButton_T1_lamp_2_clicked() { beginWrite(); if (PLC_Iam_T1) { addWrite_PLC_T1_lamp_2(true); addWrite_SRV_T1_lamp_2(true); } else { addWrite_TCP_T1_lamp_2(true); } endWrite(); ui->pushButton_T1_lamp_2->setIcon(LampPressIcon); }
void page200::on_pushButton_T1_lamp_3_clicked() { beginWrite(); if (PLC_Iam_T1) { addWrite_PLC_T1_lamp_3(true); addWrite_SRV_T1_lamp_3(true); } else { addWrite_TCP_T1_lamp_3(true); } endWrite(); ui->pushButton_T1_lamp_3->setIcon(LampPressIcon); }
void page200::on_pushButton_T1_lamp_4_clicked() { beginWrite(); if (PLC_Iam_T1) { addWrite_PLC_T1_lamp_4(true); addWrite_SRV_T1_lamp_4(true); } else { addWrite_TCP_T1_lamp_4(true); } endWrite(); ui->pushButton_T1_lamp_4->setIcon(LampPressIcon); }
void page200::on_pushButton_T1_lamp_5_clicked() { beginWrite(); if (PLC_Iam_T1) { addWrite_PLC_T1_lamp_5(true); addWrite_SRV_T1_lamp_5(true); } else { addWrite_TCP_T1_lamp_5(true); } endWrite(); ui->pushButton_T1_lamp_5->setIcon(LampPressIcon); }

void page200::on_pushButton_T2_lamp_1_clicked() { beginWrite(); if (PLC_Iam_T2) { addWrite_PLC_T2_lamp_1(true); addWrite_SRV_T2_lamp_1(true); } else { addWrite_TCP_T2_lamp_1(true); } endWrite(); ui->pushButton_T2_lamp_1->setIcon(LampPressIcon); }
void page200::on_pushButton_T2_lamp_2_clicked() { beginWrite(); if (PLC_Iam_T2) { addWrite_PLC_T2_lamp_2(true); addWrite_SRV_T2_lamp_2(true); } else { addWrite_TCP_T2_lamp_2(true); } endWrite(); ui->pushButton_T2_lamp_2->setIcon(LampPressIcon); }
void page200::on_pushButton_T2_lamp_3_clicked() { beginWrite(); if (PLC_Iam_T2) { addWrite_PLC_T2_lamp_3(true); addWrite_SRV_T2_lamp_3(true); } else { addWrite_TCP_T2_lamp_3(true); } endWrite(); ui->pushButton_T2_lamp_3->setIcon(LampPressIcon); }
void page200::on_pushButton_T2_lamp_4_clicked() { beginWrite(); if (PLC_Iam_T2) { addWrite_PLC_T2_lamp_4(true); addWrite_SRV_T2_lamp_4(true); } else { addWrite_TCP_T2_lamp_4(true); } endWrite(); ui->pushButton_T2_lamp_4->setIcon(LampPressIcon); }
void page200::on_pushButton_T2_lamp_5_clicked() { beginWrite(); if (PLC_Iam_T2) { addWrite_PLC_T2_lamp_5(true); addWrite_SRV_T2_lamp_5(true); } else { addWrite_TCP_T2_lamp_5(true); } endWrite(); ui->pushButton_T2_lamp_5->setIcon(LampPressIcon); }

void page200::on_pushButton_T3_lamp_1_clicked() { beginWrite(); if (PLC_Iam_T3) { addWrite_PLC_T3_lamp_1(true); addWrite_SRV_T3_lamp_1(true); } else { addWrite_TCP_T3_lamp_1(true); } endWrite(); ui->pushButton_T3_lamp_1->setIcon(LampPressIcon); }
void page200::on_pushButton_T3_lamp_2_clicked() { beginWrite(); if (PLC_Iam_T3) { addWrite_PLC_T3_lamp_2(true); addWrite_SRV_T3_lamp_2(true); } else { addWrite_TCP_T3_lamp_2(true); } endWrite(); ui->pushButton_T3_lamp_2->setIcon(LampPressIcon); }
void page200::on_pushButton_T3_lamp_3_clicked() { beginWrite(); if (PLC_Iam_T3) { addWrite_PLC_T3_lamp_3(true); addWrite_SRV_T3_lamp_3(true); } else { addWrite_TCP_T3_lamp_3(true); } endWrite(); ui->pushButton_T3_lamp_3->setIcon(LampPressIcon); }
void page200::on_pushButton_T3_lamp_4_clicked() { beginWrite(); if (PLC_Iam_T3) { addWrite_PLC_T3_lamp_4(true); addWrite_SRV_T3_lamp_4(true); } else { addWrite_TCP_T3_lamp_4(true); } endWrite(); ui->pushButton_T3_lamp_4->setIcon(LampPressIcon); }
void page200::on_pushButton_T3_lamp_5_clicked() { beginWrite(); if (PLC_Iam_T3) { addWrite_PLC_T3_lamp_5(true); addWrite_SRV_T3_lamp_5(true); } else { addWrite_TCP_T3_lamp_5(true); } endWrite(); ui->pushButton_T3_lamp_5->setIcon(LampPressIcon); }

void page200::on_pushButton_T4_lamp_1_clicked() { beginWrite(); if (PLC_Iam_T4) { addWrite_PLC_T4_lamp_1(true); addWrite_SRV_T4_lamp_1(true); } else { addWrite_TCP_T4_lamp_1(true); } endWrite(); ui->pushButton_T4_lamp_1->setIcon(LampPressIcon); }
void page200::on_pushButton_T4_lamp_2_clicked() { beginWrite(); if (PLC_Iam_T4) { addWrite_PLC_T4_lamp_2(true); addWrite_SRV_T4_lamp_2(true); } else { addWrite_TCP_T4_lamp_2(true); } endWrite(); ui->pushButton_T4_lamp_2->setIcon(LampPressIcon); }
void page200::on_pushButton_T4_lamp_3_clicked() { beginWrite(); if (PLC_Iam_T4) { addWrite_PLC_T4_lamp_3(true); addWrite_SRV_T4_lamp_3(true); } else { addWrite_TCP_T4_lamp_3(true); } endWrite(); ui->pushButton_T4_lamp_3->setIcon(LampPressIcon); }
void page200::on_pushButton_T4_lamp_4_clicked() { beginWrite(); if (PLC_Iam_T4) { addWrite_PLC_T4_lamp_4(true); addWrite_SRV_T4_lamp_4(true); } else { addWrite_TCP_T4_lamp_4(true); } endWrite(); ui->pushButton_T4_lamp_4->setIcon(LampPressIcon); }
void page200::on_pushButton_T4_lamp_5_clicked() { beginWrite(); if (PLC_Iam_T4) { addWrite_PLC_T4_lamp_5(true); addWrite_SRV_T4_lamp_5(true); } else { addWrite_TCP_T4_lamp_5(true); } endWrite(); ui->pushButton_T4_lamp_5->setIcon(LampPressIcon); }

void page200::on_pushButton_T5_lamp_1_clicked() { beginWrite(); if (PLC_Iam_T5) { addWrite_PLC_T5_lamp_1(true); addWrite_SRV_T5_lamp_1(true); } else { addWrite_TCP_T5_lamp_1(true); } endWrite(); ui->pushButton_T5_lamp_1->setIcon(LampPressIcon); }
void page200::on_pushButton_T5_lamp_2_clicked() { beginWrite(); if (PLC_Iam_T5) { addWrite_PLC_T5_lamp_2(true); addWrite_SRV_T5_lamp_2(true); } else { addWrite_TCP_T5_lamp_2(true); } endWrite(); ui->pushButton_T5_lamp_2->setIcon(LampPressIcon); }
void page200::on_pushButton_T5_lamp_3_clicked() { beginWrite(); if (PLC_Iam_T5) { addWrite_PLC_T5_lamp_3(true); addWrite_SRV_T5_lamp_3(true); } else { addWrite_TCP_T5_lamp_3(true); } endWrite(); ui->pushButton_T5_lamp_3->setIcon(LampPressIcon); }
void page200::on_pushButton_T5_lamp_4_clicked() { beginWrite(); if (PLC_Iam_T5) { addWrite_PLC_T5_lamp_4(true); addWrite_SRV_T5_lamp_4(true); } else { addWrite_TCP_T5_lamp_4(true); } endWrite(); ui->pushButton_T5_lamp_4->setIcon(LampPressIcon); }
void page200::on_pushButton_T5_lamp_5_clicked() { beginWrite(); if (PLC_Iam_T5) { addWrite_PLC_T5_lamp_5(true); addWrite_SRV_T5_lamp_5(true); } else { addWrite_TCP_T5_lamp_5(true); } endWrite(); ui->pushButton_T5_lamp_5->setIcon(LampPressIcon); }

void page200::on_pushButton_T6_lamp_1_clicked() { beginWrite(); if (PLC_Iam_T6) { addWrite_PLC_T6_lamp_1(true); addWrite_SRV_T6_lamp_1(true); } else { addWrite_TCP_T6_lamp_1(true); } endWrite(); ui->pushButton_T6_lamp_1->setIcon(LampPressIcon); }
void page200::on_pushButton_T6_lamp_2_clicked() { beginWrite(); if (PLC_Iam_T6) { addWrite_PLC_T6_lamp_2(true); addWrite_SRV_T6_lamp_2(true); } else { addWrite_TCP_T6_lamp_2(true); } endWrite(); ui->pushButton_T6_lamp_2->setIcon(LampPressIcon); }
void page200::on_pushButton_T6_lamp_3_clicked() { beginWrite(); if (PLC_Iam_T6) { addWrite_PLC_T6_lamp_3(true); addWrite_SRV_T6_lamp_3(true); } else { addWrite_TCP_T6_lamp_3(true); } endWrite(); ui->pushButton_T6_lamp_3->setIcon(LampPressIcon); }
void page200::on_pushButton_T6_lamp_4_clicked() { beginWrite(); if (PLC_Iam_T6) { addWrite_PLC_T6_lamp_4(true); addWrite_SRV_T6_lamp_4(true); } else { addWrite_TCP_T6_lamp_4(true); } endWrite(); ui->pushButton_T6_lamp_4->setIcon(LampPressIcon); }
void page200::on_pushButton_T6_lamp_5_clicked() { beginWrite(); if (PLC_Iam_T6) { addWrite_PLC_T6_lamp_5(true); addWrite_SRV_T6_lamp_5(true); } else { addWrite_TCP_T6_lamp_5(true); } endWrite(); ui->pushButton_T6_lamp_5->setIcon(LampPressIcon); }

void page200::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page200::~page200()
{
    delete ui;
}

