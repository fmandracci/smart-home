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

# vedi mkspecs/linux-mectsuite-*/qmake.conf
# LIBS += \
# -lATCMcommon \
# -lATCMutility \
# -lATCMcommunication \
# -lATCMlogger \
# -lATCMstore \
# -lATCMalarms \
# -lATCMrecipe \
# -lATCMtrend \
# -lATCMsystem \
# -lATCMplugin \
# -lATCMinputdialog \
# -lts \
# -lqwt 

# Input
HEADERS += \
        config/crosstable.h \
        style.h \
        pages.h

SOURCES += \
        config/crosstable.cpp \
        pages.cpp

!isEmpty(MECT_QTCREATOR_TEMPLATES) {
	# pre-elaboration
	check_missing_file.commands = @perl $${MECT_QTCREATOR_TEMPLATES}/wizards/projects/MectSuite/ATCM-template-project/cleanmissingpage.pl \"$$_PRO_FILE_\" \"$$_PRO_FILE_PWD_\"
	check_undeclared_variable.commands = @perl $${MECT_QTCREATOR_TEMPLATES}/wizards/projects/MectSuite/ATCM-template-project/check_cross_var.pl \"$$_PRO_FILE_PWD_\"
	check_gotopage_bind.commands = @perl $${MECT_QTCREATOR_TEMPLATES}/wizards/projects/MectSuite/ATCM-template-project/connectbutton.pl \"$$_PRO_FILE_PWD_\"
	check_systemini.commands = @perl $${MECT_QTCREATOR_TEMPLATES}/wizards/projects/MectSuite/ATCM-template-project/check_systemini.pl \"$$_PRO_FILE_\" \"$$_PRO_FILE_PWD_\"
	check_default_font.commands = @perl $${MECT_QTCREATOR_TEMPLATES}/wizards/projects/MectSuite/ATCM-template-project/defaultfont.pl \"$$_PRO_FILE_PWD_\"

        QMAKE_EXTRA_TARGETS += check_missing_file check_undeclared_variable check_gotopage_bind check_systemini check_default_font # crosstable_compiler
        PRE_TARGETDEPS += check_missing_file check_undeclared_variable check_gotopage_bind check_systemini check_default_font # crosstable_compiler
}

# system icons
contains(QMAKE_HOST.os,"Windows") {
        message(host operating system is Windows $$escape_expand(\\n))
	RESOURCES += systemicons.qrc # NB: no systemicons_win32.qrc
} else : contains(QMAKE_HOST.os,"Linux") {
        message(host operating system is GNU/Linux $$escape_expand(\\n))
	RESOURCES += systemicons.qrc # NB: no systemicons_linux.qrc
} else {
        error(unknown host operating system $${QMAKE_HOST.os});
}

# language
!isEmpty(QT_LUPDATE_PATH) {
update.commands = $${QT_LUPDATE_PATH}/lupdate \"$$_PRO_FILE_\"
updates.depends = $$SOURCES $$HEADERS $$FORMS $$TRANSLATIONS
release.depends = update
        QMAKE_EXTRA_TARGETS += update
        PRE_TARGETDEPS += update
}
!isEmpty(QT_LRELEASE_PATH) {
        release.commands = $${QT_LRELEASE_PATH}/lrelease \"$$_PRO_FILE_\"
        QMAKE_EXTRA_TARGETS += release
        PRE_TARGETDEPS += release
}

RESOURCES += \
    languages.qrc

include(./languages.pri)

#Current Mect Suite Version:
DEFINES += "MECT_SUITE_VERSION=\"\\\"6.0.0\\\"\""

