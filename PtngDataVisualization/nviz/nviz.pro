QT = core gui xml

isActiveConfig(debug,debug|release){
    BUILD_TYPE = Debug
    QT += testlib
    LIBS += -llibparserd
    TARGET = nvizd
}else{
    BUILD_TYPE = Release
    LIBS += -llibparser
    TARGET = nviz
}

# Additional static linkage for the ODBC portion of the Qt SQL module
contains(QT,sql){
    LIBS += -lodbc32
}

CONFIG += c++20 cmdline warn_off

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    inc/GlobalIncludes.hpp \
    inc/CommandLineHandler.hpp

SOURCES += \
        CommandLineHandler.cpp \
        NessusXmlHostVulns.cpp \
        NessusXmlPluginFamilies.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# libparser
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libparser/release/ -llibparser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libparser/debug/ -llibparserd
INCLUDEPATH += $$PWD/../libparser/inc
DEPENDPATH += $$PWD/../libparser/inc
