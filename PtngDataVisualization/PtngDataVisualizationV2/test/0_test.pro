QT += testlib xml
QT -= gui

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
    src/fileident.cpp \
    src/libparser.cpp \
    src/testutilities.cpp

HEADERS += \
    inc/libparser.hpp \
    inc/testutilities.hpp


!build_pass:message("Build type: " $$BUILD_TYPE)
