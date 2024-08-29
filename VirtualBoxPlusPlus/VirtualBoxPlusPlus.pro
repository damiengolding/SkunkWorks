QT       += core gui concurrent charts xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20 qscintilla2 warn_off

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CreatePlaylistWizard.cpp \
    DHCPServerInfo.cpp \
    LifeCycle/LifeCycleEntry.cpp \
    MachineInfo.cpp \
    MachineMetrics.cpp \
    MainWindowAvailableMachinesRefresh.cpp \
    MainWindowConfiguredNetworks.cpp \
    MainWindowDataDisplay.cpp \
    MainWindowLifeCycle.cpp \
    MainWindowRefresh.cpp \
    MainWindowRegisteredMedia.cpp \
    MainWindowRunningMachinesRefresh.cpp \
    MainWindowSignalsSlots.cpp \
    MainWindowUX.cpp \
    MainWindowUtilities.cpp \
    MainWindowVMInfoAvailable.cpp \
    MetricsAggregateWidget.cpp \
    MetricsCounter.cpp \
    MetricsMonitor.cpp \
    MetricsVisualization.cpp \
    NATNetworkInfo.cpp \
    PlaylistDialog.cpp \
    RegisteredMediaInfo.cpp \
    SettingsDialog.cpp \
    StandardInterfaceInfo.cpp \
    VirtualMachine.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    CreatePlaylistWizard.hpp \
    DHCPServerInfo.hpp \
    DataIngestion/RunningMachineConsumer.hpp \
    LifeCycle/LifeCycleEntry.hpp \
    MachineInfo.hpp \
    MachineMetrics.hpp \
    MainWindow.hpp \
    MetricsAggregateWidget.hpp \
    MetricsCounter.hpp \
    MetricsMonitor.hpp \
    MetricsVisualization.hpp \
    NATNetworkInfo.hpp \
    PlaylistDialog.hpp \
    RegisteredMediaInfo.hpp \
    SettingsDialog.hpp \
    StandardInterfaceInfo.hpp \
    VirtualMachine.hpp

FORMS += \
    MainWindow.ui \
    MetricsAggregateWidget.ui \
    MetricsCounter.ui \
    MetricsVisualization.ui \
    PlaylistDialog.ui \
    SettingsDialog.ui

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    VirtualBoxPlusPlus.qrc

# OpenMP
########
win32:CONFIG{
    QMAKE_CXXFLAGS += -fopenmp
    QMAKE_LFLAGS += -fopenmp
    LIBS += -lopenmp
    }

# Boost
win32:CONFIG{
    INCLUDEPATH += "C:\Boost_1_81_0"
    # Add one path at a time, then add individual library, e.g.
    LIBS += -L"C:\Boost_1_81_0\lib64-msvc-14.3" # -lboost_program_options-vc143-mt-gd-x64-1_81.lib
    }

win32:CONFIG(release, debug|release): LIBS += -L'C:/Third Party Software/QScintilla/Built Binaries/mingw_64/bin' -lqscintilla2_qt6
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Third Party Software/QScintilla/Built Binaries/mingw_64/bin' -lqscintilla2_qt6d

INCLUDEPATH += 'C:/Third Party Software/QScintilla/Built Binaries/mingw_64/include'
DEPENDPATH += 'C:/Third Party Software/QScintilla/Built Binaries/mingw_64/include'

#! Delete or comment the original default deployment section
#! and add "CONFIG+=MSVC" or "CONFIG+=MINGW" including the double-quotes
#! to the Qmake build step in 'Projects' - build/release take care of themselves

# Deployment
win32:CONFIG(MINGW){
win32:CONFIG(debug, debug|release){
message("MINGW Debug build")
TARGET = VirtualBoxPlusPlus_mingw64d
}else{
message("MINGW Release build")
TARGET = VirtualBoxPlusPlus_mingw64
# DEFINES += QT_NO_DEBUG_OUTPUT
}
}
win32:CONFIG(MSVC){
win32:CONFIG(debug, debug|release){
message("MSVC Debug build")
TARGET = VirtualBoxPlusPlus_msvc64d
}else{
message("MSVC Release build")
TARGET = VirtualBoxPlusPlus_msvc64
DEFINES += QT_NO_DEBUG_OUTPUT
}
}
target.path  += "..\Output"
INSTALLS += target

win32:CONFIG(MINGW){
    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Output/lib/ -lVirtualBoxPlusPlusLib_mingw64
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Output/lib/ -lVirtualBoxPlusPlusLib_mingw64d
}
win32:CONFIG(MSVC){
    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Output/lib/ -lVirtualBoxPlusPlusLib_msvc64
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Output/lib/ -lVirtualBoxPlusPlusLib_msvc64d
}

INCLUDEPATH += $$PWD/../Output/lib/inc
DEPENDPATH += $$PWD/../Output/lib/inc

win32:CONFIG(MINGW){
    win32:CONFIG(release, debug|release): LIBS += -L'C:/Third Party Software/QScintilla/Built Binaries/mingw_64/bin/' -llibqscintilla2_qt6
    else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Third Party Software/QScintilla/Built Binaries/mingw_64/bin/' -llibqscintilla2_qt6d
}

win32:CONFIG(MSVC){
    win32:CONFIG(release, debug|release): LIBS += -L'C:/Third Party Software/QScintilla/Built Binaries/msvc2019_64/bin/' -lqscintilla2_qt6
    else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Third Party Software/QScintilla/Built Binaries/msvc2019_64/bin/' -lqscintilla2_qt6d
}

INCLUDEPATH += 'C:/Third Party Software/QScintilla\Built Binaries/msvc2019_64/include'
DEPENDPATH += 'C:/Third Party Software/QScintilla/Built Binaries/msvc2019_64/include'
