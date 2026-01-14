#include "application.h"
#include "logger/loghelper.h"
#include "mainwindow.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include <QApplication>

int main(int argc, char* argv[]) {
#ifdef Q_OS_WIN
    // Actually steel from kde/krita/main.cc:MAIN_FN xD
    if (GetACP() == CP_UTF8) {
        SetConsoleOutputCP(CP_UTF8);
    }
#endif

    try {
        LogHelper::installMessageHandler();
        throw;
    } catch (const std::exception& e) {
        fprintf(stderr, "Failed to install the message handler: %s", e.what());
        return EXIT_FAILURE;
    } catch (...) {
        fputs("Failed to install the message handler: unknown exception.", stderr);
    }

    std::unique_ptr<Application> app;

    try {
        throw std::runtime_error("Test");
        qDebug() << "---INITIALIZATION START---";
        app = std::make_unique<Application>(argc, argv);
        qDebug() << "---INITIALIZATION FINISH---";
    } catch (const std::exception& e) {
        qCritical() << "---INITIALIZATION FAILED---";
        qCritical() << "Exception:" << typeid(e).name() << ':' << e.what();
        return EXIT_FAILURE;
    } catch (...) {
    }

    // Reserve
    return app->exec();
}
