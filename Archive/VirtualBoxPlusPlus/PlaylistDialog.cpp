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

  Don't use it to find and eat babies ... unless you're really REALLY hungry

*/

#include "PlaylistDialog.hpp"
#include "ui_PlaylistDialog.h"

PlaylistDialog::PlaylistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlaylistDialog)
{
    ui->setupUi(this);
    setupDialog();
}

PlaylistDialog::~PlaylistDialog()
{
    delete ui;
}

void PlaylistDialog::setupDialog(){
    lexer = new QsciLexerJSON();
    ui->scriptEditor->setLexer(lexer);
    ui->machineListTableWidget->setHorizontalHeaderLabels(QStringList()<<"Name"<<"UUID"<<"Run policy"<<"Run order" << "Run mode");

    connect( ui->machineListTableWidget,
             SIGNAL(customContextMenuRequested(const QPoint&)),
             this,
             SLOT(onCCMRMachineListTableWidgetCalled(const QPoint&))
             );

    connect(ui->newPushButton,
            SIGNAL(clicked()),
            this,
            SLOT(onNewButtonClicked())
            );

    connect(ui->openPushButton,
            SIGNAL(clicked()),
            this,
            SLOT(onOpenButtonClicked())
            );
    connect(ui->savePushButton,
            SIGNAL(clicked()),
            this,
            SLOT(onSaveButtonClicked())
            );
    connect(ui->saveAsPushButton,
            SIGNAL(clicked()),
            this,
            SLOT(onSaveAsButtonClicked())
            );

    connect(
                ui->machineListTableWidget,
                SIGNAL(itemChanged(QTableWidgetItem*)),
                this,
                SLOT(onItemContentsChanged(QTableWidgetItem*))
                );

    connect(ui->machineListTableWidget,
            SIGNAL(cellDoubleClicked(int, int)),
            this,
            SLOT(onCellDoubleClicked(int,int))
            );

    connect(ui->machineListTableWidget,
            SIGNAL(cellChanged(int, int)),
            this,
            SLOT(onCellChanged(int,int))
            );

    connect(this,
            SIGNAL(playlistDefinitionChanged()),
            this,
            SLOT(onPlaylistDefinitionChanged())
        );
}

void PlaylistDialog::loadPlaylistFile(const QFileInfo &file)
{
    loading=true;
    QFile testFile(file.absoluteFilePath());
    if(!testFile.exists()){
        qDebug()<<"File " << file.absoluteFilePath() << " doesn't exist";
        return;
    }
    //ui->mainTabWidget->setCurrentIndex(1);
    setCurrentFile(file);
    QFile inputFile(currentFile.absoluteFilePath());
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(this,"Virtual Box++","Unable to read: " + currentFile.absoluteFilePath());
        return;
    }
    QJsonParseError jPerr;
    QString scriptContents = inputFile.readAll();
    ui->scriptEditor->setText(scriptContents.trimmed());
    //qDebug()<<"JSON to latin1: " << scriptContents.toLatin1();
    QJsonDocument jDoc = QJsonDocument::fromJson(scriptContents.toLatin1(),&jPerr);
    if(jDoc.isNull()){
        qDebug()<< "jDoc is null: " << jPerr.errorString();
        return;
    }
    ui->scriptLocationLineEdit->setText(currentFile.absoluteFilePath());
    ui->scriptLocationLineEdit->setCursorPosition(0);
    QJsonObject jObj = jDoc.object();
    if(jObj.contains("name") && jObj["name"].isString())
        ui->displayNameLineEdit->setText(jObj["name"].toString());

    //setupTable(jObj);
    showPlaylist(file.absoluteFilePath());
    ui->savePushButton->setEnabled(true);
    ui->saveAsPushButton->setEnabled(true);
}

// TODO fix this so changes in the table widget are reflected in the display and the underlying file - this will probably need refactoring to a QTalbleView
void PlaylistDialog::onPlaylistDefinitionChanged()
{
//    QFile outputFile(currentFile.absoluteFilePath());
//    if( !outputFile.open(QIODevice::WriteOnly | QIODevice::Text)){
//         qDebug()<<"Could not open file: " <<  currentFile.absoluteFilePath()  << " for writing";
//         return;
//    }
//    QJsonObject jObj;
//    playlistDefinition->Write(jObj);
//    QJsonDocument jDoc(jObj);
//    outputFile.write(jDoc.toJson());
//    outputFile.close();
//    loadPlaylistFile(currentFile);
}

PlaylistDefinition *PlaylistDialog::getPlaylistDefinition() const
{
    return playlistDefinition;
}

void PlaylistDialog::setPlaylistDefinition(PlaylistDefinition *newPlaylistDefinition)
{
    if (playlistDefinition == newPlaylistDefinition)
        return;
    playlistDefinition = newPlaylistDefinition;
    emit playlistDefinitionChanged();
}

void PlaylistDialog::onCCMRMachineListTableWidgetCalled(const QPoint &point)
{
    //QMessageBox::information(this,"Virtual Box++","Right click");
    QList<QTableWidgetItem*> items = ui->machineListTableWidget->selectedItems();
    QMenu* cm = new QMenu();
    cm->addAction("Add");
    QString actStr;
    QAction* selectedAction;
    if(items.empty()){
        selectedAction = cm->exec(QCursor::pos());
        if(!selectedAction)
            return;
        actStr = selectedAction->text();
    }
    else{
        cm->addAction("Remove");
        selectedAction = cm->exec(QCursor::pos());
        if(!selectedAction)
            return;
        actStr = selectedAction->text();
    }

    //actStr =
}

