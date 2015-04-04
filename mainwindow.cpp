#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pB_UsunSiec_pressed()
{

}

void MainWindow::on_rB_StworzSiecRecznie_toggled(bool checked)
{
    if(checked)
    {
        Create_Network networkDataDialog(&(this->network), this);
        networkDataDialog.exec();
    }
}
