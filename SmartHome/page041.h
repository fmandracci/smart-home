/**
 * @file
 *
 * @section LICENSE
 * Copyright Mect s.r.l. 2013
 *
 * @brief Main page
 */
#ifndef PAGE041_H
#define PAGE041_H

#include "pagebrowser.h"

namespace Ui {
class page041;
}

class page041 : public page
{
    Q_OBJECT

public:
    explicit page041(QWidget *parent = 0);
    ~page041();
    virtual void reload(void);
    virtual void updateData();

private slots:
    void changeEvent(QEvent * event);

private:
    Ui::page041 *ui;
    void changeWidgets();
    void updateWidgets();
};

#endif // PAGE041_H

