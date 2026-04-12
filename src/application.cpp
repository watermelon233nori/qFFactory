#include "application.h"

#include "mainwindow.h"

#include <QtAssert>

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv), m_rootWidget(std::make_unique<MainWindow>()) {
    Q_ASSERT(m_rootWidget != nullptr);
}

void Application::showRootWidget() {
    m_rootWidget->show();
}

Application::~Application() {
}
