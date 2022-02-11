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


#ifndef PAGE103_H
#define PAGE103_H

#include "pagebrowser.h"

namespace Ui {
class page103;
}

class page103 : public page
{
    Q_OBJECT
    
public:
    explicit page103(QWidget *parent = 0);
    ~page103();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);    
    void on_pushButton_time_clicked() { goto_page("page020"); }
    void on_pushButton_trend_clicked();

private:
    Ui::page103 *ui;
    void changeWidgets(const QString t, const QString T, const QString Tbis, const QString Text, const QString Tsp,
                       int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color);
    void updateWidgets(int enabled_sensors, int Iam_Tn, bool Tn_isOK, int Tn_heating_status, int Tn_heating_timer, bool Tn_heating, const QColor color);
};

#endif // PAGE103_H

