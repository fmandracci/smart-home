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


#ifndef PAGE401_H
#define PAGE401_H

#include "pagebrowser.h"

#include <QColor>

namespace Ui {
class page401;
}

class page401 : public page
{
    Q_OBJECT
    
public:
    explicit page401(QWidget *parent = 0);
    ~page401();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);

private:
    Ui::page401 *ui;
    void changeWidgets(int n,
                       const QString t, const char *trend, const QString name, const QColor color,
                       const QString W, const QString var, const QString VA,
                       const QString kWh);
};

#endif // PAGE401_H

