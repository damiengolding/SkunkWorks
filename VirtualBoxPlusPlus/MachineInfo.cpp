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

#include "MainWindow.hpp"
#include "MachineInfo.hpp"

MachineInfo::MachineInfo(QObject*parent)
    : QObject(parent)
{
    //    machineNameUuidHashTable = new QHash<QString, QString>();
    virtualBoxTreeModel = new QStandardItemModel();
}

MachineInfo::~MachineInfo(){}

QStandardItemModel* MachineInfo::parseFromShowVMInfoOutput(const QString & input)
{
    //    qDebug()<<"Starting MachineInfo::parseFromShowVMInfoOutput: " << input;
    if ( input.isNull() || input.isEmpty() ) {
        qDebug()<<"isNull || isEmpty: "<< input;
        return(new QStandardItemModel());
    }
    QString workingCopy = input;
    QString cfgFile;
    QStringList pairs = workingCopy.split("\r\n");
    for(auto line : pairs){
        if( line.toLower() .startsWith( "cfgfile" )){
            if(line.split('=').count() != 2)
                continue;
            cfgFile = line.split('=').at(1);
            cfgFile = cfgFile.replace("\\\\","\\");
            cfgFile = cfgFile.remove("\"");
        }
    }
    configFile = cfgFile;
    return(createStandardModel(configFile));
}

QStandardItemModel* MachineInfo::createStandardModel(const QString &xmlFile){
    //    qDebug()<<"Starting MachineInfo::createStandardModel(const QString &xmlFile): " << xmlFile;
    virtualBoxDescriptor = new QDomDocument ("virtual_machine_config");
    QFile xfile(xmlFile);
    if( !xfile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"XML File could not be opened for reading: " << xmlFile;
        return(new QStandardItemModel());
    }

    if(!virtualBoxDescriptor->setContent(xfile.readAll())) {
        //qDebug()<<"XML File could not be parsed: " << xmlFile;
        xfile.close();
        return(new QStandardItemModel());
    }
    return(createStandardModel(virtualBoxDescriptor));
}

QStandardItemModel *MachineInfo::createAllSnapshotsTreeModel(const QDomNode &node)
{
    //qDebug()<<"Starting MachineInfo::createAllSnapshotsTreeModel";
    QDomNodeList domNodeList = node.toElement().elementsByTagName("Snapshot");
    //qDebug()<<"Total number of snapshots: " << domNodeList.count();
    virtualBoxSnapshotsTreeModel = new QStandardItemModel();
    QStandardItem *root = virtualBoxSnapshotsTreeModel->invisibleRootItem();
    for( int i = 0; i < domNodeList.count(); ++i){
        root->appendRow(createSnapshotModel(domNodeList.at(i)));
    }
    emit virtualBoxSnapshotsTreeModelChanged();
    return(virtualBoxSnapshotsTreeModel);
}

QString MachineInfo::getConfigFile() const
{
    return configFile;
}

void MachineInfo::setConfigFile(const QString &newConfigFile)
{
    if (configFile == newConfigFile)
        return;
    configFile = newConfigFile;
    emit configFileChanged();
}

