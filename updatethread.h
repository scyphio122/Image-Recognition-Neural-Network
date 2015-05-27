#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H
#include "teacher.h"

#include <QThread>

class MainWindow;
class UpdateThread: public QThread
{
private:
    Teacher* teacher;
    MainWindow* ui;
    void run();
public:
    UpdateThread();
    UpdateThread(Teacher* teacher, MainWindow *ui);

    ~UpdateThread();
};

#endif // UPDATETHREAD_H
