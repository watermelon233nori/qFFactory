#include "mainwindow.h"
#include "task/taskwindow.h"

#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QtAssert>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()) {
    Q_ASSERT(ui != nullptr);
    ui->setupUi(this);
    setupConnections();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupConnections() {
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(ui->action_Open_File, &QAction::triggered, this, &MainWindow::onOpenFileTriggered);
}

void MainWindow::onOpenFileTriggered() {
    try {
        auto pTaskWindow = new TaskWindow(this);
        qDebug("A TaskWindow was successfully created. TaskWindow address: 0x%p. Parent address: 0x%p", pTaskWindow, this);
        pTaskWindow->setAttribute(Qt::WA_DeleteOnClose);
        pTaskWindow->show();
    } catch (std::exception& ex) {
        QMessageBox::critical(this, "Internal Error", "Failed to create a task window.");
    }
}
