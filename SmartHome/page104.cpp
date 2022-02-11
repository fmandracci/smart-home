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
#include "page104.h"
#include "ui_page104.h"
#include "crosstable.h"

#include "automation.h"

page104::page104(QWidget *parent) :
    page(parent),
    ui(new Ui::page104)
{
    ui->setupUi(this);
#ifndef QT_KNOWS_THE_DPI_VALUE
    translateFontSize(this);
#endif
}

void page104::reload()
{
    switch (currentThermostat) {
    case  1: updateWidgets(LABEL_01, COLOR_01); break;
    case  2: updateWidgets(LABEL_02, COLOR_02); break;
    case  3: updateWidgets(LABEL_03, COLOR_03); break;
    case  4: updateWidgets(LABEL_04, COLOR_04); break;
    case  5: updateWidgets(LABEL_05, COLOR_05); break;
    case  6: updateWidgets(LABEL_06, COLOR_06); break;
    default: updateWidgets("??"    , COLOR_01);
    }
}

void page104::updateWidgets(const QString t, const QColor color)
{
    Q_UNUSED(t);
    Q_UNUSED(color);

    // header
    updateLedLabels(ui->label_EP, ui->label_BA, ui->label_green,
                    ui->label_T5, ui->label_T6, ui->label_red,
                    ui->label_T3, ui->label_T4, ui->label_yellow_1,
                    ui->label_T1, ui->label_T2, ui->label_yellow_2);
    ui->pushButton_time->setText(PLC_nighttime ? TIME_FMT_NIGHTTIME : TIME_FMT_DAYTIME);
//    ui->atcmButton_Tn->setText(t);
//    ui->atcmButton_Tn->setFontColor(color);

    // center
    ui->atcmLabel_measure_01->setFontColor((RTU_BitMask_1 & 0x00000001) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_02->setFontColor((RTU_BitMask_1 & 0x00000002) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_03->setFontColor((RTU_BitMask_1 & 0x00000004) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_04->setFontColor((RTU_BitMask_1 & 0x00000008) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_05->setFontColor((RTU_BitMask_1 & 0x00000010) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_06->setFontColor((RTU_BitMask_1 & 0x00000020) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_07->setFontColor((RTU_BitMask_1 & 0x00000040) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_08->setFontColor((RTU_BitMask_1 & 0x00000080) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_09->setFontColor((RTU_BitMask_1 & 0x00000100) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_10->setFontColor((RTU_BitMask_1 & 0x00000200) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_11->setFontColor((RTU_BitMask_1 & 0x00000400) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_12->setFontColor((RTU_BitMask_1 & 0x00000800) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_13->setFontColor((RTU_BitMask_1 & 0x00001000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_14->setFontColor((RTU_BitMask_1 & 0x00002000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_15->setFontColor((RTU_BitMask_1 & 0x00004000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_16->setFontColor((RTU_BitMask_1 & 0x00008000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_17->setFontColor((RTU_BitMask_1 & 0x00010000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_18->setFontColor((RTU_BitMask_1 & 0x00020000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_19->setFontColor((RTU_BitMask_1 & 0x00040000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_20->setFontColor((RTU_BitMask_1 & 0x00080000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_21->setFontColor((RTU_BitMask_1 & 0x00100000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_22->setFontColor((RTU_BitMask_1 & 0x00200000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_23->setFontColor((RTU_BitMask_1 & 0x00400000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_24->setFontColor((RTU_BitMask_1 & 0x00800000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_25->setFontColor((RTU_BitMask_1 & 0x01000000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_26->setFontColor((RTU_BitMask_1 & 0x02000000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_27->setFontColor((RTU_BitMask_1 & 0x04000000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_28->setFontColor((RTU_BitMask_1 & 0x08000000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_29->setFontColor((RTU_BitMask_1 & 0x10000000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_30->setFontColor((RTU_BitMask_1 & 0x20000000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_31->setFontColor((RTU_BitMask_1 & 0x40000000) ? COLOR_WHITE : COLOR_GREY);
    ui->atcmLabel_measure_32->setFontColor((RTU_BitMask_1 & 0x80000000) ? COLOR_WHITE : COLOR_GREY);
}

void page104::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();

    switch (currentThermostat) {
    case  1: updateWidgets(LABEL_01, COLOR_01); break;
    case  2: updateWidgets(LABEL_02, COLOR_02); break;
    case  3: updateWidgets(LABEL_03, COLOR_03); break;
    case  4: updateWidgets(LABEL_04, COLOR_04); break;
    case  5: updateWidgets(LABEL_05, COLOR_05); break;
    case  6: updateWidgets(LABEL_06, COLOR_06); break;
    default: updateWidgets("??"    , COLOR_01);
    }
}

void page104::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

page104::~page104()
{
    delete ui;
}
