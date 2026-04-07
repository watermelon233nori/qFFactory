#ifndef TASKWINDOW_H
#define TASKWINDOW_H

#include <QDialog>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
    class TaskWindow;
}
QT_END_NAMESPACE

class TaskWindow : public QDialog {
    Q_OBJECT

public:
    explicit TaskWindow(QWidget* parent = nullptr);
    ~TaskWindow();

public slots:
    void onInputFileButtonClicked();
    void onOutputFileButtonClicked();
    void onButtonBoxClicked(QAbstractButton* button);

private:
    std::unique_ptr<Ui::TaskWindow> ui;
    void setupConnections();
};

#endif