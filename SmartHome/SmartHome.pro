# Copyright (C) 2021 Francesco Mandracci
# Contact: https://github.com/fmandracci/smart-home
#
# This file is part of the Smart Home Framework.
#
# Commercial License Usage
# Licensees holding valid commercial licenses may use this file in
# accordance with the terms contained in a written agreement
# between you and the copyright owner.
#
# GNU Lesser General Public License Usage
# Alternatively, this file may be used under the terms of the GNU Lesser
# General Public License version 3 as published by the Free Software
# Foundation and appearing in the file LICENSE included in the
# packaging of this file. Please review the following information to
# ensure the GNU Lesser General Public License version 3 requirements
# will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
#

include(./template.pri)

HEADERS += \
    automation.h \
    page100.h \
    page010.h \
    page043.h \
    page045.h \
    page005.h \
    page020.h \
    page021.h \
    page022.h \
    page400.h \
    page200.h \
    page300.h \
    page044.h \
    page500.h \
    page102.h \
    page401.h \
    page402.h \
    page103.h \
    page046.h \
    page4e0.h \
    page104.h \
    page101a.h \
    page101b.h \
    page101c.h \
    page043e.h \
    page047.h \
    page048.h \
    page049.h \
    page4b0.h


FORMS += \
    page100.ui \
    page010.ui \
    page043.ui \
    page045.ui \
    page005.ui \
    page020.ui \
    page021.ui \
    page022.ui \
    page400.ui \
    page200.ui \
    page300.ui \
    page044.ui \
    page500.ui \
    page102.ui \
    page401.ui \
    page402.ui \
    page103.ui \
    page046.ui \
    page4e0.ui \
    page104.ui \
    page101a.ui \
    page101b.ui \
    page101c.ui \
    page043e.ui \
    page047.ui \
    page048.ui \
    page049.ui \
    page4b0.ui


SOURCES += \
    automation.cpp \
    page100.cpp \
    page010.cpp \
    page043.cpp \
    page045.cpp \
    page005.cpp \
    page020.cpp \
    page021.cpp \
    page022.cpp \
    page400.cpp \
    page200.cpp \
    page300.cpp \
    page044.cpp \
    page500.cpp \
    page102.cpp \
    page401.cpp \
    page402.cpp \
    page103.cpp \
    page046.cpp \
    page4e0.cpp \
    page104.cpp \
    page101a.cpp \
    page101b.cpp \
    page101c.cpp \
    page043e.cpp \
    page047.cpp \
    page048.cpp \
    page049.cpp \
    page4b0.cpp

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    hmi_tp1043.ini \
    hmi_tp1070.ini \
    hmi_tpx4100.ini \
    hmi_tpx4120.ini \
    hmi_only \
    hmi.qss \
    home_C.ini \
    home_L.ini \
    home_P.ini \
    home_X.ini \
    local_deploy.sh

other.files = $$replace(OTHER_FILES, local_deploy.sh, )
other.path = /local/root

INSTALLS += other

#contains(QMAKE_INCDIR_QT,"/opt/Qt4.8.7/imx28/rootfs/include") {
#    message(building for 'imx28' $$escape_expand(\\n))
#    DEFINES += RESIZABLE_APPLICATION
#    DEFINES += USE_PHYSICALDISPLAYSIZE

#} else : contains(QMAKE_INCDIR_QT,"/opt/Qt4.8.7/rpi4/rootfs/include") {
#    message(building for 'rpi4' $$escape_expand(\\n))
#    DEFINES += RESIZABLE_APPLICATION
#    DEFINES += USE_PHYSICALDISPLAYSIZE

#} else : contains(QMAKE_INCDIR_QT,"/opt/Qt4.8.7/host/include") {
#    message(building for 'host' $$escape_expand(\\n))
#    # use sizes defined in template.pri

#} else {
#    message(building for '???' QT_INSTALL_PREFIX is $$[QT_INSTALL_PREFIX] $$escape_expand(\\n))

#}
