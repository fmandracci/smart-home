/****************************************************************************
**
** Copyright (C) 2025 Francesco Mandracci
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
#include "page045b.h"
#include "ui_page045b.h"
#include "crosstable.h"

page045b::page045b(QWidget *parent) :
    page(parent),
    ui(new Ui::page045b)
{
    ui->setupUi(this);
    TRANSLATE_FONT_SIZE(this);
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page045b::reload()
{
    ui->headerPanel->changeWidgets(NULL, XX_PIXMAP, "BACK", "page045b BA MPNE B");

    QString atcmss = QString("QLabel, ATCMcombobox, ATCMlabel, ATCMbutton { %1 }\n").arg(FONT_SS_N(modulor->smallFont_px()));
    ui->frame->setStyleSheet(atcmss);
}

void page045b::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();
    ui->headerPanel->updateWidgets();
}

void page045b::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

/**
 * @brief This is the distructor member. The operation written here, are executed only one time when the page will be deleted.
 */
page045b::~page045b()
{
    delete ui;
}

