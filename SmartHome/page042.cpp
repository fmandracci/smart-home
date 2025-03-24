/**
 * @file
 *
 * @section LICENSE
 * Copyright Mect s.r.l. 2013
 *
 * @brief Generic page
 */
#include "app_logprint.h"
#include "atcmplugin.h"
#include "main.h"
#include "page042.h"
#include "ui_page042.h"
#include "crosstable.h"

#include <QDebug>
#include <QFontMetrics>
#include <QProcess>

/**
 * @brief this macro is used to set the PAGE042 style.
 * the syntax is html stylesheet-like
 */
#define SET_PAGE042_STYLE() { \
    QString mystyle; \
    mystyle.append(this->styleSheet()); \
    /* add there the page stylesheet customization */ \
    mystyle.append(""); \
    this->setStyleSheet(mystyle); \
    }

/**
 * @brief This is the constructor. The operation written here, are executed only one time: at the instantiation of the page.
 */
page042::page042(QWidget *parent) :
    page(parent),
    ui(new Ui::page042)
{
    ui->setupUi(this);
    /* set here the protection level (pwd_admin_e, pwd_super_user_e, pwd_user_e, pwd_operator_e), default is pwd_operator_e
     * protection_level = pwd_operator_e;
     */

    /* set up the page style */
    //SET_PAGE_STYLE();
    /* set the style described into the macro SET_PAGE042_STYLE */
    SET_PAGE042_STYLE();

    // NB: Questa pagina NON utilizza translateFontSize per permettere di calcolare un fattore di scalamento ragionevole per i Font DejaVu Sans e Ubuntu
    // translateFontSize(this);

    // Font Scale Factor
    // float scaleFactor = 0.6411;
    float scaleFactor = 0.6342;  // 10"
    // float scaleFactor = 0.678;      // 15"

    resizeLabelFont(ui->label100px, scaleFactor);
    resizeLabelFont(ui->label50px, scaleFactor);
    resizeLabelFont(ui->label25px, scaleFactor);

    resizeLabelFont(ui->label100px_2, scaleFactor);
    resizeLabelFont(ui->label50px_2, scaleFactor);
    resizeLabelFont(ui->label25px_2, scaleFactor);

}

void page042::resizeLabelFont(QLabel *myLabel, float fontFactor)
{
    QFont labelFont = QFont(myLabel->font());
    labelFont.setPointSize( (labelFont.pointSize() * fontFactor));
    myLabel->setFont(labelFont);
}


/**
 * @brief This is the reload member. The operation written here, are executed every time this page is shown.
 */
void page042::reload()
{
    // Font DejaVu Sans
    QFontMetrics fmLabel100(ui->label100px->font());
    QFontMetrics fmLabel50(ui->label50px->font());
    QFontMetrics fmLabel25(ui->label25px->font());
    qDebug("Font DejaVu Sans Label Size for label100: W:%d - H:%d Bounding Rect: W:%d H:%d", fmLabel100.width(ui->label100px->text()), fmLabel100.height(), fmLabel100.boundingRect(ui->label100px->text()).width(), fmLabel100.boundingRect(ui->label100px->text()).height());
    qDebug("Font DejaVu Sans Label Size for label50:  W:%d - H:%d Bounding Rect: W:%d H:%d", fmLabel50.width(ui->label50px->text()), fmLabel50.height(), fmLabel50.boundingRect(ui->label50px->text()).width(), fmLabel50.boundingRect(ui->label50px->text()).height());
    qDebug("Font DejaVu Sans Label Size for label25:  W:%d - H:%d Bounding Rect: W:%d H:%d", fmLabel25.width(ui->label25px->text()), fmLabel25.height(), fmLabel25.boundingRect(ui->label25px->text()).width(), fmLabel25.boundingRect(ui->label25px->text()).height());
    // Font Ubuntu
    QFontMetrics fmLabel100_2(ui->label100px_2->font());
    QFontMetrics fmLabel50_2(ui->label50px_2->font());
    QFontMetrics fmLabel25_2(ui->label25px_2->font());
    qDebug("Font Ubuntu Label Size for label100_2: W:%d - H:%d Bounding Rect: W:%d H:%d", fmLabel100_2.width(ui->label100px_2->text()), fmLabel100_2.height(), fmLabel100_2.boundingRect(ui->label100px_2->text()).width(), fmLabel100_2.boundingRect(ui->label100px_2->text()).height());
    qDebug("Font Ubuntu Label Size for label50_2:  W:%d - H:%d Bounding Rect: W:%d H:%d", fmLabel50_2.width(ui->label50px_2->text()), fmLabel50_2.height(), fmLabel50_2.boundingRect(ui->label50px_2->text()).width(), fmLabel50_2.boundingRect(ui->label50px_2->text()).height());
    qDebug("Font Ubuntu Label Size for label25_2:  W:%d - H:%d Bounding Rect: W:%d H:%d", fmLabel25_2.width(ui->label25px_2->text()), fmLabel25_2.height(), fmLabel25_2.boundingRect(ui->label25px_2->text()).width(), fmLabel25_2.boundingRect(ui->label25px_2->text()).height());
}

/**
 * @brief This is the updateData member. The operation written here, are executed every REFRESH_MS milliseconds.
 */
void page042::updateData()
{
    if (this->isVisible() == false)
    {
        return;
    }
    /* call the parent updateData member */
    page::updateData();

    /* To read the cross table variable UINT TEST1:
     *    uint_16 tmp = TEST1;
     */
    /* To write 5 into the the cross table variable UINT TEST1:
     *    doWrite_TEST1(5);
     */
}

/**
 * @brief This is the event slot to detect new language translation.
 */
void page042::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

/**
 * @brief This is the distructor member. The operation written here, are executed only one time when the page will be deleted.
 */
page042::~page042()
{
    delete ui;
}

