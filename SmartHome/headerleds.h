#ifndef HEADERLEDS_H
#define HEADERLEDS_H

#include <QWidget>
#include <QAbstractButton>
#include <QLabel>

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

    int ledSize_px()      { return led_size_px;    }
    int ledsWidth_px()    { return leds_width_px;  }
    int ledsHeight_px()   { return leds_height_px; }

    int timeHeight_px()   { return leds_width_px;  }
    int timeFont_px()     { return leds_width_px * 9 / 10; }

    int titleHeight_px()  { return led_size_px;    }
    int titleFont_px()    { return led_size_px * 6 / 10; }

    void scaleIconLabel(QLabel *button, int size_px = 0);
    void scaleButton(QAbstractButton *button, int size_px = 0);

    static void translateFontSize( QWidget *ui );
    static void scaleWidgetFontSize(QWidget *uiWidget, float newScaleFactor);

private:
    Ui::HeaderLeds *ui;
    int led_size_px;
    int leds_width_px;
    int leds_height_px;
};

#endif // HEADERLEDS_H
