#ifndef TASKWINDOW_H
#define TASKWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class TaskWindow;
}
QT_END_NAMESPACE

class TaskWindow : public QWidget {
    Q_OBJECT

public:
    explicit TaskWindow(QWidget* parent = nullptr);

private:
    Ui::TaskWindow* ui;
};

#endif