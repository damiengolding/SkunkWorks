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

#include "../inc/ptngimagewidgetplugin.hpp"
#include "../ui/ptngimagewidget.hpp"

PtngImageWidgetPlugin::PtngImageWidgetPlugin( QObject* parent) : QObject{parent}{}

QString PtngImageWidgetPlugin::name() const
{
    return("PtngImageWidget");
}

QString PtngImageWidgetPlugin::group() const
{
    return("Golding's Gym");
}

QString PtngImageWidgetPlugin::toolTip() const
{
    return{};
}

QString PtngImageWidgetPlugin::whatsThis() const
{
    return{};
}

QString PtngImageWidgetPlugin::includeFile() const
{
    return("ptngimagewidget.hpp");
}

QIcon PtngImageWidgetPlugin::icon() const
{
    return(QIcon("qrc:/goldings_gym_core_00_white.png"));
}

bool PtngImageWidgetPlugin::isContainer() const
{
    return(false);
}

// TODONOW
QWidget *PtngImageWidgetPlugin::createWidget(QWidget *parent)
{
    // MUST use parent
    // E.g. new MyWidget(parent) or everything will break
    return( new PtngImageWidget(parent) );
}

bool PtngImageWidgetPlugin::isInitialized() const
{
    return(initialized);
}

void PtngImageWidgetPlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);
}

