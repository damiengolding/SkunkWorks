QT += gui xml core sql

isActiveConfig(debug,debug|release){
    BUILD_TYPE = Debug
    TARGET=libparserd

}else{
    BUILD_TYPE = Release
    TARGET=libparser
}

# TODO - testing is currently in all builds, should it be separated to a debug-type build only?

TEMPLATE = lib
contains(BUILD, SHARED){
    !build_pass:message("Shared build");
    CONFIG += lib
}else{
    !build_pass:message("Static build");
    CONFIG += staticlib
}

CONFIG += c++20 warn_off

SOURCES += \
    src/PtngDGMLBuilder.cpp \
    src/PtngDGMLBuilderNessus.cpp \
    src/PtngDGMLBuilderNmap.cpp \
    src/PtngDGMLBuilderSimple.cpp \
    src/PtngDGMLBuilderTest.cpp \
    src/PtngDGMLConvDot.cpp \
    src/PtngHostBuilder.cpp \
    src/PtngIP4Address.cpp \
    src/PtngIdent.cpp \
    src/PtngInputParserAxfr.cpp \
    src/PtngInputParserNessus.cpp \
    src/PtngInputParserNmap.cpp

HEADERS += \
    inc/PtngDGMLBuilder.hpp \
    inc/PtngDGMLConv.hpp \
    inc/PtngEnums.hpp \
    inc/PtngHostBuilder.hpp \
    inc/PtngIP4Address.hpp \
    inc/PtngIdent.hpp \
    inc/PtngInputParser.hpp \
    inc/PtngSpecifications.hpp \
    inc/libparser_global.hpp

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

# OpenMP
unix:CONFIG{
    QMAKE_CXXFLAGS += -fopenmp
    QMAKE_LFLAGS += -fopenmp
    LIBS += -lopenmp
}

# Additional static linkage for the ODBC portion of the Qt SQL module
LIBS += -lodbc32
