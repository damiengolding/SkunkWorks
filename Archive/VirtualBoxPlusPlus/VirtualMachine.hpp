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

#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

#include <QObject>

// TODO sort out the Q_PROPERTY stuff, it's messing with the Name and Uuid accessors/mutators for some reason
class VirtualMachine : public QObject
{
    Q_OBJECT
public:
    explicit VirtualMachine(QObject *parent = nullptr);

//    QString Uuid;
//    QString Name;

    QString getUuid() const;
    void setUuid(const QString &newUuid);

    QString getName() const;
    void setName(const QString &newName);

signals:

    void UuidChanged();
    void NameChanged();

private:
    QString Uuid;
    QString Name;

    Q_PROPERTY(QString Uuid READ getUuid WRITE setUuid NOTIFY UuidChanged)
    Q_PROPERTY(QString Name READ getName WRITE setName NOTIFY NameChanged)
};

#endif // VIRTUALMACHINE_HPP
