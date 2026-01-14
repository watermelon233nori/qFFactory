#ifndef LOGHELPER_H
#define LOGHELPER_H

#include <QtLogging>

class LogHelper {
    Q_DISABLE_COPY_MOVE(LogHelper)
public:
    static void installMessageHandler(QtMessageHandler handler = nullptr);

    // Use this logger directly. (Only use this when Qt logging system down)
    void operator()(QtMsgType, const QMessageLogContext&, const QString&);

    LogHelper() = default;
};

#endif