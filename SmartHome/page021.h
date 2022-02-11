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


#ifndef PAGE021_H
#define PAGE021_H

#include "pagebrowser.h"

#include <QElapsedTimer>

namespace Ui {
class page021;
}

class page021 : public page
{
    Q_OBJECT
    
public:
    explicit page021(QWidget *parent = 0);
    ~page021();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }
    void on_atcmButtonStartStop_1_toggled(bool checked);
    void on_atcmButtonStartStop_2_toggled(bool checked);
    void on_atcmButtonReset_1_clicked();
    void on_atcmButtonReset_2_clicked();
    void on_pushButton_timer_1_clicked();
    void on_pushButton_timer_2_clicked();

private:
    Ui::page021 *ui;
    enum {IDLE = 0, RUNNING, PAUSED, RINGING, RINGING_BIS} status_1, status_2;
    QElapsedTimer timer_1, timer_2;
    qint64 value_1_ms, value_2_ms;
    void updateTimers();
    void updateWidgets();
    void resetTimer_1(int value);
    void resetTimer_2(int value);
};

#endif // PAGE021_H

