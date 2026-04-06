#include "mainwindow.h"
#include "task/taskwindow.h"

#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
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
        auto p = new TaskWindow(this);
        qDebug("A TaskWindow was successfully created. TaskWindow address: 0x%p. Parent address: 0x%p", p, this);
        p->show();
    } catch (std::exception& ex) {
        QMessageBox::critical(this, "Internal Error", "Failed to create a task window.");
    }
}
