#include "instancemanager.h"

#include <QApplication>
#include <QByteArray>

#ifdef Q_OS_WIN
// clang-format off
#include <windows.h>
#include <sddl.h>
// clang-format on
#else
#include <unistd.h>
#endif

namespace {
    QString _getCurrentUserIdString() {
#ifdef Q_OS_WIN
        HANDLE hToken = nullptr;
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
            return {};
        }

        // Get the required size of the buffer
        DWORD cbSize = 0;
        GetTokenInformation(hToken, TOKEN_INFORMATION_CLASS::TokenUser, nullptr, 0, &cbSize);
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
            CloseHandle(hToken);
            return {};
        }

        QByteArray buffer(cbSize, 0);
        if (!GetTokenInformation(hToken, TOKEN_INFORMATION_CLASS::TokenUser, buffer.data(), cbSize, &cbSize)) {
            CloseHandle(hToken);
            return {};
        }

        TOKEN_USER* tokenUser = reinterpret_cast<TOKEN_USER*>(buffer.data());
        LPSTR sidString = nullptr;

        if (!ConvertSidToStringSidA(tokenUser->User.Sid, &sidString)) {
            CloseHandle(hToken);
            return {};
        }

        QString sid = QString::fromLocal8Bit(sidString);
        LocalFree(sidString);
        CloseHandle(hToken);
        return sid; // e.g., "S-1-5-21-1234567890-1234567890-1234567890-1001"
#else
        return QString::number(getuid(), 10);
#endif
    }
} // namespace

InstanceManager InstanceManager::instance;

InstanceManager& InstanceManager::getInstance() {
    return instance;
}

bool InstanceManager::init() {
    m_server.setSocketOptions(QLocalServer::UserAccessOption);

    auto app = qApp;
    auto listenRes = m_server.listen(m_serverName);
    if (!listenRes) {
        // Failed to initialize
        qWarning("Failed to create a QLocalServer: %s", qUtf8Printable(m_server.errorString()));
        return false;
    }

    // Initialization work properly, return true.
    return true;
}

bool InstanceManager::hasAnotherInstance() {
    auto app = qApp;
    QLocalSocket sock;
    m_serverName = _getCurrentUserIdString();
    if (!m_serverName.isEmpty()) {
        m_serverName += '/';
    }

    /**
     * Actually I was ready to write the else statement like:
     * 
     * else { m_serverName = app->applicationName(); }
     * 
     * Why I wanna do this? Because I was thinking operator+= would make a deep copy even the QString is null or empty.
     * But I noticed that a deep copy only happens when a QString is not null, also means isNull() == false.
     * 
     * You can check the implementation of QString::append(const QString& str): 
     * https://code.qt.io/cgit/qt/qtbase.git/tree/src/corelib/text/qstring.cpp?h=6.8.2#n3140
     * 
     * What QString &QString::operator+=(const QString &s) do is just call the function that mentioned above.
     * https://code.qt.io/cgit/qt/qtbase.git/tree/src/corelib/text/qstring.h?h=6.8.2#n542
     * 
     * So eventually I use operator+= of QString directly, that's it.
     */
    m_serverName += app->applicationName();
    

    sock.setServerName(m_serverName);
    sock.connectToServer();
    auto connRes = sock.waitForConnected(2000);
    if (connRes) {
        sock.disconnect();
        qDebug("There's another qFFactory instance exist.");
        return true;
    }

    // There is no another instance of qFFactory, return false
    return false;
}
