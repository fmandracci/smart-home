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


#ifndef PAGE400_H
#define PAGE400_H

#include "pagebrowser.h"

#include "automation.h"
#include <QPushButton>
#include <QLabel>

namespace Ui {
class page400;
}

class page400 : public page
{
    Q_OBJECT
    
public:
    explicit page400(QWidget *parent = 0);
    ~page400();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }
    void on_pushButton_next_clicked() { currentWattmeter = 1; goto_page("page4e0"); }
    void on_pushButton_M_W_clicked() { gotoWattmeterPage(1); }
    void on_pushButton_F_W_clicked() { gotoWattmeterPage(2); }
    void on_pushButton01_W_clicked() { gotoWattmeterPage(3); }
    void on_pushButton02_W_clicked() { gotoWattmeterPage(4); }
    void on_pushButton03_W_clicked() { gotoWattmeterPage(5); }
    void on_pushButton04_W_clicked() { gotoWattmeterPage(6); }
    void on_pushButton05_W_clicked() { gotoWattmeterPage(7); }
    void on_pushButton06_W_clicked() { gotoWattmeterPage(8); }
    void on_pushButton07_W_clicked() { gotoWattmeterPage(9); }
    void on_pushButton08_W_clicked() { gotoWattmeterPage(10); }
    void on_pushButton09_W_clicked() { gotoWattmeterPage(11); }
    void on_pushButton10_W_clicked() { gotoWattmeterPage(12); }
    void on_pushButton_trend_clicked();

private:
    Ui::page400 *ui;
    int pointSize;
    void gotoWattmeterPage(int n) {
        currentWattmeter = n;
        goto_page("page401");
    }
    void changeWidgets();
    void changeWattmeterCommon(QLabel *label_max_assigned_W, QLabel *label_overload_W, QLabel *label_V, QLabel *label_Hz);
    void changeWattmeterFull(QString label, int n, const QColor color,
                             QPushButton *pushButton_W, QLabel *label_pf, QLabel *label_var, QLabel *label_VA);
    void changeWattmeter(const QString label, int n, const QColor color,QPushButton *pushButton_W);

    void updateWidgets();
    void updateWattmeterCommon(QLabel *label_max_assigned_W, QLabel *label_overload_W, QLabel *label_V, QLabel *label_Hz,
                             int value_max_assigned_W, int value_overload_W, int value_V, int value_Hz);
    void updateWattmeterFull(QString label, int n,
                             QPushButton *pushButton_W, QLabel *label_pf, QLabel *label_var, QLabel *label_VA,
                             int value_W, int value_pf, int value_var, int value_VA);
    void updateWattmeter(const QString label, int n,
                         QPushButton *pushButton_W, int value_W);
};

#endif // PAGE400_H

