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
#include "ptngencdecwidget.hpp"
#include "ui_ptngencdecwidget.h"

PtngEncDecWidget::PtngEncDecWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PtngEncDecWidget)
{
    ui->setupUi(this);
    connect(ui->pushButtonConvert,
            &QPushButton::clicked,
            this,
            &PtngEncDecWidget::convert,
            Qt::UniqueConnection
            );

    connect(ui->textEditInput,
            &QTextEdit::textChanged,
            this,
            &PtngEncDecWidget::autoConvert,
            Qt::UniqueConnection
            );
}

PtngEncDecWidget::~PtngEncDecWidget()
{
    delete ui;
}

void PtngEncDecWidget::convert()
{
    QString input = ui->textEditInput->toPlainText();
    QString output = "";
    switch ( ui->comboBoxConvert->currentIndex() ){
    case 0:{ // Plain to base 64
        QByteArray bytes = input.toLatin1();
        output = bytes.toBase64();
        ui->textEditOutput->setText( output );
        break;
    }
    case 1:{ // Base 64 to plain
        QByteArray bytes = input.toLatin1();
        output = QByteArray::fromBase64( input.toLatin1() );
        ui->textEditOutput->setText( output );
        break;
    }
    case 2:{ // Plain URL to encoded
        // output = QUrl::toPercentEncoding(input.toUtf8() );
        QUrl url( input );
        output = url.toEncoded();
        ui->textEditOutput->setText( output );
        break;
    }
    case 3:{ // Decode URL encoded
        output = QUrl::fromEncoded( input.toUtf8() ).toString();
        ui->textEditOutput->setText( output );
        break;
    }
    // case 2:{ // Plain text through qCompress
    //     QByteArray bytes = input.toLatin1();
    //     output = qCompress(bytes, 9);
    //     ui->textEditOutput->setText( output );
    //     break;
    // }
    // case 3:{ // qCompress back to plain
    //     QByteArray bytes = input.toLatin1();
    //     output = qUncompress(bytes);
    //     ui->textEditOutput->setText( output );
    //     break;
    // }
    }
}

void PtngEncDecWidget::autoConvert()
{
    if( ui->radioButtonConvertOnPaste->isChecked() ){
        convert();
    }
}

void PtngEncDecWidget::display(const QString &file)
{
    // Do nothing - there's no file, it's just an operational widget
}

void PtngEncDecWidget::setBanner(const QString &banner)
{
    // Do nothing - there's no file, it's just an operational widget
}

QString PtngEncDecWidget::getBanner()
{
    // Do nothing - there's no file, it's just an operational widget
    return{};
}
