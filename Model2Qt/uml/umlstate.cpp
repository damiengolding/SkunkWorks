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
#include "umlstate.hpp"

/*
        --- UmlState ---
    */
UmlState::UmlState()
{

}

UmlState::~UmlState()
{

}

#pragma Accessors and mutators {

QString UmlState::name() const
{
    return m_name;
}

QStringList UmlState::transitions() const
{
    return m_transitions;
}

QString UmlState::parentState() const
{
    return m_parentState;
}

QList<UmlState *> UmlState::children() const
{
    return m_children;
}

bool UmlState::isParallel() const
{
    return m_isParallel;
}

bool UmlState::isFinal() const
{
    return m_isFinal;
}

bool UmlState::isState() const
{
    return m_isState;
}

bool UmlState::useNamespace() const
{
    return m_useNamespace;
}

bool UmlState::isPushdown() const
{
    return m_isPushdown;
}

QString UmlState::stateNamespace() const
{
    return m_stateNamespace;
}

QString UmlState::type() const
{
    return m_type;
}

QString UmlState::variableName() const
{
    return m_variableName;
}

#pragma Accessors and mutators }

/*
        --- UmlStateFactory ---
    */
UmlStateFactory::UmlStateFactory()
{

}

UmlStateFactory::~UmlStateFactory()
{

}

UmlState* UmlStateFactory::createState( const QDomElement& fsmElem, const QString& fsmName, const QString& fsmNamespace, bool useNamespace )
{
    UmlState* umlState = new UmlState();
    umlState->m_name =  fsmElem.attribute("id");
    umlState->m_variableName = ModelUtils::ToCamelCase( fsmElem.attribute("id") );

    QDomElement parentElem = fsmElem.parentNode().toElement();
    if( !parentElem.isNull() )
        umlState->m_parentState = parentElem.attribute("id").isEmpty() ? fsmName : parentElem.attribute("id");
    // else
    //     umlState->m_parentState = fsmName;

    if( !fsmNamespace.isEmpty() ){
        umlState->m_stateNamespace = fsmNamespace;
    }
    umlState->m_useNamespace = useNamespace;

    if( fsmElem.tagName() == "state" ){
        umlState->m_isParallel = false;
        umlState->m_isFinal = false;
        umlState->m_isState = true;
        umlState->m_type = "state";
    }
    else if( fsmElem.tagName() == "parallel" ){
        umlState->m_isParallel = true;
        umlState->m_isFinal = false;
        umlState->m_isState = false;
        umlState->m_type = "parallel";
    }
    else if( fsmElem.tagName() == "final" ){
        umlState->m_isParallel = false;
        umlState->m_isFinal = true;
        umlState->m_isState = false;
        umlState->m_type = "final";
    }

    QList<QDomElement> children = ModelUtils::DomElementList( fsmElem.childNodes() );
    // int transCount = 0;
    for( auto child : children ){
        if( child.tagName() == "transition" ){
            umlState->m_transitions << child.attribute("target");
            // ++transCount;
        }
    }
    // qInfo() << "Transitions count for:"<<umlState->m_name << transCount;

    children.clear();
    children = ModelUtils::DomElementList( fsmElem.childNodes() );
    for( auto child : children ){
        if( child.tagName() == "state" || child.tagName() == "final" || child.tagName() == "parallel" ){
            umlState->m_children << UmlStateFactory::createState( child, fsmName, fsmNamespace, useNamespace );
        }
    }
    return( umlState );
}
