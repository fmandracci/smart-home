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


#ifndef PAGE101B_H
#define PAGE101B_H

#include "pagebrowser.h"
#include "automation.h"

#include <QColor>

namespace Ui {
class page101b;
}

class page101b : public page
{
    Q_OBJECT
    
public:
    explicit page101b(QWidget *parent = 0);
    ~page101b();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }

    void on_pushButton_sunrise_clicked();
    void on_pushButton_sunset_clicked();

    void on_pushButton_Tup_clicked()   { temperature_valueChanged(+deltaT); }
    void on_pushButton_Tdown_clicked() { temperature_valueChanged(-deltaT); }
    void on_pushButton_Hup_clicked()   { humidity_valueChanged(+deltaH);    }
    void on_pushButton_Hdown_clicked() { humidity_valueChanged(-deltaH);    }

    void on_pushButton_Tup_nt_clicked()   { temperature_nt_valueChanged(+deltaT); }
    void on_pushButton_Tdown_nt_clicked() { temperature_nt_valueChanged(-deltaT); }
    void on_pushButton_Hup_nt_clicked()   { humidity_nt_valueChanged(+deltaH);    }
    void on_pushButton_Hdown_nt_clicked() { humidity_nt_valueChanged(-deltaH);    }

    void on_pushButton_T_0_clicked()   { temperature_valueAbsolute(TemperatureSetPoint_min); }
    void on_pushButton_T_1_clicked()   { temperature_valueAbsolute(120); } // 1 12.0°C
    void on_pushButton_T_2_clicked()   { temperature_valueAbsolute(160); } // 2 16.0°C
    void on_pushButton_T_3_clicked()   { temperature_valueAbsolute(200); } // 3 20.0°C
    void on_pushButton_T_4_clicked()   { temperature_valueAbsolute(240); } // 4 24.0°C

    void on_atcmButton_set_T_everywhere_clicked();

private:
    Ui::page101b *ui;
    void changeWidgets(int sunrise, int sunset,
                       const QString Tlabel, const char *trend, const QString title,
                       const QString Tsp, const QString Tsp_nt,
                       const QString Hsp, const QString Hsp_nt,
                       int Tn_temperature, int Tn_temperature_bis,
                       int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color);
    void updateWidgets(int sunrise, int sunset, const QString Tlabel,
                       int Tn_temperature, int Tn_temperature_bis,
                       int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color);

    const int deltaT;
    const int deltaH;
    int checkTvalue(int value, int diff);
    int checkHvalue(int value, int diff);
    void temperature_valueAbsolute(int value);
    void temperature_valueChanged(int diff);
    void temperature_nt_valueChanged(int diff);
    void humidity_valueChanged(int diff);
    void humidity_nt_valueChanged(int diff);
};

#endif // PAGE101B_H

