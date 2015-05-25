#ifndef CREATE_NETWORK_H
#define CREATE_NETWORK_H

#include <QDialog>
#include "mainwindow.h"
#include "network.h"
#include <QAbstractButton>
#include <QValidator>
namespace Ui {
class Create_Network;
}

class Create_Network : public QDialog
{
    Q_OBJECT
private:
    QIntValidator *lE_neuronsValidator;
    QIntValidator *lE_layersValidator;

    Network* network;
    bool    proceedWithLoading;

public:
    explicit Create_Network( Network *network, QWidget *parent);
    bool GetProceedWithLoading();
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
