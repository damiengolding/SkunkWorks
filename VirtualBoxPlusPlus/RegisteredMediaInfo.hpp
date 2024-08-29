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

#ifndef REGISTEREDMEDIAINFO_HPP
#define REGISTEREDMEDIAINFO_HPP

#include <QObject>

class RegisteredMediaInfo : public QObject
{
    Q_OBJECT
public:
    explicit RegisteredMediaInfo(QObject *parent = nullptr);

    QString getUUID() const;
    void setUUID(const QString &newUUID);

    QString getParentUUID() const;
    void setParentUUID(const QString &newParentUUID);

    QString getState() const;
    void setState(const QString &newState);

    QString getType() const;
    void setType(const QString &newType);

    QString getLocation() const;
    void setLocation(const QString &newLocation);

    QString getStorageFormat() const;
    void setStorageFormat(const QString &newStorageFormat);

    QString getCapacity() const;
    void setCapacity(const QString &newCapacity);

    QString getEncryption() const;
    void setEncryption(const QString &newEncryption);

signals:
    void UUIDChanged();
    void parentUUIDChanged();
    void stateChanged();
    void typeChanged();
    void locationChanged();
    void storageFormatChanged();
    void capacityChanged();
    void encryptionChanged();

private:
    QString UUID;
    QString parentUUID;
    QString state;
    QString type;
    QString location;
    QString storageFormat;
    QString capacity;
    QString encryption;

    Q_PROPERTY(QString UUID READ getUUID WRITE setUUID NOTIFY UUIDChanged)
    Q_PROPERTY(QString parentUUID READ getParentUUID WRITE setParentUUID NOTIFY parentUUIDChanged)
    Q_PROPERTY(QString state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString type READ getType WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString location READ getLocation WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(QString storageFormat READ getStorageFormat WRITE setStorageFormat NOTIFY storageFormatChanged)
    Q_PROPERTY(QString capacity READ getCapacity WRITE setCapacity NOTIFY capacityChanged)
    Q_PROPERTY(QString encryption READ getEncryption WRITE setEncryption NOTIFY encryptionChanged)
};

#endif // REGISTEREDMEDIAINFO_HPP
