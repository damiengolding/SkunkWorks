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

#pragma once

#include <QObject>
#include <compare>
#include <QFileInfo>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>

#include <QStandardItemModel>
#include <QStandardItem>

class MachineInfo  : public QObject
{
	Q_OBJECT
public:
	MachineInfo(QObject *parent = nullptr );
	~MachineInfo();

    QString UUID;
	QString Name;
    auto operator <=>(const MachineInfo&) const = default;

    QStandardItemModel *parseFromShowVMInfoOutput(const QString& input);
    QHash<QString, QString> getNameValuePairs() const;
    void setNameValuePairs(const QHash<QString, QString> &newNameValuePairs);

    QStandardItemModel *getVirtualBoxTreeModel() const;
    void setVirtualBoxTreeModel(QStandardItemModel *newVirtualBoxTreeModel);

    QDomDocument *getVirtualBoxDescriptor() const;
    void setVirtualBoxDescriptor(QDomDocument *newVirtualBoxDescriptor);

    QString getConfigFile() const;
    void setConfigFile(const QString &newConfigFile);

signals:
    void treeModelChanged( const QStandardItemModel &treeModel);
    void configFileChanged();
    void nameValuePairsChanged();
    void virtualBoxDescriptorChanged();
    void virtualBoxTreeModelChanged(QStandardItemModel *newModel);

    void virtualBoxSnapshotsTreeModelChanged();

public slots:
    QStandardItemModel* createStandardModel(QDomDocument *xml);
    QStandardItemModel* createStandardModel(const QString &xmlFile);

private: // Fields
    QHash<QString,QString> nameValuePairs;
    QString configFile;
    QStandardItemModel* virtualBoxTreeModel;
    QStandardItemModel* virtualBoxSnapshotsTreeModel;
    QDomDocument *virtualBoxDescriptor;

private:
    QStandardItemModel* createAllSnapshotsTreeModel(const QDomNode &node);

    Q_PROPERTY(QStandardItemModel *virtualBoxSnapshotsTreeModel READ getVirtualBoxSnapshotsTreeModel WRITE setVirtualBoxSnapshotsTreeModel NOTIFY virtualBoxSnapshotsTreeModelChanged)

public:
    static QStandardItem* createSnapshotModel(const QDomNode &node);
    static QStandardItem* createHardwareModel(const QDomNode &node);
    Q_PROPERTY(QString configFile READ getConfigFile WRITE setConfigFile NOTIFY configFileChanged)
    Q_PROPERTY(QHash<QString, QString> nameValuePairs READ getNameValuePairs WRITE setNameValuePairs NOTIFY nameValuePairsChanged)
    Q_PROPERTY(QStandardItemModel *virtualBoxTreeModel READ getVirtualBoxTreeModel WRITE setVirtualBoxTreeModel NOTIFY virtualBoxTreeModelChanged)
    Q_PROPERTY(QDomDocument *virtualBoxDescriptor READ getVirtualBoxDescriptor WRITE setVirtualBoxDescriptor NOTIFY virtualBoxDescriptorChanged)

    QStandardItemModel *getVirtualBoxSnapshotsTreeModel() const;
    void setVirtualBoxSnapshotsTreeModel(QStandardItemModel *newVirtualBoxSnapshotsTreeModel);
};
