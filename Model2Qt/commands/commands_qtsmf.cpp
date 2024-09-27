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

#include "commands.hpp"

/*
    --- String expansions - smf standard ---
    %{STATE_INCLUDES} (states.hpp)
    %(STATE_MACHINE_DECLARATION) (states.hpp)
    %{STATE_DECLARATIONS} (states.hpp)
    %{STATE_DEFINITIONS} (states.hpp)
    %{STATE_SLOT_DECLARATIONS} (StateManager.hpp)
    %{STATE_SLOT_DEFINITIONS}  (StateManager.cpp)
    %{STATE_OBJECT_NAMES} (states.hpp)
    %{STATE_TRANSITIONS} (states.hpp)
    %{STATE_CONNECTIONS} (states.hpp)

    --- String expansions - smf etg ---
*/

void processQtSmfEtg(const QString& inputFile, bool preserveCase, bool clobberExisting , bool useNamespaces);
void processQtSmfStandard(const QString& inputFile, bool preserveCase, bool clobberExisting , bool useNamespaces);

// QString createTransitions( const QList<QDomElement>& states );
// QString createConnections( const QList<QDomElement>& states );

void processQtSmf(const QString& inputFile, bool preserveCase, bool useEtg, bool clobberExisting , bool useNamespaces){
    if( useEtg ){ // Events, transitions and guards
        processQtSmfEtg(inputFile, preserveCase, clobberExisting, useNamespaces);
    }
    else{ // Standard Qt State Machine Framework
        processQtSmfStandard(inputFile, preserveCase, clobberExisting, useNamespaces);
    }
}

