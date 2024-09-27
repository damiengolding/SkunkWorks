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
#include "ptnghostwidget.hpp"
#include "ui_ptnghostwidget.h"

PtngHostWidget::PtngHostWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PtngHostWidget)
{
    ui->setupUi(this);
    model = new QStandardItemModel();
    root = model->invisibleRootItem();
    ui->treeViewDetail->setModel(model);
    this->setFrameStyle( QFrame::Box | QFrame::Plain );
    this->setLineWidth( 3 );
}

PtngHostWidget::~PtngHostWidget()
{
    delete ui;
}

void PtngHostWidget::setDetail(const QString &hostname, const QString &ipAddress, HostStatus status, HostType type)
{
    ui->labelHostname->setText(hostname);
    ui->labelIPAddress->setText(ipAddress);
    status == Up ? ui->labelImageStatus->setPixmap( QPixmap(":/node_active_01.png") ) : ui->labelImageStatus->setPixmap( QPixmap(":/node_idle_01.png") );
    type == Subnet ? ui->labelImageHostType->setPixmap( QPixmap( ":/lan_01.png" ) )  : ui->labelImageHostType->setPixmap( QPixmap( ":/computer_01.png" ) );
}

void PtngHostWidget::addCategory(const QString &categoryName, const QStringList &categoryMembers)
{
    QStandardItem *item = new QStandardItem(categoryName);
    for( auto member : categoryMembers){
        item->appendRow( new QStandardItem( member ) );
    }
    root->appendRow( item);
}

void PtngHostWidget::display(const QString &file)
{
    Q_UNUSED(file);
}

void PtngHostWidget::setBanner(const QString &banner)
{
    Q_UNUSED(banner);
}

QString PtngHostWidget::getBanner()
{
    return{};
}

void PtngHostWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    detailVisible ? showDetail( false ) : showDetail( true );
}

void PtngHostWidget::showDetail(bool show)
{
    if( show ){
        if( ui->treeViewDetail->model() != nullptr && ui->treeViewDetail->model()->rowCount() > 0 ){
            ui->treeViewDetail->setVisible(true);
            this->resize( width(), 295 ); // Hard coded - original designer height
            detailVisible = true;
        }
    }
    else{
        ui->treeViewDetail->setVisible(false);
        this->resize( width(), 70 ); // Hard coded - min height = 60px and 2 x 5px padding
        detailVisible = false;
    }
}

