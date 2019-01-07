#-------------------------------------------------
#
# Project created by QtCreator 2018-09-26T12:03:41
#
#-------------------------------------------------

QT       += widgets sql

TARGET = libSniper
TEMPLATE = lib

DEFINES += SNIPER_LIBRARY
DEFINES += FRONTEND_COMPILATION
INCLUDEPATH += F:/GUIR/gui/api2/api_includes/

SOURCES += sniper.cpp \
    sniperdialog.cpp \
    sniperparams.cpp \
  F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/apiincludesgetters.cpp

HEADERS += sniper.h\
        sniper_global.h \
    sniperdialog.h \
    sniperparams.h \
    F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/StrategyConstants.h \
    F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/sharedStrutures.h \
    F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/sharedParams.h \
    F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/sharedEnums.h \
    F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/baseStrategyWrapper.h \
    F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/BaseHandler.h \
    F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/api2RequestResponse.h \
    F:/GUIR/gui/api2/api_includes/userParamsReader.h \
    F:/GUIR/gui/api2/api_includes/sharedResponse.h \
    F:/GUIR/gui/api2/api_includes/sharedDefines.h \
    F:/GUIR/gui/api2/api_includes/sharedCommands.h \
    F:/GUIR/gui/api2/api_includes/serializeCommands.h \
    F:/GUIR/gui/api2/api_includes/cmdDefines.h \
    F:/GUIR/gui/api2/api_includes/baseCommands.h \
    F:/GUIR/gui/api2/api_includes/apiDataTypes.h \
    F:/GUIR/gui/api2/api_includes/apiConstants.h \
    F:/GUIR/gui/api2/api_includes/api2UserCommands.h \
    F:/GUIR/gui/api2/api_includes/api2RequestResponse.h \
    F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/dllDefines.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE3CB5739
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = OrderOnTime.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    sniperdialog.ui
