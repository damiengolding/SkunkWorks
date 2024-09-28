QT += gui xml designer testlib

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++20 warn_off

SOURCES += \
    src/conversionutils.cpp \
    src/ptngcodewidgetplugin.cpp \
    src/ptngdgmlloader.cpp \
    src/ptngdgmlwidgetplugin.cpp \
    src/ptngencdecwidgetplugin.cpp \
    src/ptnghostwidgetplugin.cpp \
    src/ptngimagewidgetplugin.cpp \
    src/ptngtablewidgetplugin.cpp \
    src/ptngxmlwidgetplugin.cpp \
    ui/ptngcodewidget.cpp \
    ui/ptngdgmlwidget.cpp \
    ui/ptngencdecwidget.cpp \
    ui/ptnghostwidget.cpp \
    ui/ptngimagewidget.cpp \
    ui/ptngtablewidget.cpp \
    ui/ptngxmlwidget.cpp

HEADERS += \
    inc/conversionutils.hpp \
    inc/global_inc.hpp \
    inc/ptngabstractwidget.hpp \
    inc/ptngcodewidgetplugin.hpp \
    inc/ptngdgmlloader.hpp \
    inc/ptngdgmlwidgetplugin.hpp \
    inc/ptngencdecwidgetplugin.hpp \
    inc/ptnghostwidgetplugin.hpp \
    inc/ptngimagewidgetplugin.hpp \
    inc/ptngtablewidgetplugin.hpp \
    inc/ptngxmlwidgetplugin.hpp \
    ui/ptngcodewidget.hpp \
    ui/ptngdgmlwidget.hpp \
    ui/ptngencdecwidget.hpp \
    ui/ptnghostwidget.hpp \
    ui/ptngimagewidget.hpp \
    ui/ptngtablewidget.hpp \
    ui/ptngxmlwidget.hpp


RESOURCES += \
    res/icons.qrc

FORMS += \
    ui/ptngcodewidget.ui \
    ui/ptngdgmlwidget.ui \
    ui/ptngencdecwidget.ui \
    ui/ptnghostwidget.ui \
    ui/ptngimagewidget.ui \
    ui/ptngtablewidget.ui \
    ui/ptngxmlwidget.ui

DISTFILES += \
    res/computer_01.png \
    res/goldings_gym_core_00_white.png \
    res/lan_01.png \
    res/node_active_01.png \
    res/node_idle_01.png

# libparser
win32:CONFIG(release, debug|release): LIBS += -LC:/Tools/GoldingsGymLibraries/PtngDataVisualization/Shared/ -llibparser
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Tools/GoldingsGymLibraries/PtngDataVisualization/Shared/ -llibparserd
INCLUDEPATH += C:/Tools/GoldingsGymLibraries/PtngDataVisualization/Shared/inc
DEPENDPATH += C:/Tools/GoldingsGymLibraries/PtngDataVisualization/Shared/inc

# QScintilla
win32:CONFIG(release, debug|release): LIBS += -LC:/Tools/Libraries/QScintilla/ -lqscintilla2_qt6
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Tools/Libraries/QScintilla/ -lqscintilla2_qt6d
INCLUDEPATH += C:/Tools/Libraries/QScintilla/inc
DEPENDPATH += C:/Tools/Libraries/QScintilla/inc
