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


#ifndef PAGE402_H
#define PAGE402_H

#include "pagebrowser.h"

namespace Ui {
class page402;
}

class page402 : public page
{
    Q_OBJECT
    
public:
    explicit page402(QWidget *parent = 0);
    ~page402();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);

private:
    Ui::page402 *ui;
    void changeWidgets(const char*trend, const QString t, const QString W, const QString M_W, const QColor color);
    QColor black;
};

#endif // PAGE402_H

