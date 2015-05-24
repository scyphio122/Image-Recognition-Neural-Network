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
    Network network;
    Image  *image;
    Image  *contour;
    Teacher *teacher;
    ~MainWindow();

private slots:
    void DisplayWarning(string text);

    void ConvertMat2QPixmap(Mat image, QPixmap &pixmap);

    void on_pB_UsunSiec_pressed();

    void on_pB_BudujSiec_clicked();

    void on_pB_SaveNetwork_clicked();


    void on_le_input1_returnPressed();

    void on_lE_input2_returnPressed();

    void on_lE_input3_returnPressed();

    void on_pB_LoadImages_clicked();

    void on_hS_Threshold_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
