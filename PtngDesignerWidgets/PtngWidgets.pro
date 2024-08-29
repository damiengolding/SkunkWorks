QT += gui xml designer testlib

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++20 warn_off

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
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

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

# Additional static linkage for the ODBC portion of the Qt SQL module
LIBS += -lodbc32

# libparser
win32:CONFIG(release, debug|release): LIBS += -L"C:\Users\damie\source\repos\PtngDataVisualizationStatic\libparser\release" -llibparser
win32:CONFIG(debug, debug|release): LIBS += -L"C:\Users\damie\source\repos\PtngDataVisualizationStatic\libparser\release" -llibparser
INCLUDEPATH += "C:\Users\damie\source\repos\PtngDataVisualizationStatic\libparser\inc"
DEPENDPATH += "C:\Users\damie\source\repos\PtngDataVisualizationStatic\libparser\inc"

# WaifsAndStrays
win32: LIBS += -L"C:\Users\damie\source\repos\WaifsAndStrays\WaifsAndStraysOutput\release" -lWaifsAndStrays
INCLUDEPATH += "C:\Users\damie\source\repos\WaifsAndStrays\WaifsAndStraysOutput\inc"
DEPENDPATH += "C:\Users\damie\source\repos\WaifsAndStrays\WaifsAndStraysOutput\inc"

# QScintilla - because it's looking in the static build directory
win32: LIBS += -L"C:\Users\damie\source\repos\QScintillaBuild\Deploy\static" -lqscintilla2_qt6
INCLUDEPATH += "C:\Users\damie\source\repos\QScintillaBuild\Deploy\inc"
DEPENDPATH += "C:\Users\damie\source\repos\QScintillaBuild\Deploy\inc"

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
