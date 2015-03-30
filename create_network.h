#ifndef CREATE_NETWORK_H
#define CREATE_NETWORK_H

#include <QDialog>
#include "mainwindow.h"
#include "network.h"
#include <QAbstractButton>
namespace Ui {
class Create_Network;
}

class Create_Network : public QDialog
{
    Q_OBJECT
private:
    Network* network;

public:
    explicit Create_Network(QWidget *parent = 0, Network *network);
    ~Create_Network();

private slots:
    void on_lE_LiczbaWarstw_returnPressed();

    void on_lE_LiczbaNeuronow_returnPressed();

    void on_bB_Create_clicked(QAbstractButton *button);

private:
    Ui::Create_Network *ui;
};

#endif // CREATE_NETWORK_H
