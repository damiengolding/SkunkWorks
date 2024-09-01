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
    http_client/httpclient.cpp \
    http_server/httpserver.cpp \
        main.cpp \
    ssl_client/sslclientsignalhandler.cpp \
    ssl_client/sslsendsocket.cpp \
    ssl_server/sslreceivesocket.cpp \
    ssl_server/sslserver.cpp \
    ssl_server/sslserversignalhandler.cpp \
    tcp_client/tcpclientsignalhandler.cpp \
    tcp_client/tcpsendsocket.cpp \
    tcp_server/tcpreceivesocket.cpp \
    tcp_server/tcpserver.cpp \
    tcp_server/tcpserversignalhandler.cpp \
    utils/netdiagsutils.cpp

HEADERS += \
    commands/commands.hpp \
    http_client/httpclient.hpp \
    http_server/httpserver.hpp \
    ssl_client/sslclientsignalhandler.hpp \
    ssl_client/sslsendsocket.hpp \
    ssl_server/sslreceivesocket.hpp \
    ssl_server/sslserver.hpp \
    ssl_server/sslserversignalhandler.hpp \
    tcp_client/tcpclientsignalhandler.hpp \
    tcp_client/tcpsendsocket.hpp \
    tcp_server/tcpreceivesocket.hpp \
    tcp_server/tcpserver.hpp \
    tcp_server/tcpserversignalhandler.hpp \
    utils/netdiagsutils.hpp


!build_pass:message("Building for: " $$BUILD_TYPE)
