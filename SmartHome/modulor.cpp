#include "modulor.h"

Modulor::Modulor(int screenWidth_px, int screenHeight_px, float fontCorrector)
: screen_width_px(screenWidth_px)
, screen_height_px(screenHeight_px)
, font_corrector(fontCorrector)
{
    if (screen_width_px >= 1280) {       // 1280x800
        led_size_px = 48;
    } else if (screen_width_px >= 800) { //  800x480
        led_size_px = 30;
    } else {                            //  480x272
        led_size_px = 18;
    }

    leds_width_px  = 3 * led_size_px;
    leds_height_px = 4 * led_size_px;

    title_height_px = 1 * led_size_px;
    time_height_px = leds_width_px;
    body_height_px = screen_height_px - leds_height_px;

    title_font_px = title_height_px * 9 / 10;
    time_font_px  = time_height_px  * 9 / 10;

    huge_font_px   = led_size_px * 70 / 10;
    Large_font_px  = led_size_px * 20 / 10;
    large_font_px  = led_size_px * 15 / 10;
    normal_font_px = led_size_px * 10 / 10;
    small_font_px  = led_size_px *  5 / 10;
    tiny_font_px   = led_size_px *  4 / 10;
}

void Modulor::scaleIconLabel(QLabel *label)
{
    if (label) {
        int size_px = 2 * led_size_px;

        label->setMaximumWidth(size_px);
        label->setMaximumHeight(size_px);
    }
}

void Modulor::scaleButton(QAbstractButton *button)
{
    if (button) {
        int size_px = 3 * led_size_px;

        button->setMinimumWidth(size_px);
        button->setMinimumHeight(size_px);
        button->setMaximumWidth(size_px);
        button->setMaximumHeight(size_px);
        button->setIconSize(QSize(size_px, size_px));
    }
}

void Modulor::scaleMainButton(ATCMbutton *button)
{
    if (button) {
        int button_size_px = 5 * led_size_px;
        int icon_size_px = 4 * led_size_px;
        int border_size_px;

        if (screen_width_px >= 1280) {       // 1280x800
            border_size_px = 9;
        } else if (screen_width_px >= 800) { // 800x480
            border_size_px = 7;
        } else {                             // 480x272
            border_size_px = 5;
        }

        button->setMinimumWidth(button_size_px);
        button->setMinimumHeight(button_size_px);
        button->setMaximumWidth(button_size_px);
        button->setMaximumHeight(button_size_px);

        button->setIconSize(QSize(icon_size_px, icon_size_px));

        button->setBorderWidth(border_size_px);
        button->setBorderRadius(button_size_px + 2 * border_size_px + 1);
    }
}

// ----------------------------------------------------------------------------

void Modulor::translateFontSize(QWidget *ui )
{
    QObject *w;

    if (ui) {
        scaleWidgetFontSize(ui, font_corrector);
        foreach (w, ui->children()) {
            QWidget *ww = dynamic_cast<QWidget *>(w);
            if (ww) {
                scaleWidgetFontSize(ww, font_corrector);
            }
        }
    }
}

void Modulor::scaleWidgetFontSize(QWidget *uiWidget, float newScaleFactor)
{
    if (uiWidget and newScaleFactor != 0) {
        QFont wFont = QFont(uiWidget->font());

        wFont.setPointSize( (wFont.pointSize() * newScaleFactor));
        uiWidget->setFont(wFont);
    }
}
