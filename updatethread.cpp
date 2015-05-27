#include "updatethread.h"
#include "teacher.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

UpdateThread::UpdateThread()
{

}
UpdateThread::UpdateThread(Teacher* teacher, MainWindow* ui)
{
    this->ui = ui;
    this->teacher = teacher;
}

UpdateThread::~UpdateThread()
{

}
void UpdateThread::run()
{
    /*this->wait(1000);
    do
    {
        ui->UpdateNetworkError();
        ui->UpdateProgressBar();
        ui->update();
        this->usleep(200000);
    }while(this->teacher->GetEntireNetworkError()<this->teacher->GetQualificationThreshold());

    this->quit();
    this->wait(100);*/
    this->teacher->BackPropagationAlgorithm();
    this->quit();
    this->terminate();
}


