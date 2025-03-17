/**
 * @file
 *
 * @section LICENSE
 * Copyright Mect s.r.l. 2025
 *
 * @brief Selector of the new pages
 */
#include <math.h>

#include "app_logprint.h"
#include "crosstable.h"
#include "global_var.h"
#include "utility.h"
#include "pages.h"

#include "automation.h"

#include <QFile>
#include <QString>
#include <QSettings>

void printVncDisplayString(char * vncString)
{
    // Fix for i.mx28 projects
#ifdef KIT_IMX28
#define FONT_CORRECTOR 1.666666667      // Previous 5/3
#endif

#ifdef KIT_HOST
    // vncString is the '-geometry' argument
    mectScreenWidth = WIDTH;
    mectScreenHeight = HEIGHT;
    mectFontCorrector = 1.0;            // No font Correction in Kit Host
    sprintf(vncString, "%dx%d+%d+%d", WIDTH, HEIGHT, 0, 0);
#else // Q_WS_QWS usage
    // vncString is the '-display' argument
#define RESIZABLE_APPLICATION
#ifndef RESIZABLE_APPLICATION
    // fixed display size application
    mectScreenWidth = WIDTH;
    mectScreenHeight = HEIGHT;
    mectFontCorrector = FONT_CORRECTOR;
    sprintf(vncString, "multi: transformed:linuxfb:rot%d:0 VNC:size=%dx%d:0", ROTATION, WIDTH, HEIGHT);
#else
    // variable display size application

    int width, height, rot; // QApplication arguments
    int width_px, height_px; // physical display size in pixels
    int width_mm, height_mm; // physical display size in millimeters
    float fontCorrector = FONT_CORRECTOR;

    // what the wizard wrote in template.pri?
    rot = ROTATION;
    if (rot == 270 || rot == 90) {
        width_px = HEIGHT;
        height_px = WIDTH;
    } else {
        width_px = WIDTH;
        height_px = HEIGHT;
    }
    width_mm = WIDTH_mm;
    height_mm = HEIGHT_mm;

    // what the kernel knows? ---> maybe a different display size
    QFile virtual_size("/sys/class/graphics/fb0/virtual_size");
    if (virtual_size.open(QIODevice::ReadOnly)) {
        char buf[42];

        if (virtual_size.readLine(buf, 42) > 0) {
            int w = width_px, h = height_px;

            if (sscanf(buf, "%d,%d", &w, &h) == 2) {
                width_px = w;
                height_px = h;
            }
        }
    }

    // what the user set in hmi.ini? --> maybe a different orientation
    QSettings *options = new QSettings(HMI_INI_FILE, QSettings::IniFormat);
    if (options) {
        bool ok;
        int value;
        float fValue;

        value = options->value("rotation", rot).toInt(&ok);
        if (ok)
            rot = value;

        value = options->value("width_mm", width_mm).toInt(&ok);
        if (ok && value > 0)
            width_mm = value;

        value = options->value("height_mm", height_mm).toInt(&ok);
        if (ok && value > 0)
            height_mm = value;

        fValue = options->value("font_corrector", fontCorrector).toFloat(&ok);
        if (ok && fValue != 0)
            fontCorrector = fValue;
    }

    // set QApplication arguments
    switch (rot) {
    case 0:
    case 180:
        width = width_px; height = height_px;
        break;
    case 90:
    case 270:
        width = height_px; height = width_px;
        break;
    default:
        rot = 0;
        width = width_px; height = height_px;
    }

    mectScreenWidth = width;
    mectScreenHeight = height;
    mectFontCorrector = fontCorrector;

    sprintf(vncString, "multi: transformed:linuxfb:rot%d:mmWidth=%d:mmHeight=%d:tty=/dev/tty8:0 vnc:size=%dx%d:0", rot, width_mm, height_mm, width, height);

#endif
#endif
    fprintf(stderr, "vncString='%s' font corrector=%f\n", vncString, mectFontCorrector);

    userPageList
            << "system_ini"
            << "page100"
               /* add here the label of the new page */
               ;
    userPageList.removeDuplicates();
}

int create_page_nb(page ** p, int pageNb)
{
    switch (pageNb)
    {
    case 0x100:
        *p = (page *)(new page100);
        break;
        /* add here the case labeled with the HEX id of the new pages */
    default:
        //printf ("Fatal error: cannot find page %d\n", pageNb);
        *p = NULL;
        return 1;
    }
    return 0;
}


