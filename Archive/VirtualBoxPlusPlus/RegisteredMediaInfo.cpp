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

#include "RegisteredMediaInfo.hpp"

RegisteredMediaInfo::RegisteredMediaInfo(QObject *parent)
    : QObject{parent}
{

}

QString RegisteredMediaInfo::getUUID() const
{
    return UUID;
}

void RegisteredMediaInfo::setUUID(const QString &newUUID)
{
    if (UUID == newUUID)
        return;
    UUID = newUUID;
    emit UUIDChanged();
}

QString RegisteredMediaInfo::getParentUUID() const
{
    return parentUUID;
}

void RegisteredMediaInfo::setParentUUID(const QString &newParentUUID)
{
    if (parentUUID == newParentUUID)
        return;
    parentUUID = newParentUUID;
    emit parentUUIDChanged();
}

QString RegisteredMediaInfo::getState() const
{
    return state;
}

void RegisteredMediaInfo::setState(const QString &newState)
{
    if (state == newState)
        return;
    state = newState;
    emit stateChanged();
}

QString RegisteredMediaInfo::getType() const
{
    return type;
}

void RegisteredMediaInfo::setType(const QString &newType)
{
    if (type == newType)
        return;
    type = newType;
    emit typeChanged();
}

QString RegisteredMediaInfo::getLocation() const
{
    return location;
}

void RegisteredMediaInfo::setLocation(const QString &newLocation)
{
    if (location == newLocation)
        return;
    location = newLocation;
    emit locationChanged();
}

QString RegisteredMediaInfo::getStorageFormat() const
{
    return storageFormat;
}

void RegisteredMediaInfo::setStorageFormat(const QString &newStorageFormat)
{
    if (storageFormat == newStorageFormat)
        return;
    storageFormat = newStorageFormat;
    emit storageFormatChanged();
}

QString RegisteredMediaInfo::getCapacity() const
{
    return capacity;
}

void RegisteredMediaInfo::setCapacity(const QString &newCapacity)
{
    if (capacity == newCapacity)
        return;
    capacity = newCapacity;
    emit capacityChanged();
}

QString RegisteredMediaInfo::getEncryption() const
{
    return encryption;
}

void RegisteredMediaInfo::setEncryption(const QString &newEncryption)
{
    if (encryption == newEncryption)
        return;
    encryption = newEncryption;
    emit encryptionChanged();
}
