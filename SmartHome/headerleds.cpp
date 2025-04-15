#include "headerleds.h"
#include "ui_headerleds.h"

#include "automation.h"

HeaderLeds::HeaderLeds(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderLeds)
{
    ui->setupUi(this);
#ifdef USE_TRANSLATEFONTSIZE
    HeaderLeds::translateFontSize(this);
#endif
}

void HeaderLeds::translateFontSize( QWidget *ui )
{
    QObject *w;

    if (ui) {
        scaleWidgetFontSize(ui, mectFontCorrector);
        foreach (w, ui->children()) {
            QWidget *ww = dynamic_cast<QWidget *>(w);
            if (ww) {
                scaleWidgetFontSize(ww, mectFontCorrector);
            }
        }
    }
}

void HeaderLeds::scaleWidgetFontSize(QWidget *uiWidget, float newScaleFactor)
{
    if (uiWidget and newScaleFactor != 0) {
        QFont wFont = QFont(uiWidget->font());

        wFont.setPointSize( (wFont.pointSize() * newScaleFactor));
        uiWidget->setFont(wFont);
    }
}

HeaderLeds::~HeaderLeds()
{
    delete ui;
}

void HeaderLeds::changeHeader()
{
    ::changeHeader(NULL, NULL,
                 ui->label_EP, ui->label_BA, ui->label_green,
                 ui->label_T5, ui->label_T6, ui->label_red,
                 ui->label_T3, ui->label_T4, ui->label_yellow_1,
                 ui->label_T1, ui->label_T2, ui->label_yellow_2);
}

void HeaderLeds::updateLedLabels()
{
    ::updateLedLabels(ui->label_EP, ui->label_BA, ui->label_green,
                    ui->label_T5, ui->label_T6, ui->label_red,
                    ui->label_T3, ui->label_T4, ui->label_yellow_1,
                    ui->label_T1, ui->label_T2, ui->label_yellow_2);
}
