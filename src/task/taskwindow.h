#ifndef TASKWINDOW_H
#define TASKWINDOW_H

#include <QWidget>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
    class TaskWindow;
}
QT_END_NAMESPACE

class TaskWindow : public QWidget {
    Q_OBJECT

public:
    explicit TaskWindow(QWidget* parent = nullptr);
    void setupConnections();

private:
    std::unique_ptr<Ui::TaskWindow> ui;

    
};

#endif