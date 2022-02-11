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
#include "page020.h"
#include "ui_page020.h"
#include "crosstable.h"

#include <QDateTime>
#include "automation.h"

page020::page020(QWidget *parent) :
    page(parent),
    ui(new Ui::page020),
    firstTime(true)
{
    ui->setupUi(this);
#ifndef QT_KNOWS_THE_DPI_VALUE
    translateFontSize(this);
#endif
}

void page020::reload()
{
    if (firstTime) {
        firstTime = false;

        goto_start_page();
    }
}

void page020::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();

    updateLedLabels(ui->label_EP, ui->label_BA, ui->label_green,
                    ui->label_T5, ui->label_T6, ui->label_red,
                    ui->label_T3, ui->label_T4, ui->label_yellow_1,
                    ui->label_T1, ui->label_T2, ui->label_yellow_2);
    ui->label_time->setText(TIME_FMT);

    QString giorno(PLC_nighttime ? LABEL_NIGHTTIME : LABEL_DAYTIME);

    switch (QDate::currentDate().dayOfWeek()) {
    case 1: giorno += QString::fromUtf8("Lunedì"   ); break;
    case 2: giorno += QString::fromUtf8("Martedì"  ); break;
    case 3: giorno += QString::fromUtf8("Mercoledì"); break;
    case 4: giorno += QString::fromUtf8("Giovedì"  ); break;
    case 5: giorno += QString::fromUtf8("Venerdì"  ); break;
    case 6: giorno += QString::fromUtf8("Sabato"   ); break;
    case 7: giorno += QString::fromUtf8("Domenica" ); break;
    default: ui->label_giorno->setText("---");
    }
     ui->label_giorno->setText(giorno);
}

void page020::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page020::~page020()
{
    delete ui;
}

