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


#ifndef PAGE010_H
#define PAGE010_H

#include "pagebrowser.h"
#include "automation.h"

namespace Ui {
class page010;
}

class page010 : public page
{
    Q_OBJECT
    
public:
    explicit page010(QWidget *parent = 0);
    ~page010();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }
    void on_pushButton_home_clicked() { goto_start_page(); }

private:
    Ui::page010 *ui;
    void changeWidgets();
    void updateWidgets();
};

#endif // PAGE010_H

