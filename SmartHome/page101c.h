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


#ifndef PAGE101C_H
#define PAGE101C_H

#include "pagebrowser.h"

#include <QColor>
#include "automation.h"

namespace Ui {
class page101c;
}

class page101c : public page
{
    Q_OBJECT
    
public:
    explicit page101c(QWidget *parent = 0);
    ~page101c();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }

    void on_pushButton_plot_clicked();

    void on_pushButton_off_clicked() { changeStatus(HEATING_OFF); }
    void on_pushButton_ON_clicked() { changeStatus(HEATING_AUTO); }
    void on_pushButton_ECO_clicked() { changeStatus(HEATING_ECONOMY); }
    void on_pushButton_COMFORT_clicked() { changeStatus(HEATING_COMFORT); }
    void on_pushButton_BOOST_clicked() { changeStatus(HEATING_BOOST); }

    void on_pushButton_20m_clicked();
    void on_pushButton_40m_clicked();
    void on_pushButton_60m_clicked();
    void on_pushButton_2h_clicked() ;
    void on_pushButton_5h_clicked() ;
    void on_pushButton_8h_clicked() ;


private:
    Ui::page101c *ui;
    void changeWidgets(const QString t, const char *trend, const QString title,
                       int Tn_temperature, bool Tn_nightime, int Tn_temperature_setpoint, int Tn_temperature_setpoint_nt,
                       int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color);
    void updateWidgets(int Tn_temperature, bool Tn_nightime, int Tn_temperature_setpoint, int Tn_temperature_setpoint_nt,
                       int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color);
    void changeStatus(int status);
    void changeTimer(int timer);
};

#endif // PAGE101C_H

