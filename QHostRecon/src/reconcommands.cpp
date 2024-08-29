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
#include "../inc/reconcommands.hpp"
#include "inc/hostreconutils.hpp"

ReconCommands::ReconCommands(QObject *parent)
    : QObject{parent}
{

}

ReconCommands::~ReconCommands()
{

}

#pragma Local checks {

void ReconCommands::showNicToIp()
{
    m_addresses = QNetworkInterface::allAddresses();
    if( m_silent ) return;
    qInfo() << "########## IP Address to NIC  ##########";
    for( auto address : m_addresses ){
        qInfo() << address.toString() << "-" << HostReconUtils::IpAddressToNicName( address.toString() );
    }
    qInfo() << "";
}

void ReconCommands::showAllNics()
{
    m_interfaces = QNetworkInterface::allInterfaces();
    if( m_silent ) return;
    qInfo() << "########## Network Interface Cards ##########";
    for( auto interface : m_interfaces ){
        const int intRepresentation = static_cast<int>(interface.type());
        QString interfaceType = QMetaEnum::fromType<QNetworkInterface::InterfaceType>().valueToKey(intRepresentation);
        QString output = QString("%1 - %2 - %3 - %4 - %5")
                .arg( interface.name() )
                .arg( interface.humanReadableName() )
                .arg( interface.hardwareAddress() )
                .arg( interfaceType )
                .arg( interface.index() );
        qInfo() << output;
    }
    qInfo() << "";
}

void ReconCommands::showAllNicsConfig()
{
    m_interfaces = QNetworkInterface::allInterfaces();
    if( m_silent ) return;
    qInfo() << "########## Network Interface Cards - all config ##########";
    for( auto interface : m_interfaces ){
        const int intType = static_cast<int>(interface.type());
        QString interfaceType = QMetaEnum::fromType<QNetworkInterface::InterfaceType>().valueToKey(intType);
        qInfo() << "Name:" << interface.name();
        qInfo() << "\tSystem name:" << interface.humanReadableName();
        qInfo() << "\tHardware address:" << interface.hardwareAddress();
        qInfo() << "\tType:" << interfaceType;
        qInfo() << "\tAddress entries:";
        QList<QNetworkAddressEntry> entries = interface.addressEntries();
        for( auto entry : entries ){
            QString broadcast = entry.broadcast().toString();
            qInfo() << "------------------------------------------------------------";
            qInfo() << "\t\tAddress:" << entry.ip().toString();
            qInfo() << "\t\tNetmask:" << entry.netmask().toString();
            if( !broadcast.isEmpty() ){
                qInfo() << "\t\tBroadcast address:" << broadcast;
            }
        }
        qInfo() << "------------------------------------------------------------";
        qInfo() << "";
    }
}

void ReconCommands::showAllAddresses()
{
    m_addresses = QNetworkInterface::allAddresses();
    if( m_silent ) return;
    qInfo() << "########## Host Addresses ##########";
    for( auto address : m_addresses ){
        QString nic = HostReconUtils::IpAddressToNicName( address.toString() );
        QString prot = address.protocol() == 0 ? "IPV4" : "IPV6";
        QString output = QString( "%1 - %2 - %3" )
                .arg( prot )
                .arg( address.toString() )
                .arg( nic );
        qInfo() << output;
    }
    qInfo() << "";
}

void ReconCommands::showDomainHostName()
{
    m_domainName = QHostInfo::localDomainName();
    m_hostName = QHostInfo::localHostName();
    if( m_silent ) return;
    qInfo() << "########## Domain and hostname ##########";
    qInfo() << "Domain name:" << m_domainName;
    qInfo() << "Host name:" << m_hostName;
    qInfo() << "";
}

#pragma Local checks }

#pragma Remote checks {

// TODO handle duplicates in m_lookups
void ReconCommands::showHostResolve( const QString& hosts ){
    QStringList hostList = hosts.split(",", Qt::SkipEmptyParts);
    QStringList resolvedHosts;
    for( auto host : hostList ){
        if( resolvedHosts.contains(host) ){
            continue;
        }
        QHostInfo hostInfo = QHostInfo::fromName( host );
        m_lookups << hostInfo;
        resolvedHosts << host;
    }
    if( m_silent ) return;
    qInfo() << "########## Host resolution  ##########";
    for( auto host : m_lookups ){
        qInfo() << "Host name:" << host.hostName();
        for( auto address : host.addresses() ){
            qInfo() << "\tAddress:" << address.toString();
        }
    }
}

#pragma Remote checks }

#pragma Housekeeping {

