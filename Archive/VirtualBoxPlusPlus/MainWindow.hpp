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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QDir>
#include <QSettings>
#include <QFileInfo>
#include <QToolBar>
#include <QClipboard>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QScopedPointer>
#include <QDebug>
#include <QtConcurrent>
#include <QProgressDialog>
#include <QClipboard>
#include <QIcon>

#include "VirtualMachine.hpp"
#include "MachineInfo.hpp"
#include "MachineMetrics.hpp"
#include "MetricsMonitor.hpp"
#include "MetricsVisualization.hpp"
#include "MetricsCounter.hpp"
#include "PlaylistManager.hpp"
#include "RegisteredMediaInfo.hpp"
#include "StandardInterfaceInfo.hpp"
#include "NATNetworkInfo.hpp"
#include "DHCPServerInfo.hpp"

using namespace VirtualBoxPlusPlus;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Enums
    enum DataUpdateType{
        AVAILABLE_VMS,
        RUNNING_VMS,
        SHOW_VMINFO,
        NUM_DATA_UPDATE_TYPES
    };
    Q_ENUM(DataUpdateType)
public:
    // Housekeeping settings
    QString vboxmanageExe = "C:\\Program Files\\Oracle\\VirtualBox\\VBoxManage.exe";
    QDir homeDirectory = QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++";
    QDir currentDirectory = QDir::homePath();
    QDir playlistsDirectory = QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Playlists";
    QDir pluginsDirectory = QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Plugins";
    QDir themesDirectory = QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Themes";
    QDir commandsDirectory = QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Commands";
    QStringList additionalPlaylistDirectories;
    QStringList additionalPluginDirectories;

    QList<QFileInfo> currentPlaylists;
    QList<QFileInfo> currentPlugins;

    // Metrics
    bool startMetricsOnOpen = true;
    int sampleInterval = 2;
    int sampleCount = 1800;

    // Machine in-memory storage
    QList<VirtualMachine*> availableMachineList;
    QList<VirtualMachine*> runningMachineList;
    QList<MachineInfo*> machineInfoList;
    QList<QList<MachineMetrics*>> currentMetrics;
    PlaylistManager *playlistManager;

    // Internal objects
    MetricsMonitor *metricsMonitor;
    QProgressDialog *progressDialog;
    //QList<QFileSystemWatcher*> fileSystemWatchers;

    // Display constants
    QString versionString ="Version: 2023.1DEV";
    QString dialogTitle = "Virtual Box++";
    QString applicationBanner = "Golding's Gym - Virtual Box++";
    QString metricsCountersLabelText = "Current metrics for {0} / {1}";
    QString vminfoCountersLabelText = "Current VMInfo for {0} / {1}";
    QString snapshotsLabelText = "Snapshots for {0} / {1}";

    // Mutexes to co-ordinate data ingestion and data visualisation
    QMutex availableMachinesMutex;
    QMutex runningMachinesMutex;
    QMutex machineMetricsMutex;
    QMutex vmInfoMutex;
    QMutex registeredMediaMutex;
    QMutex configuredNetworksMutex;

    // Custom widgets
    MetricsVisualization *metricsVisualization;

    // Misc runtime
    // REFACT Get this into the SettingsDialog
    int maxMetricsErrors = 5; // This is for the occasion when vboxmanage metrics * doesn't report properly and outputs metrics name without value
    bool maxMetricsErrorsReached = false; // As above

    // File system watchers
    QFileSystemWatcher *playlistFileSystemWatcher;
    QFileSystemWatcher *pluginFileSystemWatcher;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//private:
    Ui::MainWindow *ui;

// Hand rolled stuff starts here . . .
// Initialisation and de-inititialisation
private:
void doEntryHousekeeping();
void connectObjects();
void restoreTables();
//void restoreWindowState();
void restoreApplicationSignature(QApplication *app);
void restoreSettings();
void restoreEnvironment();
void restorePlugins();
void restorePlaylists();
void startWorkerThreads();
void startFileSystemWatchers();
void doExitHousekeeping();
void saveSettings(QSettings &settings);
QStandardItem* getDriveList(int type);
QStandardItem* getNetworkList(int type);
QStandardItem* getStandardInterfaceList(int type);
QStandardItem* getNATNetsInterfaceList();
QStandardItem* getDHCPServerList();

