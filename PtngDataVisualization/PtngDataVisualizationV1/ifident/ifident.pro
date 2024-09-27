QT = core gui xml

isActiveConfig(debug,debug|release){
    BUILD_TYPE = Debug
    QT += testlib
    LIBS += -llibparserd
    TARGET = ifidentd
}else{
    BUILD_TYPE = Release
    LIBS += -llibparser
    TARGET = ifident
}

# Additional static linkage for the ODBC portion of the Qt SQL module
contains(QT,sql){
    LIBS += -lodbc32
}

CONFIG += c++20 cmdline warn_off

SOURCES += \
        main.cpp

# libparser
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libparser/release/ -llibparser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libparser/debug/ -llibparserd
INCLUDEPATH += $$PWD/../libparser/inc
DEPENDPATH += $$PWD/../libparser/inc
