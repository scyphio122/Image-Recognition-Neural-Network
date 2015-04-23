#include "create_network_dialog.h"
#include "ui_create_network.h"
#include <cstdlib>
#include <QMessageBox>

Create_Network::Create_Network(Network* network, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create_Network)
{
    ui->setupUi(this);
    lE_layersValidator = new QIntValidator(1,255, this);
    lE_neuronsValidator = new QIntValidator(1,65535, this);
    ui->lE_LiczbaWarstw->setValidator(lE_layersValidator);
    ui->lE_LiczbaNeuronow->setValidator(lE_neuronsValidator);

    this->network = network;
}
Create_Network::~Create_Network()
{
    delete lE_layersValidator;
    delete lE_neuronsValidator;
    delete ui;
}

/**
 * @brief Create_Network::on_lE_LiczbaWarstw_returnPressed
 *          This function is used to load the number of layers of the network
 */
void Create_Network::on_lE_LiczbaWarstw_returnPressed()
{
    bool conversion = false;
    uint8_t value = ui->lE_LiczbaWarstw->text().toUInt(&conversion, 10);
    this->network->SetLayersNumber(value);
    ui->sB_NrWarstwy->setMaximum(value);
    ui->lE_LiczbaNeuronow->setEnabled(true);
    ui->sB_NrWarstwy->setEnabled(true);
    ui->lE_LiczbaWarstw->setEnabled(false);
    ui->sB_NrWarstwy->setValue(1);
    ui->lE_LiczbaNeuronow->setFocus();
}
/**
 * @brief Create_Network::on_lE_LiczbaNeuronow_returnPressed
 *          This function is used to load the number of neurons in the layerIndex specified by the (spinBox.Value()-1)
 *          The spinBox.value() is decremented in order to preserve logical order in numbering the layers.
 */
void Create_Network::on_lE_LiczbaNeuronow_returnPressed()
{
        bool conversion = false;
        uint16_t number = ui->lE_LiczbaNeuronow->text().toUInt(&conversion, 10);
        //
        this->network->SetNeuronsNumber(ui->sB_NrWarstwy->value()-1, number);

        if((uint16_t)ui->sB_NrWarstwy->value() < ui->lE_LiczbaWarstw->text().toUInt(&conversion, 10))
        {
            int value = (ui->sB_NrWarstwy->value());
            ui->sB_NrWarstwy->setValue(++value);
            ui->lE_LiczbaNeuronow->selectAll();
        }
        else
        {
            ui->pB_Accept->setEnabled(true);
            ui->pb_Cancel->setEnabled(true);
            ui->pB_Retry->setEnabled(true);
        }
}


void Create_Network::on_pB_Accept_clicked()
{
     this->close();
}


void Create_Network::on_pb_Cancel_clicked()
{
    this->network->ClearAllNeuronsNumber();
    this->network->SetLayersNumber(0);
    this->close();
}


void Create_Network::on_pB_Retry_clicked()
{
    this->network->ClearAllNeuronsNumber();
    this->network->SetLayersNumber(0);
    ui->lE_LiczbaWarstw->setEnabled(true);
    ui->sB_NrWarstwy->setValue(1);
    ui->sB_NrWarstwy->setEnabled(false);
    ui->lE_LiczbaNeuronow->clear();
    ui->lE_LiczbaNeuronow->setEnabled(false);
    ui->pB_Accept->setEnabled(false);
}
