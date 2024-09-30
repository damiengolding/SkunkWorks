/*
MIT License

Copyright (c) Damien Golding 2024

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#include <QObject>
#include <QDebug>
#include <QColor>
#include <QFont>
#include <QFile>
#include <QFileInfo>

namespace GoldingsGym::Ptng {

class PtngEnums : public QObject
{
    Q_OBJECT
public:
    explicit PtngEnums(QObject* parent = nullptr);
    virtual ~PtngEnums();

    friend QDebug operator<<(QDebug debug, const PtngEnums &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public:
    enum SupportedInputTypes {
        CODE,
        TSV,
        CSV,
        ARPSCAN,
        AXFR_NMAP,
        AXFR_DIG,
        AXFR_DNS_RECON,
        AXFR_FIERCE,
        AXFR_HOST,
        AXFR_NS_LIN,
        AXFR_NS_WIN,
        DGML,
        HASHES,
        IMAGE,
        MASSCAN,
        METASPLOIT,
        NBTSCAN,
        NESSUS,
        NESSUS_HSH,
        NIKTO,
        NMAP,
        OPENVAS,
        OWASP_ZAP,
        PDF,
        SSL_SCAN,
        WAPITI,
        NUM_SUPPORTED_INPUT_TYPES
    };
    enum NetworkNodeRoles {
        ROOT,
        SUBNET,
        ACLASS,
        BCLASS,
        CCLASS,
        LEAF,
        NUM_NMAP_NODE_ROLES
    };
    enum ProcessorStates {
        START_STATE_CREATED,
        START_STATE_ENTERED,
        START_STATE_EXITED,
        PROCESS_STATE_CREATED,
        PROCESS_STATE_ENTERED,
        PROCESS_STATE_EXITED,
        FINAL_STATE_CREATED,
        FINAL_STATE_ENTERED,
        FINAL_STATE_EXITED,
        NUM_PROCESSOR_STATES
    };
    enum IssueSeverity {
        NONE,
        LOW,
        MEDIUM,
        HIGH,
        CRITICAL,
        NUM_ISSUE_SEVERITIES
    };
    enum Protocol{
        UDP,
        TCP,
        NUM_PROTOCOLS
    };
    enum NessusPluginFamily {
        WINDOWS,
        LINUX,
        NETWORK_DEVICES,
        POLICY,
        DATABASE,
        WEB,
        SERVICES,
        MOBILE,
        P2P,
        SCADA,
        DOS,
        REMOTE_CONTROL,
        MISCELLANEOUS,
        NUM_NESSUS_PLUGIN_FAMILIES
    };
    Q_ENUM(SupportedInputTypes)
    Q_ENUM(NetworkNodeRoles)
    Q_ENUM(ProcessorStates)
    Q_ENUM(IssueSeverity)
    Q_ENUM(Protocol)
    Q_ENUM(NessusPluginFamily)
public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
