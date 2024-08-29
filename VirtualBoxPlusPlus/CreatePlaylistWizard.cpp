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

#include "CreatePlaylistWizard.hpp"

// Wizard
CreatePlaylistWizard::CreatePlaylistWizard(QList<VirtualMachine*> availableMachines, QDir playlistsDirectory, QWidget *parent)  :
    AvailableMachines(availableMachines),
    PlaylistsDirectory(playlistsDirectory),
    QWizard(parent)
{
    setupWizard();
    setPage(0,sp);
    setPage(1,pip);
    setPage(2,srp);
}

CreatePlaylistWizard::~CreatePlaylistWizard(){}

// TODO Implement this to create the PlaylistDefinition object
void CreatePlaylistWizard::accept()
{
    QDialog::accept();
}

void CreatePlaylistWizard::setupWizard()
{
    setWindowTitle("New playlist");
    setObjectName("CreatePlaylistWizard");
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/Resources/Images/GG_ICON.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon);
    setWizardStyle(QWizard::ModernStyle);
    playlistDefinition = new PlaylistDefinition();
    jsonDocument = new QJsonDocument();

    sp = new StartPage(AvailableMachines,PlaylistsDirectory, this);
    pip = new PlaylistItemsPage(AvailableMachines,PlaylistsDirectory, this);
    srp = new ScriptReviewPage(AvailableMachines,PlaylistsDirectory, this);
}

QJsonDocument *CreatePlaylistWizard::getJsonDocument() const
{
    return jsonDocument;
}

void CreatePlaylistWizard::setJsonDocument(QJsonDocument *newJsonDocument)
{
    if (jsonDocument == newJsonDocument)
        return;
    jsonDocument = newJsonDocument;
    emit jsonDocumentChanged();
}

PlaylistDefinition *CreatePlaylistWizard::getPlaylistDefinition() const
{
    return playlistDefinition;
}

void CreatePlaylistWizard::setPlaylistDefinition(PlaylistDefinition *newPlaylistDefinition)
{
    if (playlistDefinition == newPlaylistDefinition)
        return;
    playlistDefinition = newPlaylistDefinition;
    emit playlistDefinitionChanged();
}

// StartPage
StartPage::StartPage(QList<VirtualMachine*> availableMachines, QDir playlistsDirectory, QWidget *parent) :
    AvailableMachines(availableMachines),
    PlaylistsDirectory(playlistsDirectory),
    QWizardPage(parent)
{
    setupPage();
    connect(locationToolButton,
            SIGNAL(clicked()),
            this,
            SLOT(OnSelectFileClicked())
            );
}
StartPage::~StartPage(){}

void StartPage::OnSelectFileClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Virtual Box++",PlaylistsDirectory.absolutePath(),"Virtual Box++ playlists (*.vbpl)");
    if(fileName.isNull()){
        return;
    }
    locationLineEdit->setText(fileName);
}

bool StartPage::validatePage()
{
//    if( locationLineEdit->text().length() > 0 && nameLineEdit->text().length() > 0){
//        return(true);
//    }
//    else{
//        QMessageBox::warning(this,"Virtual Box++","You must enter a file location to store the playlist, and a display name.");
//        return(false);
//    }
    return(true);
}

void StartPage::setupPage()
{
    setTitle("Playlist name and location");
    setSubTitle("Confirm the location for your playlist script file, and it's display name:");
    setObjectName("StartPage");
    introGridLayout = new QGridLayout(this);
    nameLabel = new QLabel(this);
    nameLabel->setObjectName("nameLabel");
    nameLabel->setText("Name");
    introGridLayout->addWidget(nameLabel, 0, 0, 1, 1);
    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setObjectName("nameLineEdit");
    registerField("playlistName*",nameLineEdit);
    introGridLayout->addWidget(nameLineEdit, 0, 1, 1, 2);
    locationLabel = new QLabel(this);
    locationLabel->setObjectName("locationLabel");
    locationLabel->setText("Location:");
    introGridLayout->addWidget(locationLabel, 1, 0, 1, 1);
    locationLineEdit = new QLineEdit(this);
    locationLineEdit->setObjectName("locationLineEdit");
    registerField("playlistFile*",locationLineEdit);
    locationLineEdit->setClearButtonEnabled(false);
    introGridLayout->addWidget(locationLineEdit, 1, 1, 1, 1);
    locationToolButton = new QToolButton(this);
    locationToolButton->setText("...");
    locationToolButton->setObjectName("locationToolButton");
    introGridLayout->addWidget(locationToolButton, 1, 2, 1, 1);
}

// PlaylistItemsPage
PlaylistItemsPage::PlaylistItemsPage(QList<VirtualMachine*> availableMachines, QDir playlistsDirectory, QWidget *parent) :
    AvailableMachines(availableMachines),
    PlaylistsDirectory(playlistsDirectory),
    QWizardPage(parent)
{
    setupPage();
}
PlaylistItemsPage::~PlaylistItemsPage(){}

