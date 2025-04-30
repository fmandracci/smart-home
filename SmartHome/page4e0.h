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

#ifndef PAGE4E0_H
#define PAGE4E0_H

#include "pagebrowser.h"

#include "automation.h"

namespace Ui {
class page4e0;
}

class page4e0 : public page
{
    Q_OBJECT
    
public:
    explicit page4e0(QWidget *parent = 0);
    ~page4e0();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }
    void on_pushButton_prev_clicked() { currentWattmeter = 1; goto_page("page400"); }
    void on_pushButton_next_clicked() { }
    void on_pushButton_M_e_clicked() { gotoWattmeterPage( 1); }
    void on_pushButton_M_clicked()   { gotoWattmeterPage( 1); }
    void on_pushButton_F_e_clicked() { gotoWattmeterPage( 2); }
    void on_pushButton_F_clicked()   { gotoWattmeterPage( 2); }
    void on_pushButton_1_clicked()   { gotoWattmeterPage( 3); }
    void on_pushButton_2_clicked()   { gotoWattmeterPage( 4); }
    void on_pushButton_3_clicked()   { gotoWattmeterPage( 5); }
    void on_pushButton_4_clicked()   { gotoWattmeterPage( 6); }
    void on_pushButton_5_clicked()   { gotoWattmeterPage( 7); }
    void on_pushButton_6_clicked()   { gotoWattmeterPage( 8); }
    void on_pushButton_7_clicked()   { gotoWattmeterPage( 9); }
    void on_pushButton_8_clicked()   { gotoWattmeterPage(10); }
    void on_pushButton_9_clicked()   { gotoWattmeterPage(11); }
    void on_pushButton_10_clicked()  { gotoWattmeterPage(12); }

private:
    Ui::page4e0 *ui;
    void changeWidgets();
    void updateWidgets();
    int fontSize_px;
    void gotoWattmeterPage(int n) {
        currentWattmeter = n;
        goto_page("page401");
    }
    void updateWattmeter(QPushButton *pushButton_kWh, const QString label, int n, int value_kWh, const QColor color);
};

#endif // PAGE4E0_H

