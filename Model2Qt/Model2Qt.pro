QT = core testlib xml
CONFIG += c++20 cmdline warn_off

isActiveConfig(debug,debug|release){
    BUILD_TYPE = Debug
    TARGET = model2qtd
}else{
    BUILD_TYPE = Release
    TARGET = model2qt
}

SOURCES += \
        fsmutils.cpp \
        main.cpp \

HEADERS += \
    commands.hpp \
    fsmutils.hpp

