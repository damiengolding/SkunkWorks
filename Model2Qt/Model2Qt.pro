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
    commands/commands_class.cpp \
    commands/commands_qtfsm.cpp \
    commands/commands_qtsmf.cpp \
        main.cpp \
    uml/umlclass.cpp \
    utils/fsmutils.cpp


RESOURCES += \
    Model2Qt.qrc

STATECHARTS += \
    test_models/FsmTest.scxml

HEADERS += \
    commands/commands.hpp \
    uml/umlclass.hpp \
    utils/fsmutils.hpp

INCLUDEPATH += ./utils/ ./uml/ ./commands/

DISTFILES += \
    test_models/ClassTest.qmodel

