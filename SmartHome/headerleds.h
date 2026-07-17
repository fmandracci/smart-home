#ifndef HEADERLEDS_H
#define HEADERLEDS_H

#include <QWidget>
#include <QAbstractButton>
#include <QLabel>
#include "mectbutton.h"

namespace Ui {
class HeaderLeds;
}

class HeaderLeds : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderLeds(QWidget *parent = 0);
    ~HeaderLeds();

    void changeWidgets();
    void updateWidgets();

private:
    Ui::HeaderLeds *ui;
};

#endif // HEADERLEDS_H
