/*
   Copyright (C) Damien Golding

   This is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this software; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA

  Don't use it to find and eat babies ... unless you're really REALLY hungry ;-)

*/

#include "NATNetworkInfo.hpp"

NATNetworkInfo::NATNetworkInfo(QObject *parent)
    : QObject{parent}
{

}

QString NATNetworkInfo::getName() const
{
    return name;
}

void NATNetworkInfo::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}

QString NATNetworkInfo::getNetwork() const
{
    return network;
}

void NATNetworkInfo::setNetwork(const QString &newNetwork)
{
    if (network == newNetwork)
        return;
    network = newNetwork;
    emit networkChanged();
}

QString NATNetworkInfo::getGateway() const
{
    return gateway;
}

void NATNetworkInfo::setGateway(const QString &newGateway)
{
    if (gateway == newGateway)
        return;
    gateway = newGateway;
    emit gatewayChanged();
}

QString NATNetworkInfo::getDhcpServer() const
{
    return dhcpServer;
}

void NATNetworkInfo::setDhcpServer(const QString &newDhcpServer)
{
    if (dhcpServer == newDhcpServer)
        return;
    dhcpServer = newDhcpServer;
    emit dhcpServerChanged();
}

QString NATNetworkInfo::getIpv6() const
{
    return ipv6;
}

void NATNetworkInfo::setIpv6(const QString &newIpv6)
{
    if (ipv6 == newIpv6)
        return;
    ipv6 = newIpv6;
    emit ipv6Changed();
}

QString NATNetworkInfo::getIpv6Prefix() const
{
    return ipv6Prefix;
}

void NATNetworkInfo::setIpv6Prefix(const QString &newIpv6Prefix)
{
    if (ipv6Prefix == newIpv6Prefix)
        return;
    ipv6Prefix = newIpv6Prefix;
    emit ipv6PrefixChanged();
}

QString NATNetworkInfo::getIpv6Default() const
{
    return ipv6Default;
}

void NATNetworkInfo::setIpv6Default(const QString &newIpv6Default)
{
    if (ipv6Default == newIpv6Default)
        return;
    ipv6Default = newIpv6Default;
    emit ipv6DefaultChanged();
}
