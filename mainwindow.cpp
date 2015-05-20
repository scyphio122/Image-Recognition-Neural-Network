#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "teacher.h"
#include <string>
#include "image.h"
#include <highgui/highgui.hpp>
extern QVector <double> object;                     // DEBUG

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

void MainWindow::DisplayWarning(string text)
{
    QMessageBox warning;
    warning.setText(QString::fromStdString(text));
    warning.setIcon(QMessageBox::Information);

    warning.exec();
    return;
}

void MainWindow::on_pB_UsunSiec_pressed()
{
    this->network.DeleteNetwork();
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
        QFileDialog loadDialog;
        QStringList fileNames;
        loadDialog.setParent(this);
        //  The ability to choose both existing and non-existing files
        loadDialog.setFileMode(QFileDialog::AnyFile);
        //  The AcceptButton is Save button
        loadDialog.setAcceptMode(QFileDialog::AcceptOpen);
        //  Show only .txt files
        loadDialog.setNameFilter("Network(*.txt)");
        //  Show detailed description of files
        loadDialog.setViewMode(QFileDialog::Detail);
        //  Set directory to C:/Users/Konrad/Desktop/
        loadDialog.setDirectory("C:/Users/Konrad/Desktop/");

        //  Show the save window and get the filename
        if (loadDialog.exec())
            fileNames = loadDialog.selectedFiles();
        if(!fileNames.isEmpty())
        {
            this->network.LoadNetwork(fileNames[0].toStdString().c_str());
            if(this->network.GetLayersNumber() != 0)
            {
                ui->pB_UsunSiec->setEnabled(true);
                ui->pB_BudujSiec->setEnabled(false);
                ui->gB_TworzenieSieci->setEnabled(false);
            }
        }
        else
            DisplayWarning(NETWORK_NOT_LOADED);
    }
    Teacher teacher;
    teacher.SetNetwork(&network);
    teacher.BackPropagationAlgorithm();

}

void MainWindow::on_pB_SaveNetwork_clicked()
{
    QFileDialog saveDialog;
    QStringList fileNames;
    saveDialog.setParent(this);
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

    if(!fileNames.isEmpty())
    {
        //  Save the network
        this->network.SaveNetwork(fileNames[0].toStdString());
    }
    else
        DisplayWarning(NETWORK_NOT_SAVED);
}

void MainWindow::on_le_input1_returnPressed()
{
    object[0] = this->ui->le_input1->text().toDouble();
}

void MainWindow::on_lE_input2_returnPressed()
{
    object[1] = this->ui->lE_input2->text().toDouble();
}

void MainWindow::on_lE_input3_returnPressed()
{
    object[2] = this->ui->lE_input3->text().toDouble();
    this->network.LoadNetworkInput(object);
    this->network.CalculateNetworkAnswer();
    QString output = QString::number(this->network.GetLayerAt(2)->GetNeuronAt(0)->GetOutput());
    this->ui->lE_output->setText((output));
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog loadDialog;
    QStringList fileNames;
    loadDialog.setParent(this);
    //  The ability to choose both existing and non-existing files
    loadDialog.setFileMode(QFileDialog::ExistingFiles);
    //  The AcceptButton is Save button
    loadDialog.setAcceptMode(QFileDialog::AcceptOpen);
    //  Show only .txt files
    loadDialog.setNameFilter("Image(*.jpg *jpeg)");
    //  Show detailed description of files
    loadDialog.setViewMode(QFileDialog::Detail);
    //  Set directory to C:/Users/Konrad/Desktop/
    loadDialog.setDirectory("C:/Users/Konrad/Desktop/");

    //  Show the save window and get the filename
    if (loadDialog.exec())
        fileNames = loadDialog.selectedFiles();
    if(!fileNames.isEmpty())
    {
        Image obraz;
        Image binarnyObraz;
        Mat kontury;
        for(int i=0; i<fileNames.size(); i++)
        {
            string directory = fileNames[i].toStdString();
            vector<vector <Point> > contours;
            obraz.SetDirectory(directory);
            obraz.LoadImage();
            obraz.Convert2HSV();
            binarnyObraz.SetImage(obraz.AutomaticThreshold(obraz.GetHSV(V_channel)));
            contours = binarnyObraz.FindContours(kontury);
            binarnyObraz.SetImage(kontury);
            QPixmap obrazWczytany;
            QPixmap kontur;
            obraz.ConvertMat2QPixmap(obraz.GetImage(), obrazWczytany);
            binarnyObraz.ConvertMat2QPixmap(binarnyObraz.GetImage(), kontur);

            ui->label_8->setPixmap(obrazWczytany);
            ui->label_7->setPixmap(kontur);
            if(getchar() == 27)
                break;
        }
    }
}
