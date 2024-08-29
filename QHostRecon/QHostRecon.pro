QT = core network xml
CONFIG += c++20 cmdline warn_off

SOURCES += \
        main.cpp \
    src/hostreconutils.cpp \
    src/reconcommands.cpp

HEADERS += \
    inc/hostreconutils.hpp \
    inc/reconcommands.hpp


isActiveConfig(debug,debug|release){
    TARGET = QHostRecond
    BUILD_TYPE = Debug
}
else{
    TARGET = QHostRecon
    BUILD_TYPE = Release
}

!build_pass:message("Building for: " $$BUILD_TYPE)
