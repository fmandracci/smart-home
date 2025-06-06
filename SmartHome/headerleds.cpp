#include "headerleds.h"
#include "ui_headerleds.h"

#include "automation.h"

HeaderLeds::HeaderLeds(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderLeds)
{
    ui->setupUi(this);
    TRANSLATE_FONT_SIZE(this);
}

void HeaderLeds::changeWidgets()
{
    this->setMinimumWidth(modulor->tripleSize_px());
    this->setMaximumWidth(modulor->tripleSize_px());

    this->setMinimumHeight(modulor->quadrupleSize_px());
    this->setMaximumHeight(modulor->quadrupleSize_px());

    // implicit:
    // ui->label_XX->setMaximumWidth(modulor->ledSize_px());
    // ui->label_XX->setMaximumHeight(modulor->ledSize_px());

    this->repaint();
}

void HeaderLeds::updateWidgets()
{
    const QString       RED_OVER_BLACK = QString("color: rgb(255,   0,   0); background-color: rgb(0, 0, 0); font: %1px \"DejaVu Sans\";\n").arg(modulor->ledSize_px());
    const QString     GREEN_OVER_BLACK = QString("color: rgb(  0, 255,   0); background-color: rgb(0, 0, 0); font: %1px \"DejaVu Sans\";\n").arg(modulor->ledSize_px());
    const QString    YELLOW_OVER_BLACK = QString("color: rgb(255, 255,   0); background-color: rgb(0, 0, 0); font: %1px \"DejaVu Sans\";\n").arg(modulor->ledSize_px());
    const QString      GREY_OVER_BLACK = QString("color: rgb( 64,  64,  64); background-color: rgb(0, 0, 0); font: %1px \"DejaVu Sans\";\n").arg(modulor->ledSize_px());
    const QString DARK_GREY_OVER_BLACK = QString("color: rgb( 32,  32,  32); background-color: rgb(0, 0, 0); font: %1px \"DejaVu Sans\";\n").arg(modulor->ledSize_px());
    const QString   MAGENTA_OVER_BLACK = QString("color: rgb(255,   0, 255); background-color: rgb(0, 0, 0); font: %1px \"DejaVu Sans\";\n").arg(modulor->ledSize_px());
    const QString      CYAN_OVER_BLACK = QString("color: rgb(  0, 255, 255); background-color: rgb(0, 0, 0); font: %1px \"DejaVu Sans\";\n").arg(modulor->ledSize_px());

    const QString     RED_OVER_BLACK_BORDER = RED_OVER_BLACK     + "border: 1px solid rgb(255,   0,   0);";
    const QString  YELLOW_OVER_BLACK_BORDER = YELLOW_OVER_BLACK  + "border: 1px solid rgb(255, 255,   0);";
    const QString MAGENTA_OVER_BLACK_BORDER = MAGENTA_OVER_BLACK + "border: 1px solid rgb(255,   0, 255);";
    const QString    CYAN_OVER_BLACK_BORDER = CYAN_OVER_BLACK    + "border: 1px solid rgb(  0, 255, 255);";

    if (PLC_EP_exists) {
        ui->label_EP->setText(LABEL_EP);
        if (not PLC_EP_isOK) {
            ui->label_EP->setStyleSheet(PLC_Iam_EP ? MAGENTA_OVER_BLACK_BORDER : MAGENTA_OVER_BLACK);
        } else if (PLC_EP_BlackoutDetected || PLC_EP_OverloadDetected) {
            ui->label_EP->setStyleSheet(PLC_Iam_EP ? RED_OVER_BLACK_BORDER : RED_OVER_BLACK);
        } else {
            ui->label_EP->setStyleSheet(PLC_Iam_EP ? CYAN_OVER_BLACK_BORDER : GREEN_OVER_BLACK);
        }
    } else {
        ui->label_EP->setText(LABEL_EP);
        ui->label_EP->setStyleSheet(DARK_GREY_OVER_BLACK);
    }

    if (PLC_BA_exists) {
        ui->label_BA->setText(LABEL_BA);
        if (not PLC_BA_isOK) {
            ui->label_BA->setStyleSheet(PLC_Iam_BA ? MAGENTA_OVER_BLACK_BORDER : MAGENTA_OVER_BLACK);
        } else if (PLC_BA_AlarmRinging || PLC_BA_BlackoutDetected) {
            ui->label_BA->setStyleSheet(PLC_Iam_BA ? RED_OVER_BLACK_BORDER : RED_OVER_BLACK);
        } else {
            ui->label_BA->setStyleSheet(PLC_Iam_BA ? CYAN_OVER_BLACK_BORDER : GREEN_OVER_BLACK);
        }
    } else {
        ui->label_BA->setText(LABEL_BA);
        ui->label_BA->setStyleSheet(DARK_GREY_OVER_BLACK);
    }

    if (PLC_BA_exists) {
        ui->label_green->setText(LABEL_B_CIRCLE);
        if (not PLC_BA_isOK) {
            ui->label_green->setStyleSheet(MAGENTA_OVER_BLACK);
        } else if (PLC_BA_led_green) {
            ui->label_green->setStyleSheet(GREEN_OVER_BLACK);
        } else {
            ui->label_green->setStyleSheet(GREY_OVER_BLACK);
        }
    } else {
        ui->label_green->setText(LABEL_B_CIRCLE);
        ui->label_green->setStyleSheet(DARK_GREY_OVER_BLACK);
    }

    if (PLC_BA_exists) {
        ui->label_red->setText(LABEL_B_CIRCLE);
        if (not PLC_BA_isOK) {
            ui->label_red->setStyleSheet(MAGENTA_OVER_BLACK);
        } else if (PLC_BA_led_red) {
            ui->label_red->setStyleSheet(RED_OVER_BLACK);
        } else {
            ui->label_red->setStyleSheet(GREY_OVER_BLACK);
        }
    } else {
        ui->label_red->setText(LABEL_B_CIRCLE);
        ui->label_red->setStyleSheet(DARK_GREY_OVER_BLACK);
    }

    if (PLC_BA_exists) {
        ui->label_yellow_1->setText(LABEL_B_CIRCLE);
        if (not PLC_BA_isOK) {
            ui->label_yellow_1->setStyleSheet(MAGENTA_OVER_BLACK);
        } else if (PLC_BA_led_yellow1) {
            ui->label_yellow_1->setStyleSheet(YELLOW_OVER_BLACK);
        } else {
            ui->label_yellow_1->setStyleSheet(GREY_OVER_BLACK);
        }
    } else {
        ui->label_yellow_1->setText(LABEL_B_CIRCLE);
        ui->label_yellow_1->setStyleSheet(DARK_GREY_OVER_BLACK);
    }

    if (PLC_BA_exists) {
        ui->label_yellow_2->setText(LABEL_B_CIRCLE);
        if (not PLC_BA_isOK) {
            ui->label_yellow_2->setStyleSheet(MAGENTA_OVER_BLACK);
        } else if (PLC_BA_led_yellow2) {
            ui->label_yellow_2->setStyleSheet(YELLOW_OVER_BLACK);
        } else {
            ui->label_yellow_2->setStyleSheet(GREY_OVER_BLACK);
        }
    } else {
        ui->label_yellow_2->setText(LABEL_B_CIRCLE);
        ui->label_yellow_2->setStyleSheet(DARK_GREY_OVER_BLACK);
    }

    if (PLC_Tn_count >= 1) {
        ui->label_T1->setText(PLC_T1_heating ? LABEL_01_ON : LABEL_01);
        if (not PLC_T1_isOK) {
            ui->label_T1->setStyleSheet(PLC_Iam_T1 ? MAGENTA_OVER_BLACK_BORDER : MAGENTA_OVER_BLACK);
        } else if (PLC_T1_heating) {
            ui->label_T1->setStyleSheet(PLC_Iam_T1 ? YELLOW_OVER_BLACK_BORDER : YELLOW_OVER_BLACK);
        } else {
            ui->label_T1->setStyleSheet(PLC_Iam_T1 ? CYAN_OVER_BLACK_BORDER : GREEN_OVER_BLACK);
        }
    } else {
        ui->label_T1->setText(LABEL_01);
        ui->label_T1->setStyleSheet(DARK_GREY_OVER_BLACK);
    }

    if (PLC_Tn_count >= 2) {
        ui->label_T2->setText(PLC_T2_heating ? LABEL_02_ON : LABEL_02);
        if (not PLC_T2_isOK) {
            ui->label_T2->setStyleSheet(PLC_Iam_T2 ? MAGENTA_OVER_BLACK_BORDER : MAGENTA_OVER_BLACK);
        } else if (PLC_T2_heating) {
            ui->label_T2->setStyleSheet(PLC_Iam_T2 ? YELLOW_OVER_BLACK_BORDER : YELLOW_OVER_BLACK);
        } else {
            ui->label_T2->setStyleSheet(PLC_Iam_T2 ? CYAN_OVER_BLACK_BORDER : GREEN_OVER_BLACK);
        }
    } else {
        ui->label_T2->setText(LABEL_02);
        ui->label_T2->setStyleSheet(DARK_GREY_OVER_BLACK);
    }

    if (PLC_Tn_count >= 3) {
        ui->label_T3->setText(PLC_T3_heating ? LABEL_03_ON : LABEL_03);
        if (not PLC_T3_isOK) {
            ui->label_T3->setStyleSheet(PLC_Iam_T3 ? MAGENTA_OVER_BLACK_BORDER : MAGENTA_OVER_BLACK);
        } else if (PLC_T3_heating) {
            ui->label_T3->setStyleSheet(PLC_Iam_T3 ? YELLOW_OVER_BLACK_BORDER : YELLOW_OVER_BLACK);
        } else {
            ui->label_T3->setStyleSheet(PLC_Iam_T3 ? CYAN_OVER_BLACK_BORDER : GREEN_OVER_BLACK);
        }
    } else {
        ui->label_T3->setText(LABEL_03);
        ui->label_T3->setStyleSheet(DARK_GREY_OVER_BLACK);
    }

    if (PLC_Tn_count >= 4) {
        ui->label_T4->setText(PLC_T4_heating ? LABEL_04_ON : LABEL_04);
        if (not PLC_T4_isOK) {
            ui->label_T4->setStyleSheet(PLC_Iam_T4 ? MAGENTA_OVER_BLACK_BORDER : MAGENTA_OVER_BLACK);
        } else if (PLC_T4_heating) {
            ui->label_T4->setStyleSheet(PLC_Iam_T4 ? YELLOW_OVER_BLACK_BORDER : YELLOW_OVER_BLACK);
        } else {
            ui->label_T4->setStyleSheet(PLC_Iam_T4 ? CYAN_OVER_BLACK_BORDER : GREEN_OVER_BLACK);
        }
    } else {
        ui->label_T4->setText(LABEL_04);
        ui->label_T4->setStyleSheet(DARK_GREY_OVER_BLACK);
    }

    if (PLC_Tn_count >= 5) {
        ui->label_T5->setText(PLC_T5_heating ? LABEL_05_ON : LABEL_05);
        if (not PLC_T5_isOK) {
            ui->label_T5->setStyleSheet(PLC_Iam_T5 ? MAGENTA_OVER_BLACK_BORDER : MAGENTA_OVER_BLACK);
        } else if (PLC_T5_heating) {
            ui->label_T5->setStyleSheet(PLC_Iam_T5 ? YELLOW_OVER_BLACK_BORDER : YELLOW_OVER_BLACK);
        } else {
            ui->label_T5->setStyleSheet(PLC_Iam_T5 ? CYAN_OVER_BLACK_BORDER : GREEN_OVER_BLACK);
        }
    } else {
        ui->label_T5->setText(LABEL_05);
        ui->label_T5->setStyleSheet(DARK_GREY_OVER_BLACK);
    }

    if (PLC_Tn_count >= 6) {
        ui->label_T6->setText(PLC_T6_heating ? LABEL_06_ON : LABEL_06);
        if (not PLC_T6_isOK) {
            ui->label_T6->setStyleSheet(PLC_Iam_T6 ? MAGENTA_OVER_BLACK_BORDER : MAGENTA_OVER_BLACK);
        } else if (PLC_T6_heating) {
            ui->label_T6->setStyleSheet(PLC_Iam_T6 ? YELLOW_OVER_BLACK_BORDER : YELLOW_OVER_BLACK);
        } else {
            ui->label_T6->setStyleSheet(PLC_Iam_T6 ? CYAN_OVER_BLACK_BORDER : GREEN_OVER_BLACK);
        }
    } else {
        ui->label_T6->setText(LABEL_06);
        ui->label_T6->setStyleSheet(DARK_GREY_OVER_BLACK);
    }
}

HeaderLeds::~HeaderLeds()
{
    delete ui;
}
