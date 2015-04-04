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
    explicit Create_Network( Network *network, QWidget *parent);
    ~Create_Network();

private slots:
    void on_lE_LiczbaWarstw_returnPressed();

    void on_lE_LiczbaNeuronow_returnPressed();

    void on_pB_Accept_clicked();

    void on_pb_Cancel_clicked();

    void on_pB_Retry_clicked();

private:
    Ui::Create_Network *ui;
};

#endif // CREATE_NETWORK_H
