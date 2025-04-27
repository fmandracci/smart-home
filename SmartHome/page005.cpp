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
    TRANSLATE_FONT_SIZE(this);
    connect(ui->headerPanel, SIGNAL(newPage(const char*,bool)), this, SLOT(goto_page(const char*,bool)));
}

void page005::reload()
{
    changeWidgets();
    updateWidgets();
}

void page005::updateData()
{
    if (not this->isVisible()) {
        return;
    }
    page::updateData();
    updateWidgets();
}

void page005::changeWidgets()
{
    ui->headerPanel->changeWidgets(NULL, XX_PIXMAP, "BACK", "page005: Config");

    QString pagess = "QWidget#page005 { background-color: rgb(0, 0, 0); }\n";
    QString tabss1 = QString("QTabBar::tab"
                             "{ "
                             "background-color: rgb(0, 0, 0);"
                             "border-top-left-radius: %1px; border-top-right-radius: %1px;"
                             "border: 1px solid rgb(255, 255, 255);"
                             "padding: 2px;"
                             "min-width: %2px; min-height: %2px; "
                             "%3"
                             "}\n").arg(ui->headerPanel->ledSize_px() / 2)
                                   .arg(2 * ui->headerPanel->ledSize_px())
                                   .arg(FONT_SS_B(ui->headerPanel->titleFont_px()));
    QString tabss2 = QString("QTabBar::tab:selected"
                             "{"
                             "color: rgb(0, 0, 0);"
                             "background-color: rgb(255, 255, 255);"
                             "border: 1px solid rgb(255, 255, 0);"
                             "}\n");
    QString tabss3 = QString("QTabBar::tab:!selected"
                             "{"
                             "color: rgb(255, 255, 255);"
                             "}\n");
    QString atcmss = QString("ATCMcombobox, ATCMlabel, ATCMbutton { %1 }\n").arg(FONT_SS_N(ui->headerPanel->titleFont_px()));

    this->setStyleSheet(pagess + tabss1 + tabss2 + tabss3 + atcmss);
}

void page005::updateWidgets()
{
    ui->headerPanel->updateWidgets();
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
