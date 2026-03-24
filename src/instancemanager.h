#ifndef INSTANCEMANAGER_H
#define INSTANCEMANAGER_H

#include <QLocalServer>
#include <QLocalSocket>
#include <QObject>
#include <QtClassHelperMacros>

class InstanceManager {
    Q_DISABLE_COPY_MOVE(InstanceManager)
public:
    static InstanceManager& getInstance();
    bool init();
    bool hasAnotherInstance();

private:
    // Single instance
    static InstanceManager instance;

    QLocalServer m_server;
    QString m_serverName;

    InstanceManager() = default;
};

#endif
