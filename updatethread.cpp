#include "updatethread.h"
#include "teacher.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
/*UpdateThread::UpdateThread()
{

}*//*
UpdateThread::UpdateThread(Teacher* teacher, Ui::MainWindow* ui)
{
    this->ui = ui;
    this->teacher = teacher
}

UpdateThread::~UpdateThread()
{

}
void UpdateThread::run()
{
    do
    {
        this->ui->UpdateNetworkError();
        this->ui->UpdateProgressBar();
        this->wait(100);
    }while(this->teacher->GetEntireNetworkError()<this->teacher->GetQualificationThreshold());
}

*/
