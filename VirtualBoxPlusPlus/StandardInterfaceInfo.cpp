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

#include "StandardInterfaceInfo.hpp"

StandardInterfaceInfo::StandardInterfaceInfo(QObject *parent)
    : QObject{parent}
{

}

QString StandardInterfaceInfo::getName() const
{
    return name;
}

void StandardInterfaceInfo::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}

QString StandardInterfaceInfo::getGUID() const
{
    return GUID;
}

void StandardInterfaceInfo::setGUID(const QString &newGUID)
{
    if (GUID == newGUID)
        return;
    GUID = newGUID;
    emit GUIDChanged();
}

QString StandardInterfaceInfo::getDHCP() const
{
    return DHCP;
}

void StandardInterfaceInfo::setDHCP(const QString &newDHCP)
{
    if (DHCP == newDHCP)
        return;
    DHCP = newDHCP;
    emit DHCPChanged();
}

QString StandardInterfaceInfo::getIPAddress() const
{
    return IPAddress;
}

void StandardInterfaceInfo::setIPAddress(const QString &newIPAddress)
{
    if (IPAddress == newIPAddress)
        return;
    IPAddress = newIPAddress;
    emit IPAddressChanged();
}

QString StandardInterfaceInfo::getNetworkMask() const
{
    return NetworkMask;
}

void StandardInterfaceInfo::setNetworkMask(const QString &newNetworkMask)
{
    if (NetworkMask == newNetworkMask)
        return;
    NetworkMask = newNetworkMask;
    emit NetworkMaskChanged();
}

QString StandardInterfaceInfo::getIPV6Address() const
{
    return IPV6Address;
}

void StandardInterfaceInfo::setIPV6Address(const QString &newIPV6Address)
{
    if (IPV6Address == newIPV6Address)
        return;
    IPV6Address = newIPV6Address;
    emit IPV6AddressChanged();
}

QString StandardInterfaceInfo::getIPV6NetworkMaskPrefixLength() const
{
    return IPV6NetworkMaskPrefixLength;
}

void StandardInterfaceInfo::setIPV6NetworkMaskPrefixLength(const QString &newIPV6NetworkMaskPrefixLength)
{
    if (IPV6NetworkMaskPrefixLength == newIPV6NetworkMaskPrefixLength)
        return;
    IPV6NetworkMaskPrefixLength = newIPV6NetworkMaskPrefixLength;
    emit IPV6NetworkMaskPrefixLengthChanged();
}

QString StandardInterfaceInfo::getHardwareAddress() const
{
    return hardwareAddress;
}

void StandardInterfaceInfo::setHardwareAddress(const QString &newHardwareAddress)
{
    if (hardwareAddress == newHardwareAddress)
        return;
    hardwareAddress = newHardwareAddress;
    emit hardwareAddressChanged();
}

QString StandardInterfaceInfo::getMediumType() const
{
    return mediumType;
}

void StandardInterfaceInfo::setMediumType(const QString &newMediumType)
{
    if (mediumType == newMediumType)
        return;
    mediumType = newMediumType;
    emit mediumTypeChanged();
}

QString StandardInterfaceInfo::getWireless() const
{
    return wireless;
}

void StandardInterfaceInfo::setWireless(const QString &newWireless)
{
    if (wireless == newWireless)
        return;
    wireless = newWireless;
    emit wirelessChanged();
}

QString StandardInterfaceInfo::getStatus() const
{
    return status;
}

void StandardInterfaceInfo::setStatus(const QString &newStatus)
{
    if (status == newStatus)
        return;
    status = newStatus;
    emit statusChanged();
}

QString StandardInterfaceInfo::getVBoxNetworkName() const
{
    return VBoxNetworkName;
}

void StandardInterfaceInfo::setVBoxNetworkName(const QString &newVBoxNetworkName)
{
    if (VBoxNetworkName == newVBoxNetworkName)
        return;
    VBoxNetworkName = newVBoxNetworkName;
    emit VBoxNetworkNameChanged();
}
