#pragma once
#include <QObject>
#include <QDebug>
#include <QColor>
#include <QFont>
#include <QFile>
#include <QFileInfo>
namespace GoldingsGym::ptng {
class PtngEnums : public QObject
{
    Q_OBJECT
public:
    explicit PtngEnums(QObject* parent = nullptr);
    virtual ~PtngEnums();

    friend QDebug operator<<(QDebug debug, const PtngEnums &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public:
	enum SupportedInputTypes { };
	enum NetworkNodeRoles { };
	enum ProcessorStates { };
	enum IssueSeverity { };
	enum Protocol{ };
	enum NessusPluginFamily { };
	Q_ENUM(SupportedInputTypes);
	Q_ENUM(NetworkNodeRoles);
	Q_ENUM(ProcessorStates);
	Q_ENUM(IssueSeverity);
	Q_ENUM(Protocol);
	Q_ENUM(NessusPluginFamily);
public slots:

signals:

};
} // End of namespace GoldingsGym::ptng
