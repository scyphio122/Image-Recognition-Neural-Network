#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

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
        string dir;
        dir = "C:/Users/Konrad/Desktop/network.txt";
        this->network.LoadNetwork(dir.c_str());
    }
    if(this->network.GetLayersNumber() != 0)
    {
        ui->pB_UsunSiec->setEnabled(true);
        ui->pB_BudujSiec->setEnabled(false);
        ui->gB_TworzenieSieci->setEnabled(false);
    }

}

void MainWindow::on_pB_SaveNetwork_clicked()
{
    QFileDialog saveDialog;
    QStringList fileNames;

    //  The ability to choose both existing and non-existing files
    saveDialog.setFileMode(QFileDialog::AnyFile);
    //  The AcceptButton is Save button
    saveDialog.setAcceptMode(QFileDialog::AcceptSave);
    //  Show only .txt files
    saveDialog.setNameFilter("Network(*.txt)");
    //  Show detailed description of files
    saveDialog.setViewMode(QFileDialog::Detail);
    //  Set directory to C:/Users/Konrad/Desktop/
    saveDialog.setDirectory("C:/Users/Konrad/Desktop/");

    //  Show the save window and get the filename
    if (saveDialog.exec())
        fileNames = saveDialog.selectedFiles();

    //  Save the network
    this->network.SaveNetwork(fileNames[0].toStdString());


}
