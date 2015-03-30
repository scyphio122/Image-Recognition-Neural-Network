#include "create_network.h"
#include "ui_create_network.h"


Create_Network::Create_Network(QWidget *parent, Network* network) :
    QDialog(parent),
    ui(new Ui::Create_Network)
{
    ui->setupUi(this);
    QIntValidator lE_layersValidator(1,255, this);
    QIntValidator lE_neuronsValidator(1,65535, this);
    ui->lE_LiczbaWarstw->setValidator(lE_layersValidator);
    ui->lE_LiczbaNeuronow->setValidator(lE_neuronsValidator);

    this->network = network;
}

Create_Network::~Create_Network()
{
    delete ui;
}

void Create_Network::on_lE_LiczbaWarstw_returnPressed()
{
    bool conversion;
    ui->sB_NrWarstwy->setMaximum(ui->lE_LiczbaWarstw->text().toUInt(conversion, 10));
    ui->lE_LiczbaNeuronow->setEnabled(true);
    ui->sB_NrWarstwy->setEnabled(true);
}
