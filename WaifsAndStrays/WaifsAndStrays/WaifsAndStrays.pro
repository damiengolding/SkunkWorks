QT += gui xml testlib

TEMPLATE = lib
CONFIG += c++20 warn_off staticlib

isActiveConfig(debug,debug|release){
    BUILD_TYPE = Debug
    TARGET = WaifsAndStraysd
}else{
    BUILD_TYPE = Release
    WaifsAndStrays
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEBUG

SOURCES += \
    src/ConversionUtils.cpp \
    src/Logger.cpp \
    src/StyleSheet.cpp


HEADERS += \
    inc/ConversionUtils.hpp \
    inc/Logger.hpp \
    inc/StyleSheet.hpp


# Deployment
# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
