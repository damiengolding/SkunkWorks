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
#include "ui_MainWindow.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>

void MainWindow::onRefreshConfiguredNetworksCalled(){
    QMutexLocker locker(&configuredNetworksMutex);
    QStandardItemModel *ret = new QStandardItemModel();
    QStandardItem *root = ret->invisibleRootItem();
    QStandardItem *networks = new QStandardItem("Configured networks");
    root->appendRow(networks);

    ui->applicationOutputTextEdit->append("Refreshing configured networks");
    QFileInfo fi(vboxmanageExe);
    if( !fi.exists() ){
        qDebug()<<"VBoxManage.exe not found at: " << fi.absoluteFilePath();
        return;
    }

    networks->appendRow(getNetworkList(1));
    networks->appendRow(getNetworkList(2));
    networks->appendRow(getNetworkList(3));
    networks->appendRow(getNetworkList(4));
    emit configuredNetworksRefreshed(ret);
}

void MainWindow::updateConfiguredNetworks(QStandardItemModel* model){
    ui->configuredNetworksTreeView->setModel(model);
}

QStandardItem* MainWindow::getNetworkList(int type){
    QStandardItem *ret;
    switch(type){
    case 1:{ // hostonlyifs
        ret = getStandardInterfaceList(1);
        break;
    }
    case 2:{ // bridgedifs
        ret = getStandardInterfaceList(2);
        break;
    }
    case 3:{ // natnets
        ret = getStandardInterfaceList(3);
        break;
    }
    case 4:{ // dhcpservers
        ret = getStandardInterfaceList(4);
        break;
    }
    default:
        return(new QStandardItem("Incorrect argument to network listing"));
    };

    return(ret);
}

