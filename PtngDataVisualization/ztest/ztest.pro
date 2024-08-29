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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Tools/Libraries/PtngDataVisualization/Static/ -llibparser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Tools/Libraries/PtngDataVisualization/Static/ -llibparserd

INCLUDEPATH += $$PWD/../../../../../../Tools/Libraries/PtngDataVisualization/Static/inc
DEPENDPATH += $$PWD/../../../../../../Tools/Libraries/PtngDataVisualization/Static/inc
