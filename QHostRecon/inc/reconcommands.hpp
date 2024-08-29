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

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMetaEnum>

#include <QNetworkInterface>
#include <QHostInfo>
#include <QHostAddress>

#include "hostreconutils.hpp"

class ReconCommands : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool writeToXml READ writeToXml WRITE setWriteToXml NOTIFY writeToXmlChanged FINAL)
    Q_PROPERTY(QString outputFileName READ outputFileName WRITE setOutputFileName NOTIFY outputFileNameChanged FINAL)
    Q_PROPERTY(QList<QNetworkInterface> interfaces READ interfaces WRITE setInterfaces NOTIFY interfacesChanged FINAL)
    Q_PROPERTY(QList<QHostAddress> addresses READ addresses WRITE setAddresses NOTIFY addressesChanged FINAL)
    Q_PROPERTY(QString ipAddress READ ipAddress WRITE setIpAddress NOTIFY ipAddressChanged FINAL)
    Q_PROPERTY(QString domainName READ domainName WRITE setDomainName NOTIFY domainNameChanged FINAL)
    Q_PROPERTY(QString hostName READ hostName WRITE setHostName NOTIFY hostNameChanged FINAL)
    Q_PROPERTY(bool silent READ silent WRITE setSilent NOTIFY silentChanged FINAL)
    Q_PROPERTY(QList<QHostInfo> lookups READ lookups WRITE setLookups NOTIFY lookupsChanged FINAL)
    Q_PROPERTY(ReconType reconType READ reconType WRITE setReconType NOTIFY reconTypeChanged FINAL)

public:
    explicit ReconCommands(QObject *parent = nullptr);
    ~ReconCommands();

    enum ReconType{
        None,
        Local,
        Remote
    };
    Q_ENUM( ReconType )

    bool writeToXml() const;
    void setWriteToXml(bool newWriteToXml);

    QString outputFileName() const;
    void setOutputFileName(const QString &newOutputFileName);

    QList<QNetworkInterface> interfaces() const;
    void setInterfaces(const QList<QNetworkInterface> &newInterfaces);

    QList<QHostAddress> addresses() const;
    void setAddresses(const QList<QHostAddress> &newAddresses);

    QString ipAddress() const;
    void setIpAddress(const QString &newIpAddress);

    QString domainName() const;
    void setDomainName(const QString &newDomainName);

    QString hostName() const;
    void setHostName(const QString &newHostName);

    bool silent() const;
    void setSilent(bool newSilent);

    QList<QHostInfo> lookups() const;
    void setLookups(const QList<QHostInfo> &newLookups);

    ReconType reconType() const;
    void setReconType(ReconType newReconType);

public slots:
    // Local checks
    void showNicToIp();
    void showAllNics();
    void showAllNicsConfig();
    void showAllAddresses();
    void showDomainHostName();

    // Remote checks
    void showHostResolve( const QString& hosts );

    // Housekeeping
    void writeOutput();

signals:
    void writeToXmlChanged();
    void outputFileNameChanged();
    void interfacesChanged();
    void addressesChanged();
    void ipAddressChanged();
    void domainNameChanged();
    void hostNameChanged();
    void silentChanged();
    void lookupsChanged();
    void reconTypeChanged();

private:
    bool m_writeToXml = false;
    QString m_outputFileName;
    QList<QNetworkInterface> m_interfaces;
    QList<QHostAddress> m_addresses;
    QString m_ipAddress = QString();
    QString m_domainName = QString();
    QString m_hostName = QString();
    bool m_silent = false;
    QList<QHostInfo> m_lookups;
    ReconType m_reconType = ReconType::None;
};