QStandardItemModel* MachineInfo::createStandardModel(QDomDocument *xml){
    //    qDebug()<<"Starting MachineInfo::createStandardModel(QDomDocument *xml)";
    QDomElement rootElement = xml->documentElement();
    QString testAttr1 = rootElement.attribute("xmlns","foo");
    QString testAttr2 = rootElement.attribute("version","bar");
    if( testAttr1.compare("http://www.virtualbox.org/") != 0 || testAttr2.compare("1.19-windows") != 0 ){
        qDebug()<<"Not a valid Virtual Machine descriptor";
        return(new QStandardItemModel());
    }

    QDomNodeList domNodeList = rootElement.elementsByTagName("Machine");
    //qDebug()<<"Number of Machine child nodes: " << domNodeList.count();
    QDomNode machineNode = domNodeList.at(0);
    Name = machineNode.toElement().attribute("name","foo");
    UUID = machineNode.toElement().attribute("uuid","bar");
    QString displayName = "Machine: " + Name + " - " + UUID;
    QStandardItem *root = virtualBoxTreeModel->invisibleRootItem();
    QStandardItem *machine = new QStandardItem("Machine");
    //QStandardItem *machine = new QStandardItem(displayName);
    root->appendRow(machine);

    // Machine details
    QStandardItem *name = new QStandardItem("Machine name: " + machineNode.toElement().attribute("name","Not found") );
    QStandardItem *uuid = new QStandardItem("Machine UUID: " + machineNode.toElement().attribute("uuid","Not found") );
    QStandardItem *osType = new QStandardItem("OS Type: "  + machineNode.toElement().attribute("OSType","Not found")  );
    QStandardItem *currentSnapshot = new QStandardItem("Running snapshot: " + machineNode.toElement().attribute("currentSnapshot","Not found") );
    QStandardItem *snapshotFolder = new QStandardItem("Snapshot folder: "  + machineNode.toElement().attribute("snapshotFolder","Not found") );
    QStandardItem *lastStateChange = new QStandardItem("Last state change: " + machineNode.toElement().attribute("lastStateChange","Not found") );
    QStandardItem *description;
    domNodeList = machineNode.toElement().elementsByTagName("Description");
    if( domNodeList.count() != 1){
        // qDebug()<<"No description";
        description = new QStandardItem("Description: Not found");
    }
    else{
        QString descriptionText = domNodeList.at(0).toElement().text();
        description = new QStandardItem("Description:");
        QStandardItem *descText = new QStandardItem(descriptionText);
        description->appendRow(descText);
    }

    machine->appendRow(name);
    machine->appendRow(uuid);
    machine->appendRow(osType);
    machine->appendRow(currentSnapshot);
    machine->appendRow(snapshotFolder);
    machine->appendRow(lastStateChange);
    machine->appendRow(description);

    // Sub-groups
    // Media-registry
    QStandardItem *mediaRegistry = new QStandardItem("Media registry");
    domNodeList = machineNode.toElement().elementsByTagName("HardDisk");
//    qDebug()<<"Hard disk count: " << domNodeList.count();

    for( int i = 0; i < domNodeList.length(); ++i){
        // uuid,format,location,type
        //QDomElement domElement = domNode.toElement();
        QDomElement domElement = domNodeList.at(i).toElement();
        QStandardItem *item = new QStandardItem("Hard drive");
        QStandardItem *uuid,*format,*location,*type;
        uuid = new QStandardItem("Uuid: " + domElement.attribute("uuid"));
        format = new QStandardItem("Format: " + domElement.attribute("format"));
        location = new QStandardItem("Location: " + domElement.attribute("location"));
        type = new QStandardItem("Type: " + domElement.attribute("type","N/A"));
        item->appendRow(uuid);
        item->appendRow(format);
        item->appendRow(type);
        item->appendRow(location);
        mediaRegistry->appendRow(item);
    }

    // Extra data
    QStandardItem *extraData = new QStandardItem("Extra data");
    QDomNode extraDataNode = machineNode.toElement().firstChildElement("ExtraData");
    domNodeList = extraDataNode.toElement().elementsByTagName("ExtraDataItem");
    for( int i = 0; i < domNodeList.count(); ++i){
        QDomNode extraDataNode = domNodeList.at(i);
        QStandardItem *item = new QStandardItem("Extra data " + QString::number(i));
        item->appendRow(new QStandardItem( "Name: "
                        + extraDataNode.toElement().attribute("name", "Not found"))
                        );
        item->appendRow(new QStandardItem( "Value: "
                        + extraDataNode.toElement().attribute("value", "Not found"))
                        );

        extraData->appendRow(item);
    }

    // Snapshot details
    QStandardItem *snapshotDetails = new QStandardItem("Running snapshot details");
    QDomNode snapNode = machineNode.toElement().firstChildElement("Snapshot");
    snapshotDetails->appendRow(createSnapshotModel(snapNode));

    // Hardware
    QDomNode hardwareNode = machineNode.toElement().firstChildElement("Hardware");
//    QStandardItem *hardware = new QStandardItem("Hardware");
    QStandardItem *hardware = MachineInfo::createHardwareModel(hardwareNode);

    // Groups
    QStandardItem *groups = new QStandardItem("Groups");
    QDomNode groupNode = machineNode.toElement().firstChildElement("Groups");
    domNodeList = groupNode.toElement().elementsByTagName("Group");
    for(int i =0; i < domNodeList.count();++i){
        QDomNode group = domNodeList.at(i);
        QStandardItem *item = new QStandardItem("Group " + QString::number(i));
        item->appendRow(new QStandardItem("Group name: "
                            + group.toElement().attribute("name","Not found")
                            ));
        groups->appendRow(item);
    }

    machine->appendRow(mediaRegistry);
    machine->appendRow(extraData);
    machine->appendRow(snapshotDetails);
    machine->appendRow(hardware);
    machine->appendRow(groups);
    //root = machine;
    emit virtualBoxTreeModelChanged(virtualBoxTreeModel);

    // Finally, create the full snapshots tree model
    createAllSnapshotsTreeModel(machineNode);
    return(virtualBoxTreeModel);
}

