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
#include "ptngimagewidget.hpp"
#include "ui_ptngimagewidget.h"

PtngImageWidget::PtngImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PtngImageWidget)
{
    ui->setupUi(this);

    ui->pushButtonZoomIn->setVisible(false);
    ui->pushButtonZoomOut->setVisible(false);
    ui->pushButtonOrig->setVisible(false);

    // connect( ui->pushButtonZoomIn,
    //          SIGNAL( clicked() ),
    //          this,
    //          SLOT( zoomIn() ),
    //          Qt::UniqueConnection
    //          );

    // connect( ui->pushButtonZoomOut,
    //          SIGNAL( clicked() ),
    //          this,
    //          SLOT( zoomOut() ),
    //          Qt::UniqueConnection
    //          );

    // connect( ui->pushButtonOrig,
    //          SIGNAL( clicked() ),
    //          this,
    //          SLOT( originalSize() ),
    //          Qt::UniqueConnection
    //          );

    // ui->labelImage->setBackgroundRole(QPalette::Base);
    // ui->labelImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    // ui->labelImage->setScaledContents(true);
}

PtngImageWidget::~PtngImageWidget()
{
    delete ui;
}

void PtngImageWidget::zoomIn()
{
    changeScale(1.25);
}

void PtngImageWidget::zoomOut()
{
    changeScale(0.75);
}

void PtngImageWidget::originalSize()
{
    ui->labelImage->adjustSize();
    scale = 1.0;
    // changeScale(1);
}

void PtngImageWidget::changeScale(double factor)
{
    scale *= factor;
    ui->labelImage->resize(scale * ui->labelImage->pixmap(Qt::ReturnByValue).size());
    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);
}

void PtngImageWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void PtngImageWidget::display(const QString &file)
{
    if( inputFile == file ) return;
    inputFile = file;
    ui->labelImage->setPixmap(inputFile);
    ui->labelBanner->setText(inputFile);
    emit inputFileChanged();
}

void PtngImageWidget::setBanner(const QString &banner)
{
    this->banner = banner;
    ui->labelBanner->setText(this->banner);
    emit bannerChanged();
}

QString PtngImageWidget::getBanner()
{
    return(banner);
}
