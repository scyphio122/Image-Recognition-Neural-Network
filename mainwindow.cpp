#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "teacher.h"
#include <string>
#include "image.h"
#include <highgui/highgui.hpp>
#include <QWaitCondition>
#include <QCursor>
#include <QValidator>
#include <stdint.h>

extern QVector <double> object;                     // DEBUG

QDoubleValidator *lE_errorThresholdValid;
QDoubleValidator *lE_betaValid;
QDoubleValidator *lE_momentumValid;
QDoubleValidator *lE_etaValid;
QIntValidator    *lE_maxTeachingCounterThreshValid;
QDoubleValidator *lE_expectedOutputValid;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->teacher = new Teacher;
    teacher->SetNetwork(&network);

    image = new Image;
    QLocale local;


    teachingImageCounter = 0;
    lE_errorThresholdValid = new QDoubleValidator (0, 2, 6, ui->lE_networkErrorThreshold);
    lE_betaValid           = new QDoubleValidator   (0, 1, 2, ui->lE_beta);
    lE_momentumValid       = new QDoubleValidator (0, 1, 2, ui->lE_momentum);
    lE_etaValid            = new QDoubleValidator (0, 1, 2, ui->lE_eta);
    lE_maxTeachingCounterThreshValid   = new QIntValidator (1, 4294967295, ui->lE_maxTeacyingCycleNumber);
    lE_expectedOutputValid = new QDoubleValidator (-1, 1, 4, ui->lE_ExpectedOutput);

    ui->lE_ExpectedOutput->setValidator(lE_expectedOutputValid);
    ui->lE_eta->setValidator(lE_etaValid);
    ui->lE_beta->setValidator(lE_betaValid);
    ui->lE_maxTeacyingCycleNumber->setValidator(lE_maxTeachingCounterThreshValid);
    ui->lE_momentum->setValidator(lE_momentumValid);
    ui->lE_networkErrorThreshold->setValidator(lE_errorThresholdValid);

}

MainWindow::~MainWindow()
{
    //delete contour;
    delete image;
    delete teacher;
    delete ui;

    image = NULL;
    //contour = NULL;
    teacher = NULL;

    delete lE_errorThresholdValid;
    delete lE_betaValid;
    delete lE_momentumValid;
    delete lE_etaValid;
    delete lE_maxTeachingCounterThreshValid;
    delete lE_expectedOutputValid;
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
    ui->gB_LoadingImages->setEnabled(false);
    ui->cB_Teaching->setChecked(false);
    ui->gB_teachingParameters->setEnabled(false);
    ui->pB_SaveNetwork->setEnabled(false);
}

void MainWindow::on_pB_BudujSiec_clicked()
{
    Create_Network networkDataDialog(&(this->network), this);
    if(ui->rB_StworzSiecRecznie->isChecked())
    {
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
                ui->cB_Teaching->setEnabled(true);
            }
        }
        else
        {
            DisplayWarning(NETWORK_NOT_LOADED);
            return;
        }
    }
    if(networkDataDialog.GetProceedWithLoading() == true)
    {
        ui->pB_UsunSiec->setEnabled(true);
        ui->pB_BudujSiec->setEnabled(false);
        ui->gB_LoadingImages->setEnabled(true);
        ui->pB_SaveNetwork->setEnabled(true);
        ui->pB_Classify->setEnabled(false);
        ui->cB_Teaching->setEnabled(true);
    }
    else
        return;

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

void MainWindow::on_pB_LoadImages_clicked()
{
    QFileDialog loadDialog;

    ui->pB_startTeaching->setEnabled(false);
    teachingImageCounter = 0;
    if(!imageFileNames.empty())
        imageFileNames.clear();
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
        imageFileNames = loadDialog.selectedFiles();
    if(!imageFileNames.isEmpty())
    {
        string directory = imageFileNames[0].toStdString();
        //LoadImages(directory);
        if(ui->gB_teachingParameters->isEnabled())
            on_pB_nextImage_clicked();
        else
            LoadImages(directory);
    }
    if(!ui->cB_Teaching->isChecked())
         ui->pB_Classify->setEnabled(true);
    else
    {
        ui->pB_nextImage->setEnabled(true);

    }
}

