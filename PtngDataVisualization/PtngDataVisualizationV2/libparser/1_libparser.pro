QT += gui core xml network sql

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
    data/ptnghostbuilder.cpp \
    data/ptnghostspec.cpp \
    data/ptngipv4addressbuilder.cpp \
    data/ptngipv4addressspec.cpp \
    data/ptngissuebuilder.cpp \
    data/ptngissuespec.cpp \
    data/ptngnessusreport.cpp \
    data/ptngnmapreport.cpp \
    data/ptngportbuilder.cpp \
    data/ptngportspec.cpp \
    io/ptngdgmloutput.cpp \
    io/ptngdotoutput.cpp \
    io/ptngidentifier.cpp \
    io/ptnginputarpscan.cpp \
    io/ptnginputdnsrecon.cpp \
    io/ptnginputhost.cpp \
    io/ptnginputnbtscan.cpp \
    io/ptnginputnessus.cpp \
    io/ptnginputnmapaxfr.cpp \
    io/ptnginputnmapenumeration.cpp \
    io/ptnginputnslookuplin.cpp \
    io/ptnginputnslookupwin.cpp \
    io/ptnginputsslscan.cpp \
    io/ptngnamicsoftoutput.cpp \
    utils/ptngstylesheet.cpp

HEADERS += \
    data/abstractbuilder.hpp \
    data/abstractitemspec.hpp \
    data/abstractreportspec.hpp \
    data/ptnghostbuilder.hpp \
    data/ptnghostspec.hpp \
    data/ptngipv4addressbuilder.hpp \
    data/ptngipv4addressspec.hpp \
    data/ptngissuebuilder.hpp \
    data/ptngissuespec.hpp \
    data/ptngnessusreport.hpp \
    data/ptngnmapreport.hpp \
    data/ptngportbuilder.hpp \
    data/ptngportspec.hpp \
    inc/libparser_global.hpp \
    io/abstractptnginput.hpp \
    io/abstractptngoutput.hpp \
    io/ptngdgmloutput.hpp \
    io/ptngdotoutput.hpp \
    io/ptngidentifier.hpp \
    io/ptnginputarpscan.hpp \
    io/ptnginputdnsrecon.hpp \
    io/ptnginputhost.hpp \
    io/ptnginputnbtscan.hpp \
    io/ptnginputnessus.hpp \
    io/ptnginputnmapaxfr.hpp \
    io/ptnginputnmapenumeration.hpp \
    io/ptnginputnslookuplin.hpp \
    io/ptnginputnslookupwin.hpp \
    io/ptnginputsslscan.hpp \
    io/ptngnamicsoftoutput.hpp \
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
    !build_pass:message("Including library reference to odbc32")
}

RESOURCES += \
    res/resources.qrc
