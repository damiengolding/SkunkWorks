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

#ifndef STANDARDINTERFACEINFO_H
#define STANDARDINTERFACEINFO_H

#include <QObject>

class StandardInterfaceInfo : public QObject
{
    Q_OBJECT
public:
    explicit StandardInterfaceInfo(QObject *parent = nullptr);

    QString getName() const;
    void setName(const QString &newName);

    QString getGUID() const;
    void setGUID(const QString &newGUID);

    QString getDHCP() const;
    void setDHCP(const QString &newDHCP);

    QString getIPAddress() const;
    void setIPAddress(const QString &newIPAddress);

    QString getNetworkMask() const;
    void setNetworkMask(const QString &newNetworkMask);

    QString getIPV6Address() const;
    void setIPV6Address(const QString &newIPV6Address);

    QString getIPV6NetworkMaskPrefixLength() const;
    void setIPV6NetworkMaskPrefixLength(const QString &newIPV6NetworkMaskPrefixLength);

    QString getHardwareAddress() const;
    void setHardwareAddress(const QString &newHardwareAddress);

    QString getMediumType() const;
    void setMediumType(const QString &newMediumType);

    QString getWireless() const;
    void setWireless(const QString &newWireless);

    QString getStatus() const;
    void setStatus(const QString &newStatus);

    QString getVBoxNetworkName() const;
    void setVBoxNetworkName(const QString &newVBoxNetworkName);

signals:
    void nameChanged();
    void GUIDChanged();
    void DHCPChanged();
    void IPAddressChanged();
    void NetworkMaskChanged();
    void IPV6AddressChanged();
    void IPV6NetworkMaskPrefixLengthChanged();
    void hardwareAddressChanged();
    void mediumTypeChanged();
    void wirelessChanged();
    void statusChanged();
    void VBoxNetworkNameChanged();

private:
    QString name;
    QString GUID;
    QString DHCP;
    QString IPAddress;
    QString NetworkMask;
    QString IPV6Address;
    QString IPV6NetworkMaskPrefixLength;
    QString hardwareAddress;
    QString mediumType;
    QString wireless;
    QString status;
    QString VBoxNetworkName;
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString GUID READ getGUID WRITE setGUID NOTIFY GUIDChanged)
    Q_PROPERTY(QString DHCP READ getDHCP WRITE setDHCP NOTIFY DHCPChanged)
    Q_PROPERTY(QString IPAddress READ getIPAddress WRITE setIPAddress NOTIFY IPAddressChanged)
    Q_PROPERTY(QString NetworkMask READ getNetworkMask WRITE setNetworkMask NOTIFY NetworkMaskChanged)
    Q_PROPERTY(QString IPV6Address READ getIPV6Address WRITE setIPV6Address NOTIFY IPV6AddressChanged)
    Q_PROPERTY(QString IPV6NetworkMaskPrefixLength READ getIPV6NetworkMaskPrefixLength WRITE setIPV6NetworkMaskPrefixLength NOTIFY IPV6NetworkMaskPrefixLengthChanged)
    Q_PROPERTY(QString hardwareAddress READ getHardwareAddress WRITE setHardwareAddress NOTIFY hardwareAddressChanged)
    Q_PROPERTY(QString mediumType READ getMediumType WRITE setMediumType NOTIFY mediumTypeChanged)
    Q_PROPERTY(QString wireless READ getWireless WRITE setWireless NOTIFY wirelessChanged)
    Q_PROPERTY(QString status READ getStatus WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString VBoxNetworkName READ getVBoxNetworkName WRITE setVBoxNetworkName NOTIFY VBoxNetworkNameChanged)
};

#endif // STANDARDINTERFACEINFO_H

//Name:            Intel(R) Dual Band Wireless-AC 8265
//GUID:            e5102fe8-ad53-4412-81e0-07bc83dac4c3
//DHCP:            Enabled
//IPAddress:       10.119.217.144
//NetworkMask:     255.255.192.0
//IPV6Address:     fe80::c915:58b8:bd19:2f7e
//IPV6NetworkMaskPrefixLength: 64
//HardwareAddress: f8:59:71:85:3f:63
//MediumType:      Ethernet
//Wireless:        Yes
//Status:          Up
//VBoxNetworkName: HostInterfaceNetworking-Intel(R) Dual Band Wireless-AC 8265
