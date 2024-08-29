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

#include "LifeCycleEntry.hpp"

LifeCycleEntry::LifeCycleEntry(MainWindow *mainWindow, QObject *parent)
    : mainWindow(mainWindow), QObject{parent}
{

}

void LifeCycleEntry::doEntryHousekeeping(){
    restoreApplicationSignature(qApp);
    restoreSettings();
    restoreTables();
    restorePlugins();
    restorePlaylists();
    restoreToolbars();
    mainWindow->onRefreshMetricsWindowCalled(); // REFACT is there a tidier equivalent to the non-existent QString::empty()?
    restoreUserInterfaceStrings();
    startWorkerThreads();
    emit setUpComplete();
}

void LifeCycleEntry::restoreUserInterfaceStrings(){
    mainWindow->ui->goldingsGymLabel->setText(mainWindow->applicationBanner);
    mainWindow->ui->versionLabel->setText(mainWindow->versionString);
    QString noMachineSelected = "No machine selected";
    mainWindow->ui->vminfoCountersLabel->setText(noMachineSelected);
    mainWindow->ui->metricsCountersLabel->setText(noMachineSelected);
    mainWindow->ui->snapshotsLabel->setText(noMachineSelected);
}

void LifeCycleEntry::restorePlugins(){
//    qDebug()<<"restorePlugins";
    // Clear the table first
    mainWindow->ui-> pluginsTableWidget->clearContents();
    mainWindow->ui->pluginsTableWidget->setRowCount(0);
    int rc = mainWindow->ui->pluginsTableWidget->rowCount();
    for (int i = rc - 1; i > 0; --i) {
        mainWindow->ui->pluginsTableWidget->removeRow(i);
    }
    // Then re-populate it
    mainWindow->onRefreshPluginsCalled(mainWindow->pluginsDirectory);
    for(QDir dir : mainWindow->additionalPluginDirectories){
        mainWindow->onRefreshPluginsCalled(dir);
    }
}

void LifeCycleEntry::restorePlaylists(){
//    playlistManager = new PlaylistManager();
    //    playlistManager->TestPlaylistText();
    //    qDebug()<<"restorePlaylists";
    // Clear the table first
    mainWindow->ui->playlistsTableWidget->clearContents();
    mainWindow->ui->playlistsTableWidget->setRowCount(0);
    int rc = mainWindow->ui->playlistsTableWidget->rowCount();
    for (int i = rc - 1; i > 0; --i) {
        mainWindow->ui->playlistsTableWidget->removeRow(i);
    }
    // Then re-populate it
    mainWindow->onRefreshPlaylistsCalled(mainWindow->playlistsDirectory);
    for(QDir dir : mainWindow->additionalPlaylistDirectories){
        mainWindow->onRefreshPlaylistsCalled(dir);
    }
}

void LifeCycleEntry::restoreTables()
{
    mainWindow->ui->availableMachinesTableWidget->setHorizontalHeaderLabels(QStringList() <<"UUID"<<"Name");
    mainWindow->ui->runningMachinesTableWidget->setHorizontalHeaderLabels(QStringList() <<"UUID"<<"Name");
    mainWindow->ui->playlistsTableWidget->setHorizontalHeaderLabels(QStringList() << "Playlists"<< "Location");
    // TODO reimplement for QTreeView
//    mainWindow->ui->machineInfoTableView->setHorizontalHeaderLabels(QStringList() << "Name" << "Value");
    mainWindow->ui->pluginsTableWidget->setHorizontalHeaderLabels(QStringList()<<"Plugin name" << "Location");

    // Table contents
    mainWindow ->onAvailableMachinesDataRefreshCalled();
    mainWindow->onRunningMachinesDataRefreshCalled();
    // FIXME
//    mainWindow->onVMInfoDataRefreshCalled(availableMachineList);
    mainWindow->onRefreshRegisteredMediaCalled();
    mainWindow->onRefreshConfiguredNetworksCalled();
}

void LifeCycleEntry::restoreToolbars(){

    // Create and add to menu bar
    playlistManagerToolbarAction = new QAction(QIcon(":/Resources/Images/PLAYLIST.png"),"Playlist manager");
    mainWindow->ui->menuView->addAction(playlistManagerToolbarAction);
    connect(playlistManagerToolbarAction,SIGNAL(triggered()),this,SLOT(onShowPlaylistDialog()));

    interfaceRefreshToolbarAction = new QAction(QIcon(":/Resources/Images/REFRESH.png"),"Refresh UI");
    mainWindow->ui->menuView->addAction(interfaceRefreshToolbarAction);
    connect(interfaceRefreshToolbarAction,SIGNAL(triggered()),this,SLOT(onRefreshAllUi()));
    mainWindow->ui->menuView->addSeparator();
    playlistRunnerToolbarAction = new QAction(QIcon(":/Resources/Images/PLAYLIST_RUN.png"),"Execute a playlist");
    mainWindow->ui->menuView->addAction(playlistRunnerToolbarAction);

    playlistSchedulerToolbarAction = new QAction(QIcon(":/Resources/Images/PLAYLIST_SCHEDULER.png"),"Schedule a playlist to run regularly through the Windows Task Scheduler (taskschd)");
   mainWindow-> ui->menuView->addAction(playlistSchedulerToolbarAction);

//    //addToolBar(Qt::LeftToolBarArea, internalActions);
//    addToolBar(internalActions);
//    internalActions->setAllowedAreas(Qt::AllToolBarAreas);
//    //internalActions->setMovable(false);
//    internalActions->setObjectName("internalActions");
//    settingsToolbarAction = new QAction(QIcon(":/Resources/Images/SETTINGS.png"),"Settings");
//    internalActions->addAction(settingsToolbarAction);
//    connect(settingsToolbarAction,SIGNAL(triggered()),this,SLOT(onShowSettingsDialog()));

//    internalActions->addSeparator();

}

