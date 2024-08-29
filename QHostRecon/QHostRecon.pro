QT = core network xml
CONFIG += c++20 cmdline warn_off

isActiveConfig(debug,debug|release){
    TARGET = qhostrecond
    BUILD_TYPE = Debug
}
else{
    TARGET = qhostrecon
    BUILD_TYPE = Release
}

SOURCES += \
        main.cpp \
    src/hostreconutils.cpp \
    src/reconcommands.cpp

HEADERS += \
    inc/hostreconutils.hpp \
    inc/reconcommands.hpp

!build_pass:message("Building for: " $$BUILD_TYPE)
