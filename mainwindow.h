#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "create_network_dialog.h"
#include "network.h"
#include <QMainWindow>
#include "image.h"
#include "teacher.h"


#define NETWORK_NOT_SAVED   "Sieć nie została zapisana."
#define NETWORK_NOT_LOADED  "Sieć nie została wczytana."

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Network *network;
    Image  *image;
    Teacher *teacher;
    QStringList imageFileNames;
    uint16_t    teachingImageCounter;
    void UpdateProgressBar();
    void UpdateNetworkError();
    void GetNetworkTeacherImage(Network *network, Teacher* teacher, Image* image);
    ~MainWindow();

private slots:
    void DisplayWarning(string text);

    void ConvertMat2QPixmap(Mat image, QPixmap &pixmap);
    void LoadImages(string directory);


    void on_pB_UsunSiec_pressed();

    void on_pB_BudujSiec_clicked();

    void on_pB_SaveNetwork_clicked();

    void on_pB_LoadImages_clicked();

    void on_hS_Threshold_valueChanged(int value);

    void on_pB_nextImage_clicked();

    void on_lE_ExpectedOutput_returnPressed();

    void on_pB_startTeaching_clicked();

    void on_pB_Classify_clicked();

    void on_cB_Teaching_toggled(bool checked);


    void on_lE_beta_textChanged(const QString &arg1);

    void on_lE_eta_textChanged(const QString &arg1);

    void on_lE_momentum_textChanged(const QString &arg1);

    void on_lE_networkErrorThreshold_textChanged(const QString &arg1);

    void on_lE_maxTeacyingCycleNumber_textChanged(const QString &arg1);

    void on_lE_ExpectedOutput_textChanged(const QString &arg1);




    void on_lE_ObjectName_returnPressed();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
