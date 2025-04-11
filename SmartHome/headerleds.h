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
    void updateLedLabels();
    static void translateFontSize( QWidget *ui );
    static void scaleWidgetFontSize(QWidget *uiWidget, float newScaleFactor);

private:
    Ui::HeaderLeds *ui;
};

#endif // HEADERLEDS_H
