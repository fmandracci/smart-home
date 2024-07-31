#
# @file
#
# @section LICENSE
# Copyright Mect s.r.l. 2013
#
# @brief Qmake project file for TPX1043_03_C
#

INSTALLS += target

config.files = config/Crosstable.csv config/system.ini
config.path = /local/etc/sysconfig


splash.files = config/splash.png
splash.path = /local/etc/sysconfig/img

customtrend.files =  config/trend1.csv config/trend_Wall.csv config/trend_W-M.csv config/trend_W-F.csv config/trend_W01.csv config/trend_W02.csv config/trend_W03.csv config/trend_W04.csv config/trend_W05.csv config/trend_W06.csv config/trend_W07.csv config/trend_W08.csv config/trend_W09.csv config/trend_W10.csv config/trend_Tall.csv config/trend_T1.csv config/trend_T2.csv config/trend_T3.csv config/trend_T4.csv config/trend_T4puffer.csv config/trend_T5.csv config/trend_T6.csv config/trend_H1.csv config/trend_H2.csv config/trend_H3.csv config/trend_H4.csv config/trend_H5.csv config/trend_H6.csv
customtrend.path = /local/data/customtrend

INSTALLS += config splash customtrend

# language
OTHER_FILES += \
    languages_it.ts \
    languages_en.ts

include(./common.pri)

TYPE = "TPX1043_03_C"

# display size
MODEL = "<width>480</width><height>272</height>"

equals(MODEL, "<width>320</width><height>240</height>") {
    DEFINES+=WIDTH=320
    DEFINES+=HEIGHT=240
    DEFINES+=ROTATION=0
}
equals(MODEL, "<width>240</width><height>320</height>") {
    DEFINES+=WIDTH=240
    DEFINES+=HEIGHT=320
    DEFINES+=ROTATION=270
}
equals(MODEL, "<width>480</width><height>272</height>") {
    DEFINES+=WIDTH=480
    DEFINES+=HEIGHT=272
    DEFINES+=ROTATION=0
}
equals(MODEL, "<width>272</width><height>480</height>") {
    DEFINES+=WIDTH=272
    DEFINES+=HEIGHT=480
    DEFINES+=ROTATION=90
}
equals(MODEL, "<width>800</width><height>480</height>") {
    DEFINES+=WIDTH=800
    DEFINES+=HEIGHT=480
    DEFINES+=ROTATION=0
}
equals(MODEL, "<width>480</width><height>800</height>") {
    DEFINES+=WIDTH=480
    DEFINES+=HEIGHT=800
    DEFINES+=ROTATION=270
}

