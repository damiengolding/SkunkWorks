# This is the qmake file for the QScintilla plugin for Qt Designer.

isActiveConfig(debug,debug|release){
    TARGET = qscintillaplugind
}else{
    TARGET = qscintillaplugin
}

TEMPLATE = lib

# Comment this in to build a dynamic library supporting multiple architectures
# on macOS.
#QMAKE_APPLE_DEVICE_ARCHS = x86_64 arm64

CONFIG += plugin qscintilla2

QT += designer

# Work around QTBUG-39300.
CONFIG -= android_install

HEADERS = qscintillaplugin.h
SOURCES = qscintillaplugin.cpp

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Deploy/shared/ -lqscintilla2_qt6
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Deploy/shared/ -lqscintilla2_qt6d

INCLUDEPATH += $$PWD/../../Deploy/shared/inc
DEPENDPATH += $$PWD/../../Deploy/shared/inc
