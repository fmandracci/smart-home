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


#ifndef PAGE300_H
#define PAGE300_H

#include "pagebrowser.h"

#include "crosstable.h"

namespace Ui {
class page300;
}

class page300 : public page
{
    Q_OBJECT
    
public:
    explicit page300(QWidget *parent = 0);
    ~page300();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }

    void on_pushButton_EP_relay_A_toggled(bool value) { beginWrite(); if (PLC_Iam_EP) { addWrite_PLC_EP_relay_A(value); addWrite_SRV_EP_relay_A(value); } else { addWrite_TCP_EP_relay_A(value); } endWrite(); }
    void on_pushButton_EP_relay_B_toggled(bool value) { beginWrite(); if (PLC_Iam_EP) { addWrite_PLC_EP_relay_B(value); addWrite_SRV_EP_relay_B(value); } else { addWrite_TCP_EP_relay_B(value); } endWrite(); }
    void on_pushButton_EP_relay_C_toggled(bool value) { beginWrite(); if (PLC_Iam_EP) { addWrite_PLC_EP_relay_C(value); addWrite_SRV_EP_relay_C(value); } else { addWrite_TCP_EP_relay_C(value); } endWrite(); }
    void on_pushButton_EP_relay_D_toggled(bool value) { beginWrite(); if (PLC_Iam_EP) { addWrite_PLC_EP_relay_D(value); addWrite_SRV_EP_relay_D(value); } else { addWrite_TCP_EP_relay_D(value); } endWrite(); }

    void on_pushButton_EP_relay_E_toggled(bool value) { beginWrite(); if (PLC_Iam_EP) { addWrite_PLC_EP_relay_E(value); addWrite_SRV_EP_relay_E(value); } else { addWrite_TCP_EP_relay_E(value); } endWrite(); }
    void on_pushButton_EP_relay_F_toggled(bool value) { beginWrite(); if (PLC_Iam_EP) { addWrite_PLC_EP_relay_F(value); addWrite_SRV_EP_relay_F(value); } else { addWrite_TCP_EP_relay_F(value); } endWrite(); }
    void on_pushButton_EP_relay_G_toggled(bool value) { beginWrite(); if (PLC_Iam_EP) { addWrite_PLC_EP_relay_G(value); addWrite_SRV_EP_relay_G(value); } else { addWrite_TCP_EP_relay_G(value); } endWrite(); }
    void on_pushButton_EP_relay_H_toggled(bool value) { beginWrite(); if (PLC_Iam_EP) { addWrite_PLC_EP_relay_H(value); addWrite_SRV_EP_relay_H(value); } else { addWrite_TCP_EP_relay_H(value); } endWrite(); }

private:
    Ui::page300 *ui;
    void setupRelay(QPushButton *button, QLabel *label, int n);
    void updateRelay(QPushButton *button, int n, int value);
};

#endif // PAGE300_H

