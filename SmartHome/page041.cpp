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
#include "page041.h"
#include "ui_page041.h"
#include "crosstable.h"

#include "automation.h"

page041::page041(QWidget *parent) :
    page(parent),
    ui(new Ui::page041)
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    translateFontSize(this);
#endif
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page041::reload()
{
    changeWidgets();
    updateWidgets();
}

void page041::updateData()
{
    if (this->isVisible() == false)
    {
        return;
    }
    page::updateData();
    updateWidgets();
}

void page041::changeWidgets()
{
    ui->headerPanel->changeWidgets("trend1.csv", XX_PIXMAP, "BACK", "page041: TPX*");
}

void page041::updateWidgets()
{
    ui->headerPanel->updateWidgets();
}

void page041::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page041::~page041()
{
    delete ui;
}
