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

#ifndef DHCPSERVERINFO_HPP
#define DHCPSERVERINFO_HPP

#include <QObject>

class DHCPServerInfo : public QObject
{
    Q_OBJECT
public:
    explicit DHCPServerInfo(QObject *parent = nullptr);

    QString getNetworkName() const;
    void setNetworkName(const QString &newNetworkName);

    QString getDhcpdIP() const;
    void setDhcpdIP(const QString &newDhcpdIP);

    QString getLowerIPAddress() const;
    void setLowerIPAddress(const QString &newLowerIPAddress);

    QString getUpperIPAddress() const;
    void setUpperIPAddress(const QString &newUpperIPAddress);

    QString getNetworkMask() const;
    void setNetworkMask(const QString &newNetworkMask);

    QString getEnabled() const;
    void setEnabled(const QString &newEnabled);

    QString getGlobalConfiguration() const;
    void setGlobalConfiguration(const QString &newGlobalConfiguration);

    QString getMinLeaseTime() const;
    void setMinLeaseTime(const QString &newMinLeaseTime);

    QString getDefaultLeaseTime() const;
    void setDefaultLeaseTime(const QString &newDefaultLeaseTime);

    QString getMaxLeaseTime() const;
    void setMaxLeaseTime(const QString &newMaxLeaseTime);

    QString getForcedOptions() const;
    void setForcedOptions(const QString &newForcedOptions);

    QString getSuppressedOptions() const;
    void setSuppressedOptions(const QString &newSuppressedOptions);

    QString getOneLegacy() const;
    void setOneLegacy(const QString &newOneLegacy);

    QString getGroups() const;
    void setGroups(const QString &newGroups);

    QString getIndividualConfigs() const;
    void setIndividualConfigs(const QString &newIndividualConfigs);

signals:

    void networkNameChanged();

    void dhcpdIPChanged();

    void lowerIPAddressChanged();

    void upperIPAddressChanged();

    void networkMaskChanged();

    void enabledChanged();

    void globalConfigurationChanged();

    void minLeaseTimeChanged();

    void defaultLeaseTimeChanged();

    void maxLeaseTimeChanged();

    void forcedOptionsChanged();

    void suppressedOptionsChanged();

    void oneLegacyChanged();

    void groupsChanged();

    void individualConfigsChanged();

private:
    QString networkName;
    QString dhcpdIP;
    QString lowerIPAddress;
    QString upperIPAddress;
    QString networkMask;
    QString enabled;
    QString globalConfiguration;
    QString minLeaseTime;
    QString defaultLeaseTime;
    QString maxLeaseTime;
    QString forcedOptions;
    QString suppressedOptions;
    QString oneLegacy;
    QString groups;
    QString individualConfigs;

    Q_PROPERTY(QString networkName READ getNetworkName WRITE setNetworkName NOTIFY networkNameChanged)
    Q_PROPERTY(QString dhcpdIP READ getDhcpdIP WRITE setDhcpdIP NOTIFY dhcpdIPChanged)
    Q_PROPERTY(QString lowerIPAddress READ getLowerIPAddress WRITE setLowerIPAddress NOTIFY lowerIPAddressChanged)
    Q_PROPERTY(QString upperIPAddress READ getUpperIPAddress WRITE setUpperIPAddress NOTIFY upperIPAddressChanged)
    Q_PROPERTY(QString networkMask READ getNetworkMask WRITE setNetworkMask NOTIFY networkMaskChanged)
    Q_PROPERTY(QString enabled READ getEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString globalConfiguration READ getGlobalConfiguration WRITE setGlobalConfiguration NOTIFY globalConfigurationChanged)
    Q_PROPERTY(QString minLeaseTime READ getMinLeaseTime WRITE setMinLeaseTime NOTIFY minLeaseTimeChanged)
    Q_PROPERTY(QString defaultLeaseTime READ getDefaultLeaseTime WRITE setDefaultLeaseTime NOTIFY defaultLeaseTimeChanged)
    Q_PROPERTY(QString maxLeaseTime READ getMaxLeaseTime WRITE setMaxLeaseTime NOTIFY maxLeaseTimeChanged)
    Q_PROPERTY(QString forcedOptions READ getForcedOptions WRITE setForcedOptions NOTIFY forcedOptionsChanged)
    Q_PROPERTY(QString suppressedOptions READ getSuppressedOptions WRITE setSuppressedOptions NOTIFY suppressedOptionsChanged)
    Q_PROPERTY(QString oneLegacy READ getOneLegacy WRITE setOneLegacy NOTIFY oneLegacyChanged)
    Q_PROPERTY(QString groups READ getGroups WRITE setGroups NOTIFY groupsChanged)
    Q_PROPERTY(QString individualConfigs READ getIndividualConfigs WRITE setIndividualConfigs NOTIFY individualConfigsChanged)
};

#endif // DHCPSERVERINFO_HPP
