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
#pragma once

#include <QWidget>
#include <QScrollBar>

#include "../inc/global_inc.hpp"
#include "../inc/ptngabstractwidget.hpp"

namespace Ui {
class PtngImageWidget;
}

class PtngImageWidget : public QWidget, public PtngAbstractWidget
{
    Q_OBJECT

public:
    explicit PtngImageWidget(QWidget *parent = nullptr);
    ~PtngImageWidget();

protected slots:
    void zoomIn();
    void zoomOut();
    void originalSize();
    void changeScale( double factor );

private:
    Ui::PtngImageWidget *ui;
    QString banner;
    QString inputFile;
    double scale = 1;

    // PtngAbstractWidget interface
public:
    void display(const QString &file) override;
    void setBanner(const QString &banner) override;
    QString getBanner() override;

signals:
    void bannerChanged();
    void loadCompleted();
    void inputFileChanged();

protected:
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
};