void ReconCommands::writeOutput()
{
    if( !m_writeToXml ) return;
    QFile file(m_outputFileName);
    if( !file.open( QIODevice::WriteOnly) ){
        qCritical() << "Unable to open file" << m_outputFileName << "for writing";
        return;
    }

    QXmlStreamWriter writer( &file );
    writer.setAutoFormatting(true);

    writer.writeStartDocument();
    writer.writeStartElement("qhostrecon");
    if( m_reconType == ReconType::Local ){
        writer.writeStartElement("local_checks");
        // Domain and host name
        writer.writeStartElement("domain_id");
        writer.writeAttribute("host_name",m_hostName);
        QString domainName = m_domainName.isEmpty() ? "NOT_RESOLVED" : m_domainName;
        writer.writeAttribute("domain_name",domainName);
        writer.writeEndElement();

        // Network interface cards
        writer.writeStartElement("nics");
        for( auto interface : m_interfaces ){
            writer.writeStartElement("nic");
            const int intType = static_cast<int>(interface.type());
            QString interfaceType = QMetaEnum::fromType<QNetworkInterface::InterfaceType>().valueToKey(intType);
            writer.writeAttribute("name",interface.name());
            writer.writeAttribute("system_name",interface.humanReadableName());
            QString macAddr = interface.hardwareAddress();
            if( !macAddr.isEmpty() ){
                writer.writeAttribute("mac",macAddr);
            }
            writer.writeAttribute("type",interfaceType);
            writer.writeStartElement("address_entries");
            QList<QNetworkAddressEntry> entries = interface.addressEntries();
            for( auto entry : entries ){
                writer.writeStartElement("address_entry");
                QString broadcast = entry.broadcast().toString();
                writer.writeAttribute("address",entry.ip().toString());
                writer.writeAttribute("netmask",entry.netmask().toString());
                if( !broadcast.isEmpty() ){
                    writer.writeAttribute("broadcast",broadcast);
                }
                writer.writeEndElement();
            }
            writer.writeEndElement();
            writer.writeEndElement();
        }
        writer.writeEndElement();

        // NIC for address
        writer.writeStartElement("nic-for-ip");
        for( auto address : m_addresses ){
            QString nic = HostReconUtils::IpAddressToNicName( address.toString() );
            writer.writeStartElement("ip-to-nic");
            writer.writeAttribute("address",address.toString());
            writer.writeAttribute("nic", nic );
            writer.writeEndElement();
        }
        writer.writeEndElement();

        // IP addresses
        writer.writeStartElement("addresses");
        for( auto address : m_addresses ){
            QString nic = HostReconUtils::IpAddressToNicName( address.toString() );
            QString prot = address.protocol() == 0 ? "IPV4" : "IPV6";
            writer.writeStartElement("address");
            writer.writeAttribute("address",address.toString());
            writer.writeAttribute("nic", nic );
            writer.writeAttribute("protocol", prot );
            writer.writeEndElement();
        }
        writer.writeEndElement();

        writer.writeEndElement();
    }
    if( m_reconType == ReconType::Remote ){
        // TODO write out remote checks
        writer.writeStartElement("remote_checks");
            writer.writeStartElement("lookups");
                for( auto host : m_lookups ){
                    writer.writeStartElement("lookup");
                    writer.writeAttribute("hostname", host.hostName() );
                    for( auto address : host.addresses() ){
                        writer.writeStartElement("address");
                            QString prot = address.protocol() == 0 ? "IPV4" : "IPV6";
                            writer.writeAttribute("address", address.toString() );
                            writer.writeAttribute("protocol", prot );
                        writer.writeEndElement();
                    }
                    writer.writeEndElement();
                }
            writer.writeEndElement();

        writer.writeEndElement();
    }
    writer.writeEndElement(); // Close root node
    writer.writeEndDocument();
    file.close();
}

ReconCommands::ReconType ReconCommands::reconType() const
{
    return m_reconType;
}

void ReconCommands::setReconType(ReconType newReconType)
{
    if (m_reconType == newReconType)
        return;
    m_reconType = newReconType;
    emit reconTypeChanged();
}

bool ReconCommands::silent() const
{
    return m_silent;
}

void ReconCommands::setSilent(bool newSilent)
{
    if (m_silent == newSilent)
        return;
    m_silent = newSilent;
    emit silentChanged();
}

#pragma Housekeeping }

#pragma Properties {

QList<QHostInfo> ReconCommands::lookups() const
{
    return m_lookups;
}

void ReconCommands::setLookups(const QList<QHostInfo> &newLookups)
{
    m_lookups = newLookups;
    emit lookupsChanged();
}

QString ReconCommands::domainName() const
{
    return m_domainName;
}

void ReconCommands::setDomainName(const QString &newDomainName)
{
    if (m_domainName == newDomainName)
        return;
    m_domainName = newDomainName;
    emit domainNameChanged();
}

QString ReconCommands::hostName() const
{
    return m_hostName;
}

void ReconCommands::setHostName(const QString &newHostName)
{
    if (m_hostName == newHostName)
        return;
    m_hostName = newHostName;
    emit hostNameChanged();
}

QString ReconCommands::ipAddress() const
{
    return m_ipAddress;
}

void ReconCommands::setIpAddress(const QString &newIpAddress)
{
    if (m_ipAddress == newIpAddress)
        return;
    m_ipAddress = newIpAddress;
    emit ipAddressChanged();
}

bool ReconCommands::writeToXml() const
{
    return m_writeToXml;
}

void ReconCommands::setWriteToXml(bool newWriteToXml)
{
    if (m_writeToXml == newWriteToXml)
        return;
    m_writeToXml = newWriteToXml;
    emit writeToXmlChanged();
}

QString ReconCommands::outputFileName() const
{
    return m_outputFileName;
}

void ReconCommands::setOutputFileName(const QString &newOutputFileName)
{
    if (m_outputFileName == newOutputFileName)
        return;
    m_outputFileName = newOutputFileName;
    emit outputFileNameChanged();
}

QList<QNetworkInterface> ReconCommands::interfaces() const
{
    return m_interfaces;
}

void ReconCommands::setInterfaces(const QList<QNetworkInterface> &newInterfaces)
{
    m_interfaces = newInterfaces;
    emit interfacesChanged();
}

QList<QHostAddress> ReconCommands::addresses() const
{
    return m_addresses;
}

void ReconCommands::setAddresses(const QList<QHostAddress> &newAddresses)
{
    if (m_addresses == newAddresses)
        return;
    m_addresses = newAddresses;
    emit addressesChanged();
}

#pragma Properties }
