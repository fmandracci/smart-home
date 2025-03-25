#ifndef HEADERLEDS_H
#define HEADERLEDS_H

#include <QWidget>

namespace Ui {
class HeaderLeds;
}

class HeaderLeds : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderLeds(QWidget *parent = 0);
    ~HeaderLeds();

    void changeHeader();
    void updateWidget();

private:
    Ui::HeaderLeds *ui;
};

#endif // HEADERLEDS_H
