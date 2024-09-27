/*
MIT License

Copyright (c) %date% %author%

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
#include <QBrush>
#include <QProgressDialog>
#include "../inc/ptngabstractwidget.hpp"
#include "../inc/global_inc.hpp"

namespace Ui {
class PtngXmlWidget;
}

class  PtngXmlWidget : public QWidget, public PtngAbstractWidget
{
    Q_OBJECT
    Q_PROPERTY(QString banner READ getBanner WRITE setBanner NOTIFY bannerChanged FINAL)

public:
    explicit PtngXmlWidget(QWidget *parent = nullptr);
    ~PtngXmlWidget();

protected slots:
    void displayNmap(QDomDocument *doc, QStandardItemModel *model);
    void displayNmapAxfr(QDomDocument *doc, QStandardItemModel *model);
    void displayDnsrecon(QDomDocument *doc, QStandardItemModel *model);
    void displayNessus(QDomDocument *doc, QStandardItemModel *model, const QString &inputFile);
    void displayMasscan(QDomDocument *doc, QStandardItemModel *model);
    void displaySslScan(QDomDocument *doc, QStandardItemModel *model);
    void displayNikto(QDomDocument *doc, QStandardItemModel *model);
    void displayWapiti(QDomDocument *doc, QStandardItemModel *model);
    void displayOwaspZap(QDomDocument *doc, QStandardItemModel *model);
    void displayMetasploit(QDomDocument *doc, QStandardItemModel *model);
    void displayDgml(QDomDocument *doc, QStandardItemModel *model);

    void showCCMMenu(const QPoint &point);
    void copy(bool checked = false);

private:
    Ui::PtngXmlWidget *ui;
    PtngEnums::SupportedInputTypes type;
    QString banner;
    bool hasFile = false;

signals:
    void bannerChanged();
    void loadCompleted();


    // PtngAbstractWidget interface
public:
    void display(const QString &inputFile) override;
    void setBanner(const QString &newBanner) override;
    QString getBanner() override;
};

