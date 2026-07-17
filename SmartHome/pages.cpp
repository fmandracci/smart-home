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

#include <QApplication>
#include <QIcon>
#include <QFile>
#include <QString>
#include <QSettings>

void beforeMectScreenSetup()
{
    // set project default values

    mectScreenWidth     = WIDTH;
    mectScreenHeight    = HEIGHT;
    mectScreenWidth_mm  = WIDTH_mm;
    mectScreenHeight_mm = HEIGHT_mm;
    mectScreenRotation  = ROTATION;
    mectFontCorrector   = FONT_CORRECTOR;
}

void afterMectScreenSetup()
{
    // use effective values (if necessary)

    modulor = new Modulor(mectScreenWidth, mectScreenHeight, mectFontCorrector);

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
}

void setMectPageList()
{
    mectPageList
            << "system_ini"
            << "page010"
            << "page011"
            << "page012"
            << "page020"
            << "page021"
            << "page022"

            << "page041"
            << "page042"
            << "page043"
            << "page043e"
            << "page044"
            << "page045a"
            << "page045b"
            << "page045e"
            << "page046"
            << "page047"
            << "page048"
            << "page049c"
            << "page049d"

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
}

page *createPageByNumber(int pageNb)
{
    page *retval = nullptr;

    switch (pageNb)
    {
    case 0x010:
        retval = (page *)(new page010);
        break;
    case 0x011:
        retval = (page *)(new page011);
        break;
    case 0x012:
        retval = (page *)(new page012);
        break;
    case 0x020:
        retval = (page *)(new page020);
        break;
    case 0x021:
        retval = (page *)(new page021);
        break;
    case 0x022:
        retval = (page *)(new page022);
        break;
    case 0x041:
        retval = (page *)(new page041);
        break;
    case 0x042:
        retval = (page *)(new page042);
        break;
    case 0x043:
        retval = (page *)(new page043);
        break;
    case 0x043e:
        retval = (page *)(new page043e);
        break;
    case 0x044:
        retval = (page *)(new page044);
        break;
    case 0x045a:
        retval = (page *)(new page045a);
        break;
    case 0x045b:
        retval = (page *)(new page045b);
        break;
    case 0x045e:
        retval = (page *)(new page045e);
        break;
    case 0x046:
        retval = (page *)(new page046);
        break;
    case 0x047:
        retval = (page *)(new page047);
        break;
    case 0x048:
        retval = (page *)(new page048);
        break;
    case 0x049c:
        retval = (page *)(new page049c);
        break;
    case 0x049d:
        retval = (page *)(new page049d);
        break;
    case 0x100:
        retval = (page *)(new page100);
        break;
    case 0x101a:
        retval = (page *)(new page101a);
        break;
    case 0x101b:
        retval = (page *)(new page101b);
        break;
    case 0x101c:
        retval = (page *)(new page101c);
        break;
    case 0x200:
        retval = (page *)(new page200);
        break;
    case 0x300:
        retval = (page *)(new page300);
        break;
    case 0x400:
        retval = (page *)(new page400);
        break;
    case 0x4e0:
        retval = (page *)(new page4e0);
        break;
    case 0x401:
        retval = (page *)(new page401);
        break;
    case 0x402:
        retval = (page *)(new page402);
        break;
    case 0x500:
        retval = (page *)(new page500);
        break;

        /* add here the case labeled with the HEX id of the new pages */
    default:
        qCritical("cannot create page%04x", pageNb);
    }
    return retval;
}

