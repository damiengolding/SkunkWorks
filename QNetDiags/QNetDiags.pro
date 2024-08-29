QT = core network httpserver
CONFIG += c++20 cmdline warn_off

isActiveConfig(debug,debug|release){
    BUILD_TYPE = Debug
    TARGET = qnetdiagsd
}
else{
    BUILD_TYPE = Release
    TARGET = qnetdiags
}

SOURCES += \
        main.cpp \
        QNetDiagsConfig.cpp \
        QNetDiagsLogger.cpp \

HEADERS += \
    QNetDiagsConfig.hpp \
    QNetDiagsLogger.hpp \


!build_pass:message("Building for: " $$BUILD_TYPE)
