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

#ifndef PAGE011_H
#define PAGE011_H

#include "pagebrowser.h"
#include "global_functions.h" // beep()

namespace Ui {
class page011;
}

class page011 : public page
{
    Q_OBJECT

public:
    explicit page011(QWidget *parent = 0);
    ~page011();
    virtual void reload(void);
    virtual void updateData();

private slots:
    void changeEvent(QEvent * event);

    void on_pushButton_set_home_clicked()  ;
    void on_pushButton_TPX_clicked()       ;
    void on_pushButton_TPAC1007_clicked()  ;

    void on_pushButton_Config_clicked()    ;
    void on_pushButton_Menu_clicked()      ;
    void on_pushButton_EP_7M_clicked()     ;
    void on_pushButton_EP_7E_clicked()     ;

    void on_pushButton_DateTime_clicked()  ;
    void on_pushButton_Display_clicked()   ;
    void on_pushButton_Tn_ARQ01_clicked()  ;
    void on_pushButton_XX_MPNC_clicked()   ;

    void on_pushButton_NetConf_clicked()   ;
    void on_pushButton_Info_clicked()      ;
    void on_pushButton_XX_MPNE_C_clicked() ;
    void on_pushButton_XX_MPNE_D_clicked() ;

    void on_pushButton_Fonts_clicked()     ;
    void on_pushButton_BA_test_clicked()   ;
    void on_pushButton_BA_MPNE_A_clicked() ;
    void on_pushButton_BA_MPNE_B_clicked() ;
    void on_pushButton_BA_MPNE_E_clicked() ;

private:
    Ui::page011 *ui;
    void changeWidgets();
    void updateWidgets();
    void highlightButton(QPushButton *button);
};

#endif // PAGE011_H