void processQtSmfEtg(const QString& inputFile, bool preserveCase, bool clobberExisting , bool useNamespaces){
    qInfo() << "Processing scxml (Qt FSM with events, transitions and guards)" << QDir::toNativeSeparators( inputFile ) << "into Qt QObjects";
    QDomDocument* doc = ModelUtils::VerifiedDomDocument(inputFile);
    Q_ASSERT( doc != nullptr );
    qInfo() << "Scxml doc is OK";

    /*
        --- Containers ---
    */
    QList<QDomElement> states = ModelUtils::DomElementList(doc->elementsByTagName("state"));
    QList<UmlState*> umlStates;

    /*
        --- States and parallels - QDomElement ---
    */
    QString machineInitialState = doc->documentElement().toElement().attribute("initial");
    QString fsmFull = doc->documentElement().toElement().attribute("name");
    QStringList fsmFullSplit = fsmFull.split("-", Qt::SkipEmptyParts);
    QString fsmName;
    QString fsmNamespace;
    if( fsmFullSplit.count() == 1 ){
        fsmName = fsmFullSplit.at(0);
        fsmNamespace = fsmFullSplit.at(0);
    }
    else if( fsmFullSplit.count() == 2 ){
        fsmName = fsmFullSplit.at(0);
        fsmNamespace = fsmFullSplit.at(1);
    }
    qInfo() << "State machine name is:"<< ModelUtils::ToCamelCase( fsmName );
    qInfo() << "FSM namspace is:"<<fsmNamespace;
    qInfo() << "State machine initial (idle) state is:"<< ModelUtils::ToCamelCase( machineInitialState );

    /*
        --- States and parallels - UmlState* ---
    */
    for( auto state : states ){
        UmlState* umlState = UmlStateFactory::createState(state, fsmName, fsmNamespace, useNamespaces);
        if( umlState->hasChildren() ){ // Not interested in pushdown automata
            continue;
        }
        umlStates << umlState;
    }
    qInfo() << "States:"<< states.count();
    // qInfo() << "Number of UmlState objects:"<<umlStates.count();

    /*
        --- Create eventstruct.hpp ---
    */
    QFile etgStructFile( ":/templates/qtsmfetg/etg_struct_hdr.txt" );
    etgStructFile.open(QIODevice::ReadOnly);
    QString etgStructString = etgStructFile.readAll();
    etgStructFile.close();

    QStringList etgEvents;
    etgEvents << "// Custom events";
    for( auto umlState : umlStates ){
        QString etgEvent = QString("\tEnter%1,")
                .arg(umlState->name());
        etgEvents << etgEvent;
    }
    QString allEvents = etgEvents.join("\n\t");
    allEvents += "\n\t\tNumEvents";
    etgStructString.replace("%{EVENT_DEFINITIONS}", allEvents);

    // Write file out
    if( QFileInfo::exists("eventstruct.hpp") && !clobberExisting ) {
        qInfo() << "Refusing to overwrite an existing file.";
    }
    else{
        QFile etgStructOut("eventstruct.hpp");
        if( !etgStructOut.open(QIODevice::WriteOnly) ){
            qInfo() << "Unable to open eventstruct.hpp for writing";
        }
        QTextStream s1( &etgStructOut );
        s1 << etgStructString;
        etgStructOut.close();
    }

    /*
        --- Create eventstransitionsguards.hpp ---
    */
    QFile etgHeaderFile( ":/templates/qtsmfetg/etg_hdr.txt" );
    etgHeaderFile.open(QIODevice::ReadOnly);
    QString etgHeaderString = etgHeaderFile.readAll();
    etgHeaderFile.close();

    // State machine
    etgHeaderString.replace("%(STATE_MACHINE_VARIABLE}", ModelUtils::ToCamelCase( fsmName ) );

    // States
    QStringList etgStates;
    etgStates << "// Custom states";
    for( auto umlState : umlStates ){
        QString stateDecl = QString("QState* %1;").arg(umlState->variableName());
        etgStates << stateDecl;
    }
    QString allStates = etgStates.join("\n");
    etgHeaderString.replace("%{STATES}", allStates);

    // Transitions
    QStringList etgTransitions;
    etgTransitions << "// Custom transitions";
    for( auto umlState : umlStates ){
        QString transitionDecl = QString("EnumTransition* to%1;").arg(umlState->name());
        etgTransitions << transitionDecl;
    }
    QString allTransitions = etgTransitions.join("\n");
    etgHeaderString.replace("%{TRANSITIONS}", allTransitions);

    // Write file out
    if( QFileInfo::exists("eventstransitionsguards.hpp") && !clobberExisting ){
        qInfo() << "Refusing to overwrite an existing file.";
    }
    else{
        QFile etgHeaderOut("eventstransitionsguards.hpp");
        if( !etgHeaderOut.open(QIODevice::WriteOnly) ){
            qInfo() << "Unable to open eventstransitionsguards.hpp for writing";
        }
        QTextStream s2( &etgHeaderOut );
        s2 << etgHeaderString;
        etgHeaderOut.close();
    }

    /*
        --- Create eventstransitionsguards.cpp ---
    */
    QFile etgImplFile( ":/templates/qtsmfetg/etg_impl.txt" );
    etgImplFile.open(QIODevice::ReadOnly);
    QString etgImplString = etgImplFile.readAll();
    etgImplFile.close();

    // State machine
    etgImplString.replace("%(STATE_MACHINE_VARIABLE}", ModelUtils::ToCamelCase( fsmName ) );
    QString setFsmInitialState = QString("%1->setInitialState(%2);")
            .arg(ModelUtils::ToCamelCase( fsmName ))
            .arg( ModelUtils::ToCamelCase( machineInitialState ) );
    etgImplString.replace("%{INITIAL_STATE}", setFsmInitialState );

    // Init states
    etgStates.clear();
    etgStates << "// Custom states";
    for( auto umlState : umlStates ){
        QString entry = QString("%1 = new QState();").arg(umlState->variableName());
        etgStates << entry;
    }
    allStates = etgStates.join("\n\t");
    etgImplString.replace("%{INIT_STATES}", allStates);

    // Add states
    QStringList etgAddStates;
    etgAddStates << "// Add states to the state machine";
    for( auto umlState : umlStates ){
        QString entry = QString("%1->addState(%2);")
                .arg( ModelUtils::ToCamelCase( fsmName ) )
                .arg(umlState->variableName());
        etgAddStates << entry;
    }
    etgImplString.replace("%{ADD_STATES}", etgAddStates.join("\n\t"));

    // Transition objects
    QStringList etgTransitionObjects;
    etgTransitionObjects << "// Init EnumTransition objects";
    for( auto umlState : umlStates ){
        // umlState->variableName() = new EnumTransition(EnumStruct::);
        QString entry = QString("to%1 = new EnumTransition(EnumStruct::Enter%1)")
                .arg(umlState->name());
        etgTransitionObjects << entry;
    }
    etgImplString.replace("%{TRANSITION_OBJECTS}", etgTransitionObjects.join("\n\t"));

    // Transitions
    etgTransitions.clear();
    etgTransitions << "// Transition targets";
    for( auto umlState : umlStates ){
        QString entry = QString("to%1->setTargetState(%1);")
                .arg(umlState->name());
        etgTransitions << entry;
    }
    etgImplString.replace("%{TRANSITION_TARGETS}", etgTransitions.join("\n\t"));

    // State transitions
    etgTransitions.clear();
    etgTransitions << "// QState transition targets";
    for( auto umlState : umlStates ){
        if( umlState->name() == machineInitialState ){
            continue;
        }
        QString entry = QString("%1->addTransition(to%2);")
                .arg(ModelUtils::ToCamelCase(machineInitialState))
                .arg( umlState->name() );
        etgTransitions << entry;
    }
    etgImplString.replace("%{TRANSITION_QSTATES}", etgTransitions.join("\n\t"));

    // Write file out
    if( QFileInfo::exists("eventstransitionsguards.hpp") && !clobberExisting ){
        qInfo() << "Refusing to overwrite an existing file.";
    }
    else{
        QFile etgImplOut("eventstransitionsguards.cpp");
        if( !etgImplOut.open(QIODevice::WriteOnly) ){
            qInfo() << "Unable to open eventstransitionsguards.cpp for writing";
        }
        QTextStream s3( &etgImplOut );
        s3 << etgImplString;
        etgImplOut.close();
    }
}

