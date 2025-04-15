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
    headerleds.h \
    headerpanel.h \
    page005.h \
    page010.h \
    page011.h \
    page020.h \
    page021.h \
    page022.h \
    page041.h \
    page042.h \
    page043.h \
    page043e.h \
    page044.h \
    page045.h \
    page046.h \
    page047.h \
    page048.h \
    page049.h \
    page100.h \
    page101a.h \
    page101b.h \
    page101c.h \
    page200.h \
    page300.h \
    page400.h \
    page401.h \
    page402.h \
    page4e0.h \
    page500.h \


FORMS += \
    headerleds.ui \
    headerpanel.ui \
    page005.ui \
    page010.ui \
    page011.ui \
    page020.ui \
    page021.ui \
    page022.ui \
    page041.ui \
    page042.ui \
    page043.ui \
    page043e.ui \
    page044.ui \
    page045.ui \
    page046.ui \
    page047.ui \
    page048.ui \
    page049.ui \
    page100.ui \
    page101a.ui \
    page101b.ui \
    page101c.ui \
    page200.ui \
    page300.ui \
    page400.ui \
    page401.ui \
    page402.ui \
    page4e0.ui \
    page500.ui \


SOURCES += \
    automation.cpp \
    headerleds.cpp \
    headerpanel.cpp \
    page005.cpp \
    page010.cpp \
    page011.cpp \
    page020.cpp \
    page021.cpp \
    page022.cpp \
    page041.cpp \
    page042.cpp \
    page043.cpp \
    page043e.cpp \
    page044.cpp \
    page045.cpp \
    page046.cpp \
    page047.cpp \
    page048.cpp \
    page049.cpp \
    page100.cpp \
    page101a.cpp \
    page101b.cpp \
    page101c.cpp \
    page200.cpp \
    page300.cpp \
    page400.cpp \
    page401.cpp \
    page402.cpp \
    page4e0.cpp \
    page500.cpp \


RESOURCES += \
    resources.qrc

OTHER_FILES += \
    hmi.ini \
    hmi_bis.ini \
    hmi_only \
    hmi.qss

other.files =  hmi_only hmi.qss
other.path = /local/root

INSTALLS += other

