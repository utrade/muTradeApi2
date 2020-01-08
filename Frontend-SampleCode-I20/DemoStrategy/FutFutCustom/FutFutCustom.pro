#-------------------------------------------------
#
# Project created by QtCreator 2017-05-03T14:19:49
#
#-------------------------------------------------

contains(QT_VERSION, ^5.*) {
QT += widgets
}

QT       += sql

TARGET = libFutFutCustom
TEMPLATE = lib

DEFINES += FRONTEND_COMPILATION
INCLUDEPATH += ../includes/api2/api_includes

SOURCES += sampleTwoLeg.cpp \
    uilibrary.cpp \
    futfutparams.cpp \
    ../includes/dll_includes/apiincludesgetters.cpp

HEADERS += sampleTwoLeg.h\
        sampleTwoLeg_global.h \
    uilibrary.h \
    futfutparams.h \
    ../includes/dll_includes/StrategyConstants.h \
    ../includes/dll_includes/sharedStrutures.h \
    ../includes/dll_includes/sharedParams.h \
    ../includes/dll_includes/sharedEnums.h \
    ../includes/dll_includes/baseStrategyWrapper.h \
    ../includes/dll_includes/BaseHandler.h \
    ../includes/api_includes/userParamsReader.h \
    ../includes/api_includes/sharedResponse.h \
    ../includes/api_includes/sharedDefines.h \
    ../includes/api_includes/sharedCommands.h \
    ../includes/api_includes/serializeCommands.h \
    ../includes/api_includes/cmdDefines.h \
    ../includes/api_includes/baseCommands.h \
    ../includes/api_includes/apiDataTypes.h \
    ../includes/api_includes/apiConstants.h \
    ../includes/api_includes/api2UserCommands.h \
    ../includes/api_includes/api2RequestResponse.h \
    ../includes/dll_includes/dllDefines.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEAFC03A2
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = sampleFutFutCustom.dll
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
    uilibrary.ui
