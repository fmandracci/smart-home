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


#ifndef PAGE045E_H
#define PAGE045E_H

#include "pagebrowser.h"

namespace Ui {
class page045e;
}

class page045e : public page
{
    Q_OBJECT

public:
    explicit page045e(QWidget *parent = 0);
    ~page045e();
    virtual void reload(void);
    virtual void updateData();

private slots:
    void changeEvent(QEvent * event);

private:
    Ui::page045e *ui;
};

#endif // PAGE045E_H

