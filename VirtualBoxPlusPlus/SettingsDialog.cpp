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

#include "SettingsDialog.hpp"
#include "ui_SettingsDialog.h"

#include <QMessageBox>
#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    settings = new QSettings(qApp->organizationName(),qApp->applicationName());
    setUpData();
    setUpConnections();
    setUpTables();
}

void SettingsDialog::setUpData(){
    vboxmanageExe = settings->value("vboxmanageExe","C:\\Program Files\\Oracle\\VirtualBox\\VBoxManage.exe").toString();
    ui->vboxmanageLineEdit->setText(vboxmanageExe);
    homeDirectory = settings->value("homeDirectory",QDir::home().absolutePath()).toString();
    ui->homeLineEdit->setText(homeDirectory.absolutePath());
    playlistDirectory = settings->value("playlistDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Playlists").toString();
    ui->playlistLlineEdit->setText(playlistDirectory.absolutePath());
    pluginDirectory = settings->value("pluginDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Plugins").toString();
    ui->pluginLineEdit->setText(pluginDirectory.absolutePath());

    //Directories and VBoxManage
    ui->commandLineEdit->setText(commandDirectory.absolutePath());
    commandDirectory = settings->value("commandDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Commands").toString();
    ui->commandLineEdit->setText(commandDirectory.absolutePath());

    QString apld = settings->value("additionalPlaylistDirectories").toString();
    if(!apld.isEmpty()){
        // Clear the table first
        ui->playlistDirsTableWidget->clearContents();
        ui->playlistDirsTableWidget->setRowCount(0);
        int rc = ui->playlistDirsTableWidget->rowCount();
        for (int i = rc - 1; i > 0; --i) {
            ui->playlistDirsTableWidget->removeRow(i);
        }
        // Then re-populate it
        QStringList apldList = apld.split(';');
        int row = 0;
        for(QString d : apldList){
            if(additionalPlaylistDirectories.indexOf(d) == -1){
                additionalPlaylistDirectories.append(d);
            }
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(d);
            ui->playlistDirsTableWidget->insertRow(row);
            ui->playlistDirsTableWidget->setItem(row,0,item);
            ++row;
        }
    }

    apld = settings->value("additionalPluginDirectories").toString();
    if( !apld.isEmpty()){
        // Clear the table first
        ui->pluginDirsTableWidget->clearContents();
        ui->pluginDirsTableWidget->setRowCount(0);
        int rc = ui->pluginDirsTableWidget->rowCount();
        for (int i = rc - 1; i > 0; --i) {
            ui->pluginDirsTableWidget->removeRow(i);
        }
        // Then re-populate it
        QStringList apldList = apld.split(';');
        int row = 0;
        for(QString d : apldList){
            if(additionalPluginDirectories.indexOf(d) == -1){
                additionalPluginDirectories.append(d);
            }
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(d);
            ui->pluginDirsTableWidget->insertRow(row);
            ui->pluginDirsTableWidget->setItem(row,0,item);
            ++row;
        }
    }

    // Metrics
    startMetricsOnOpen = settings->value("startMetricsOnOpen","true").toString().toLower() == "true" ? true : false;
    ui->metricsFromStartupRadioButton->setChecked(startMetricsOnOpen);

    sampleInterval = settings->value("sampleInterval","2").toInt();
    ui->sampleIntervalSpinBox->setValue(sampleInterval);

    sampleCount = settings->value("sampleCount","1800").toInt();
    ui->sampleCountSpinBox->setValue(sampleCount);
}

void SettingsDialog::saveData(){
    settings->setValue("vboxmanageExe",ui->vboxmanageLineEdit->text());
    settings->setValue("homeDirectory",ui->homeLineEdit->text());
    settings->setValue("playlistDirectory",ui->playlistLlineEdit->text());
    settings->setValue("pluginDirectory",ui->pluginLineEdit->text());
    //Directories and VBoxManage
    settings->setValue("commandDirectory",ui->commandLineEdit->text());
    settings->setValue("additionalPlaylistDirectories",additionalPlaylistDirectories.join(';'));
    settings->setValue("additionalPluginDirectories",additionalPluginDirectories.join(';'));
    // Metrics
    settings->setValue("startMetricsOnOpen",ui->metricsFromStartupRadioButton->isChecked());
    settings->setValue("sampleInterval",ui->sampleIntervalSpinBox->value());
    settings->setValue("sampleCount",ui->sampleCountSpinBox->value());
}

