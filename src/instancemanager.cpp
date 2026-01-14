#include "instancemanager.h"

#include <QApplication>
#include <QByteArray>

InstanceManager InstanceManager::instance;

InstanceManager& InstanceManager::getInstance() {
    return instance;
}

bool InstanceManager::init() {
    m_server.setSocketOptions(QLocalServer::UserAccessOption);

    auto app = qApp;
    auto listenRes = m_server.listen(app->applicationName());
    if (!listenRes) {
        // Failed to initialize
        qWarning("Failed to create a QtLocalServer: %s", qUtf8Printable(m_server.errorString()));
        return false;
    }

    // Initialization work properly, return true.
    return true;
}

bool InstanceManager::hasAnotherInstance() {
    auto app = qApp;
    m_socket.setServerName(app->applicationName());
    m_socket.connectToServer();
    auto connRes = m_socket.waitForConnected(2000);
    if (connRes) {
        m_socket.disconnect();
        return true;
    }

    // There is no another instance of qFFactory, return false
    return false;
}
