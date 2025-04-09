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



#ifndef PAGE500_H
#define PAGE500_H

#include "pagebrowser.h"

#include <QLabel>
#include "automation.h"

namespace Ui {
class page500;
}

class page500 : public page
{
    Q_OBJECT
    
public:
    explicit page500(QWidget *parent = 0);
    ~page500();
    virtual void reload(void);
    virtual void updateData();
    
private slots:
    void changeEvent(QEvent * event);
    void on_pushButton_time_clicked() { goto_page("page020"); }

    void on_pushButton_OFF_clicked();
    void on_pushButton_DAYTIME_clicked();
    void on_pushButton_NIGHTTIME_clicked();
    void on_pushButton_EVERYTHING_clicked();
    void on_pushButton_TESTING_clicked();
    void on_pushButton_ENABLED_clicked();
    void on_pushButton_MUTED_clicked();
    void on_pushButton_RINGING_clicked();

private:
    Ui::page500 *ui;
    const QString   ACTIVE_StyleSheet;
    const QString Possible_StyleSheet;
    const QString inactive_StyleSheet;
    const QString    GREY_OVER_BLACK;
    const QString   GREEN_OVER_BLACK;
    const QString     RED_OVER_BLACK;
    const QString  ORANGE_OVER_BLACK;
    const QString MAGENTA_OVER_BLACK;

    void enableDisableCommands();
    void sendCommand(uint32_t command);
    // unsigned old_sensor_status[1 + ALARM_SENSORS_MAX]; // starts @ 1
    void updateSensor(int i, unsigned status, QLabel *label_ok, QLabel *label_sensor);
    void changeWidgets();
    void updateWidgets();
};

#endif // PAGE500_H

