##
# @file
#
# @section LICENSE
# Copyright Mect s.r.l. 2025
#
# @brief Qmake project file
#

TARGET = hmi
TEMPLATE = app

target.path = /local/root

INCLUDEPATH += . ./config

# Input
HEADERS += \
        config/crosstable.h \
        pages.h

SOURCES += \
        config/crosstable.cpp \
        pages.cpp

!isEmpty(MECT_QTCREATOR_TEMPLATES) {
	# pre-elaboration
	check_missing_file.commands        = @perl $${MECT_QTCREATOR_TEMPLATES}/wizards/projects/MectSuite/MECT-template-project/cleanmissingpage.pl \"$$_PRO_FILE_\" \"$$_PRO_FILE_PWD_\"
	check_undeclared_variable.commands = @perl $${MECT_QTCREATOR_TEMPLATES}/wizards/projects/MectSuite/MECT-template-project/check_cross_var.pl \"$$_PRO_FILE_PWD_\"
	check_gotopage_bind.commands       = @perl $${MECT_QTCREATOR_TEMPLATES}/wizards/projects/MectSuite/MECT-template-project/connectbutton.pl \"$$_PRO_FILE_PWD_\"
	check_systemini.commands           = @perl $${MECT_QTCREATOR_TEMPLATES}/wizards/projects/MectSuite/MECT-template-project/check_systemini.pl \"$$_PRO_FILE_\" \"$$_PRO_FILE_PWD_\"

        QMAKE_EXTRA_TARGETS += check_missing_file check_undeclared_variable check_gotopage_bind check_systemini
        PRE_TARGETDEPS      += check_missing_file check_undeclared_variable check_gotopage_bind check_systemini
}

# system icons
contains(QMAKE_HOST.os,"Windows") {
        message(host operating system is Windows $$escape_expand(\\n))
} else : contains(QMAKE_HOST.os,"Linux") {
        message(host operating system is GNU/Linux $$escape_expand(\\n))
} else {
        error(unknown host operating system $${QMAKE_HOST.os});
}
RESOURCES += systemicons.qrc

# language

QT_LUPDATE_PATH = $$[QT_INSTALL_BINS]
QT_LRELEASE_PATH = $$[QT_INSTALL_BINS]

lupdate.commands = $${QT_LUPDATE_PATH}/lupdate \"$$_PRO_FILE_\"

# lrelease.depends = lupdate
# lrelease.commands = $${QT_LRELEASE_PATH}/lrelease \"$$_PRO_FILE_\"

lrelease_compiler.name     = lrelease ${QMAKE_FILE_IN}
lrelease_compiler.input    = TRANSLATIONS
lrelease_compiler.output   = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
lrelease_compiler.commands = $${QT_LRELEASE_PATH}/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
lrelease_compiler.CONFIG  += no_link target_predeps
QMAKE_EXTRA_COMPILERS += lrelease_compiler

QMAKE_EXTRA_TARGETS += lupdate # lrelease
PRE_TARGETDEPS += lupdate # lrelease

RESOURCES += \
    languages.qrc

include(./languages.pri)

#Current Mect Suite Version:
DEFINES += "MECT_SUITE_VERSION=\"\\\"6.1.1\\\"\""
