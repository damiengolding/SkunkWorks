QT += testlib xml
# QT -= gui

isActiveConfig(debug,debug|release){
    BUILD_TYPE = Debug
    TARGET=ptngtestharnessd
}else{
    BUILD_TYPE = Release
    TARGET=ptngtestharness
}

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_ptngtest.cpp

# libparser
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libparser/release/ -llibparser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libparser/debug/ -llibparserd
INCLUDEPATH += $$PWD/../libparser/inc
DEPENDPATH += $$PWD/../libparser/inc
