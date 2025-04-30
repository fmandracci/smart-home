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


#ifndef PAGE200_H
#define PAGE200_H

#include "pagebrowser.h"

#include "crosstable.h"

namespace Ui {
class page200;
}

class page200 : public page
{
    Q_OBJECT
    
public:
    explicit page200(QWidget *parent = 0);
    ~page200();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }

    void on_pushButton_T1_lamp_1_clicked();
    void on_pushButton_T1_lamp_2_clicked();
    void on_pushButton_T1_lamp_3_clicked();
    void on_pushButton_T1_lamp_4_clicked();
    void on_pushButton_T1_lamp_5_clicked();

    void on_pushButton_T2_lamp_1_clicked();
    void on_pushButton_T2_lamp_2_clicked();
    void on_pushButton_T2_lamp_3_clicked();
    void on_pushButton_T2_lamp_4_clicked();
    void on_pushButton_T2_lamp_5_clicked();

    void on_pushButton_T3_lamp_1_clicked();
    void on_pushButton_T3_lamp_2_clicked();
    void on_pushButton_T3_lamp_3_clicked();
    void on_pushButton_T3_lamp_4_clicked();
    void on_pushButton_T3_lamp_5_clicked();

    void on_pushButton_T4_lamp_1_clicked();
    void on_pushButton_T4_lamp_2_clicked();
    void on_pushButton_T4_lamp_3_clicked();
    void on_pushButton_T4_lamp_4_clicked();
    void on_pushButton_T4_lamp_5_clicked();

    void on_pushButton_T5_lamp_1_clicked();
    void on_pushButton_T5_lamp_2_clicked();
    void on_pushButton_T5_lamp_3_clicked();
    void on_pushButton_T5_lamp_4_clicked();
    void on_pushButton_T5_lamp_5_clicked();

    void on_pushButton_T6_lamp_1_clicked();
    void on_pushButton_T6_lamp_2_clicked();
    void on_pushButton_T6_lamp_3_clicked();
    void on_pushButton_T6_lamp_4_clicked();
    void on_pushButton_T6_lamp_5_clicked();

private:
    Ui::page200 *ui;
    const QIcon LampOffIcon;
    const QIcon LampPressIcon;
    const QIcon LampOnIcon;
    const QIcon LampWarningIcon;
    const QColor black;

    void changeWidgets();
    void changeLamps(int t, const QColor color, const QString name,
                     QLabel *label_n, int enabled_lamps_t,
                     QPushButton *button_t_1, QPushButton *button_t_2, QPushButton *button_t_3, QPushButton *button_t_4, QPushButton *button_t_5,
                     QLabel *label_t_1, QLabel *label_t_2, QLabel *label_t_3, QLabel *label_t_4, QLabel *label_t_5,
                     const QString name_t_1, const QString name_t_2, const QString name_t_3, const QString name_t_4, const QString name_t_5);
    void changeLamp(int t, const QString colorSS, int enabled_lamps_t, int n, QPushButton *button_t_n, QLabel *label_t_n, const QString name_t_n);
    void updateWidgets();
    void updateLamp(int t, bool isOK, int enabled_lamps_t, int n, QPushButton *button, bool feedback);
    void updateLamps(int t, int enabled_lamps_t,
                     QPushButton *button_t_1, QPushButton *button_t_2, QPushButton *button_t_3, QPushButton *button_t_4, QPushButton *button_t_5,
                     QLabel *label_t_1, QLabel *label_t_2, QLabel *label_t_3, QLabel *label_t_4, QLabel *label_t_5);
};

#endif // PAGE200_H

