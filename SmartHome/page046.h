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


#ifndef PAGE046_H
#define PAGE046_H

#include "pagebrowser.h"

#include <atcmbutton.h>

namespace Ui {
class page046;
}

class page046 : public page
{
    Q_OBJECT
    
public:
    explicit page046(QWidget *parent = 0);
    ~page046();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event); 
    void on_pushButton_Test_toggled(bool checked);

private:
    Ui::page046 *ui;
    void setSensor(ATCMbutton *button, int n);
};

#endif // PAGE046_H