QStandardItem *MachineInfo::createSnapshotModel(const QDomNode &node)
{
    //qDebug()<<"Starting MachineInfo::createSnapshotModel(QDomNode node)";
    QStandardItem *snapshotItem;
    if(node.isNull()){
        qDebug()<<"No running shapshot found";
        return(new QStandardItem());
    }
    //    qDebug()<< "seem to have got this far";
    QDomNode workingNode = node;
    QDomElement workingElement = workingNode.toElement();
    QDomNodeList domNodeList;
    QString snName = workingElement.attribute("name","Anonymous");
    //    qDebug()<< "and seem to have got this far";
    snapshotItem = new QStandardItem("Snapshot: " +  workingElement.attribute("name","Name not found") );
    //    qDebug()<< "also seem to have got this far";
    snapshotItem->appendRow( new QStandardItem("Name: " + workingElement.attribute("name","Not found") ) );
    snapshotItem->appendRow( new QStandardItem("UUID: " + workingElement.attribute("uuid","Not found") ) );
    //    qDebug()<< "but probably not this far";

    // Hardware
    workingNode = workingElement.firstChildElement("Hardware");//  .elementsByTagName("Hardware");
    if( workingNode.isNull()){
                qDebug()<<"No hardware child element:" << domNodeList.count();
                return(snapshotItem);
    }
    QStandardItem *hardwareItem = createHardwareModel(workingNode);
    snapshotItem->appendRow(hardwareItem);
    return(snapshotItem);
}

