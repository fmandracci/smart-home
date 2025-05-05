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


#ifndef AUTOMATION_H
#define AUTOMATION_H

#include "main.h"
#include "hmi_logger.h"
#include "global_functions.h"

#include "modulor.h"
#include "headerleds.h"

#include "crosstable.h" // PLC_...

#define XX_PIXMAP ":/icons/icons/Settings.png"
#define TM_PIXMAP ":/icons/icons/Chronometer.png"
#define EP_PIXMAP ":/icons/icons/Wattmeter.png"
#define RL_PIXMAP ":/icons/icons/Flash.png"
#define TH_PIXMAP ":/icons/icons/HeatCool.png"
#define LM_PIXMAP ":/icons/icons/LampIcon.png"
#define BA_PIXMAP ":/icons/icons/Antifurto.png"

// vedi plc/Resource1.cst

#define ControlType_None   0
#define ControlType_OnOff  1
#define ControlType_PID    2

#define TemperatureError        -2730
#define	TemperatureSetPoint_min    70 //  7.0 *C <-- 10.0 °C
#define	TemperatureSetPoint_max   300 // 30.0 °C

#define HumidityError          0
#define	HumiditySetPoint_min 100 // 10.0 %
#define	HumiditySetPoint_max 900 // 90.0 %

#define HEATING_OFF      0
#define HEATING_AUTO     1
#define HEATING_ECONOMY  2
#define HEATING_COMFORT  3
#define HEATING_BOOST    4
#define HEATING_COUNT    5

const QString heating_name(int heating_status);

extern int currentThermostat;
extern int currentWattmeter;

extern Modulor *modulor;
#define TRANSLATE_FONT_SIZE(x) modulor->translateFontSize(x)

#if defined(MECT_SUITE_3_5)

//extern int mectScreenWidth;
//extern int mectScreenHeight;
//extern float mectFontCorrector;

#elif defined(MECT_SUITE_3_4)

extern int mectScreenWidth;
extern int mectScreenHeight;
extern float mectFontCorrector;

#else
#error wrong framework
#endif

#define HOME_INI_FILE "/local/root/home.ini"

// °☀ ①②③④ ⑤⑥⑦⑧ ⑨⑩

#define LABEL_DEGREE      QString::fromUtf8("°")  // QChar(0x00B0) Degree Sign
#define LABEL_N_DASH      QString::fromUtf8("–")  // QChar(0x2013) En Dash
#define LABEL_M_DASH      QString::fromUtf8("—")  // QChar(0x2014) Em Dash
#define LABEL_M_SPACE     QString::fromUtf8(" ")  // QChar(0x2003) Em Space
#define LABEL_M_QUAD      QString::fromUtf8(" ")  // QChar(0x2001) Em Quad
#define LABEL_F_SPACE     QString::fromUtf8(" ")  // QChar(0x2007) Figure Space
#define LABEL_W_CIRCLE    QString::fromUtf8("○")  // QChar(0x25CB) White Circle
#define LABEL_B_CIRCLE    QString::fromUtf8("●")  // QChar(0x25CF) Black Circle
#define LABEL_MB_CIRCLE   QString::fromUtf8("⚫")  // QChar(0x26AB) Medium Black Circle
#define LABEL_BSUNRAYS    QString::fromUtf8("☀") // QChar(0x2600) Black Sun with Rays
#define LABEL_HOTSPRINGS  QString::fromUtf8("♨") // QChar(0x2668) Hot Springs
#define LABEL_WSUNRAYS    QString::fromUtf8("☼")  // QChar(0x263c) White Sun with Rays
#define LABEL_MOON        QString::fromUtf8("☽")  // QChar(0x263d) First Quarter Moon
#define LABEL_HIGHVOLTAGE QString::fromUtf8("⚡")  // QChar(0x26A1) High Voltage Sign
#define LABEL_B_DIAMOND   QString::fromUtf8("❖")  // QChar(0x2756) Black Diamond Minux White X
#define LABEL_DCIRCLE     QString::fromUtf8("◌")  // QChar(0x25CC) Dotted Circle
#define LABEL_BULLET      QString::fromUtf8("•")  // QChar(0x2022) Bullet
#define LABEL_DOT         QString::fromUtf8("·")  // QChar(0x00B7) Middle Dot
#define LABEL_MCIRCLE     QString::fromUtf8("⚪")  // QChar(0x26AA) Medium White Circle
#define LABEL_WARNING     QString::fromUtf8("⚠")  // QChar(0x26A0) Warning Sign
#define LABEL_CELSIUS     QString::fromUtf8("℃")  // QChar(0x2103) Degree Celsius
#define LABEL_FARHENHEIT  QString::fromUtf8("℉")  // QChar(0x2109) Degree Farenheit
#define LABEL_DELTA       QString::fromUtf8("Δ")  // QChar(0x0394) Greek Capital Letter Delta
#define LABEL_SUM         QString::fromUtf8("∑")  // QChar(0x2211) N-ary summation
#define LABEL_LESS_OR_EQ  QString::fromUtf8("≤")  // QChar(0x2264) Less than or equal
#define LABEL_TRIANGLE    QString::fromUtf8("‣")  // QChar(0x2023) Triangular Bullet

