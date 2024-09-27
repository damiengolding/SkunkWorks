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
    uml/umlrelation.cpp \
    uml/umlstate.cpp \
    utils/modelutils.cpp


RESOURCES += \
    Model2Qt.qrc

STATECHARTS += \
    test_models/EtgTest.scxml \
    test_models/FsmTest.scxml

HEADERS += \
    commands/commands.hpp \
    uml/umlclass.hpp \
    uml/umlrelation.hpp \
    uml/umlstate.hpp \
    utils/modelutils.hpp

INCLUDEPATH += ./utils/ ./uml/ ./commands/

DISTFILES += \
    doc/NAMESPACES.txt \
    doc/class_model.png \
    doc/etg_state_chart.png \
    doc/state_chart.png \
    templates/qtsmfetg/etg_hdr.txt \
    test_models/ClassTest.qmodel

