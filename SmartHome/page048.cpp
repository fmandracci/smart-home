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
#include "page048.h"
#include "ui_page048.h"
#include "crosstable.h"

#include <QDebug>

page048::page048(QWidget *parent) :
    page(parent),
    ui(new Ui::page048)
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
}

void page048::reload()
{
}

void page048::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();
    
}

void page048::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page048::~page048()
{
    delete ui;
}


void page048::on_atcmButton_back_clicked()
{
    variableList.clear();
    qDebug() << "variableList = " << variableList;
}
