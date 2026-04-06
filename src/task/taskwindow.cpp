#include "taskwindow.h"

#include "ui_taskwindow.h"

#include <QFileDialog>
#include <QStandardPaths>

TaskWindow::TaskWindow(QWidget* parent) : QDialog{parent}, ui(std::make_unique<Ui::TaskWindow>()) {
    assert(ui != nullptr);
    ui->setupUi(this);
    setupConnections();
}

TaskWindow::~TaskWindow() = default;

void TaskWindow::setupConnections() {
    connect(ui->inputFilePushButton, &QPushButton::clicked, this, &TaskWindow::onInputFileButtonClicked);
    connect(ui->outputFilePushButton, &QPushButton::clicked, this, &TaskWindow::onOutputFileButtonClicked);
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

void TaskWindow::onOutputFileButtonClicked() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save as...",
                                                    QStandardPaths::standardLocations(QStandardPaths::HomeLocation).front());
    if (!fileName.isEmpty()) {
        ui->outputFileLineEdit->setText(fileName);
    } else {
        qInfo("The output file name are not specified.");
    }
}