QStandardItem *MachineInfo::createHardwareModel(const QDomNode &node)
{
    //qDebug()<<"Starting MachineInfo::createSnapshotModel(QDomNode node)";
    QStandardItem *hardwareItem = new QStandardItem("Hardware");
    if(node.isNull()){
        qDebug()<<"No running snapshot found";
        return(hardwareItem);
    }
    QDomNode workingNode = node;
    QDomElement workingElement = workingNode.toElement();
    QDomNodeList domNodeList;

    // Hardware
    if(node.isNull()){
                qDebug()<<"No hardware child element:" << domNodeList.count();
                return(hardwareItem);
    }
    workingNode = node;
    workingElement = workingNode.toElement();
    // Hardware child item declarations
    QStandardItem *cpu = new QStandardItem("CPU");
    cpu->appendRow(new QStandardItem("PAE enabled: "
                                     + workingElement.firstChildElement("CPU").firstChildElement("PAE").attribute("enabled","Not found")
                                     ));
    cpu->appendRow(new QStandardItem("Long mode enabled: "
                                     + workingElement.firstChildElement("CPU").firstChildElement("LongMode").attribute("enabled","Not found")
                                     ));

    QStandardItem *memory = new QStandardItem("Memory");
    memory->appendRow(new QStandardItem( "RAM: "
                                          + workingElement.firstChildElement("Memory").attribute("RAMSize","Not found")
                                         ));

    QStandardItem *hid = new QStandardItem("HID");
    hid->appendRow(new QStandardItem( "Pointing device: "
                                          + workingElement.firstChildElement("HID").attribute("Pointing","Not found")
                                         ));

    QStandardItem *display = new QStandardItem("Display");
    display->appendRow(new QStandardItem( "Controller: "
                                          + workingElement.firstChildElement("Display").attribute("controller","Not found")
                                         ));
    display->appendRow(new QStandardItem( "VRAM allocated: "
                                          + workingElement.firstChildElement("Display").attribute("VRAMSize","Not found")
                                         ));

    QStandardItem *bios = new QStandardItem("BIOS");
    bios->appendRow(new QStandardItem( "IOAPIC status: "
                                          + workingElement.firstChildElement("BIOS").firstChildElement("IOAPIC").attribute("enabled","Not found")
                                         ));

    QStandardItem *usb = new QStandardItem("USB");
    domNodeList = workingElement.firstChildElement("USB").firstChildElement("Controllers").elementsByTagName("Controller");
    /*QStandardItem *controller*/;
    for(int i = 0; i <domNodeList.count();++i){
        QStandardItem *controller = new QStandardItem("Controller");
        controller->appendRow(new QStandardItem("Name: "
                              + domNodeList.at(i).toElement().attribute("name","Not found")
                              ));
        controller->appendRow(new QStandardItem("Type: "
                              + domNodeList.at(i).toElement().attribute("type","Not found")
                              ));

        usb->appendRow(controller);
    }
    QStandardItem *network = new QStandardItem("Network");
    domNodeList = workingElement.firstChildElement("Network").elementsByTagName("Adapter");
    for( int i = 0; i < domNodeList.count(); ++i){
        QStandardItem *adapter = new QStandardItem("Adapter " + QString::number(i));
        adapter->appendRow(new QStandardItem("Slot: "
                                             + domNodeList.at(i).toElement().attribute("slot","Not found")
                                             ));
        adapter->appendRow(new QStandardItem("Enabled: "
                                             + domNodeList.at(i).toElement().attribute("enabled","Not found")
                                             ));
        adapter->appendRow(new QStandardItem("MAC Address: "
                                             + domNodeList.at(i).toElement().attribute("MACAddress","Not found")
                                             ));
        adapter->appendRow(new QStandardItem("Promiscuous mode policy: "
                                             + domNodeList.at(i).toElement().attribute("promiscuousModePolicy","Not found")
                                             ));
        adapter->appendRow(new QStandardItem("Type: "
                                             + domNodeList.at(i).toElement().attribute("type","Not found")
                                             ));

        QDomNode dmNode = domNodeList.at(i).firstChildElement("DisabledModes");
        QStandardItem *dmItem = new QStandardItem("Disabled modes");
        QStandardItem *natItem = new QStandardItem("NAT");
        natItem->appendRow(new QStandardItem("Local host reachable: "
                                             + dmNode.firstChildElement("NAT").attribute("localhost-reachable","Not found")
                                             ));
        QStandardItem *natNetworkItem = new QStandardItem("NAT Network");
        natNetworkItem->appendRow(new QStandardItem("Name: "
                                             + dmNode.firstChildElement("NATNetwork").attribute("name","Not found")
                                             ));
        QStandardItem *internalNetworkItem = new QStandardItem("Internal network");
        internalNetworkItem->appendRow(new QStandardItem("Name: "
                                             + dmNode.firstChildElement("InternalNetwork").attribute("name","Not found")
                                             ));
        dmItem->appendRow(natItem);
        dmItem->appendRow(natNetworkItem);
        dmItem->appendRow(internalNetworkItem);
        adapter->appendRow(dmItem);
        adapter->appendRow(new QStandardItem("Bridged interface: "
                                             + domNodeList.at(i).firstChildElement("BridgedInterface").attribute("name","Not found")
                                             ));

        network->appendRow(adapter);
    }

    QStandardItem *audioAdapter = new QStandardItem("Audio adapter");
    // codec,driver,enabled,enabledOut
    audioAdapter->appendRow(new QStandardItem("Codec: "
                                + workingElement.firstChildElement("AudioAdapter").attribute("codec","Not found")
                                ));
    audioAdapter->appendRow(new QStandardItem("Driver: "
                                + workingElement.firstChildElement("AudioAdapter").attribute("driver","Not found")
                                ));
    audioAdapter->appendRow(new QStandardItem("Enabled: "
                                + workingElement.firstChildElement("AudioAdapter").attribute("enabled","Not found")
                                ));
    audioAdapter->appendRow(new QStandardItem("Enabled out"
                                + workingElement.firstChildElement("AudioAdapter").attribute("enabledOut","Not found")
                                ));

    QStandardItem *rtc = new QStandardItem("Real Time Clock (RTC)");
    rtc->appendRow(new QStandardItem("Local or UTC: "
                       + workingElement.firstChildElement("RTC").attribute("localOrUtc","Not found")
                       ));


    QStandardItem *clipboard = new QStandardItem("Clipboard");
    clipboard->appendRow(new QStandardItem("Clipboard mode: "
                             + workingElement.firstChildElement("Clipboard").attribute("mode","Not found")
                             ));

    QStandardItem *sharedFolders = new QStandardItem("Shared folders");
    // name,hostPath,writable,autoMount
    domNodeList = workingElement.firstChildElement("SharedFolders").elementsByTagName("SharedFolder");
    for( int i = 0; i < domNodeList.count(); ++i ){
        QStandardItem *item = new QStandardItem("Shared folder " + QString::number(i));
        item->appendRow(new QStandardItem("Name: "
                            + domNodeList.at(i).toElement().attribute("name","Not found")
                            ));
        item->appendRow(new QStandardItem("Host path: "
                            + domNodeList.at(i).toElement().attribute("hostPath","Not found")
                            ));
        item->appendRow(new QStandardItem("Writable: "
                            + domNodeList.at(i).toElement().attribute("writable","Not found")
                            ));
        item->appendRow(new QStandardItem("Auto-mount: "
                            + domNodeList.at(i).toElement().attribute("autoMount","Not found")
                            ));

        sharedFolders->appendRow(item);
    }

    QStandardItem *guestProperties = new QStandardItem("Guest properties");
    // name,value,timestamp,flags
    domNodeList = workingElement.firstChildElement("GuestProperties").elementsByTagName("GuestProperty");
    for( int i = 0; i < domNodeList.count(); ++i ){
        QStandardItem *item = new QStandardItem("Guest property" + QString::number(i));
        item->appendRow(new QStandardItem("Name: "
                            + domNodeList.at(i).toElement().attribute("name","Not found")
                            ));
        item->appendRow(new QStandardItem("Value: "
                            + domNodeList.at(i).toElement().attribute("value","Not found")
                            ));
        item->appendRow(new QStandardItem("Timestamp: "
                            + domNodeList.at(i).toElement().attribute("timestamp","Not found")
                            ));
        item->appendRow(new QStandardItem("Flags: "
                            + domNodeList.at(i).toElement().attribute("flags","Not found")
                            ));

        guestProperties->appendRow(item);
    }

    QStandardItem *storageControllers = new QStandardItem("Storage controllers");
    // name,type,PortCount,useHostIOCache,Bootable
    domNodeList = workingElement.firstChildElement("StorageControllers").elementsByTagName("StorageController");
    for( int i = 0; i < domNodeList.count(); ++i ){
        QStandardItem *item = new QStandardItem("Storage controller" + QString::number(i));
        item->appendRow(new QStandardItem("Name: "
                            + domNodeList.at(i).toElement().attribute("name","Not found")
                            ));
        item->appendRow(new QStandardItem("Type: "
                            + domNodeList.at(i).toElement().attribute("type","Not found")
                            ));
        item->appendRow(new QStandardItem("Port count: "
                            + domNodeList.at(i).toElement().attribute("PortCount","Not found")
                            ));
        item->appendRow(new QStandardItem("Use host IO cache: "
                            + domNodeList.at(i).toElement().attribute("useHostIOCache","Not found")
                            ));
        item->appendRow(new QStandardItem("Bootable: "
                            + domNodeList.at(i).toElement().attribute("Bootable","Not found")
                            ));
        QStandardItem *attachedDevice = new QStandardItem("Attached device");
        //passthrough,type,port,hotpluggable,device
        attachedDevice->appendRow(new QStandardItem("Type: "
                                      + domNodeList.at(i).toElement().firstChildElement("AttachedDevice").attribute("type","Not found")
                                      ));
        attachedDevice->appendRow(new QStandardItem("Pass through: "
                                      + domNodeList.at(i).toElement().firstChildElement("AttachedDevice").attribute("passthrough","Not found")
                                      ));
        attachedDevice->appendRow(new QStandardItem("Port: "
                                      + domNodeList.at(i).toElement().firstChildElement("AttachedDevice").attribute("port","Not found")
                                      ));
        attachedDevice->appendRow(new QStandardItem("Hot pluggable: "
                                      + domNodeList.at(i).toElement().firstChildElement("AttachedDevice").attribute("hotpluggable","Not found")
                                      ));
        attachedDevice->appendRow(new QStandardItem("Device: "
                                      + domNodeList.at(i).toElement().firstChildElement("AttachedDevice").attribute("device","Not found")
                                      ));
        item->appendRow(attachedDevice);
        storageControllers->appendRow(item);
   }
    hardwareItem->appendRow(cpu);
    hardwareItem->appendRow(memory);
    hardwareItem->appendRow(hid);
    hardwareItem->appendRow(display);
    hardwareItem->appendRow(bios);
    hardwareItem->appendRow(usb);
    hardwareItem->appendRow(network);
    hardwareItem->appendRow(audioAdapter);
    hardwareItem->appendRow(rtc);
    hardwareItem->appendRow(sharedFolders);
    hardwareItem->appendRow(clipboard);
    hardwareItem->appendRow(guestProperties);
    hardwareItem->appendRow(storageControllers);
    return(hardwareItem);
}

