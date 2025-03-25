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

#ifndef PAGE100_H
#define PAGE100_H

#include "pagebrowser.h"

#include "automation.h"

namespace Ui {
class page100;
}

class page100 : public page
{
    Q_OBJECT
    
public:
    explicit page100(QWidget *parent = 0);
    ~page100();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }
    void on_pushButton_trend_clicked();
    void on_pushButton_status_1_clicked() { currentThermostat = 1; goto_page("page101c"); }
    void on_pushButton_status_2_clicked() { currentThermostat = 2; goto_page("page101c"); }
    void on_pushButton_status_3_clicked() { currentThermostat = 3; goto_page("page101c"); }
    void on_pushButton_status_4_clicked() { currentThermostat = 4; goto_page("page101c"); }
    void on_pushButton_status_5_clicked() { currentThermostat = 5; goto_page("page101c"); }
    void on_pushButton_status_6_clicked() { currentThermostat = 6; goto_page("page101c"); }
    void on_pushButton_1_clicked() { currentThermostat = 1; goto_page("page101a"); }
    void on_pushButton_2_clicked() { currentThermostat = 2; goto_page("page101a"); }
    void on_pushButton_3_clicked() { currentThermostat = 3; goto_page("page101a"); }
    void on_pushButton_4_clicked() { currentThermostat = 4; goto_page("page101a"); }
    void on_pushButton_5_clicked() { currentThermostat = 5; goto_page("page101a"); }
    void on_pushButton_6_clicked() { currentThermostat = 6; goto_page("page101a"); }
    void on_pushButton_SP_1_clicked() { currentThermostat = 1; goto_page("page101b"); }
    void on_pushButton_SP_2_clicked() { currentThermostat = 2; goto_page("page101b"); }
    void on_pushButton_SP_3_clicked() { currentThermostat = 3; goto_page("page101b"); }
    void on_pushButton_SP_4_clicked() { currentThermostat = 4; goto_page("page101b"); }
    void on_pushButton_SP_5_clicked() { currentThermostat = 5; goto_page("page101b"); }
    void on_pushButton_SP_6_clicked() { currentThermostat = 6; goto_page("page101b"); }

private:
    Ui::page100 *ui;
    void changeWidgets();
    void updateWidgets();
    void changeTemperature(QLabel *label_n, QPushButton *pushButton_setpoint,
                           QPushButton *pushButton_status, QPushButton *pushButton, QLabel *label_ext,
                           int n, const QColor color);
    void updateTemperature(QLabel *label_n, const QString label_on, const QString label_off, QPushButton *pushButton_setpoint,
                           QPushButton *pushButton_status, QPushButton *pushButton, QLabel *label_ext,
                           int n, int sensors,
                           int tsp, int tsp_nt, int t, int t_bis, int t_ext, int h,
                           int Iam_Tn, bool Tn_isOK, int Tn_heating_status, bool Tn_heating);
};

#endif // PAGE100_H