void SettingsDialog::setUpConnections()
{
    connect(ui->vboxmanageLineEdit,SIGNAL(textChanged(const QString)),this,SLOT(onVBoxManageExeChanged(const QString)));
    connect(ui->homeLineEdit,SIGNAL(textChanged(const QString)),this,SLOT(onHomeDirectoryChanged(const QString)));
    connect(ui->playlistLlineEdit,SIGNAL(textChanged(const QString)),this,SLOT(onPlaylistDirectoryChanged(const QString)));
    connect(ui->pluginLineEdit,SIGNAL(textChanged(const QString)),this,SLOT(onPluginDirectoryChanged(const QString)));
    connect(ui->homePushButton,SIGNAL(clicked()),this,SLOT(onHomePushButton()));
    connect(ui->playlistPushButton,SIGNAL(clicked()),this,SLOT(onPlaylistPushButton()));
    connect(ui->vboxmanagePushButton,SIGNAL(clicked()),this,SLOT(onVBoxManagePushButton()));
    connect(ui->pluginPushButton,SIGNAL(clicked()),this,SLOT(onPluginPushButton()));

    connect(ui->metricsFromStartupRadioButton,SIGNAL(toggled(bool) ), this,SLOT(onMetricsFromStartupRadioButtonChanged(bool)));
    connect(ui->sampleIntervalSpinBox,SIGNAL( valueChanged(int) ), this,SLOT(onSampleIntervalSpinBoxChanged(int)));
    connect(ui->sampleCountSpinBox,SIGNAL( valueChanged(int) ), this,SLOT(onSampleCountSpinBoxChanged(int)));

    connect(ui->pluginDirsTableWidget,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(onCCMRAddPluginsDirectoryCalled(const QPoint&)));
    connect(ui->playlistDirsTableWidget,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(onCCMRAddPlaylistsDirectoryCalled(const QPoint&)));

    connect(ui->additionalDirectoriesTabWidget,SIGNAL(tabBarDoubleClicked(int)),this,SLOT(onTabBarDoubleClicked(int)));
}

void SettingsDialog::onTabBarDoubleClicked(int i ){
    doCCMRMenu(i);
}

void SettingsDialog::onCCMRAddPluginsDirectoryCalled(const QPoint &point){
    doCCMRMenu(0);
}

void SettingsDialog::onCCMRAddPlaylistsDirectoryCalled(const QPoint& point){
    doCCMRMenu(1);
}

// REFACT Bring QMenu* cm = new QMenu();cm->addAction("Add"); before the if/else switch?
void SettingsDialog::doCCMRMenu(int i){
    //QMessageBox::information(this,"Virtual Box++","Menu request for: " + QString::number(i));
    if(i == 0){ // Plugins directories
        QList<QTableWidgetItem*> items = ui->pluginDirsTableWidget->selectedItems();
        if(items.empty()){
            QMenu* cm = new QMenu();
            cm->addAction("Add");
            QAction* selectedAction = cm->exec(QCursor::pos());
            if (!selectedAction) {
                return;
            }
            QString actStr = selectedAction->text();
            if(actStr.toLower() == "add"){
                //QMessageBox::information(this,"Virtual Box++","Clicked add");
                QString ret = QFileDialog::getExistingDirectory(this,"Virtual Box++",pluginDirectory.absolutePath());
                if(ret != nullptr){
                    onPluginDirectoriesChanged(ret,true);
                }
            }
        }
        else{
            QTableWidgetItem* item = items.at(0);
            if(item==nullptr)return;
            QMenu* cm = new QMenu();
            cm->addAction("Add");
            if(items.count()>=1){
                cm->addAction("Remove");
            }
            QAction* selectedAction = cm->exec(QCursor::pos());
            if (!selectedAction) {
                return;
            }
            QString actStr = selectedAction->text();
            if(actStr.toLower() == "add"){
                //QMessageBox::information(this,"Virtual Box++","Clicked add");
                QString ret = QFileDialog::getExistingDirectory(this,"Virtual Box++",pluginDirectory.absolutePath());
                if(ret != nullptr){
                    onPluginDirectoriesChanged(ret,true);
                }
            }
            else if(actStr.toLower() == "remove"){
                //QMessageBox::information(this,"Virtual Box++","Clicked remove" + item->text());
                onPluginDirectoriesChanged(item->text(),false);
            }
        }
    }
    else if(i==1){ // Playlists  directories
        QList<QTableWidgetItem*> items = ui->playlistDirsTableWidget->selectedItems();
        if(items.empty()){
            QMenu* cm = new QMenu();
            cm->addAction("Add");
            QAction* selectedAction = cm->exec(QCursor::pos());
            if (!selectedAction) {
                return;
            }
            QString actStr = selectedAction->text();
            if(actStr.toLower() == "add"){
                //QMessageBox::information(this,"Virtual Box++","Clicked add");
                QString ret = QFileDialog::getExistingDirectory(this,"Virtual Box++",playlistDirectory.absolutePath());
                if(ret != nullptr){
                    onPlaylistDirectoriesChanged(ret,true);
                }
            }
        }
        else{
            QTableWidgetItem* item = items.at(0);
            if(item==nullptr)return;
            QMenu* cm = new QMenu();
            cm->addAction("Add");
            if(items.count()>=1){
                cm->addAction("Remove");
            }
            QAction* selectedAction = cm->exec(QCursor::pos());
            if (!selectedAction) {
                return;
            }
            QString actStr = selectedAction->text();
            if(actStr.toLower() == "add"){
                //QMessageBox::information(this,"Virtual Box++","Clicked add");
                QString ret = QFileDialog::getExistingDirectory(this,"Virtual Box++",playlistDirectory.absolutePath());
                if(ret != nullptr){
                    onPlaylistDirectoriesChanged(ret,true);
                }
            }
            else if(actStr.toLower() == "remove"){
                //QMessageBox::information(this,"Virtual Box++","Clicked remove" + item->text());
                onPlaylistDirectoriesChanged(item->text(),false);
            }
        }
    }
    saveData();
    setUpData();
}

