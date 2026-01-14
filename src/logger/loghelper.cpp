#include "loghelper.h"

#include <QChar>
#include <QDateTime>
#include <QIODevice>
#include <QMetaEnum>
#include <QStringLiteral>
#include <QTimeZone>

// Windows specified
#ifdef Q_OS_WIN
#include <io.h>
#endif

// Unix/Linux specified
#ifdef Q_OS_UNIX
#include <unistd.h>
#endif

#include <algorithm>
#include <iostream>
#include <mutex>
#include <tuple>

namespace {
    constexpr const char* _ansiColorStrings[] = {
        "\x1b[30m", // Foreground black
        "\x1b[31m", // Foreground red
        "\x1b[32m", // Foreground green
        "\x1b[33m", // Foreground yellow
        "\x1b[34m", // Foreground blue
        "\x1b[35m", // Foreground magenta
        "\x1b[36m", // Foreground cyan
        "\x1b[37m", // Foreground white
        "\x1b[40m", // Background black
        "\x1b[41m", // Background red
        "\x1b[42m", // Background green
        "\x1b[43m", // Background yellow
        "\x1b[44m", // Background blue
        "\x1b[45m", // Background magenta
        "\x1b[46m", // Background cyan
        "\x1b[47m", // Background white
    };
    constexpr const char* _ansiReset = "\033[0m";

    const QString _msgTypeString[] = {
        QStringLiteral("[CRITICAL]"), QStringLiteral("[DEBUG]"), QStringLiteral("[FATAL]"),
        QStringLiteral("[INFO]"), QStringLiteral("[WARNING]"),
        QStringLiteral("[UNKNOWN]")};

    enum _ansiColorIndex : size_t {
        ForegroundBlack = 0,
        ForegroundRed,
        ForegroundGreen,
        ForegroundYellow,
        ForegroundBlue,
        ForegroundMagenta,
        ForegroundCyan,
        ForegroundWhite,
        BackgroundBlack,
        BackgroundRed,
        BackgroundGreen,
        BackgroundYellow,
        BackgroundBlue,
        BackgroundMagenta,
        BackgroundCyan,
        BackgroundWhite
    };

    const char* _getColorStringPrefix(const QtMsgType type) {
        switch (type) {
            case QtMsgType::QtFatalMsg:
                return _ansiColorStrings[BackgroundRed];
            case QtMsgType::QtCriticalMsg:
                return _ansiColorStrings[ForegroundRed];
            case QtMsgType::QtWarningMsg:
                return _ansiColorStrings[ForegroundYellow];
            case QtMsgType::QtDebugMsg:
                return _ansiColorStrings[ForegroundBlue];
            default: // covers QtInfoMsg and any invalid enums
                return _ansiColorStrings[ForegroundWhite];
        }
    }

    const QString& _getMsgTypeString(const QtMsgType type) {
        switch (type) {
            case QtMsgType::QtFatalMsg:
                return _msgTypeString[2];
            case QtMsgType::QtCriticalMsg:
                return _msgTypeString[0];
            case QtMsgType::QtWarningMsg:
                return _msgTypeString[4];
            case QtMsgType::QtDebugMsg:
                return _msgTypeString[1];
            case QtMsgType::QtInfoMsg:
                return _msgTypeString[3];
            default:
                return _msgTypeString[5];
        }
    }

    auto _getPrefixString(const QtMsgType type) {
        return _getColorStringPrefix(type) % _getMsgTypeString(type) % _ansiReset;
    }

    bool _isATty(FILE* file) {
#ifdef Q_OS_WIN
        return _isatty(fileno(file));
#else
        return isatty(fileno(file));
#endif
    }

    // Default message handler
    void _messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
        QDateTime now = QDateTime::currentDateTime();
        QString colorOutput = _getPrefixString(type)
                              % _ansiColorStrings[ForegroundWhite]
                              % QStringLiteral(" [")
                              % now.toString(Qt::DateFormat::ISODateWithMs)
                              % QStringLiteral("] ")
                              % _ansiReset
                              % msg;
        static QTextStream stdoutStream(stdout, QIODevice::WriteOnly);
        static bool isStdoutTty = _isATty(stdout);
        static std::mutex stdoutMutex;
        {
            std::lock_guard guard{stdoutMutex};
            stdoutStream << colorOutput << '\n';
            if (isStdoutTty) {
                stdoutStream.flush();
            }
        }
        // TODO print context if debug mode is enabled.
    }
} // namespace

void LogHelper::installMessageHandler(QtMessageHandler handler) {
    try {
        qInstallMessageHandler(handler ? handler : _messageHandler);
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to install message handler: [typeid(e).name() => " + std::string(typeid(e).name()) + std::string(e.what()));
    } catch (...) {
        throw std::runtime_error("Failed to install message handler: unknown exception");
    }
}

void LogHelper::operator()(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    _messageHandler(type, context, msg);
}