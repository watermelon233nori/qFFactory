#include "taskwindow.h"

#include "ui_taskwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QStandardPaths>

#include <future>

TaskWindow::TaskWindow(QWidget* parent) : QDialog{parent}, ui(std::make_unique<Ui::TaskWindow>()) {
    assert(ui != nullptr);
    ui->setupUi(this);
    setupConnections();
}

TaskWindow::~TaskWindow() = default;

void TaskWindow::setupConnections() {
    connect(ui->inputFilePushButton, &QPushButton::clicked, this, &TaskWindow::onInputFileButtonClicked);
    connect(ui->outputFilePushButton, &QPushButton::clicked, this, &TaskWindow::onOutputFileButtonClicked);
    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &TaskWindow::onButtonBoxClicked);
}

void TaskWindow::onInputFileButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    QString(),
                                                    QStandardPaths::standardLocations(QStandardPaths::HomeLocation).front());
    if (!fileName.isEmpty()) {
        ui->inputFileLineEdit->setText(fileName);
    } else {
        qInfo("There's no input file(s) are selected.");
    }
}

void TaskWindow::onOutputFileButtonClicked() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    QString(),
                                                    QStandardPaths::standardLocations(QStandardPaths::HomeLocation).front());
    if (!fileName.isEmpty()) {
        ui->outputFileLineEdit->setText(fileName);
    } else {
        qInfo("The output file name are not specified.");
    }
}

void TaskWindow::onButtonBoxClicked(QAbstractButton* button) {
    using namespace Qt::StringLiterals;
    if (button == ui->buttonBox->button(QDialogButtonBox::Apply)) {
        auto execPath = QStandardPaths::findExecutable("ffmpeg");
        QProcess proc;
        if (execPath.isEmpty()) {
            proc.setProgram(execPath);
        }
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Running command");
        msgBox.setStandardButtons(QMessageBox::Ok);
    } else {
    }
}
