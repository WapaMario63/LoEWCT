#ifndef THREADS_H
#define THREADS_H

#include <QObject>

class Threads : public QObject
{
    Q_OBJECT
public:
    void runLoginServThread();
    void runGameServThread();

    bool stopLoginServThread;
    bool stopGameServThread;

signals:
    void loggedConsole(QString);
};

#endif // THREADS_H
