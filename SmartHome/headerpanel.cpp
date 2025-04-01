#include "headerpanel.h"
#include "ui_headerpanel.h"

#include "automation.h"
#include "crosstable.h"

HeaderPanel::HeaderPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderPanel),
    pparent((page *)parent)
{
    ui->setupUi(this);
}

bool HeaderPanel::goto_page(const char *page, bool remember)
{
    emit newPage(page, remember);
    return true;
}

void HeaderPanel::changeWidgets()
{
    int pointSize_time;
    int pointSize_home;

    if (mectScreenWidth >= 1280) {
        pointSize_time = 42;
        pointSize_home = 32;
    } else if (mectScreenWidth >= 800) {
        pointSize_time = 32;
        pointSize_home = 28;
    } else {
        pointSize_time = 28;
        pointSize_home = 24;
    }

    ui->header_leds->changeHeader();
    ui->pushButton_time->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(pointSize_time));
    ui->atcmButton_home->setStyleSheet(COLOR_SS(COLOR_HEADER) + FONT_SS_B(pointSize_home));
}

void HeaderPanel::updateWidgets()
{
    ui->header_leds->updateLedLabels();
    ui->pushButton_time->setText(PLC_nighttime ? TIME_FMT_NIGHTTIME : TIME_FMT_DAYTIME);
}

HeaderPanel::~HeaderPanel()
{
    delete ui;
}
