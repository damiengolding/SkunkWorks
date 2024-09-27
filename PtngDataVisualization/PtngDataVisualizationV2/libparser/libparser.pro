QT += gui xml network

isActiveConfig(debug,debug|release){
    TARGET = libparserd
    BUILD_TYPE = Debug
}
else{
    TARGET = libparser
    BUILD_TYPE = Release
}

TEMPLATE = lib
DEFINES += LIBPARSER_LIBRARY

CONFIG += c++20 warn_off

SOURCES +=

HEADERS += \
    libparser_global.hpp

DISTFILES += \
    models/ptngbuilders.qmodel \
    models/ptngdatatypes.qmodel \
    models/ptnginputoutput.qmodel \
    models/ptngutilities.qmodel

!build_pass:message("Build type: " $$BUILD_TYPE)
