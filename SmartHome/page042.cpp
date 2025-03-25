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
#include "page042.h"
#include "ui_page042.h"
#include "crosstable.h"

#include "automation.h"

#include <QDebug>
#include <QFontMetrics>
#include <QProcess>

page042::page042(QWidget *parent) :
    page(parent),
    ui(new Ui::page042)
{
    ui->setupUi(this);

    // translateFontSize(this);

    QSettings *options = new QSettings(HMI_INI_FILE, QSettings::IniFormat);
    int width_mm = WIDTH_mm;
    int height_mm = HEIGHT_mm;
    float fontCorrector = FONT_CORRECTOR;

    if (options) {
        bool ok;
        int value;
        float fValue;

        value = options->value("width_mm", width_mm).toInt(&ok);
        if (ok && value > 0)
            width_mm = value;

        value = options->value("height_mm", height_mm).toInt(&ok);
        if (ok && value > 0)
            height_mm = value;

        fValue = options->value("font_corrector", fontCorrector).toFloat(&ok);
        if (ok && fValue != 0)
            fontCorrector = fValue;
    }

    resizeLabelFont(ui->label100px, fontCorrector); // mectFontCorrector
    resizeLabelFont(ui->label50px, fontCorrector); // mectFontCorrector
    resizeLabelFont(ui->label25px, fontCorrector); // mectFontCorrector
    resizeLabelFont(ui->label_font_corrector, fontCorrector); // mectFontCorrector

    resizeLabelFont(ui->label100px_2, fontCorrector); // mectFontCorrector
    resizeLabelFont(ui->label50px_2, fontCorrector); // mectFontCorrector
    resizeLabelFont(ui->label25px_2, fontCorrector); // mectFontCorrector

    ui->label_font_corrector->setText(QString("%1 (%2 mm x %3 mm)").arg(mectFontCorrector).arg(width_mm).arg(height_mm));
}

void page042::resizeLabelFont(QLabel *myLabel, float fontFactor)
{
    QFont labelFont = QFont(myLabel->font());

    labelFont.setPointSize( (labelFont.pointSize() * fontFactor));
    myLabel->setFont(labelFont);
}

void page042::reload()
{
    // Font DejaVu Sans
    QFontMetrics fmLabel100(ui->label100px->font());
    QFontMetrics fmLabel50(ui->label50px->font());
    QFontMetrics fmLabel25(ui->label25px->font());
    qDebug("Font DejaVu Sans Label Size for label100: W:%d - H:%d Bounding Rect: W:%d H:%d", fmLabel100.width(ui->label100px->text()), fmLabel100.height(), fmLabel100.boundingRect(ui->label100px->text()).width(), fmLabel100.boundingRect(ui->label100px->text()).height());
    qDebug("Font DejaVu Sans Label Size for label50:  W:%d - H:%d Bounding Rect: W:%d H:%d", fmLabel50.width(ui->label50px->text()), fmLabel50.height(), fmLabel50.boundingRect(ui->label50px->text()).width(), fmLabel50.boundingRect(ui->label50px->text()).height());
    qDebug("Font DejaVu Sans Label Size for label25:  W:%d - H:%d Bounding Rect: W:%d H:%d", fmLabel25.width(ui->label25px->text()), fmLabel25.height(), fmLabel25.boundingRect(ui->label25px->text()).width(), fmLabel25.boundingRect(ui->label25px->text()).height());

    // Font Ubuntu
    QFontMetrics fmLabel100_2(ui->label100px_2->font());
    QFontMetrics fmLabel50_2(ui->label50px_2->font());
    QFontMetrics fmLabel25_2(ui->label25px_2->font());
    qDebug("Font Ubuntu Label Size for label100_2: W:%d - H:%d Bounding Rect: W:%d H:%d", fmLabel100_2.width(ui->label100px_2->text()), fmLabel100_2.height(), fmLabel100_2.boundingRect(ui->label100px_2->text()).width(), fmLabel100_2.boundingRect(ui->label100px_2->text()).height());
    qDebug("Font Ubuntu Label Size for label50_2:  W:%d - H:%d Bounding Rect: W:%d H:%d", fmLabel50_2.width(ui->label50px_2->text()), fmLabel50_2.height(), fmLabel50_2.boundingRect(ui->label50px_2->text()).width(), fmLabel50_2.boundingRect(ui->label50px_2->text()).height());
    qDebug("Font Ubuntu Label Size for label25_2:  W:%d - H:%d Bounding Rect: W:%d H:%d", fmLabel25_2.width(ui->label25px_2->text()), fmLabel25_2.height(), fmLabel25_2.boundingRect(ui->label25px_2->text()).width(), fmLabel25_2.boundingRect(ui->label25px_2->text()).height());
}

void page042::updateData()
{
    if (this->isVisible() == false)
    {
        return;
    }
    page::updateData();
}

void page042::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

page042::~page042()
{
    delete ui;
}

