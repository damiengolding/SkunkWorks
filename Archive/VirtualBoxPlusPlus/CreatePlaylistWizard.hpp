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

#ifndef CREATEPLAYLISTWIZARD_HPP
#define CREATEPLAYLISTWIZARD_HPP

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWizard>
#include <QtWidgets/QWizardPage>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QPlainTextEdit>
#include <QMenu>

#include "Qsci/qsciscintilla.h"
#include "Qsci/qscilexerjson.h"

#include "VirtualMachine.hpp"
#include "PlaylistDefinition.hpp"
#include "PlaylistItem.hpp"

using namespace VirtualBoxPlusPlus;

class StartPage;
class PlaylistItemsPage;
class ScriptReviewPage;

// Wizard
class CreatePlaylistWizard : public QWizard{
    Q_OBJECT

    friend class StartPage;
    friend class PlaylistItemsPage;
    friend class ScriptReviewPage;

public:
    CreatePlaylistWizard(QList<VirtualMachine*> availableMachines, QDir playlistsDirectory, QWidget *parent = nullptr);
    ~CreatePlaylistWizard();

    void accept() override;

    PlaylistDefinition *getPlaylistDefinition() const;
    void setPlaylistDefinition(PlaylistDefinition *newPlaylistDefinition);

    QJsonDocument *getJsonDocument() const;
    void setJsonDocument(QJsonDocument *newJsonDocument);

signals:
    void playlistDefinitionChanged();

    void jsonDocumentChanged();

private slots:
    void setupWizard();

private:
    StartPage *sp;
    PlaylistItemsPage *pip;
    ScriptReviewPage *srp;

protected:
    QList<VirtualMachine*> AvailableMachines;
    QDir PlaylistsDirectory;

    QFile outputFile;
    QString playlistName;
    PlaylistDefinition *playlistDefinition;
    QJsonDocument *jsonDocument;

    Q_PROPERTY(PlaylistDefinition *playlistDefinition READ getPlaylistDefinition WRITE setPlaylistDefinition NOTIFY playlistDefinitionChanged)
    Q_PROPERTY(QJsonDocument *jsonDocument READ getJsonDocument WRITE setJsonDocument NOTIFY jsonDocumentChanged)
};

// Start page
class StartPage : public QWizardPage{
    Q_OBJECT
public:
    StartPage(QList<VirtualMachine*> availableMachines, QDir playlistsDirectory, QWidget *parent =  nullptr);
    ~StartPage();

    bool validatePage() override;

private slots: // Accessors and mutators
    void setupPage();
    void OnSelectFileClicked();

private: // Fields
    QGridLayout *introGridLayout;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *locationLabel;
    QLineEdit *locationLineEdit;
    QToolButton *locationToolButton;

    QList<VirtualMachine*> AvailableMachines;
    QDir PlaylistsDirectory;
};

// PlaylistItems page
class PlaylistItemsPage : public QWizardPage{
    Q_OBJECT
public:
    PlaylistItemsPage(QList<VirtualMachine*> availableMachines, QDir playlistsDirectory, QWidget *parent =  nullptr);
    ~PlaylistItemsPage();
    bool validatePage() override;
    void initializePage() override;
private slots: // Accessors and mutators
    void setupPage();
    void onComboBoxChanged(const QString &text);
    void onCustomContextMenuRequested(const QPoint &point);

private: // Fields
    QGridLayout *vmGridLayout;
    QLabel *runOrderLabel;
    QLabel *runTypeLabel;
    QLabel *interfaceTypeLabel;
    QSpinBox *runOrderSpinBox;
    QComboBox *runTypeComboBox;
    QComboBox *interfaceTypeComboBox;
    QLabel *machineLabel;
    QComboBox *machineComboBox;
    QTableWidget *machineTableWidget;
    QLineEdit *jsonTextField;
    QList<VirtualMachine*> AvailableMachines;
    QDir PlaylistsDirectory;
    PlaylistDefinition *playlistDefinition;
};

// ScriptReviewPage

class ScriptReviewPage : public QWizardPage{
    Q_OBJECT
public:
    ScriptReviewPage(QList<VirtualMachine*> availableMachines, QDir playlistsDirectory, QWidget *parent =  nullptr);
    ~ScriptReviewPage();
    bool validatePage() override;
private: // Fields
    QList<VirtualMachine*> AvailableMachines;
    QDir PlaylistsDirectory;
    QGridLayout *summaryGridLayout;
    QsciScintilla *scriptEdit;
    QsciLexerJSON *lexer;
    QString initialJsonText;

private slots: // Accessors and mutators
    void setupPage();
    void initializePage() override;
};

#endif // CREATEPLAYLISTWIZARD_HPP
