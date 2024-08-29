QT += gui xml core sql testlib

isActiveConfig(debug,debug|release){
    BUILD_TYPE = Debug
    # QT += testlib
}else{
    BUILD_TYPE = Release
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

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/PtngConfig.cpp \
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
    src/PtngInputParserNmap.cpp \
    src/PtngInputParserTest.cpp

HEADERS += \
    inc/PtngConfig.hpp \
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

# Naming
win32:CONFIG(release, debug|release): TARGET=libparser
else:win32:CONFIG(debug, debug|release): TARGET=libparserd

# Additional static linkage for the ODBC portion of the Qt SQL module
LIBS += -lodbc32

# WaifsAndStrays
win32: LIBS += -L"C:\Users\damie\source\repos\WaifsAndStrays\WaifsAndStraysOutput\release" -lWaifsAndStrays
INCLUDEPATH += "C:\Users\damie\source\repos\WaifsAndStrays\WaifsAndStraysOutput\inc"
DEPENDPATH += "C:\Users\damie\source\repos\WaifsAndStrays\WaifsAndStraysOutput\inc"

# Boost
#    INCLUDEPATH += "C:\Boost_1_81_0"
# Add one path at a time, then add individual library, e.g.
#    LIBS += -L"C:\Boost_1_81_0lib64-msvc-14.3" -lboost_program_options-vc143-mt-gd-x64-1_81.lib
