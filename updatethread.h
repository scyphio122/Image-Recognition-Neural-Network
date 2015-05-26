#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H
#include "teacher.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

class UpdateThread: public QThread
{
private:
    Teacher* teacher;
    MainWindow* ui;
    void run();
public:
    UpdateThread();
    UpdateThread(Teacher* teacher, Ui::MainWindow* ui);

    ~UpdateThread();
};

#endif // UPDATETHREAD_H