bool PlaylistItemsPage::validatePage()
{
    QJsonObject jObj;
    playlistDefinition->Write(jObj);
    QJsonDocument jDoc(jObj);

    QString jsonString = QString::fromLatin1(jDoc.toJson());
    jsonTextField->setText(jsonString);
//    qDebug().noquote()<<"jsonString #1: " << jsonString;
    setField("jsonTextField",jsonString);
//    qDebug().noquote()<<"jsonString #2: " << field("jsonTextField").toString();
    return(true);
}

void PlaylistItemsPage::initializePage()
{
    playlistDefinition = new PlaylistDefinition();
    playlistDefinition->setName( field("playlistName").toString() );
}

void PlaylistItemsPage::setupPage()
{
    setTitle("Playlist members");
    setSubTitle("Confirm the virtual machines, and their configuration, for your playlist");
    setObjectName("PlaylistItemsPage");
    vmGridLayout = new QGridLayout(this);
    vmGridLayout->setObjectName("vmGridLayout");
    vmGridLayout->setContentsMargins(3, 3, 3, 3);
    runOrderLabel = new QLabel(this);
    runOrderLabel->setObjectName("runOrderLabel");
    runOrderLabel->setText("Run order:");
    vmGridLayout->addWidget(runOrderLabel, 0, 0, 1, 1);
    runTypeLabel = new QLabel(this);
    runTypeLabel->setObjectName("runTypeLabel");
    runTypeLabel->setText("Run type:");
    vmGridLayout->addWidget(runTypeLabel, 0, 1, 1, 1);
    interfaceTypeLabel = new QLabel(this);
    interfaceTypeLabel->setObjectName("interfaceTypeLabel");
    interfaceTypeLabel->setText("Interface type:");
    vmGridLayout->addWidget(interfaceTypeLabel, 0, 2, 1, 1);
    runOrderSpinBox = new QSpinBox(this);
    runOrderSpinBox->setObjectName("runOrderSpinBox");
    vmGridLayout->addWidget(runOrderSpinBox, 1, 0, 1, 1);
    runTypeComboBox = new QComboBox(this);
    runTypeComboBox->addItem( "Series");
    runTypeComboBox->addItem( "Parallel");
    runTypeComboBox->setObjectName("runTypeComboBox");
    vmGridLayout->addWidget(runTypeComboBox, 1, 1, 1, 1);
    interfaceTypeComboBox = new QComboBox(this);
    interfaceTypeComboBox->addItem("GUI");
    interfaceTypeComboBox->addItem("Detachable");
    interfaceTypeComboBox->addItem("Headless");
    interfaceTypeComboBox->addItem( "SDL");
    interfaceTypeComboBox->setObjectName("interfaceTypeComboBox");
    vmGridLayout->addWidget(interfaceTypeComboBox, 1, 2, 1, 1);
    machineLabel = new QLabel(this);
    machineLabel->setObjectName("machineLabel");
    machineLabel->setText( "Select a machine:");
    vmGridLayout->addWidget(machineLabel, 2, 0, 1, 1);
    machineComboBox = new QComboBox(this);
    machineComboBox->addItem("[Select]");
    machineComboBox->setObjectName("machineComboBox");
    machineComboBox->setEditable(false);
    vmGridLayout->addWidget(machineComboBox, 2, 1, 1, 2);
    machineTableWidget = new QTableWidget(this);
    if (machineTableWidget->columnCount() < 5)
        machineTableWidget->setColumnCount(5);
    machineTableWidget->setHorizontalHeaderLabels(QStringList()<<"Name"<<"UUID"<<"Order"<<"Start policy"<<"Start type");
    machineTableWidget->setObjectName("machineTableWidget");
    machineTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    machineTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    machineTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    machineTableWidget->setSortingEnabled(true);
    machineTableWidget->setColumnCount(5);
    machineTableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
    machineTableWidget->horizontalHeader()->setStretchLastSection(true);
    machineTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    machineTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    vmGridLayout->addWidget(machineTableWidget, 3, 0, 1, 3);

    jsonTextField = new QLineEdit(this);
    jsonTextField->setVisible(false);
    jsonTextField->setEnabled(true);
    jsonTextField->setReadOnly(false);
    registerField("jsonTextField",jsonTextField);

    for(auto vm : AvailableMachines){
        machineComboBox->addItem(vm->getName());
    }

    // Connections
    connect(machineComboBox,
            SIGNAL(currentTextChanged(const QString&)),
            this,
            SLOT(onComboBoxChanged(const QString&))
            );

    connect(machineTableWidget,
            SIGNAL(customContextMenuRequested(const QPoint&)),
            this,
            SLOT(onCustomContextMenuRequested(const QPoint&))
            );
}