//
#define LABEL_DIE_FACE_1  QString::fromUtf8("⚀")  // QChar(0x2680) Die Face 1
#define LABEL_DIE_FACE_2  QString::fromUtf8("⚁")  // QChar(0x2681) Die Face 2
#define LABEL_DIE_FACE_3  QString::fromUtf8("⚂")  // QChar(0x2682) Die Face 3
#define LABEL_DIE_FACE_4  QString::fromUtf8("⚃")  // QChar(0x2683) Die Face 4
#define LABEL_DIE_FACE_5  QString::fromUtf8("⚄")  // QChar(0x2684) Die Face 5
#define LABEL_DIE_FACE_6  QString::fromUtf8("⚅")  // QChar(0x2685) Die Face 6

#define LABEL_MISSING   LABEL_WARNING // LABEL_M_SPACE // LABEL_F_SPACE
#define LABEL_OFF       LABEL_M_SPACE
#define LABEL_AUTO      LABEL_MCIRCLE
#define LABEL_HEATING   LABEL_HOTSPRINGS

#define LABEL_DAYTIME   LABEL_WSUNRAYS
#define LABEL_NIGHTTIME LABEL_MOON

#define LABEL_NULL_H     QString::fromUtf8("––.–") // LABEL_N_DASH
#define LABEL_NULL_T     QString::fromUtf8("–––.–") // LABEL_N_DASH
#define LABEL_NULL_W     QString::fromUtf8("–––––") // LABEL_N_DASH
#define LABEL_NULL_kWh   QString::fromUtf8("––––––.–") // LABEL_N_DASH

#define LABEL__M QString::fromUtf8("M")  //
#define LABEL__F QString::fromUtf8("F")  //

#define LABEL_EP LABEL_HIGHVOLTAGE
#define LABEL_BA LABEL_B_DIAMOND

#define LABEL_01 QString::fromUtf8("①")  // QChar(0x2780)
#define LABEL_02 QString::fromUtf8("②")  // QChar(0x2781)
#define LABEL_03 QString::fromUtf8("③")  // QChar(0x2782)
#define LABEL_04 QString::fromUtf8("④")  // QChar(0x2783)

#define LABEL_05 QString::fromUtf8("⑤")  // QChar(0x2784)
#define LABEL_06 QString::fromUtf8("⑥")  // QChar(0x2785)
#define LABEL_07 QString::fromUtf8("⑦")  // QChar(0x2786)
#define LABEL_08 QString::fromUtf8("⑧")  // QChar(0x2787)
#define LABEL_09 QString::fromUtf8("⑨")  // QChar(0x2788)
#define LABEL_10 QString::fromUtf8("⑩")  // QChar(0x2789)

#if 0
// ➊➋➌➍➎➏➐➑➒➓
#define LABEL_01_ON QString::fromUtf8("➊")  // QChar(0x278A)
#define LABEL_02_ON QString::fromUtf8("➋")  // QChar(0x278B)
#define LABEL_03_ON QString::fromUtf8("➌")  // QChar(0x278C)
#define LABEL_04_ON QString::fromUtf8("➍")  // QChar(0x278D)

