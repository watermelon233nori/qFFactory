#include "taskwindow.h"

#include "ui_taskwindow.h"

#include <QFileDialog>
#include <QStandardPaths>

TaskWindow::TaskWindow(QWidget* parent) : QDialog{parent} {
    ui->setupUi(this);
    setupConnections();
}

TaskWindow::~TaskWindow() = default;


void TaskWindow::setupConnections() {
    connect(ui->inputFilePushButton, &std::remove_pointer_t<decltype(ui->inputFilePushButton)>::clicked,
            this, &std::remove_pointer_t<decltype(this)>::onInputFileButtonClicked);
}

void TaskWindow::onInputFileButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open a input file...",
                                                    QStandardPaths::standardLocations(QStandardPaths::HomeLocation).front());
    if (!fileName.isEmpty()) {
        ui->inputFileLineEdit->setText(fileName);
    } else {
        qInfo("There's no input file(s) are selected.");
    }
}