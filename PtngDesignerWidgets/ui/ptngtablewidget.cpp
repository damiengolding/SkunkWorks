/*
MIT License

Copyright (c) Damien Golding 2024

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "ptngtablewidget.hpp"
#include "qclipboard.h"
#include "qmenu.h"
#include "ui_ptngtablewidget.h"
#include "PtngEnums.hpp"
using namespace ptng;

#include <QFile>
#include <QMessageBox>
#include <QProgressDialog>

PtngTableWidget::PtngTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PtngTableWidget)
{
    ui->setupUi(this);
    connect(ui->tableView,
            SIGNAL( customContextMenuRequested(const QPoint&) ),
            this,
            SLOT( showCCMMenu(const QPoint& ) ),
            Qt::UniqueConnection
            );
}

PtngTableWidget::~PtngTableWidget()
{
    delete ui;
}

void PtngTableWidget::display(const QString &inputFile)
{
    QScopedPointer<QFile> file(new QFile( inputFile ));
    if( !file->open(QIODevice::ReadOnly) ){
        qWarning() << "File"<<inputFile<<"could not be opened for reading";
        return;
    }
    // Parse and display the XML
    QProgressDialog progressDialog("Click \"Abort\" to return to the GUI","Abort",0,0,this);
    progressDialog.setWindowModality(Qt::WindowModal);
    // progressDialog.
    connect( this,
             SIGNAL( loadCompleted() ),
             &progressDialog,
             SLOT( close() ),
             Qt::UniqueConnection
             );
    QStandardItemModel *tableModel = new QStandardItemModel(this);
    PtngEnums::SupportedInputTypes type = PtngIdent::checkFile(inputFile);
    if( type == PtngEnums::CSV ){
        QFileInfo fi(inputFile);
        ui->labelBanner->setToolTip(fi.absoluteFilePath());
        ui->labelBanner->setText("CSV: " % fi.fileName());
        progressDialog.open();
        displayCsv( file.data(), tableModel);
        ui->tableView->setModel(tableModel);
        hasfile = true;
        ui->labelBanner->setText(inputFile);
        emit loadCompleted();
    }
    else if( type == PtngEnums::TSV ){
        QFileInfo fi(inputFile);
        ui->labelBanner->setToolTip(fi.absoluteFilePath());
        ui->labelBanner->setText("TSV: " % fi.fileName());
        progressDialog.open();
        displayTsv( file.data(), tableModel);
        ui->tableView->setModel(tableModel);
        hasfile = true;
        ui->labelBanner->setText(inputFile);
        emit loadCompleted();
    }
    else{
        QString msg = QString( "TABLE WIDGET : Supplied file %1 is of an  unsupported type" ).arg(inputFile);
        QMessageBox::information(this,"PtngTableWIdget",msg);
    }
}

void PtngTableWidget::displayCsv(QFile *inputFile, QStandardItemModel *model)
{
        QStringList lines;
        while( !inputFile->atEnd() ){
            lines << inputFile->readLine();
        }
        QString header = lines.first();
        lines.removeFirst();
        QStringList headers = header.split(',');
        model->setHorizontalHeaderLabels(headers);

        for( int i = 0; i < lines.count(); ++i ){
            QStringList entries = lines.at(i).split(',');
            model->insertRow(i);
            for( int j = 0; j < entries.count();++j ) {
                QString entry = entries.at(j);
                entry = entry.remove("\r\n");
                model->setItem(i, j, new QStandardItem( entry ) );
            }
        }
}

void PtngTableWidget::displayTsv(QFile *inputFile, QStandardItemModel *model)
{
    QStringList lines;
    while( !inputFile->atEnd() ){
        lines << inputFile->readLine();
    }
    QString header = lines.first();
    lines.removeFirst();
    QStringList headers = header.split('\t');
    model->setHorizontalHeaderLabels(headers);

    for( int i = 0; i < lines.count(); ++i ){
        QStringList entries = lines.at(i).split('\t');
        model->insertRow(i);
        for( int j = 0; j < entries.count();++j ) {
            QString entry = entries.at(j);
            entry = entry.remove("\r\n");
            model->setItem(i, j, new QStandardItem( entry ) );
        }
    }
}

void PtngTableWidget::showCCMMenu(const QPoint &point)
{
    if( !hasfile ){
        return;
    }
    QMenu *ccMenu = new QMenu();
    QAction *copy = new QAction();
    copy->setText("Copy selected");
    connect( copy,
             SIGNAL( triggered(bool)),
             this,
             SLOT( copy(bool) ),
             Qt::UniqueConnection
             );
    ccMenu->addAction(copy);
    ccMenu->exec(QCursor::pos());
}

void PtngTableWidget::copy(bool checked)
{
    QModelIndexList selections = ui->tableView->selectionModel()->selectedIndexes();
    QStringList stringList;
    for( auto selection : selections ){
        stringList << selection.data().toString();
    }
    QString copyText = stringList.join("\n");
    QClipboard *clipBoard = QGuiApplication::clipboard();
    clipBoard->setText(copyText);
}

void PtngTableWidget::setBanner(const QString &banner)
{
    this->banner = banner;
    ui->labelBanner->setText(this->banner);
    emit bannerChanged();
}

QString PtngTableWidget::getBanner()
{
    return(banner);
}
