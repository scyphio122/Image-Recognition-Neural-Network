#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "create_network_dialog.h"
#include "network.h"
#include <QMainWindow>

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
    ~MainWindow();

private slots:
    void DisplayWarning(string text);

    void on_pB_UsunSiec_pressed();

    void on_pB_BudujSiec_clicked();

    void on_pB_SaveNetwork_clicked();


    void on_le_input1_returnPressed();

    void on_lE_input2_returnPressed();

    void on_lE_input3_returnPressed();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
