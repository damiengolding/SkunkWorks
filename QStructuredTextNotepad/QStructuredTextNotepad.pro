QT       += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++20 warn_off

isActiveConfig(debug,debug|release){
    BUILD_TYPE = Debug
    TARGET = STNotepadd
}
else{
    BUILD_TYPE = Release
    TARGET = STNotepad
}

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/utils/stnconfig.cpp \
    src/utils/stnlogger.cpp

HEADERS += \
    inc/utils/stnconfig.hpp \
    inc/utils/stnlogger.hpp \
    mainwindow.hpp \

FORMS += \
    mainwindow.ui

!build_pass:message("Building for:" $$BUILD_TYPE)

RESOURCES += \
    resources.qrc

DISTFILES += \
    diagrams/modelviewcontroller.qmodel
