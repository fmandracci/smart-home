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


#ifndef PAGE022_H
#define PAGE022_H

#include "pagebrowser.h"

#include <QElapsedTimer>

namespace Ui {
class page022;
}

class page022 : public page
{
    Q_OBJECT
    
public:
    explicit page022(QWidget *parent = 0);
    ~page022();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }
    void on_atcmButton_StartPause_toggled(bool checked);
    void on_atcmButton_Reset_clicked();

protected:
     void timerEvent(QTimerEvent *event);

private:
    Ui::page022 *ui;
    void changeWidgets();
    void updateWidgets();
    enum {IDLE = 0, RUNNING, PAUSED} status;
    QElapsedTimer timer;
    qint64 value_ms;
    QColor cyan;
    void updateTimer();
};

#endif // PAGE022_H

