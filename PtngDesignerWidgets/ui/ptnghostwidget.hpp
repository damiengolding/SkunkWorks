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
#include <QFrame>
#include "../inc/ptngabstractwidget.hpp"
#include "../inc/global_inc.hpp"

namespace Ui {
class PtngHostWidget;
}

class PtngHostWidget : public QFrame, public PtngAbstractWidget  // public QWidget, public PtngAbstractWidget
{
    Q_OBJECT

public:
    explicit PtngHostWidget(QWidget *parent = nullptr);
    ~PtngHostWidget();

    enum HostStatus {
        Up,
        Down,
        Indeterminate
    };
    Q_ENUM(HostStatus)

    enum HostType {
        Leaf,
        Subnet,
        Attacker
    };
    Q_ENUM(HostType)

public slots:
    void setDetail( const QString &hostname, const QString &ipAddress, HostStatus status, HostType type );
    void addCategory( const QString &categoryName, const QStringList &categoryMembers);
    void showDetail(bool show);

private:
    Ui::PtngHostWidget *ui;
    bool detailVisible = true;
    QStandardItemModel *model = nullptr;
    QStandardItem *root = nullptr;

    // PtngAbstractWidget interface
public:
    void display(const QString &file) override;
    void setBanner(const QString &banner) override;
    QString getBanner() override;

    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};