// Slots
public slots:
// Misc GUI stuff
void onShowAboutQt();
void onShowAboutVboxPlusPlus();
void onShowVBoxPlusPlusHelp();
void onApplicationExitCalled();
void restoreUserInterfaceStrings();
void onShowSettingsDialog();
void onShowPlaylistDialog();
// Custom context menu requests
void onCCMRAvailableMachinesCalled(const QPoint &point);
void onCCMRRunningMachinesCalled(const QPoint& point);
void onCCMRPlaylistsCalled(const QPoint& point);
void onCCMRPluginsCalled(const QPoint &point);

void onMachineSelectionChangeCalled(QTableWidgetItem *current, QTableWidgetItem *previous);
void showHideExplorerDock();
void showHideOutputDock();

// Data acquisition
void onAvailableMachinesDataRefreshCalled();
void onRunningMachinesDataRefreshCalled();
void onVMInfoDataRefreshCalled(QList<VirtualMachine*> machines);
QList<VirtualMachine*> onVBoxManageListOutputAvailable(DataUpdateType dataType, const QString &outputText);
MachineInfo* onVBoxManageVMInfoOutputAvailable(const QString &outputText,const QString &name, const QString &uuid);
void onMetricsUpdated(QList<QList<MachineMetrics*>> metrics);
//void onMetricsUpdateAvailable();
void onMetricsMaxReadErrorReached(int errors);
void onRefreshMetricsWindowCalled();//const QString &name, const QString &uuid);
void onRefreshSnapshotsWindowCalled(const QString &name, const QString &uuid);
void onRefreshRegisteredMediaCalled();
void onRefreshConfiguredNetworksCalled();
void updateRegisteredMedia(QStandardItemModel* model);
void updateConfiguredNetworks(QStandardItemModel* model);

// Data display
void onRefreshMachinesDisplayCalled(DataUpdateType dataType, QList<VirtualMachine*> machines);
void onRefreshVMInfoDisplayCalled(MachineInfo* machineInfo);
QList<QFileInfo> onRefreshPluginsCalled(QDir directory);
QList<QFileInfo> onRefreshPlaylistsCalled(QDir directory);

// UX events - general
void onMachineSelectionChanged(const QString &name, const QString &uuid);

// UX events - refresh
void onRefreshAllUi();
void onRefreshAvailableVMList();
void onRefreshRunningVMList();

// Process and associated admin
void onProcessFinished(int exitCode, QProcess::ExitStatus = QProcess::NormalExit);

// File system watchers
void playlistDirectoryChanged(const QString &path);
void pluginDirectoryChanged(const QString &path);
void playlistFileChanged(const QString &path);
void pluginFileChanged(const QString &path);
void addPlaylistDirectoryToFSW(const QString &path);
void removePlaylistDirectoryFromFSW(const QString &path);
void addPluginDirectoryToFSW(const QString &path);
void removePluginDirectoryFromFSW(const QString &path);

// Overrides
protected:
void closeEvent(QCloseEvent *event) override;

// Signals
signals:
void dataUpdateAvailable(DataUpdateType dataType, QList<VirtualMachine*> machines);
void uiUpdateAvailable(DataUpdateType dataType, QList<VirtualMachine*> machines);
void infoUpdateAvailable(DataUpdateType dataType, QList<MachineInfo*> machineInfo);
void metricsUpdateAvailable(QList<QList<MachineMetrics*>>);
void setUpComplete();
void machineSelectionChanged(const QString &name, const QString &uuid);
void refreshUiRequested();
void registeredMediaRefreshed(QStandardItemModel *model);
void configuredNetworksRefreshed(QStandardItemModel *model);

// Miscellaneous nonsense
public:
static QString unQuote(const QString& quoted);
static QString measureTypeToString(MachineMetrics::MeasureType type);
static MachineMetrics::MeasureType stringToMeasureType(const QString &typeStr, QString &out);
static void clearTableWidget(QTableWidget *tableWidget);
// This is because the closeEvent handler can be called twice if exit comes through the menu rather than from the x at the top right hand corner
bool closeEventCalled = false;
bool tableHasUuid(QTableWidget* table, const QString &test);
bool tableHasName(QTableWidget* table, const QString &test);
// A bunch of stuff about tool bars because Qt Creator and Qt Designer dare to be different . .
void restoreToolbars();
QToolBar *internalActions = new QToolBar();
QAction *settingsToolbarAction;
QAction *playlistManagerToolbarAction;
QAction *playlistRunnerToolbarAction;
QAction *playlistSchedulerToolbarAction;
QAction *interfaceRefreshToolbarAction;
};

#endif // MAINWINDOW_HPP
