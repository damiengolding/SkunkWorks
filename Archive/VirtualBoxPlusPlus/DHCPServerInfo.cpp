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

#include "DHCPServerInfo.hpp"

DHCPServerInfo::DHCPServerInfo(QObject *parent)
    : QObject{parent}
{

}

QString DHCPServerInfo::getNetworkName() const
{
    return networkName;
}

void DHCPServerInfo::setNetworkName(const QString &newNetworkName)
{
    if (networkName == newNetworkName)
        return;
    networkName = newNetworkName;
    emit networkNameChanged();
}

QString DHCPServerInfo::getDhcpdIP() const
{
    return dhcpdIP;
}

void DHCPServerInfo::setDhcpdIP(const QString &newDhcpdIP)
{
    if (dhcpdIP == newDhcpdIP)
        return;
    dhcpdIP = newDhcpdIP;
    emit dhcpdIPChanged();
}

QString DHCPServerInfo::getLowerIPAddress() const
{
    return lowerIPAddress;
}

void DHCPServerInfo::setLowerIPAddress(const QString &newLowerIPAddress)
{
    if (lowerIPAddress == newLowerIPAddress)
        return;
    lowerIPAddress = newLowerIPAddress;
    emit lowerIPAddressChanged();
}

QString DHCPServerInfo::getUpperIPAddress() const
{
    return upperIPAddress;
}

void DHCPServerInfo::setUpperIPAddress(const QString &newUpperIPAddress)
{
    if (upperIPAddress == newUpperIPAddress)
        return;
    upperIPAddress = newUpperIPAddress;
    emit upperIPAddressChanged();
}

QString DHCPServerInfo::getNetworkMask() const
{
    return networkMask;
}

void DHCPServerInfo::setNetworkMask(const QString &newNetworkMask)
{
    if (networkMask == newNetworkMask)
        return;
    networkMask = newNetworkMask;
    emit networkMaskChanged();
}

QString DHCPServerInfo::getEnabled() const
{
    return enabled;
}

void DHCPServerInfo::setEnabled(const QString &newEnabled)
{
    if (enabled == newEnabled)
        return;
    enabled = newEnabled;
    emit enabledChanged();
}

QString DHCPServerInfo::getGlobalConfiguration() const
{
    return globalConfiguration;
}

void DHCPServerInfo::setGlobalConfiguration(const QString &newGlobalConfiguration)
{
    if (globalConfiguration == newGlobalConfiguration)
        return;
    globalConfiguration = newGlobalConfiguration;
    emit globalConfigurationChanged();
}

QString DHCPServerInfo::getMinLeaseTime() const
{
    return minLeaseTime;
}

void DHCPServerInfo::setMinLeaseTime(const QString &newMinLeaseTime)
{
    if (minLeaseTime == newMinLeaseTime)
        return;
    minLeaseTime = newMinLeaseTime;
    emit minLeaseTimeChanged();
}

QString DHCPServerInfo::getDefaultLeaseTime() const
{
    return defaultLeaseTime;
}

void DHCPServerInfo::setDefaultLeaseTime(const QString &newDefaultLeaseTime)
{
    if (defaultLeaseTime == newDefaultLeaseTime)
        return;
    defaultLeaseTime = newDefaultLeaseTime;
    emit defaultLeaseTimeChanged();
}

QString DHCPServerInfo::getMaxLeaseTime() const
{
    return maxLeaseTime;
}

void DHCPServerInfo::setMaxLeaseTime(const QString &newMaxLeaseTime)
{
    if (maxLeaseTime == newMaxLeaseTime)
        return;
    maxLeaseTime = newMaxLeaseTime;
    emit maxLeaseTimeChanged();
}

QString DHCPServerInfo::getForcedOptions() const
{
    return forcedOptions;
}

void DHCPServerInfo::setForcedOptions(const QString &newForcedOptions)
{
    if (forcedOptions == newForcedOptions)
        return;
    forcedOptions = newForcedOptions;
    emit forcedOptionsChanged();
}

QString DHCPServerInfo::getSuppressedOptions() const
{
    return suppressedOptions;
}

void DHCPServerInfo::setSuppressedOptions(const QString &newSuppressedOptions)
{
    if (suppressedOptions == newSuppressedOptions)
        return;
    suppressedOptions = newSuppressedOptions;
    emit suppressedOptionsChanged();
}

QString DHCPServerInfo::getOneLegacy() const
{
    return oneLegacy;
}

void DHCPServerInfo::setOneLegacy(const QString &newOneLegacy)
{
    if (oneLegacy == newOneLegacy)
        return;
    oneLegacy = newOneLegacy;
    emit oneLegacyChanged();
}

QString DHCPServerInfo::getGroups() const
{
    return groups;
}

void DHCPServerInfo::setGroups(const QString &newGroups)
{
    if (groups == newGroups)
        return;
    groups = newGroups;
    emit groupsChanged();
}

QString DHCPServerInfo::getIndividualConfigs() const
{
    return individualConfigs;
}

void DHCPServerInfo::setIndividualConfigs(const QString &newIndividualConfigs)
{
    if (individualConfigs == newIndividualConfigs)
        return;
    individualConfigs = newIndividualConfigs;
    emit individualConfigsChanged();
}
