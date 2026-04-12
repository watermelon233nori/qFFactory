#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QtClassHelperMacros>

#include <memory>

class Application final : public QApplication {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Application)
private:
    std::unique_ptr<QWidget> m_rootWidget;

public:
    explicit Application(int& argc, char** argv);
    void showRootWidget();
    ~Application();
};

#endif