QDomDocument *MachineInfo::getVirtualBoxDescriptor() const
{
    return virtualBoxDescriptor;
}

void MachineInfo::setVirtualBoxDescriptor(QDomDocument *newVirtualBoxDescriptor)
{
    if (virtualBoxDescriptor == newVirtualBoxDescriptor)
        return;
    virtualBoxDescriptor = newVirtualBoxDescriptor;
    emit virtualBoxDescriptorChanged();
}

QStandardItemModel *MachineInfo::getVirtualBoxTreeModel() const
{
    return virtualBoxTreeModel;
}

void MachineInfo::setVirtualBoxTreeModel(QStandardItemModel *newVirtualBoxTreeModel)
{
    if (virtualBoxTreeModel == newVirtualBoxTreeModel)
        return;
    virtualBoxTreeModel = newVirtualBoxTreeModel;
    emit virtualBoxTreeModelChanged(virtualBoxTreeModel);
}

QHash<QString, QString> MachineInfo::getNameValuePairs() const
{
    return nameValuePairs;
}

void MachineInfo::setNameValuePairs(const QHash<QString, QString> &newNameValuePairs)
{
    if (nameValuePairs == newNameValuePairs)
        return;
    nameValuePairs = newNameValuePairs;
    emit nameValuePairsChanged();
}

QStandardItemModel *MachineInfo::getVirtualBoxSnapshotsTreeModel() const
{
    return virtualBoxSnapshotsTreeModel;
}

void MachineInfo::setVirtualBoxSnapshotsTreeModel(QStandardItemModel *newVirtualBoxSnapshotsTreeModel)
{
    if (virtualBoxSnapshotsTreeModel == newVirtualBoxSnapshotsTreeModel)
        return;
    virtualBoxSnapshotsTreeModel = newVirtualBoxSnapshotsTreeModel;
    emit virtualBoxSnapshotsTreeModelChanged();
}

