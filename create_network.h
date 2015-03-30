#ifndef CREATE_NETWORK_H
#define CREATE_NETWORK_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Create_Network;
}

class Create_Network : public QDialog
{
    Q_OBJECT
private:
    MainWindow* window;

public:
    explicit Create_Network(QWidget *parent = 0, MainWindow* window);
    ~Create_Network();

private slots:
    void on_lE_LiczbaWarstw_returnPressed();

private:
    Ui::Create_Network *ui;
};

#endif // CREATE_NETWORK_H