void MainWindow::on_hS_Threshold_valueChanged(int value)
{
     QPixmap kontur;

     if(!image->GetHSV(V_channel).empty())
     {
         image->HandMadeThreshold(image->GetHSV(V_channel), value);


        /* erode(kontury, kontury, 21);
         morphologyEx(kontury, kontury, MORPH_OPEN, 3 );
         medianBlur(kontury, kontury, 3);*/
         image->FindContours();

         image->CalculateHuMoments();
         image->CalculateMalinowskaCoefficient();
         vector <double>huMoments = image->GetHuMoments();
         ui->lE_Hu1->setText(QString::number(huMoments[0]));
         ui->lE_Hu2->setText(QString::number(huMoments[1]));
         ui->lE_Hu3->setText(QString::number(huMoments[2]));
         ui->lE_Hu4->setText(QString::number(huMoments[3]));
         ui->lE_Hu5->setText(QString::number(huMoments[4]));
         ui->lE_Hu6->setText(QString::number(huMoments[5]));
         ui->lE_Hu7->setText(QString::number(huMoments[6]));
         ui->lE_Malinowska->setText(QString::number(image->GetMalinowskaCoefficient()));

         ConvertMat2QPixmap(image->GetContourImage(), kontur);
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

void MainWindow::LoadImages(string directory)
{

    image->SetDirectory(directory);
    image->LoadImage();
    image->Convert2HSV();
    image->AutomaticThreshold(image->GetHSV(V_channel));

    //bitwise_not(contour->GetImage(), contour->GetImage());
    erode(image->GetContourImage(), image->GetContourImage(), 21);
    morphologyEx(image->GetContourImage(), image->GetContourImage(), MORPH_OPEN, 3 );
    medianBlur(image->GetContourImage(), image->GetContourImage(), 3);


    image->FindContours();

    image->CalculateHuMoments();
    image->CalculateMalinowskaCoefficient();
    vector <double>huMoments = image->GetHuMoments();       //  temp
    ui->lE_Hu1->setText(QString::number(huMoments[0]));
    ui->lE_Hu2->setText(QString::number(huMoments[1]));
    ui->lE_Hu3->setText(QString::number(huMoments[2]));
    ui->lE_Hu4->setText(QString::number(huMoments[3]));
    ui->lE_Hu5->setText(QString::number(huMoments[4]));
    ui->lE_Hu6->setText(QString::number(huMoments[5]));
    ui->lE_Hu7->setText(QString::number(huMoments[6]));
    ui->lE_Malinowska->setText(QString::number(image->GetMalinowskaCoefficient()));


    QPixmap obrazWczytany;
    QPixmap kontur;
    ConvertMat2QPixmap(image->GetImage(), obrazWczytany);
    ConvertMat2QPixmap(image->GetContourImage(), kontur);
    ui->lE_originalImage->setPixmap(obrazWczytany);
    ui->lE_Contour->setPixmap(kontur);

    huMoments.clear();  //  clear temp
}

void MainWindow::on_pB_nextImage_clicked()
{

    if(teacher->GetExpectedOutputSize()>= imageFileNames.size())
    {
        if(!ui->pB_startTeaching->isEnabled())
            ui->pB_startTeaching->setEnabled(true);
        return;
    }
    if(teachingImageCounter <imageFileNames.size())
    {
        LoadImages(imageFileNames[teachingImageCounter].toStdString());
        double expectedOutput = ui->lE_ExpectedOutput->text().toDouble();
        teacher->SetImage(this->image);
        this->teacher->AppendTeachingExampleFromTheLoadedImage(expectedOutput);
        teachingImageCounter++;
    }
    else
    {
        if(!ui->pB_startTeaching->isEnabled())
            ui->pB_startTeaching->setEnabled(true);
        teachingImageCounter = 0;
    }
}

void MainWindow::on_lE_ExpectedOutput_returnPressed()
{
    on_pB_nextImage_clicked();
}

void MainWindow::on_pB_startTeaching_clicked()
{
    double value;
    value = ui->lE_momentum->text().toDouble();
    this->teacher->SetMomentum(value);

    value = ui->lE_eta->text().toDouble();
    this->teacher->SetEta(value);

    value = ui->lE_maxTeacyingCycleNumber->text().toULongLong();
    this->teacher->SetMaxTeachingCycleCounter(value);

    value = ui->lE_networkErrorThreshold->text().toDouble();
    this->teacher->SetQualificationError(value);

    this->teacher->BackPropagationAlgorithm();

}

void MainWindow::on_pB_Classify_clicked()
{
    vector <double> input;
    input.resize(this->network.GetNeuronsNumber(0));
    for(uint16_t i=0; i<this->network.GetNeuronsNumber(0)-1;i++)
    {
        input[i] = image->GetHuMoment(i);
    }
    input[network.GetNeuronsNumber(0)-1] = image->GetMalinowskaCoefficient();

    this->network.LoadNetworkInput(input);
    network.CalculateNetworkAnswer();

    this->ui->lE_output->setText(QString::number(network.GetNetworkAnswer()));

}


void MainWindow::on_cB_Teaching_toggled(bool checked)
{
    //  if is checked
    if(checked == true)
    {
        ui->gB_teachingParameters->setEnabled(true);
        ui->pB_Classify->setEnabled(false);
    }
    else
    {
        ui->gB_teachingParameters->setEnabled(false);
        ui->pB_nextImage->setEnabled(false);
    }
    ui->pB_startTeaching->setEnabled(false);
    ui->lE_Contour->clear();
    ui->lE_originalImage->clear();
    ui->lE_Hu1->clear();
    ui->lE_Hu2->clear();
    ui->lE_Hu3->clear();
    ui->lE_Hu4->clear();
    ui->lE_Hu5->clear();
    ui->lE_Hu6->clear();
    ui->lE_Hu7->clear();
    ui->lE_Malinowska->clear();
    ui->lE_output->clear();
}

void MainWindow::on_lE_beta_textChanged(const QString &arg1)
{
    QString text = arg1;
    double value = text.toDouble();
    int pos =  ui->lE_beta->cursorPosition();
    QValidator::State state = ui->lE_beta->validator()->validate(text, pos);
    if(state == QValidator::Invalid || (state == QValidator::Intermediate && (text.toStdString() != "-")))
    {
        ui->lE_beta->backspace();
    }
}

void MainWindow::on_lE_eta_textChanged(const QString &arg1)
{
    QString text = arg1;
    int pos =  ui->lE_eta->cursorPosition();
    QValidator::State state = ui->lE_eta->validator()->validate(text, pos);
    if(state == QValidator::Invalid || (state == QValidator::Intermediate && (text.toStdString() != "-")))
    {
        ui->lE_eta->backspace();
    }
}

void MainWindow::on_lE_momentum_textChanged(const QString &arg1)
{
    QString text = arg1;
    int pos =  ui->lE_momentum->cursorPosition();
    QValidator::State state = ui->lE_momentum->validator()->validate(text, pos);
    if(state == QValidator::Invalid || (state == QValidator::Intermediate && (text.toStdString() != "-")))
    {
        ui->lE_momentum->backspace();
    }
}


void MainWindow::on_lE_networkErrorThreshold_textChanged(const QString &arg1)
{
    QString text = arg1;
    int pos =  ui->lE_networkErrorThreshold->cursorPosition();
    QValidator::State state = ui->lE_networkErrorThreshold->validator()->validate(text, pos);
    if(state == QValidator::Invalid || (state == QValidator::Intermediate && (text.toStdString() != "-")))
    {
        ui->lE_networkErrorThreshold->backspace();
    }
}

void MainWindow::on_lE_maxTeacyingCycleNumber_textChanged(const QString &arg1)
{
    QString text = arg1;
    int pos =  ui->lE_maxTeacyingCycleNumber->cursorPosition();
    QValidator::State state = ui->lE_maxTeacyingCycleNumber->validator()->validate(text, pos);
    if(state == QValidator::Invalid || (state == QValidator::Intermediate && (text.toStdString() != "-")))
    {
        ui->lE_maxTeacyingCycleNumber->backspace();
    }
}


void MainWindow::on_lE_ExpectedOutput_textChanged(const QString &arg1)
{
    QString text = arg1;
    int pos =  ui->lE_ExpectedOutput->cursorPosition();
    QValidator::State state = ui->lE_ExpectedOutput->validator()->validate(text, pos);
    if(state == QValidator::Invalid || (state == QValidator::Intermediate && (text.toStdString() != "-")))
    {
        ui->lE_ExpectedOutput->backspace();
    }
}
