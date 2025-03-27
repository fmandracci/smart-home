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
#include "page005.h"
#include "ui_page005.h"
#include "crosstable.h"

#include "automation.h"

page005::page005(QWidget *parent) :
    page(parent),
    ui(new Ui::page005)
{
    ui->setupUi(this);
    /* set here the protection level (pwd_admin_e, pwd_super_user_e, pwd_user_e, pwd_operator_e), default is pwd_operator_e
     * protection_level = pwd_operator_e;
     */
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
}

void page005::reload()
{
    int pointSize;

    if (mectScreenWidth >= 1280) {
        pointSize = 12;
    } else if (mectScreenWidth >= 800) {
        pointSize = 10;
    } else {
        pointSize =  9;
    }

    ui->label_time->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(pointSize));
    ui->headerLeds->changeHeader();
}

void page005::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();

    ui->label_time->setText(TIME_FMT + "\n" + TEMP_FMT);
    ui->headerLeds->updateLedLabels();
}

void page005::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page005::~page005()
{
    delete ui;
}
