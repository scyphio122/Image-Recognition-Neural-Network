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
    network.ClearAllNeuronsNumber();
    network.SetLayersNumber(0);
    ui->gB_TworzenieSieci->setEnabled(true);
    ui->pB_BudujSiec->setEnabled(true);
    ui->pB_UsunSiec->setEnabled(false);
}



void MainWindow::on_pB_BudujSiec_clicked()
{
    if(ui->rB_StworzSiecRecznie->isChecked())
    {
        Create_Network networkDataDialog(&(this->network), this);
        networkDataDialog.exec();

    }
    else
    {
        //TODO: Wczytywanie sieci z pliku
    }
    if(this->network.GetLayersNumber() != 0)
    {
        ui->pB_UsunSiec->setEnabled(true);
        ui->pB_BudujSiec->setEnabled(false);
        ui->gB_TworzenieSieci->setEnabled(false);
    }

}
