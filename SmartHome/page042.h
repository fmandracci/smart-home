/**
 * @file
 *
 * @section LICENSE
 * Copyright Mect s.r.l. 2013
 *
 * @brief Main page
 */
#ifndef PAGE042_H
#define PAGE042_H

#include "pagebrowser.h"

#include <QLabel>

namespace Ui {
class page042;
}

class page042 : public page
{
    Q_OBJECT

public:
    explicit page042(QWidget *parent = 0);
    ~page042();
    virtual void reload(void);
    virtual void updateData();

private slots:
    void changeEvent(QEvent * event);

private:
    void resizeLabelFont(QLabel *myLabel, float fontFactor);
    Ui::page042 *ui;
};

#endif // PAGE042_H

