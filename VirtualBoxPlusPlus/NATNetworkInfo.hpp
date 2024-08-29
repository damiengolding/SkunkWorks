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

#ifndef NATNETWORKINFO_HPP
#define NATNETWORKINFO_HPP

#include <QObject>

class NATNetworkInfo : public QObject
{
    Q_OBJECT
public:
    explicit NATNetworkInfo(QObject *parent = nullptr);

    QString getName() const;
    void setName(const QString &newName);

    QString getNetwork() const;
    void setNetwork(const QString &newNetwork);

    QString getGateway() const;
    void setGateway(const QString &newGateway);

    QString getDhcpServer() const;
    void setDhcpServer(const QString &newDhcpServer);

    QString getIpv6() const;
    void setIpv6(const QString &newIpv6);

    QString getIpv6Prefix() const;
    void setIpv6Prefix(const QString &newIpv6Prefix);

    QString getIpv6Default() const;
    void setIpv6Default(const QString &newIpv6Default);

signals:
    void nameChanged();
    void networkChanged();
    void gatewayChanged();
    void dhcpServerChanged();
    void ipv6Changed();
    void ipv6PrefixChanged();
    void ipv6DefaultChanged();

private:
    QString name;
    QString network;
    QString gateway;
    QString dhcpServer;
    QString ipv6;
    QString ipv6Prefix;
    QString ipv6Default;
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString network READ getNetwork WRITE setNetwork NOTIFY networkChanged)
    Q_PROPERTY(QString gateway READ getGateway WRITE setGateway NOTIFY gatewayChanged)
    Q_PROPERTY(QString dhcpServer READ getDhcpServer WRITE setDhcpServer NOTIFY dhcpServerChanged)
    Q_PROPERTY(QString ipv6 READ getIpv6 WRITE setIpv6 NOTIFY ipv6Changed)
    Q_PROPERTY(QString ipv6Prefix READ getIpv6Prefix WRITE setIpv6Prefix NOTIFY ipv6PrefixChanged)
    Q_PROPERTY(QString ipv6Default READ getIpv6Default WRITE setIpv6Default NOTIFY ipv6DefaultChanged)
};

#endif // NATNETWORKINFO_HPP

//Name:         NatNetwork
//Network:      10.0.2.0/24
//Gateway:      10.0.2.1
//DHCP Server:  Yes
//IPv6:         No
//IPv6 Prefix:  fd17:625c:f037:2::/64
//IPv6 Default: No
