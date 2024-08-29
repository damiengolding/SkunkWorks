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

#include "../inc/ptngdgmlwidgetplugin.hpp"
#include "../ui/ptngdgmlwidget.hpp"

PtngDGMLWidgetPlugin::PtngDGMLWidgetPlugin( QObject* parent) : QObject{parent}{}

QString PtngDGMLWidgetPlugin::name() const
{
    return("PtngDgmlWidget");
}

QString PtngDGMLWidgetPlugin::group() const
{
    return("Golding's Gym");
}

QString PtngDGMLWidgetPlugin::toolTip() const
{
    return{};
}

QString PtngDGMLWidgetPlugin::whatsThis() const
{
    return{};
}

QString PtngDGMLWidgetPlugin::includeFile() const
{
    return("ptngdgmlwidget.hpp");
}

QIcon PtngDGMLWidgetPlugin::icon() const
{
    return(QIcon("qrc:/goldings_gym_core_00_white.png"));
}

bool PtngDGMLWidgetPlugin::isContainer() const
{
    return(false);
}

QWidget *PtngDGMLWidgetPlugin::createWidget(QWidget *parent)
{
    return(new PtngDgmlWidget( parent ) );
}

bool PtngDGMLWidgetPlugin::isInitialized() const
{
    return(initialized);
}

void PtngDGMLWidgetPlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);
}