// TODO Implement check for duplicate
void SettingsDialog::onPluginDirectoriesChanged(const QString &dir,bool added){
    if(added){
        qDebug()<<"Should be adding plugin directory: " <<dir;
        if(additionalPluginDirectories.indexOf(dir) == -1){
            additionalPluginDirectories.append(dir);
        }
    }
    else{
        QList<QTableWidgetItem*> items = ui->pluginDirsTableWidget->selectedItems();
        int rowToRemove = items.at(0)->row();
        if(items.count() !=1){
            qDebug()<<"No plugin directory item selected " <<dir;
            return;
        }
        additionalPluginDirectories.remove(additionalPluginDirectories.indexOf(dir));
        ui->pluginDirsTableWidget->removeRow(rowToRemove);
    }
    settings->setValue("additionalPluginDirectories",additionalPluginDirectories.join(';'));
    saveData();
    setUpData();
}
// TODO Implement check for duplicate
void SettingsDialog::onPlaylistDirectoriesChanged(const QString &dir,bool added){
    if(added){
        qDebug()<<"Should be adding playlist directory: " <<dir;
        if(additionalPlaylistDirectories.indexOf(dir) == -1){
            additionalPlaylistDirectories.append(dir);
        }
    }
    else{
        QList<QTableWidgetItem*> items = ui->playlistDirsTableWidget->selectedItems();
        int rowToRemove = items.at(0)->row();
        if(items.count() !=1){
            qDebug()<<"No plugin directory item selected " <<dir;
            return;
        }
        additionalPlaylistDirectories.remove(additionalPlaylistDirectories.indexOf(dir));
        ui->pluginDirsTableWidget->removeRow(rowToRemove);
    }
    settings->setValue("additionalPlaylistDirectories",additionalPlaylistDirectories.join(';'));
    saveData();
    setUpData();
}

void SettingsDialog::onMetricsFromStartupRadioButtonChanged(bool checked){
    if(checked){
        startMetricsOnOpen = true;
    }
    else{
        startMetricsOnOpen = false;
    }
}

void SettingsDialog::onSampleIntervalSpinBoxChanged(int value){
    sampleInterval = value;
}

void SettingsDialog::onSampleCountSpinBoxChanged(int value){
    sampleCount = value;
}

void SettingsDialog::setUpTables(){
    QStringList headerTitles;// = new QStringList();
    headerTitles <<"Directory";
    ui->playlistDirsTableWidget->setHorizontalHeaderLabels(headerTitles);
    ui->pluginDirsTableWidget->setHorizontalHeaderLabels(headerTitles);
}

void SettingsDialog::onVBoxManageExeChanged(const QString &text){
    //QMessageBox::information(this,dialogTitle,text);
    vboxmanageExe = text;
}

void SettingsDialog::onHomeDirectoryChanged(const QString &text){
    //QMessageBox::information(this,dialogTitle,text);
    homeDirectory = text;
}

void SettingsDialog::onPlaylistDirectoryChanged(const QString &text){
    //QMessageBox::information(this,dialogTitle,text);
    playlistDirectory = text;
}

void SettingsDialog::onPluginDirectoryChanged(const QString &text){
    //QMessageBox::information(this,dialogTitle,text);
    pluginDirectory = text;
}

void SettingsDialog::onVBoxManagePushButton(){
    QString ret = QFileDialog::getOpenFileName(this,"Virtual Box++ - set the location for VBoxManage.exe",QDir::homePath(),"VBoxManage.exe (VBoxManage.exe)");
    if(ret != nullptr){
        vboxmanageExe = ret;
        ui->vboxmanageLineEdit->setText(ret);
    }
}

void SettingsDialog::onHomePushButton(){
    QString ret = QFileDialog::getExistingDirectory(this,"Virtual Box++ - set the location for your home directory",homeDirectory.absolutePath());
    if(ret != nullptr){
        homeDirectory = ret;
        ui->homeLineEdit->setText(ret);
    }
}

void SettingsDialog::onPlaylistPushButton(){
    QString ret = QFileDialog::getExistingDirectory(this,"Virtual Box++ - set the location for your playlist directory",playlistDirectory.absolutePath());
    if(ret != nullptr){
        playlistDirectory = ret;
        ui->playlistLlineEdit->setText(ret);
    }
}

void SettingsDialog::onPluginPushButton(){
    QString ret = QFileDialog::getExistingDirectory(this,"Virtual Box++ - set the location for your default plugin directory",pluginDirectory.absolutePath());
    if(ret != nullptr){
        pluginDirectory = ret;
        ui->pluginLineEdit->setText(ret);
    }
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