void processQtSmfStandard(const QString& inputFile, bool preserveCase, bool clobberExisting , bool useNamespaces){
    qInfo() << "Processing scxml (standard Qt FSM)" << QDir::toNativeSeparators( inputFile ) << "into Qt QObjects";
    QDomDocument* doc = ModelUtils::VerifiedDomDocument(inputFile);
    Q_ASSERT( doc != nullptr );
    qInfo() << "Scxml doc is OK";

    /*
        --- Containers ---
    */
    QList<QDomElement> states = ModelUtils::DomElementList(doc->elementsByTagName("state"));
    QList<QDomElement> parallels = ModelUtils::DomElementList(doc->elementsByTagName("parallel"));
    QList<QDomElement> finals = ModelUtils::DomElementList(doc->elementsByTagName("final"));
    QList<QDomElement> allStates;
    QList<UmlState*> umlStates;

    /*
        --- States and parallels - QDomElement ---
    */
    QString machineInitialState = doc->documentElement().toElement().attribute("initial");
    QString fsmFull = doc->documentElement().toElement().attribute("name");
    QStringList fsmFullSplit = fsmFull.split("-", Qt::SkipEmptyParts);
    QString fsmName;
    QString fsmNamespace;
    if( fsmFullSplit.count() == 1 ){
        fsmName = fsmFullSplit.at(0);
        fsmNamespace = fsmFullSplit.at(0);
    }
    else if( fsmFullSplit.count() == 2 ){
        fsmName = fsmFullSplit.at(0);
        fsmNamespace = fsmFullSplit.at(1);
    }
    qInfo() << "State machine name is:"<< ModelUtils::ToCamelCase( fsmName );
    qInfo() << "State machine namspace is:"<<fsmNamespace;
    qInfo() << "State machine initial state is:"<< ModelUtils::ToCamelCase( machineInitialState );

    /*
        --- States and parallels - UmlState* ---
    */
    allStates << states << parallels << finals;
    for( auto state : allStates ){
        UmlState* umlState = UmlStateFactory::createState(state, fsmName, fsmNamespace, useNamespaces);
        umlStates << umlState;
    }
    qInfo() << "States:"<< states.count();
    qInfo() << "Parallels:"<< parallels.count();
    qInfo() << "Final states:"<< finals.count();
    qInfo() << "All state objects:"<<allStates.count();

    /*
        --- Create states.hpp ---
    */
    QFile statesFile( ":/templates/qtsmf/fsm_states.txt" );
    statesFile.open(QIODevice::ReadOnly);
    QString statesFileString = statesFile.readAll();
    statesFile.close();

    // Housekeeping
    statesFileString.replace( "%(STATE_MACHINE_NAME)", ModelUtils::ToCamelCase( fsmName ) );
    QString stateMachineDec = QString("QStateMachine* %1;").arg(fsmName);
    // statesFileString.replace( "%(STATE_MACHINE_DECLARATION)", stateMachineDec );

    // Declarations
    QStringList stateDeclarations;
    stateDeclarations << "// Custom states";
    for( auto umlState : umlStates ){
        QString type = umlState->isFinal() ? "QFinalState" : "QState";
        QString decl = QString("%1* %2;")
                .arg(type)
                .arg(umlState->variableName());
        stateDeclarations << decl;
    }
    QString allStateDeclarations = stateDeclarations.join("\n\t");
    statesFileString.replace("%{STATE_DECLARATIONS}", allStateDeclarations);

    // Definitions
    QStringList stateDefinitions;
    stateDefinitions << "// Custom state definitions";
    for( auto umlState : umlStates ){
        QString param;
        QString type = umlState->isFinal() ? "QFinalState" : "QState";
        if( umlState->parentState() == fsmName ){
            param = ModelUtils::ToCamelCase(fsmName);
        }
        else if( umlState->isParallel() ){
            param = "QState::ParallelStates";
        }
        else{
            param = ModelUtils::ToCamelCase(umlState->parentState());
        }
        QString decl = QString("%1* = new %2(%3);")
                .arg(umlState->variableName())
                .arg(type)
                .arg(param);
        stateDefinitions << decl;
    }
    QString initialStateDefinition = QString("%1->setInitialState(%2);")
            .arg(ModelUtils::ToCamelCase(fsmName))
            .arg(ModelUtils::ToCamelCase(machineInitialState));

    stateDefinitions << initialStateDefinition;
    QString allStateDefinitions = stateDefinitions.join("\n\t");
    statesFileString.replace("%{STATE_DEFINITIONS}", allStateDefinitions);

    // Object names
    QStringList objectNames;
    objectNames << "// Object names";
    for( auto umlState : umlStates ){
        QString objName = QString("%1->setObjectName(\"%1\");").arg(umlState->variableName());
        objectNames << objName;
    }
    QString allObjectNames = objectNames.join("\n\t");
    statesFileString.replace("%{STATE_OBJECT_NAMES}", allObjectNames);

    // Transitions
    QStringList transitions;
    transitions << "// Transitions";
    for( auto umlState : umlStates ){
        for( auto transition : umlState->transitions() ){
            QString trans = QString("%1->addTransition( %1, &QState::finished, %2);")
                    .arg(umlState->variableName())
                    .arg( ModelUtils::ToCamelCase(transition));
            transitions << trans;
        }
    }
    QString allTransitionNames = transitions.join("\n\t");
    statesFileString.replace("%{STATE_TRANSITIONS}", allTransitionNames);

    // Connections
    QStringList connections;
    connections << "// Custom state connections";
    for( auto umlState : umlStates ){
        QString connection = QString("QObject::connect( %1, &QState::entered, stateManager, &StateManager::%1EnteredAction, Qt::QueuedConnection );")
                .arg(umlState->variableName());
        connections << connection;
    }
    QString allConnections = connections.join("\n\t");
    statesFileString.replace("%{STATE_CONNECTIONS}", allConnections);

    // Write file out
    if( QFileInfo::exists("states.hpp") && !clobberExisting ){
        qInfo() << "Refusing to overwrite an existing file.";
    }
    else{
        QFile statesOut("states.hpp");
        if( !statesOut.open(QIODevice::WriteOnly) ){
            qInfo() << "Unable to open states.hpp for writing";
        }
        QTextStream s1( &statesOut );
        s1 << statesFileString;
        statesOut.close();
    }

    /*
        --- Create statemanager.hpp ---
    */
    QFile smHeaderFile( ":/templates/qtsmf/statemanager_hdr.txt" );
    smHeaderFile.open(QIODevice::ReadOnly);
    QString smHeaderString = smHeaderFile.readAll();
    smHeaderFile.close();

    connections.clear();
    connections << "// Custom state slot declarations";
    for( auto umlState : umlStates ){
        QString connection = QString("void %1EnteredAction();")
                .arg(umlState->variableName());
        connections << connection;
    }
    allConnections = connections.join("\n\t");
    smHeaderString.replace("%{STATE_SLOT_DECLARATIONS}", allConnections);

    // Write file out
    if( QFileInfo::exists("statemanager.hpp") && !clobberExisting ){
        qInfo() << "Refusing to overwrite an existing file.";
    }
    else{
        QFile smHeaderOut("statemanager.hpp");
        if( !smHeaderOut.open(QIODevice::WriteOnly) ){
            qInfo() << "Unable to open statemanager.hpp for writing";
        }
        QTextStream s2( &smHeaderOut );
        s2 << smHeaderString;
        smHeaderOut.close();
    }

    /*
        --- Create statemanager.cpp ---
    */
    QFile smImplFile( ":/templates/qtsmf/statemanager_impl.txt" );
    smImplFile.open(QIODevice::ReadOnly);
    QString smImplString = smImplFile.readAll();
    smImplFile.close();

    connections.clear();
    // connections << "// Custom state slot definitions";
    for( auto umlState : umlStates ){
        QString connection = QString("void StateManager::%1EnteredAction(){}")
                .arg(umlState->variableName());
        connections << connection;
    }
    allConnections = connections.join("\n");
    smImplString.replace("%{STATE_SLOT_DEFINITIONS}", allConnections);

    // Write file out
    if( QFileInfo::exists("statemanager.cpp") && !clobberExisting ){
        qInfo() << "Refusing to overwrite an existing file.";
    }
    else{
        QFile smImplOut("statemanager.cpp");
        if( !smImplOut.open(QIODevice::WriteOnly) ){
            qInfo() << "Unable to open statemanager.cpp for writing";
        }
        QTextStream s3( &smImplOut );
        s3 << smImplString;
        smImplOut.close();
    }
}

