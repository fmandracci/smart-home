##
# @file
#
# @section LICENSE
# Copyright Mect s.r.l. 2025
#
# @brief Qmake project file
#

#contains(QMAKE_HOST.os,Windows){
#        QT_ROOTFS = C:/Qt487/imx28/rootfs
#        QT_LUPDATE_PATH = C:/Qt487/desktop/bin
#        QT_LRELEASE_PATH = C:/Qt487/imx28/qt-everywhere-opensource-src-4.8.7/bin
#        ATCM_TEMPLATE_BASE_DIR = C:/Qt487/desktop/QtCreator/share/qtcreator/templates/wizards
#}
#!contains(QMAKE_HOST.os,Windows){
#        QT_ROOTFS        = /opt/Qt4.8.7/host
#        QT_LUPDATE_PATH  = /opt/Qt4.8.7/host/bin
#        QT_LRELEASE_PATH = /opt/Qt4.8.7/host/bin
#        ATCM_TEMPLATE_BASE_DIR = /opt/Qt4.8.7/desktop/QtCreator/share/qtcreator/templates/wizards
#}
#
#isEmpty(QT_ROOTFS) {
#        error(QT_ROOTFS is empty)
#}
#isEmpty(QT_LUPDATE_PATH) {
#        warning(QT_LUPDATE_PATH is empty)
#}
#isEmpty(QT_LRELEASE_PATH) {
#        warning(QT_LRELEASE_PATH is empty)
#}
#isEmpty(ATCM_TEMPLATE_BASE_DIR) {
#        warning(ATCM_TEMPLATE_BASE_DIR is empty)
#}

#ATCM_ARM_LIBRARY_LIBPATH = $$QT_ROOTFS/usr/lib
#ATCM_ARM_PLUGINS_LIBPATH = $$QT_ROOTFS/usr/lib
#ATCM_ARM_LIBRARY_INCPATH = $$QT_ROOTFS/usr/include
#ATCM_ARM_PLUGINS_INCPATH = $$QT_ROOTFS/usr/include

#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE += -O3
#QMAKE_CXXFLAGS_RELEASE += -Wno-psabi
#QMAKE_CXXFLAGS_DEBUG   += -Wno-psabi

TARGET = hmi
TEMPLATE = app

target.path = /local/root

INCLUDEPATH += . ./config

LIBS += \
-lATCMcommon \
-lATCMutility \
-lATCMcommunication \
-lATCMlogger \
-lATCMstore \
-lATCMalarms \
-lATCMrecipe \
-lATCMtrend \
-lATCMsystem \
-lATCMplugin \
-lATCMinputdialog \
-lts \
-lqwt 

# Input
HEADERS += \
        config/crosstable.h \
        style.h \
        pages.h

SOURCES += \
        config/crosstable.cpp \
        pages.cpp

!isEmpty(ATCM_TEMPLATE_BASE_DIR) {
	# pre-elaboration
	check_missing_file.commands = @perl $${ATCM_TEMPLATE_BASE_DIR}/ATCM-template-project/cleanmissingpage.pl \"$$_PRO_FILE_\" \"$$_PRO_FILE_PWD_\"
	check_undeclared_variable.commands = @perl $${ATCM_TEMPLATE_BASE_DIR}/ATCM-template-project/check_cross_var.pl \"$$_PRO_FILE_PWD_\"
	check_gotopage_bind.commands = @perl $${ATCM_TEMPLATE_BASE_DIR}/ATCM-template-project/connectbutton.pl \"$$_PRO_FILE_PWD_\"
	check_systemini.commands = @perl $${ATCM_TEMPLATE_BASE_DIR}/ATCM-template-project/check_systemini.pl \"$$_PRO_FILE_\" \"$$_PRO_FILE_PWD_\"
        # check_default_font.commands = @perl $${ATCM_TEMPLATE_BASE_DIR}/ATCM-template-project/defaultfont.pl \"$$_PRO_FILE_PWD_\"
	# crosstable_compiler invocation removed from defaultfont.pl and from QMAKE_EXTRA_TARGETS and PRE_TARGETDEPS
	# crosstable_compiler invocation added to "save" command in CTE
	# crosstable_compiler.commands = $${MECT_PREFIX}/desktop/QtCreator/bin/ctc -c config/Crosstable.csv -g plc/Crosstable.gvl -i config/Crosstable.h -s config/Crosstable.cpp

        QMAKE_EXTRA_TARGETS += check_missing_file check_undeclared_variable check_gotopage_bind check_systemini # check_default_font  # crosstable_compiler
        PRE_TARGETDEPS += check_missing_file check_undeclared_variable check_gotopage_bind check_systemini # check_default_font  # crosstable_compiler
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
DEFINES += "MECT_SUITE_VERSION=\"\\\"3.5.2\\\"\""
