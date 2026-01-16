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
#warning Untested
        // TODO I don't have a Linux desktop environment and macOS, so actually I have never test this part of code.
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
