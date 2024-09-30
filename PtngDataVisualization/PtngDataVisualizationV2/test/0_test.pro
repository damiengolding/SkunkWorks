QT += gui core testlib xml

CONFIG += qt console c++20 warn_off depend_includepath testcase
CONFIG -= app_bundle
TEMPLATE = app

isActiveConfig(debug,debug|release){
    TARGET = libparsertestd
    BUILD_TYPE = Debug
}
else{
    TARGET = libparsertest
    BUILD_TYPE = Release
}

SOURCES +=  tst_libparser.cpp \
    src/libparser.cpp \
    src/testutilities.cpp

HEADERS += \
    inc/libparser.hpp \
    inc/testutilities.hpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../StaticOutput/libparser/release/ -llibparser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../StaticOutput/libparser/debug/ -llibparserd

INCLUDEPATH += $$PWD/../libparser
DEPENDPATH += $$PWD/../libparser


!build_pass:message("Build type: " $$BUILD_TYPE)
