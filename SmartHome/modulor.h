#ifndef MODULOR_H
#define MODULOR_H

#include <QWidget>
#include <QAbstractButton>
#include <QLabel>
#include <atcmbutton.h>

class Modulor
{
public:
    Modulor(int screen_width_px = 480, int screen_height_px = 272, float fontCorrector = 1.0);

    int ledSize_px()       { return led_size_px;    }

    int doubleSize_px()    { return double_size_px; }
    int tripleSize_px()    { return triple_size_px; }
    int quadrupleSize_px() { return quadruple_size_px; }

    int bodyHeight_px()    { return body_height_px; }

    int hugeFont_px()      { return huge_font_px; }
    int LARGEFont_px()     { return LARGE_font_px; }
    int LargeFont_px()     { return Large_font_px; }
    int largeFont_px()     { return large_font_px; }
    int normalFont_px()    { return normal_font_px; }
    int smallFont_px()     { return small_font_px; }
    int tinyFont_px()      { return tiny_font_px; }

    void scaleIconLabel(QLabel *button);
    void scaleDoubleButton(QAbstractButton *button);
    void scaleTripleButton(QAbstractButton *button);
    void scaleQuadrupleButton(ATCMbutton *button);
    void scaleMainButton(ATCMbutton *button);

    void translateFontSize(QWidget *ui );
    void scaleWidgetFontSize(QWidget *uiWidget, float newScaleFactor);

private:
    int screen_width_px;
    int screen_height_px;
    float font_corrector;

    int led_size_px;
    int double_size_px;
    int triple_size_px;
    int quadruple_size_px;
    int body_height_px;

    int huge_font_px;
    int LARGE_font_px;
    int Large_font_px;
    int large_font_px;
    int normal_font_px;
    int small_font_px;
    int tiny_font_px;
};

#endif // MODULOR_H
