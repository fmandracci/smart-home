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
#include "page043.h"
#include "ui_page043.h"
#include "crosstable.h"

#include <QDebug>

page043::page043(QWidget *parent) :
    page(parent),
    ui(new Ui::page043)
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
}

void page043::reload()
{
}

void page043::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();
    
}

void page043::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page043::~page043()
{
    delete ui;
}


void page043::on_atcmButton_back_clicked()
{
    variableList.clear();
    qDebug() << "variableList = " << variableList;
}
