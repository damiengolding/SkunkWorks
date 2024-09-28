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

#ifndef PLAYLISTDIALOG_HPP
#define PLAYLISTDIALOG_HPP

#include <QDialog>
#include <QObject>
#include <QMessageBox>
#include <QDir>
#include <QMenu>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>

#include "Qsci/qscilexerjson.h"

#include "VirtualMachine.hpp"
#include "PlaylistDefinition.hpp"
#include "PlaylistItem.hpp"
#include "CreatePlaylistWizard.hpp"

#include "MainWindow.hpp"

namespace Ui {
class PlaylistDialog;
}

class PlaylistDialog : public QDialog
{
    Q_OBJECT
    QsciLexerJSON *lexer;
public:
    explicit PlaylistDialog(QWidget *parent = nullptr);
    ~PlaylistDialog();

public slots:
    void onCCMRMachineListTableWidgetCalled(const QPoint &point);
    void onItemContentsChanged(QTableWidgetItem *item);
    void onCellDoubleClicked(int a, int b);
    void onNewButtonClicked();
    void onOpenButtonClicked();
    void onSaveButtonClicked();
    void onSaveAsButtonClicked();
    void loadPlaylistFile(const QFileInfo& file);
    void onPlaylistDefinitionChanged();

private:
    Ui::PlaylistDialog *ui;
    QList<VirtualMachine*> availableMachineList;
    Q_PROPERTY(QList<VirtualMachine *> availableMachineList READ getAvailableMachineList WRITE setAvailableMachineList NOTIFY availableMachineListChanged)

    QDir playlistsDirectory;
    QFileInfo currentFile;
    PlaylistDefinition *playlistDefinition;
    void showPlaylist(const QString &file);
    void setupDialog();

    Q_PROPERTY(QDir playlistsDirectory READ getPlaylistsDirectory WRITE setPlaylistsDirectory NOTIFY PlaylistsDirectoryChanged)
    Q_PROPERTY(QFileInfo currentFile READ getCurrentFile WRITE setCurrentFile NOTIFY CurrentFileChanged)
    bool loading = true;
    Q_PROPERTY(PlaylistDefinition *playlistDefinition READ getPlaylistDefinition WRITE setPlaylistDefinition NOTIFY playlistDefinitionChanged)

public:
    QList<VirtualMachine *> getAvailableMachineList() const;
    void setAvailableMachineList(const QList<VirtualMachine *> &newAvailableMachineList);
    QDir getPlaylistsDirectory() const;
    void setPlaylistsDirectory(const QDir &newPlaylistsDirectory);

    QFileInfo getCurrentFile() const;
    void setCurrentFile(const QFileInfo &newCurrentFile);

    PlaylistDefinition *getPlaylistDefinition() const;
    void setPlaylistDefinition(PlaylistDefinition *newPlaylistDefinition);

signals:
    void availableMachineListChanged();
    void PlaylistsDirectoryChanged();
    void CurrentFileChanged();
    void playlistDefinitionChanged();
};

#endif // PLAYLISTDIALOG_HPP