void PlaylistDialog::onItemContentsChanged(QTableWidgetItem *item)
{
    if( item->column() == 0 || item->column() == 1 )
        return;
    if( loading ){
        return;
    }
    else{
        QMessageBox::information(this,"Virtual Box++","PlaylistDialog::onItemContentsChanged");
    }
}

void PlaylistDialog::onCellDoubleClicked(int a, int b)
{
    loading = false;
}

void PlaylistDialog::onNewButtonClicked()
{
    CreatePlaylistWizard *cpw = new CreatePlaylistWizard(availableMachineList,playlistsDirectory);
    cpw->exec();
    //QMessageBox::information(this,"Virtual Box++","New clicked:\n" + PlaylistsDirectory.absolutePath());
}

void PlaylistDialog::onOpenButtonClicked()
{
    //QMessageBox::information(this,"Virtual Box++","Open clicked:\n" + playlistsDirectory.absolutePath());
    QString fileName = QFileDialog::getOpenFileName(this,"Virtual Box++",playlistsDirectory.absolutePath(),"Virtual Box++ PLaylists (*.vbpl)");
    if( fileName.isNull() )
        return;

    showPlaylist(fileName);
}

void PlaylistDialog::onSaveButtonClicked()
{
    QMessageBox::information(this,"Virtual Box++","Save clicked");
}

void PlaylistDialog::onSaveAsButtonClicked()
{
    QMessageBox::information(this,"Virtual Box++","Save as clicked");
}

void PlaylistDialog::showPlaylist(const QString &file)
{
    QFile inputFile(file);
    if( !inputFile.exists()){
        QMessageBox::warning(this,"Virtual Box++","Unable to find playlist file: " + file);
        return;
    }
    if( !inputFile.open(QIODevice::ReadOnly| QIODevice::Text)){
        QMessageBox::warning(this,"Virtual Box++","Unable to open playlist file: " + file) + " for reading)";
        return;
    }
    QString jsonString = inputFile.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLatin1());
    QJsonObject jsonObject = jsonDocument.object();
    playlistDefinition = new PlaylistDefinition();
    playlistDefinition->Read(jsonObject);
    /*
     displayNameLineEdit
     scriptLocationLineEdit
     <<"Name"<<"UUID"<<"Run policy"<<"Run order" << "Run mode");
     */
    ui->displayNameLineEdit->setText(playlistDefinition->getName());
    ui->scriptLocationLineEdit->setText(file);
    // Clear the machines table first
    MainWindow::clearTableWidget(ui->machineListTableWidget);
    // Then re-populate it
    int row = 0;
    for(auto playlistItem : playlistDefinition->playlistItems){
        QTableWidgetItem* item0 = new QTableWidgetItem();
        item0->setFlags(item0->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem* item1 = new QTableWidgetItem();
        item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem* item2 = new QTableWidgetItem();
        item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem* item3 = new QTableWidgetItem();
        item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem* item4 = new QTableWidgetItem();
        item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
        item0->setText(playlistItem->getName());
        item1->setText(playlistItem->getUUID());
        item2->setText(QString::number(playlistItem->getPolicy()));
        item3->setText(QString::number(playlistItem->getOrder()));
        item4->setText(QString::number(playlistItem->getMode()));
        ui->machineListTableWidget->insertRow(row);
        ui->machineListTableWidget->setItem(row,0,item0);
        ui->machineListTableWidget->setItem(row,1,item1);
        ui->machineListTableWidget->setItem(row,2,item2);
        ui->machineListTableWidget->setItem(row,3,item3);
        ui->machineListTableWidget->setItem(row,4,item4);
        row++;
    }

    ui->scriptEditor->setText(jsonDocument.toJson());
}

QFileInfo PlaylistDialog::getCurrentFile() const
{
    return currentFile;
}

void PlaylistDialog::setCurrentFile(const QFileInfo &newCurrentFile)
{
    if (currentFile == newCurrentFile)
        return;
    currentFile = newCurrentFile;
    loadPlaylistFile(currentFile);
    //QMessageBox::information(this,"Virtual Box++","New current file: " + CurrentFile.absoluteFilePath());
    emit CurrentFileChanged();
}

QDir PlaylistDialog::getPlaylistsDirectory() const
{
    return playlistsDirectory;
}

void PlaylistDialog::setPlaylistsDirectory(const QDir &newPlaylistsDirectory)
{
    if (playlistsDirectory == newPlaylistsDirectory)
        return;
    playlistsDirectory = newPlaylistsDirectory;
    emit PlaylistsDirectoryChanged();
}

QList<VirtualMachine *> PlaylistDialog::getAvailableMachineList() const
{
    return availableMachineList;
}

void PlaylistDialog::setAvailableMachineList(const QList<VirtualMachine *> &newAvailableMachineList)
{
    if (availableMachineList == newAvailableMachineList)
        return;
    availableMachineList = newAvailableMachineList;

    //    ui->machineReferenceComboBox->clear();
    //    for( auto machine : availableMachineList){
    //        ui->machineReferenceComboBox->addItem(machine->Name );
    //    }

    emit availableMachineListChanged();
}