#define LABEL_05_ON QString::fromUtf8("➎")  // QChar(0x278E)
#define LABEL_06_ON QString::fromUtf8("➏")  // QChar(0x278F)
#define LABEL_07_ON QString::fromUtf8("➐")  // QChar(0x2790)
#define LABEL_08_ON QString::fromUtf8("➑")  // QChar(0x2791)
#define LABEL_09_ON QString::fromUtf8("➒")  // QChar(0x2792)
#define LABEL_10_ON QString::fromUtf8("➓")  // QChar(0x2793)
#else
// ❶❷❸❹❺❻❼❽❾❿
#define LABEL_01_ON QString::fromUtf8("❶")  // QChar(0x2776)
#define LABEL_02_ON QString::fromUtf8("❷")  // QChar(0x2777)
#define LABEL_03_ON QString::fromUtf8("❸")  // QChar(0x2778)
#define LABEL_04_ON QString::fromUtf8("❹")  // QChar(0x2779)

#define LABEL_05_ON QString::fromUtf8("❺")  // QChar(0x277A)
#define LABEL_06_ON QString::fromUtf8("❻")  // QChar(0x277B)
#define LABEL_07_ON QString::fromUtf8("❼")  // QChar(0x277C)
#define LABEL_08_ON QString::fromUtf8("❽")  // QChar(0x277D)
#define LABEL_09_ON QString::fromUtf8("❾")  // QChar(0x277E)
#define LABEL_10_ON QString::fromUtf8("❿")  // QChar(0x277F)
#endif

#define COLOR_WHITE QColor(255,255,255)
#define COLOR_GREY  QColor(128,128,128)

#define COLOR_HEADER  QColor(255, 85,  0)
#define COLOR_CLOCK   QColor(255,  0,  0)

#define COLOR_00 QColor(255,170,255) // QColor(255,170,255)

#define COLOR_01 QColor(255,  0,  0) // QColor(255,  0,  0)
#define COLOR_02 QColor(255,128,  0) // QColor(255, 85,  0)

#define COLOR_03 QColor(255,255,  0) // QColor(255,170,  0)
#define COLOR_04 QColor(  0,255,  0) // QColor( 85,170,  0)
#define COLOR_05 QColor(  0,192,255) // QColor(  0,170,255)
#define COLOR_06 QColor(  0,127,255) // QColor(170, 85,255)
#define COLOR_07 QColor(255,  0,255) // QColor(170,170,170)

#define COLOR_08 QColor(255,255,192) // QColor(128,128,128)
#define COLOR_09 QColor(192,255,192) // QColor(216,216,216)
#define COLOR_10 QColor(192,192,255) // QColor(255,170,255)
#define COLOR_11 QColor(127,192,255) // QColor(170,255,255)
#define COLOR_12 QColor(255,192,255) // QColor(255,255,255)

#define TEMP_FMT           QString("%1.%2%3").arg(PLC_CPU_TEMP / 10).arg(PLC_CPU_TEMP % 10).arg(LABEL_CELSIUS)
#define TIME_FMT           QTime::currentTime().toString("HH:mm")
#define TIME_FMT_DAYTIME   QTime::currentTime().toString(LABEL_DAYTIME   + "HH:mm" + LABEL_F_SPACE)
#define TIME_FMT_NIGHTTIME QTime::currentTime().toString(LABEL_NIGHTTIME + "HH:mm" + LABEL_F_SPACE)

// #define COLOR_SS(color)    QString("background-color: rgb(0, 0, 0);\ncolor: rgb(%1, %2, %3);\n").arg(color.red()).arg(color.green()).arg(color.blue())
#define COLOR_SS(color)    QString("color: rgb(%1, %2, %3);\n").arg(color.red()).arg(color.green()).arg(color.blue())
#define BG_COLOR_SS(color) QString("background-color: rgb(%1, %2, %3);\n").arg(color.red()).arg(color.green()).arg(color.blue())

#define FONT_SS_N(size_px)  QString("font: %1px \"DejaVu Sans\";\n"            ).arg(size_px)
#define FONT_SS_B(size_px)  QString("font: bold %1px \"DejaVu Sans\";\n"       ).arg(size_px)
#define FONT_SS_I(size_px)  QString("font: italic %1px \"DejaVu Sans\";\n"     ).arg(size_px)
#define FONT_SS_BI(size_px) QString("font: bold italic %1px \"DejaVu Sans\";\n").arg(size_px)

