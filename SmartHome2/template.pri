#
# @file
#
# @section LICENSE
# Copyright Mect s.r.l. 2013
#
# @brief Qmake project file for TPX4120_01_A
#

INSTALLS += target

config.files = config/Crosstable.csv config/system.ini
config.path = /local/etc/sysconfig


splash.files = config/splash.png
splash.path = /local/etc/sysconfig/img

customtrend.files = config/trend1.csv
customtrend.path = /local/data/customtrend

INSTALLS += config splash customtrend 

# language
OTHER_FILES += \
    languages_it.ts \
    languages_en.ts

include(./common.pri)

TYPE = "TPX4120_01_A"

# display size
MODEL = "<width>1280</width><height>800</height>"

DEFINES += WIDTH_mm=261
DEFINES += HEIGHT_mm=163 
DEFINES += FONT_CORRECTOR=0.6342

equals(MODEL, "<width>1280</width><height>800</height>") {
    DEFINES += WIDTH=1280
    DEFINES += HEIGHT=800
    DEFINES += ROTATION=0
}
equals(MODEL, "<width>800</width><height>1280</height>") {
    DEFINES += WIDTH=800
    DEFINES += HEIGHT=1280
    DEFINES += ROTATION=270
}


