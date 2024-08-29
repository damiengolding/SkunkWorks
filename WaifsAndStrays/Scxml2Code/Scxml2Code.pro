QT = core testlib xml
CONFIG += c++20 cmdline warn_off

isActiveConfig(debug,debug|release){
    BUILD_TYPE = Debug
    TARGET = scxml2coded
}else{
    BUILD_TYPE = Release
    TARGET = scxml2code
}

SOURCES += \
        fsmutils.cpp \
        main.cpp \

HEADERS += \
    fsmutils.hpp

RESOURCES += \
    res/Scxml2Code.qrc