#define BORDER_SS(color)    QString("border: 1px solid rgb(%1, %2, %3);\n").arg(color.red()).arg(color.green()).arg(color.blue())
#define BORDER3_SS(color)    QString("border: 3px solid rgb(%1, %2, %3);\n").arg(color.red()).arg(color.green()).arg(color.blue())

#define ALARM_STATUS_ZERO     0x0000 // not configured yet
#define ALARM_STATUS_OFF      0x0001
#define ALARM_STATUS_ARMED    0x0002
#define ALARM_STATUS_ENABLED  0x0003
#define ALARM_STATUS_RINGING  0x0004
#define ALARM_STATUS_MUTED    0x0005
#define ALARM_STATUS_TESTING  0xC1A0

#define ALARM_COMMAND_NONE       0x00000000
#define ALARM_COMMAND_DAYTIME    0xc1a0CC01
#define ALARM_COMMAND_NIGHTTIME  0xc1a0CC02
#define ALARM_COMMAND_EVERYTHING 0xc1a0CC03
#define ALARM_COMMAND_ENABLE     0xc1a0EEEE
#define ALARM_COMMAND_DISABLE    0xc1a0DDDD
#define ALARM_COMMAND_ACK        0xc1a0BBBB
#define ALARM_COMMAND_TEST       0xc1a0FFFF

#define ALARM_CONFIG_INDEX_NOTHING    0
#define ALARM_CONFIG_INDEX_DAYTIME    1
#define ALARM_CONFIG_INDEX_NIGHTTIME  2
#define ALARM_CONFIG_INDEX_EVERYTHING 3

#define ALARM_SENSOR_DISABLED 0 // not visible
#define ALARM_SENSOR_IGNORED  1 // dark grey
#define ALARM_SENSOR_STILL_NG 2 // yellow
#define ALARM_SENSOR_GOOD     3 // green
#define ALARM_SENSOR_NOT_GOOD 4 // red
#define ALARM_SENSOR_WAS_NG   5 // orange
#define ALARM_SENSOR_COUNT    6

#define ALARM_SENSORS_MAX    32

#define ControlType_0   0
#define ControlType_1   1
#define ControlType_2   2
#define ControlType_3   3
#define ControlType_4   4
#define ControlType_5   5
#define ControlType_6   6
#define ControlType_7   7
#define ControlType_8   8
#define ControlType_9   9
#define ControlType_10 10
#define ControlType_11 11
#define ControlType_12 12
#define ControlType_13 13
#define ControlType_14 14
#define ControlType_15 15
#define ControlType_16 16

void setup(void);
void loop(void);

int ms2hhmmss(int ms);
int hhmmss2ms(int hhmmss);

#define goto_start_page() \
{ \
    if (PLC_Iam_EP) { \
        goto_page("page400"); \
    } else if (PLC_Iam_T1 and PLC_Iam_T2 and PLC_Iam_T3) { \
        goto_page("page100"); \
    } else if (PLC_Iam_T1 or PLC_Iam_T2 or PLC_Iam_T3 or PLC_Iam_T4 or PLC_Iam_T5 or PLC_Iam_T6) { \
        if (PLC_Iam_T1) { currentThermostat = 1;} \
        if (PLC_Iam_T2) { currentThermostat = 2;} \
        if (PLC_Iam_T3) { currentThermostat = 3;} \
        if (PLC_Iam_T4) { currentThermostat = 4;} \
        if (PLC_Iam_T5) { currentThermostat = 5;} \
        if (PLC_Iam_T6) { currentThermostat = 6;} \
        goto_page("page101a"); \
    } else if (PLC_Iam_BA) { \
        goto_page("page500"); \
    } else { \
        goto_page("page010"); \
    } \
}

#define goto_trend_page(name) { \
    strncpy(_actual_trend_, name, sizeof(_actual_trend_)); \
    _trend_data_reload_ = true; \
    goto_page("trend"); \
}

void resetPLC_timeOffset();

#endif // AUTOMATION_H

