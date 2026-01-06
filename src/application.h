#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QtClassHelperMacros>

class Application final : public QApplication {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Application)
public:
    explicit Application(int& argc, char** argv);
};

#endif