/****************************************************************************
**
** Copyright (C) 2021 Francesco Mandracci
** Contact: https://github.com/fmandracci/smart-home
**
** This file is part of the Smart Home Framework.
**
** Commercial License Usage
** Licensees holding valid commercial licenses may use this file in
** accordance with the terms contained in a written agreement
** between you and the copyright owner.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
****************************************************************************/


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
#ifdef KIT_HOST
    // vncString is the '-geometry' argument
    mectScreenWidth = WIDTH;
    mectScreenHeight = HEIGHT;
    mectFontCorrector = FONT_CORRECTOR;
    sprintf(vncString, "%dx%d+%d+%d", WIDTH, HEIGHT, 0, 0);

#else // Q_WS_QWS
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

#if defined(MECT_SUITE_3_5)
    sprintf(vncString, "multi: transformed:linuxfb:rot%d:mmWidth=%d:mmHeight=%d:tty=/dev/tty8:0 vnc:size=%dx%d:0",
            rot, width_mm, height_mm, width, height);
#elif defined(MECT_SUITE_3_4)
    sprintf(vncString, "multi: transformed:linuxfb:rot%d:0 vnc:size=%dx%d:0",
            rot, width, height);
#else
#error
#endif

#endif
#endif
    fprintf(stderr, "vncString='%s' font corrector=%f\n", vncString, mectFontCorrector);

    // ------------ system.ini changes _before_ starting the plc runtime (this is hmi_only !) ------------

    // 1) on TPAC models TPAC1007_04_A{A,C,}: setting internal rtu baudrate
    //    NB: directly reading the model file, because the plc isn't started yet

    if (system("grep -qe TPAC1007_04_A[ACD] /rootfs_version") == 0) { // NB: no TPAC1007_04_A[BE]
        QSettings system_ini("/local/etc/sysconfig/system.ini", QSettings::IniFormat);

        if (system_ini.value("SERIAL_PORT_3/baudrate").toInt() != 225000) {
            system_ini.setValue("SERIAL_PORT_3/baudrate", "225000");
            system_ini.sync();
        }
    }

    // 2) on control types 6 and 16: adjusting serial port 0 parameters
    //    NB: directly reading the retentives file, because the plc isn't started yet

    QFile file("/local/retentive");
    if (file.open(QIODevice::ReadOnly) and file.seek((ID_PLC_control_type - 1) * 4)) {
        QByteArray bytes = file.read(4);

        if (bytes.size() >= 4) {

            if (bytes[0] == (char)ControlType_6) {
                QSettings system_ini("/local/etc/sysconfig/system.ini", QSettings::IniFormat);

                if (system_ini.value("SERIAL_PORT_0/silence_ms").toInt() != 20) {
                    system_ini.setValue("SERIAL_PORT_0/silence_ms", "20");
                    system_ini.sync();
                }
            }
            else if (bytes[0] == (char)ControlType_16) {
                QSettings system_ini("/local/etc/sysconfig/system.ini", QSettings::IniFormat);

                if (system_ini.value("SERIAL_PORT_0/baudrate").toInt() != 9600) {
                    system_ini.setValue("SERIAL_PORT_0/baudrate", "9600");
                    system_ini.sync();
                }
            }
        }
    }

    // -------------------------------------------------------------------------------------------------

    userPageList
            << "system_ini"
            << "page010"
            << "page011"
            << "page012"
            << "page020"
            << "page021"
            << "page022"

//            << "page041"
//            << "page042"
//            << "page043"
//            << "page043e"
//            << "page044"
//            << "page045a"
//            << "page045b"
//            << "page045e"
//            << "page046"
//            << "page047"
//            << "page048"
//            << "page049c"
//            << "page049d"

            << "page100"
            << "page101a"
            << "page101b"
            << "page101c"
            << "page200"
            << "page300"
            << "page400"
            << "page4e0"
            << "page401"
            << "page402"
            << "page500"

               /* add here the label of the new page */
               ;
    userPageList.removeDuplicates();
}

int create_page_nb(page ** p, int pageNb)
{
    switch (pageNb)
    {
    case 0x010:
        *p = (page *)(new page010);
        break;
    case 0x011:
        *p = (page *)(new page011);
        break;
    case 0x012:
        *p = (page *)(new page012);
        break;
    case 0x020:
        *p = (page *)(new page020);
        break;
    case 0x021:
        *p = (page *)(new page021);
        break;
    case 0x022:
        *p = (page *)(new page022);
        break;
    case 0x041:
        *p = (page *)(new page041);
        break;
    case 0x042:
        *p = (page *)(new page042);
        break;
    case 0x043:
        *p = (page *)(new page043);
        break;
    case 0x043e:
        *p = (page *)(new page043e);
        break;
    case 0x044:
        *p = (page *)(new page044);
        break;
    case 0x045a:
        *p = (page *)(new page045a);
        break;
    case 0x045b:
        *p = (page *)(new page045b);
        break;
    case 0x045e:
        *p = (page *)(new page045e);
        break;
    case 0x046:
        *p = (page *)(new page046);
        break;
    case 0x047:
        *p = (page *)(new page047);
        break;
    case 0x048:
        *p = (page *)(new page048);
        break;
    case 0x049c:
        *p = (page *)(new page049c);
        break;
    case 0x049d:
        *p = (page *)(new page049d);
        break;
    case 0x100:
        *p = (page *)(new page100);
        break;
    case 0x101a:
        *p = (page *)(new page101a);
        break;
    case 0x101b:
        *p = (page *)(new page101b);
        break;
    case 0x101c:
        *p = (page *)(new page101c);
        break;
    case 0x200:
        *p = (page *)(new page200);
        break;
    case 0x300:
        *p = (page *)(new page300);
        break;
    case 0x400:
        *p = (page *)(new page400);
        break;
    case 0x4e0:
        *p = (page *)(new page4e0);
        break;
    case 0x401:
        *p = (page *)(new page401);
        break;
    case 0x402:
        *p = (page *)(new page402);
        break;
    case 0x500:
        *p = (page *)(new page500);
        break;

        /* add here the case labeled with the HEX id of the new pages */
    default:
        //printf ("Fatal error: cannot find page %d\n", pageNb);
        *p = NULL;
        return 1;
    }
    return 0;
}