QStandardItem* MainWindow::getStandardInterfaceList(int type){
    QStandardItem *ret;
    QString listType;
    switch(type){
    case 1: { // hostonlyifs
        ret = new QStandardItem("Host-only interfaces");
        listType = "hostonlyifs";
        break;
    }
    case 2:{ // bridgedifs
        ret = new QStandardItem("Bridged interfaces");
        listType = "bridgedifs";
        break;
    }
    case 3:{ // natnets
        ret = getNATNetsInterfaceList();
        return(ret);
    }
    case 4:{ // dhcpservers
        ret = getDHCPServerList();
        return(ret);
    }
    default:
        return(new QStandardItem("Incorrect argument to MainWindow::getStandardInterfaceList(int type): " + QString::number(type)));
    };

    QStringList args;
    args << "list" << listType;
    QProcess *proc = new QProcess();
    proc->start(vboxmanageExe,args);
    proc->waitForReadyRead();
    QString result = proc->readAllStandardOutput();
    if(result.length()==0){
        ui->applicationOutputTextEdit->append("No " + listType +  " interfaces found");
        return(new QStandardItem("No " + listType +  " interfaces found"));
    }

    // Parse the output into StandardInterfaceInfo instances
    QStringList lineSplit = result.split("\n");
    QList<StandardInterfaceInfo*> configuredNetworkList;
    StandardInterfaceInfo *info = new StandardInterfaceInfo();
    for(auto line : lineSplit){
        if( line == "\r"){
            configuredNetworkList.append(info);
            info = new StandardInterfaceInfo();
            continue;
        }
        line = line.remove(' ');
        if( line.toLower().startsWith("name") ){
            info->setName(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("guid") ){
            info->setGUID(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("dhcp") ){
            info->setDHCP(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("ipaddress") ){
            info->setIPAddress(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("networkmask") ){
            info->setNetworkMask(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("ipv6address") ){
            int start = line.indexOf(":") + 1;
            int chars = line.length() - start;
            info->setIPV6Address(line.sliced(start,chars) );
        }
        else if( line.toLower().startsWith("ipv6networkmask") ){
            info->setIPV6NetworkMaskPrefixLength(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("hardwareaddress") ){
            int start = line.indexOf(":") + 1;
            int chars = line.length() - start;
            info->setHardwareAddress(line.sliced(start,chars) );
        }
        else if( line.toLower().startsWith("mediumtype") ){
            info->setMediumType(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("wireless") ){
            info->setWireless(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("status") ){
            info->setStatus(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("vboxnetworkname") ){
            info->setVBoxNetworkName(line.split(':').at(1));
        }
        else{
            continue;
        }
    }
    for(auto info : configuredNetworkList){
        QStandardItem *item = new QStandardItem(info->getVBoxNetworkName());
        item->appendRow(new QStandardItem("Name: " + info->getName() ));
        item->appendRow(new QStandardItem("GUID: " + info->getGUID() ));
        item->appendRow(new QStandardItem("DHCP: " + info->getDHCP() ));
        item->appendRow(new QStandardItem("IP Address: " + info->getIPAddress() ));
        item->appendRow(new QStandardItem("Network mask: " + info->getNetworkMask() ));
        item->appendRow(new QStandardItem("IPV6 Address: " + info->getIPV6Address() ));
        item->appendRow(new QStandardItem("IPV6 Network mask prefix length: " + info->getIPV6NetworkMaskPrefixLength() ));
        item->appendRow(new QStandardItem("Hardware address: " + info->getHardwareAddress() ));
        item->appendRow(new QStandardItem("Medium type: " + info->getMediumType() ));
        item->appendRow(new QStandardItem("Wireless: " + info->getWireless() ));
        item->appendRow(new QStandardItem("Status: " + info->getStatus() ));
        ret->appendRow(item);
    }
    return(ret);
}

QStandardItem* MainWindow::getNATNetsInterfaceList(){
    QStandardItem *ret = new QStandardItem("NAT networks");
    QStringList args;
    args << "list" << "natnets";
    QProcess *proc = new QProcess();
    proc->start(vboxmanageExe,args);
    proc->waitForReadyRead();
    QString result = proc->readAllStandardOutput();
    if(result.length()==0){
        ui->applicationOutputTextEdit->append("No NAT networks found");
        return(new QStandardItem("No NAT networks found"));
    }

    // Parse the output into StandardInterfaceInfo instances
    QStringList lineSplit = result.split("\n");
    QList<NATNetworkInfo*> natNetworkList;
    NATNetworkInfo *info = new NATNetworkInfo();
    for(auto line : lineSplit){
        if( line == "\r"){
            natNetworkList.append(info);
            info = new NATNetworkInfo();
            continue;
        }
        line = line.remove(' ');
        if( line.toLower().startsWith("name") ){
            info->setName(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("network") ){
            info->setNetwork(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("gateway") ){
            info->setGateway(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("dhcp") ){
            info->setDhcpServer(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("ipv6:") ){
            info->setIpv6(line.split(':').at(1));
        }
        else if( line.toLower().startsWith( "ipv6prefix" )){
            int start = line.indexOf(":") + 1;
            int chars = line.length() - start;
            info->setIpv6Prefix(line.sliced(start,chars) );
        }
        else if( line.toLower().startsWith( "ipv6default") ) {
            info->setIpv6Default(line.split(':').at(1));
        }
        else{
            continue;
        }
    }
    for(auto info : natNetworkList){
        QStandardItem *item = new QStandardItem(info->getName());
        item->appendRow(new QStandardItem("Network: " + info->getNetwork() ));
        item->appendRow(new QStandardItem("Gateway: " + info->getGateway()) );
        item->appendRow(new QStandardItem("DHCP Server: " + info->getDhcpServer() ));
        item->appendRow(new QStandardItem("IPV6: " + info->getIpv6() ));
        item->appendRow(new QStandardItem("IPV6 Prefix: " + info->getIpv6Prefix() ));
        item->appendRow(new QStandardItem("IPV6 Default: " + info->getIpv6Default()));
        ret->appendRow(item);
    }
    return(ret);
}

QStandardItem* MainWindow::getDHCPServerList(){
    QStandardItem *ret = new QStandardItem("DHCP Servers");
    QStringList args;
    args << "list" << "dhcpservers";
    QProcess *proc = new QProcess();
    proc->start(vboxmanageExe,args);
    proc->waitForReadyRead();
    QString result = proc->readAllStandardOutput();
    if(result.length()==0){
        ui->applicationOutputTextEdit->append("No DHCP servers found");
        return(new QStandardItem("NoDHCP servers found"));
    }

    // Parse the output into StandardInterfaceInfo instances
    QStringList lineSplit = result.split("\n");
    QList<DHCPServerInfo*> dhcpServerList;
    DHCPServerInfo *info = new DHCPServerInfo();
    for(auto line : lineSplit){
        line = line.remove(' ');
        if( line == "\r" || line.isEmpty()){
            dhcpServerList.append(info);
            info = new DHCPServerInfo();
            continue;
        }
        if( line.toLower().startsWith("networkname") ){
            info->setNetworkName(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("dhcpdip") ){
            info->setDhcpdIP(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("lowerip") ){
            info->setLowerIPAddress(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("upperip") ){
            info->setUpperIPAddress(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("networkmask") ){
            info->setNetworkMask(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("enabled") ){
            info->setEnabled(line.split(':').at(1));
        }
        // This item is a dummy, it's the parent  the next 6 items
        else if( line.toLower().startsWith("global") ){
            info->setGlobalConfiguration("global");
        }
        else if( line.toLower().startsWith("minlease") ){
            info->setMinLeaseTime(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("maxlease") ){
            info->setMaxLeaseTime(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("forced") ){
            info->setForcedOptions(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("suppressed") ){
            info->setSuppressedOptions(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("1/legacy") ){
            info->setOneLegacy(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("groups") ){
            info->setGroups(line.split(':').at(1));
        }
        else if( line.toLower().startsWith("individual") ){
            info->setIndividualConfigs(line.split(':').at(1));
        }
        else{
            continue;
        }
    }
    for(auto info : dhcpServerList){
        QStandardItem *item = new QStandardItem(info->getNetworkName());
        QStandardItem *global = new QStandardItem("Global configuration");
        item->appendRow(new QStandardItem("DHCPd IP: " + info->getDhcpdIP() ));
        item->appendRow(new QStandardItem("Lower IP Address: " + info->getLowerIPAddress() ));
        item->appendRow(new QStandardItem("Upper IP Address: " + info->getUpperIPAddress() ));
        item->appendRow(new QStandardItem("Network mask: " + info->getNetworkMask() ));
        item->appendRow(new QStandardItem("Enabled: " + info->getEnabled()));
        item->appendRow(new QStandardItem("Groups: " + info->getGroups() ));
        item->appendRow(new QStandardItem("Individual configs: " + info->getIndividualConfigs()) );

        global->appendRow(new QStandardItem("Minimum lease time: " + info->getMinLeaseTime() ));
        global->appendRow(new QStandardItem("Default lease time: " + info->getDefaultLeaseTime() ));
        global->appendRow(new QStandardItem("Maximum lease time: " + info->getMaxLeaseTime() ));
        global->appendRow(new QStandardItem("Forced option: " + info->getForcedOptions()));
        global->appendRow(new QStandardItem("Suppressed options: " + info->getSuppressedOptions() ));
        global->appendRow(new QStandardItem("1/legacy: " + info->getOneLegacy() ));

        item->appendRow(global);
        ret->appendRow(item);
    }

    return(ret);
}
