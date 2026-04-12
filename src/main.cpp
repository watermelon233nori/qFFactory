#include "application.h"
#include "logger/loghelper.h"
#include "mainwindow.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include <QApplication>

int main(int argc, char* argv[]) {
#ifdef Q_OS_WIN
    // Actually steal from KDE/krita/main.cc:MAIN_FN xD
    if (GetACP() == CP_UTF8) {
        SetConsoleOutputCP(CP_UTF8);
    }
#endif

    try {
        LogHelper::installMessageHandler();
    } catch (const std::exception& e) {
        fprintf(stderr, "Failed to install the message handler: %s\n", e.what());
        return EXIT_FAILURE;
    } catch (...) {
        fputs("Failed to install the message handler: unknown exception.\n", stderr);
        return EXIT_FAILURE;
    }

    qDebug("The message handler is installed successfully.");

    std::unique_ptr<Application> app;

    try {
        qDebug("---INITIALIZATION START---");
        app = std::make_unique<Application>(argc, argv);
        qDebug("The app is created successfully.");

        app->showRootWidget();
        qDebug("Show the root window of the app.");

        qDebug("---INITIALIZATION FINISH---");
    } catch (const std::exception& e) {
        qCritical("---INITIALIZATION FAILED---");
        qCritical("Exception: %s", e.what());
        return EXIT_FAILURE;
    } catch (...) {
    }

    qDebug("Start application event loop.");
    auto ret = app->exec();
    qDebug("Finish application event loop.");
    qInfo("Ready to close...");
    return ret;
}
