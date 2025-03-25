#include "headerleds.h"
#include "ui_headerleds.h"

#include "automation.h"

HeaderLeds::HeaderLeds(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderLeds)
{
    ui->setupUi(this);
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

void HeaderLeds::updateWidget()
{
    updateLedLabels(ui->label_EP, ui->label_BA, ui->label_green,
                    ui->label_T5, ui->label_T6, ui->label_red,
                    ui->label_T3, ui->label_T4, ui->label_yellow_1,
                    ui->label_T1, ui->label_T2, ui->label_yellow_2);
}
