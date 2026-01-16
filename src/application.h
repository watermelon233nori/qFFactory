#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QPointer>
#include <QtClassHelperMacros>

class Application final : public QApplication {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Application)
private:
    QPointer<QWidget> m_rootWidget;

public:
    explicit Application(int& argc, char** argv);
    void showRootWidget();
    ~Application();
};

#endif