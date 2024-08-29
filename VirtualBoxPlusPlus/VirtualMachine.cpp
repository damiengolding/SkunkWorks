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

#include "VirtualMachine.hpp"

VirtualMachine::VirtualMachine(QObject *parent)
    : QObject{parent}
{

}

QString VirtualMachine::getName() const
{
    return Name;
}

void VirtualMachine::setName(const QString &newName)
{
    if (Name == newName)
        return;
    Name = newName;
    emit NameChanged();
}

QString VirtualMachine::getUuid() const
{
    return Uuid;
}

void VirtualMachine::setUuid(const QString &newUuid)
{
    if (Uuid == newUuid)
        return;
    Uuid = newUuid;
    emit UuidChanged();
}