void LifeCycleEntry::startWorkerThreads() {
    metricsMonitor = new MetricsMonitor();
    //MetricsMonitor *mm = new MetricsMonitor();
    connect(metricsMonitor,
            SIGNAL(metricsUpdated(QList<QList<MachineMetrics*>>)),
            this,
            SLOT(onMetricsUpdated(QList<QList<MachineMetrics*>>)));

    connect(metricsMonitor,
            SIGNAL(maxReadErrorsReached(int)),
            this,
            SLOT(onMetricsMaxReadErrorReached(int)));

    // TODO no need to get these from mainWindow, get them straight from QSettings
    metricsMonitor->vboxmanageExecutablePath = mainWindow->vboxmanageExe;
    metricsMonitor->setRunningMachines(mainWindow->runningMachineList);
    metricsMonitor->setMaxMetricsErrors(mainWindow->maxMetricsErrors);
    metricsMonitor->setStartMetricsOnOpen( mainWindow->startMetricsOnOpen );
    metricsMonitor->setSampleCount(mainWindow->sampleCount);
    metricsMonitor->setSampleInterval(mainWindow->sampleInterval);
    metricsMonitor->start();
//    qDebug()<<"Started monitor thread";
    startFileSystemWatchers();
}

// TODO QFileWatchers on all source directories
void LifeCycleEntry::startFileSystemWatchers(){
    qDebug()<<"Starting file system watchers";
    playlistFileSystemWatcher = new QFileSystemWatcher();
    playlistFileSystemWatcher->addPath(mainWindow->playlistsDirectory.absolutePath());
    playlistFileSystemWatcher->addPaths(mainWindow->additionalPlaylistDirectories);
    connect(playlistFileSystemWatcher,
            SIGNAL(fileChanged(const QString&)),
                   this,
                   SLOT(playlistFileChanged(const QString&))
                        );

            connect(playlistFileSystemWatcher,
                    SIGNAL(directoryChanged(const QString&)),
                           this,
                           SLOT(playlistDirectoryChanged(const QString&))
                                );

                    pluginFileSystemWatcher = new QFileSystemWatcher();

            pluginFileSystemWatcher = new QFileSystemWatcher();
            pluginFileSystemWatcher->addPath(mainWindow->pluginsDirectory.absolutePath());
            pluginFileSystemWatcher->addPaths(mainWindow->additionalPluginDirectories);
            connect(pluginFileSystemWatcher,
                    SIGNAL(fileChanged(const QString&)),
                           this,
                           SLOT(pluginFileChanged(const QString&))
                                );

                    connect(pluginFileSystemWatcher,
                            SIGNAL(directoryChanged(const QString&)),
                                   this,
                                   SLOT(pluginDirectoryChanged(const QString&))
                                        );
}

