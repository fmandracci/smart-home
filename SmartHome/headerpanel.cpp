#include "headerpanel.h"
#include "ui_headerpanel.h"

#include "automation.h"
#include "crosstable.h"

HeaderPanel::HeaderPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderPanel),
    pparent((page *)parent),
    trend()
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    HeaderLeds::translateFontSize(this);
#endif
}

bool HeaderPanel::goto_page(const char *page, bool remember)
{
    emit newPage(page, remember);
    return true;
}

void HeaderPanel::changeWidgets(const char *trend, const char *icon, const char *back, const char *title)
{
    int pointSize_time  = 32; // 28
    int pointSize_bttn  = 36; // 24
    int pointSize_title =  6; //  6

//    if (mectScreenWidth >= 1280) {
//        pointSize_time = 42;
//        pointSize_bttn = 32;
//    } else if (mectScreenWidth >= 800) {
//        pointSize_time = 32;
//        pointSize_bttn = 28;
//    } else {
//        pointSize_time = 28;
//        pointSize_bttn = 24;
//    }

    ui->header_leds->changeHeader();
    ui->pushButton_trend->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(pointSize_bttn));
    ui->pushButton_time->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(pointSize_time));
    ui->label_title->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_N(pointSize_title));
    ui->atcmButton_back->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(pointSize_bttn));
    ui->atcmButton_home->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(pointSize_bttn));

    if (trend)
        HeaderPanel::trend = trend;
    else
        ui->pushButton_trend->setVisible(false);
    if (icon)
        ui->label_icon->setPixmap(QPixmap(icon));
    else
        ui->label_icon->setVisible(false);
    if (back)
        ui->atcmButton_back->setPageName(back);
    else
        ui->atcmButton_back->setVisible(false);
    if (title)
        ui->label_title->setText(title);
    else
        ui->label_title->setVisible(false);
}

void HeaderPanel::updateWidgets(const QString datetime)
{
    ui->header_leds->updateLedLabels();
    if (datetime != NULL)
        ui->pushButton_time->setText(datetime);
    else
        ui->pushButton_time->setText(PLC_nighttime ? TIME_FMT_NIGHTTIME : TIME_FMT_DAYTIME);
}

HeaderPanel::~HeaderPanel()
{
    delete ui;
}
