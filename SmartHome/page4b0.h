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

#ifndef PAGE4B0_H
#define PAGE4B0_H

#include "pagebrowser.h"

#include "automation.h"

namespace Ui {
class page4b0;
}

class page4b0 : public page
{
    Q_OBJECT
    
public:
    explicit page4b0(QWidget *parent = 0);
    ~page4b0();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }
    void on_pushButton_prev_clicked() { currentWattmeter = 1; goto_page("page4e0"); }
    void on_pushButton_trend_clicked();

private:
    Ui::page4b0 *ui;
    void changeWidgets();
    void changeThermostat(int n, const QColor color, QLabel *label_n, const QString label);
    void updateWidgets();
    void updateValues(int n, const QColor color, QLabel *label_r_W, QLabel *label_a_W,
                      int value_r_W, int value_a_W);
    const QString tic_0;
    const QString tic_1;
    const QString tic_2;
    const QString tic_3;
    const QString tic_4;
    const QString tic_5;
    const QString tic_6;
};

#endif // PAGE4B0_H

