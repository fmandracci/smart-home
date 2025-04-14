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


#ifndef PAGE101A_H
#define PAGE101A_H

#include "pagebrowser.h"

#include <QColor>

namespace Ui {
class page101a;
}

class page101a : public page
{
    Q_OBJECT
    
public:
    explicit page101a(QWidget *parent = 0);
    ~page101a();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }
    void on_pushButton_trend_clicked();

private:
    Ui::page101a *ui;
    void changeWidgets(const QString t, const char *trend, const QString title, const QString T, const QString Tbis, const QString Text,
                       const QString Thumidity, const QString Thumidity_bis, const QString Thumidity_ext,
                       int Tn_max_request_W, const QString Tn_requested_W, const QString EP_Tn_assigned_W,
                       int daily_heating_s, int monthly_heating_s,
                       int Tn_temperature_setpoint, int Tn_temperature_setpoint_nt,
                       int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color);
    void updateWidgets(int daily_heating_s, int monthly_heating_s,
                       int Tn_temperature_setpoint, int Tn_temperature_setpoint_nt,
                       int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating,  const QColor color);
};

#endif // PAGE101A_H