// REFACT This is messy in a generalised but still irritating way
void LifeCycleEntry::restoreSettings()
{
    qDebug()<<"Restoring settings";
    QSettings settings(qApp->organizationName(), qApp->applicationName());
    // Geometry and position
    mainWindow->restoreGeometry(settings.value("geometry").toByteArray());
    mainWindow->restoreState(settings.value("windowState").toByteArray());

    // Create the directory structure if it doesn't exist
    if (!mainWindow->homeDirectory.exists()) {
        mainWindow->homeDirectory.mkpath(mainWindow->homeDirectory.absolutePath());
    }
    if (!mainWindow->pluginsDirectory.exists()) {
        mainWindow->pluginsDirectory.mkpath(mainWindow->pluginsDirectory.absolutePath());
    }
    if (!mainWindow->playlistsDirectory.exists()) {
        mainWindow->playlistsDirectory.mkpath(mainWindow->playlistsDirectory.absolutePath());
    }
    if (!mainWindow->themesDirectory.exists()) {
        mainWindow->themesDirectory.mkpath(mainWindow->themesDirectory.absolutePath());
    }
    if (!mainWindow->commandsDirectory.exists()) {
        mainWindow->commandsDirectory.mkpath(mainWindow->commandsDirectory.absolutePath());
    }

    // Now handle the QSettings
    mainWindow->vboxmanageExe = settings.value("vboxmanageExe","C:\\Program Files\\Oracle\\VirtualBox\\VBoxManage.exe").toString();
    mainWindow->homeDirectory = settings.value("homeDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++").toString();
    mainWindow->currentDirectory = settings.value("currentDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++").toString();
    mainWindow->playlistsDirectory = settings.value("playlistsDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Playlists").toString();
    mainWindow->pluginsDirectory = settings.value("pluginsDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Plugins").toString();
    mainWindow->commandsDirectory = settings.value("commandsDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Commands").toString();

    // REFACT this is a kludge, but it does work
    mainWindow->additionalPlaylistDirectories.clear();
    QStringList directories = settings.value("additionalPlaylistDirectories","dummy;dummy").toString().split(';');
    if(directories.at(0).toLower() != "dummy"){
        for( auto directory : directories){
            QDir d(directory);
            if(d.exists()){
                mainWindow->additionalPlaylistDirectories.append(d.absolutePath());
            }
        }
    }

    mainWindow->additionalPluginDirectories.clear();
    directories = settings.value("additionalPluginDirectories","dummy;dummy").toString().split(';');
    if(directories.at(0).toLower() != "dummy"){
        for( auto directory : directories){
            QDir d(directory);
            if(d.exists()){
                mainWindow->additionalPluginDirectories.append(d.absolutePath());
            }
        }
    }

    // Metrics
    mainWindow->startMetricsOnOpen = settings.value("startMetricsOnOpen",true).toBool();
    mainWindow->sampleInterval = settings.value("sampleInterval",2).toInt();
    mainWindow->sampleCount = settings.value("sampleCount",1800).toInt();
}

void LifeCycleEntry::restoreApplicationSignature(QApplication *app){
    app->setApplicationName("Virtual Box++");
    app->setApplicationVersion("2023.1DEV");
    app->setOrganizationName("Golding's Gym");
    app->setOrganizationDomain("https://www.linkedin.com/company/goldings-gym/");
}

// FIXME This all needs to be be reviewed, all slots and signals for mainwindow
void LifeCycleEntry::connectObjects()
{
    // Menu and tool bar actions
//    connect(ui->actionAboutQt,SIGNAL(triggered()),this,SLOT(onShowAboutQt()));
//    connect(ui->actionHelp,SIGNAL(triggered()),this,SLOT(onShowVBoxPlusPlusHelp()));
//    connect(ui->actionAboutVirtualBoxPlusPlus,SIGNAL(triggered()),this,SLOT(onShowAboutVboxPlusPlus()));
//    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(onApplicationExitCalled()));
//    connect(ui->actionSettings,SIGNAL(triggered()),this,SLOT(onShowSettingsDialog()));

//    // Data ingestion and display actions
//    connect(this,SIGNAL(dataUpdateAvailable(DataUpdateType, QList<VirtualMachine*>)),this,SLOT(onRefreshMachinesDisplayCalled(DataUpdateType, QList<VirtualMachine*>)));

//    // Main menu actions
//    connect(ui->actionExplorerDockWindow,SIGNAL(triggered()),this,SLOT(showHideExplorerDock()));
//    connect(ui->actionOutputDockWindow,SIGNAL(triggered()),this,SLOT(showHideOutputDock()));

//    //Context menu actions
//    connect(ui->availableMachinesTableWidget,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(onCCMRAvailableMachinesCalled(const QPoint&)));
//    connect(ui->runningMachinesTableWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(onCCMRRunningMachinesCalled(const QPoint&)));
//    connect(ui->playlistsTableWidget,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(onCCMRPlaylistsCalled(const QPoint&)));
//    connect(ui->pluginsTableWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(onCCMRPluginsCalled(const QPoint&)));
//    connect(this,SIGNAL(machineSelectionChanged(const QString&, const QString&)),this,SLOT(onMachineSelectionChanged(const QString&, const QString&)));

//    // Data display actions
//    connect(ui->availableMachinesTableWidget,
//            SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)),
//            this,
//            SLOT(onMachineSelectionChangeCalled(QTableWidgetItem*, QTableWidgetItem*)));
//    connect(ui->runningMachinesTableWidget,
//            SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)),
//            this,
//            SLOT(onMachineSelectionChangeCalled(QTableWidgetItem*, QTableWidgetItem*)));

//    connect(this,
//             SIGNAL(refreshUiRequested()),
//             this,
//             SLOT(onRefreshAllUi() ) );

//    connect(this,
//            SIGNAL(registeredMediaRefreshed(QStandardItemModel*)),
//            this,
//            SLOT(updateRegisteredMedia(QStandardItemModel*))
//            );

//    connect(this,
//            SIGNAL(configuredNetworksRefreshed(QStandardItemModel*)),
//            this,
//            SLOT(updateConfiguredNetworks(QStandardItemModel*))
//            );
}


MainWindow *LifeCycleEntry::getMainWindow() const
{
    return mainWindow;
}

void LifeCycleEntry::setMainWindow(MainWindow *newMainWindow)
{
    if (mainWindow == newMainWindow)
        return;
    mainWindow = newMainWindow;
    emit mainWindowChanged();
}