void PlaylistItemsPage::onComboBoxChanged(const QString &text)
{
    if(text.toLower() == "[select]")
        return;
    QString vmName, vmUuid;
    vmName = machineComboBox->currentText();
    QList<QTableWidgetItem*> items = machineTableWidget->findItems(vmName,Qt::MatchFixedString);
    if(items.count() > 0){
        QMessageBox::information(this,"Virtual Box++","The machine " + vmName + " is already in use");
        return;
    }
    //QMessageBox::information(this,"Virtual Box++","OnMachineSelectionChanged: " + text);
    int rc = machineTableWidget->rowCount();
    for(auto vm : AvailableMachines){
        if(text.toLower() == vmName.toLower() ){
            vmUuid = vm->getUuid();
            break;
        }
    }

    QTableWidgetItem *i0 = new QTableWidgetItem(vmName);
    QTableWidgetItem *i1 = new QTableWidgetItem(vmUuid);
    QTableWidgetItem *i2 = new QTableWidgetItem(QString::number(runOrderSpinBox->value()));
    QTableWidgetItem *i3 = new QTableWidgetItem(runTypeComboBox->currentText());
    QTableWidgetItem *i4 = new QTableWidgetItem(interfaceTypeComboBox->currentText());
    machineTableWidget->insertRow(rc);
    machineTableWidget->setItem(rc,0,i0);
    machineTableWidget->setItem(rc,1,i1);
    machineTableWidget->setItem(rc,2,i2);
    machineTableWidget->setItem(rc,3,i3);
    machineTableWidget->setItem(rc,4,i4);

    PlaylistItem *playlistItem = new PlaylistItem();
    playlistItem->setName(vmName);
    playlistItem->setUUID(vmUuid);
    playlistItem->setOrder(runOrderSpinBox->value());
    playlistItem->setMode(PlaylistItem::StringToStartMode( interfaceTypeComboBox->currentText() ));
    playlistItem->setPolicy(PlaylistItem::StringToExecutionPolicy(runTypeComboBox->currentText()));
    playlistDefinition->AddPlaylistItem(playlistItem);

    runOrderSpinBox->setValue( runOrderSpinBox->value() + 1 );
    //qDebug()<<"PlaylistItems: " << playlistDefinition->getPlaylistItems().count();
}

void PlaylistItemsPage::onCustomContextMenuRequested(const QPoint &point)
{
    QList<QTableWidgetItem*> selectedItems = machineTableWidget->selectedItems();
    if( selectedItems.count() == 0){
        return;
    }
    QMenu *menu = new QMenu();
    menu->addAction("Remove");
    QAction *selectedAction = menu->exec(QCursor::pos());
    if(selectedAction == nullptr)
        return;
     QTableWidgetItem *selectedItem;
     QString selectedMachineName;
    if( selectedAction->text().toLower() == "remove" ){
        selectedItem = selectedItems.at(0);
        selectedMachineName = selectedItem->text();
        qDebug()<<"Selected machine: " << selectedMachineName;
        int rowIndex = machineTableWidget->row(selectedItem);
        machineTableWidget->removeRow(rowIndex);
        for(auto PlaylistItem : playlistDefinition->playlistItems){
            if( PlaylistItem->getName() == selectedMachineName ){
                playlistDefinition->removePlaylistItem(PlaylistItem);
                break;
            }
        }
    }


}

// ScriptReviewPage
ScriptReviewPage::ScriptReviewPage(QList<VirtualMachine*> availableMachines, QDir playlistsDirectory, QWidget *parent) :
    AvailableMachines(availableMachines),
    PlaylistsDirectory(playlistsDirectory),
    QWizardPage(parent)
{
    setupPage();
}
ScriptReviewPage::~ScriptReviewPage(){}

void ScriptReviewPage::setupPage()
{
    setObjectName("ScriptReviewPage");
    lexer = new QsciLexerJSON();
    summaryGridLayout = new QGridLayout(this);
    summaryGridLayout->setObjectName("summaryGridLayout");
    summaryGridLayout->setContentsMargins(5, 5, 5, 5);
    scriptEdit = new QsciScintilla(this);
    scriptEdit->setObjectName("scriptEdit");
    QFont font;
    font.setFamilies({QString::fromUtf8("Open Sans")});
    font.setPointSize(10);
    scriptEdit->setFont(font);
    scriptEdit->setLexer(lexer);
    summaryGridLayout->addWidget(scriptEdit, 0, 0, 1, 1);
}

void ScriptReviewPage::initializePage()
{
    QString jsonString = field("jsonTextField").toString();
    initialJsonText = jsonString;
    scriptEdit->setText(jsonString);
}

bool ScriptReviewPage::validatePage()
{
    QString fileName = field("playlistFile").toString();
    QFile outputFile(fileName);
    if( !outputFile.open( QIODevice::WriteOnly | QIODevice::Text ) ){
        QMessageBox::warning(this,"Virtual Box++","Unable to open file " + fileName + " for writing");
        qDebug()<<"Unable to open file " << fileName << " for writing";
        return(false);
    }
    QTextStream outputTextStream(&outputFile);
    outputTextStream << scriptEdit->text();
    outputFile.close();
    return(true);
}
