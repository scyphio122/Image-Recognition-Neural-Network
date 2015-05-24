#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "teacher.h"
#include <string>
#include "image.h"
#include <highgui/highgui.hpp>
#include <QWaitCondition>

extern QVector <double> object;                     // DEBUG

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = new Image;
    contour = new Image;

}

MainWindow::~MainWindow()
{
    delete contour;
    delete image;
    delete ui;

    image = NULL;
    contour = NULL;
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
    loadDialog.setDirectory("C:/Users/Konrad/Desktop/obrazki binarne");

    //  Show the save window and get the filename
    if (loadDialog.exec())
        fileNames = loadDialog.selectedFiles();
    if(!fileNames.isEmpty())
    {
        Mat kontury;
        for(int i=0; i<fileNames.size(); i++)
        {
            string directory = fileNames[i].toStdString();

            image->SetDirectory(directory);
            image->LoadImage();
            image->Convert2HSV();
            contour->SetImage(image->AutomaticThreshold(image->GetHSV(V_channel)));

            //bitwise_not(contour->GetImage(), contour->GetImage());
            erode(contour->GetImage(), contour->GetImage(), 21);
            morphologyEx(contour->GetImage(), contour->GetImage(), MORPH_OPEN, 3 );
            medianBlur(contour->GetImage(), contour->GetImage(), 3);


            contour->FindContours(kontury);
            contour->SetImage(kontury);

            contour->CalculateHuMoments();
            contour->CalculateMalinowskaCoefficient();
            vector <double>huMoments = contour->GetHuMoments();
            ui->lE_Hu1->setText(QString::number(huMoments[0]));
            ui->lE_Hu2->setText(QString::number(huMoments[1]));
            ui->lE_Hu3->setText(QString::number(huMoments[2]));
            ui->lE_Hu4->setText(QString::number(huMoments[3]));
            ui->lE_Hu5->setText(QString::number(huMoments[4]));
            ui->lE_Hu6->setText(QString::number(huMoments[5]));
            ui->lE_Hu7->setText(QString::number(huMoments[6]));
            ui->lE_Malinowska->setText(QString::number(contour->GetMalinowskaCoefficient()));


            QPixmap obrazWczytany;
            QPixmap kontur;
            ConvertMat2QPixmap(image->GetImage(), obrazWczytany);
            ConvertMat2QPixmap(contour->GetImage(), kontur);
            ui->lE_originalImage->setPixmap(obrazWczytany);
            ui->lE_Contour->setPixmap(kontur);

            huMoments.clear();
        }
    }
}

void MainWindow::on_hS_Threshold_valueChanged(int value)
{
     QPixmap kontur;
     Mat kontury;

     if(!image->GetHSV(V_channel).empty())
     {
         HandMadeThreshold(image->GetHSV(V_channel), kontury, value);


        /* erode(kontury, kontury, 21);
         morphologyEx(kontury, kontury, MORPH_OPEN, 3 );
         medianBlur(kontury, kontury, 3);*/
         contour->SetImage(kontury);
         contour->FindContours(kontury);

         contour->CalculateHuMoments();
         contour->CalculateMalinowskaCoefficient();
         vector <double>huMoments = contour->GetHuMoments();
         ui->lE_Hu1->setText(QString::number(huMoments[0]));
         ui->lE_Hu2->setText(QString::number(huMoments[1]));
         ui->lE_Hu3->setText(QString::number(huMoments[2]));
         ui->lE_Hu4->setText(QString::number(huMoments[3]));
         ui->lE_Hu5->setText(QString::number(huMoments[4]));
         ui->lE_Hu6->setText(QString::number(huMoments[5]));
         ui->lE_Hu7->setText(QString::number(huMoments[6]));
         ui->lE_Malinowska->setText(QString::number(contour->GetMalinowskaCoefficient()));

         ConvertMat2QPixmap(kontury, kontur);
         ui->lE_Contour->setPixmap(kontur);

     }
}

/**
 * @brief MainWindow::ConvertMat2QPixmap -   This function is called in order to convert the Mat image to Pixmap
 * @param image                     -   The image to convert (input)
 * @param pixmap                    -   The pixmap where the image will be stored (output)
 */
void MainWindow::ConvertMat2QPixmap(Mat image, QPixmap &pixmap)
{
     Mat temp;
     image.copyTo(temp);

     if(!temp.empty())
     {
         if(image.rows > 240 || image.cols > 320)
             cv::resize(image, temp, Size(320, 240), 0,0);
     }


     QImage imageqt;
     imageqt.fill(qRgba(0,0,0,0));
    //  If the image is colourer (?)
    if(image.channels() == 3)
    {
         imageqt = QImage(temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
         imageqt = imageqt.convertToFormat(QImage::Format_RGBA8888);
    }
    else    //  If the image is gray-scaled
        imageqt = QImage(temp.data, temp.cols, temp.rows, temp.step, QImage::Format_Mono);

    pixmap = QPixmap::fromImage(imageqt);
}
