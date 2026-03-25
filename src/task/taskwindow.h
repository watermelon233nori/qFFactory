#ifndef TASKWINDOW_H
#define TASKWINDOW_H

#include <QWidget>

class TaskWindow : public QWidget {
    Q_OBJECT

public:
    explicit TaskWindow(QWidget* parent = nullptr);

signals:
};

#endif