#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupConnections();
}

void MainWindow::setupConnections() {
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt, Qt::DirectConnection);
}