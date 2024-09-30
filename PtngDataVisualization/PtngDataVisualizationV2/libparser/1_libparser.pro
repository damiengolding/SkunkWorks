QT += gui core xml network

isActiveConfig(debug,debug|release){
    TARGET = libparserd
    BUILD_TYPE = Debug
}
else{
    TARGET = libparser
    BUILD_TYPE = Release
}

TEMPLATE = lib
contains(BUILD, SHARED){
    CONFIG += lib
    BUILD_OUTPUT = Shared
}else{
    CONFIG += staticlib
    BUILD_OUTPUT = Static
}

DEFINES += LIBPARSER_LIBRARY
CONFIG += c++20 warn_off

SOURCES += \
    utils/ptngenums.cpp \
    utils/ptngstylesheet.cpp

HEADERS += \
    libparser_global.hpp \
    utils/ptngenums.hpp \
    utils/ptngstylesheet.hpp

DISTFILES += \
    models/ptngdata.qmodel \
    models/ptnginputoutput.qmodel \
    models/ptngutilities.qmodel

!build_pass:message("Build type:" $$BUILD_TYPE "for output type: " $$BUILD_OUTPUT)

contains(QT,sql){
    LIBS += -lodbc32
    !build_pass:message("Including reference to odbc32")
}

RESOURCES += \
    res/resources.qrc
