#include "application.h"

#include "mainwindow.h"

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv)
    , m_rootWidget(new MainWindow) {
}