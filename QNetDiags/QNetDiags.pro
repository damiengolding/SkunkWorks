QT = core network httpserver xml
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
    commands/client_commands.cpp \
    commands/server_commands.cpp \
        main.cpp \
    tcp_server/tcpreceivesocket.cpp \
    tcp_server/tcpserver.cpp \
    tcp_server/tcpsignalhandler.cpp \
    utils/netdiagsutils.cpp

HEADERS += \
    commands/commands.hpp \
    tcp_server/tcpreceivesocket.hpp \
    tcp_server/tcpserver.hpp \
    tcp_server/tcpsignalhandler.hpp \
    utils/netdiagsutils.hpp


!build_pass:message("Building for: " $$BUILD_TYPE)
