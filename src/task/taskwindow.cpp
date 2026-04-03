#include "taskwindow.h"

#include "ui_taskwindow.h"

TaskWindow::TaskWindow(QWidget* parent)
    : QWidget{parent} {
}

void TaskWindow::setupConnections() {
    connect(ui->inputFilePushButton, &QPushButton::clicked, this, &TaskWindow::onInputFileButtonClicked);
}

void TaskWindow::onInputFileButtonClicked() {
    // TODO
}