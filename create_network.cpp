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

/**
 * @brief Create_Network::on_lE_LiczbaWarstw_returnPressed
 *          This function is used to load the number of layers of the network
 */
void Create_Network::on_lE_LiczbaWarstw_returnPressed()
{
    bool conversion = false;
    uint16_t value = ui->lE_LiczbaWarstw->text().toUInt(conversion, 10);
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
        uint16_t number = ui->lE_LiczbaNeuronow->text().toUInt(conversion, 10);
        //
        this->network->SetNeuronsNumber(ui->sB_NrWarstwy->value()-1, number);

        if(ui->sB_NrWarstwy->value()< ui->lE_LiczbaWarstw->text().toUInt(conversion, 10))
        {
            ui->sB_NrWarstwy->setValue(++ui->sB_NrWarstwy->value());
            ui->lE_LiczbaNeuronow->selectAll();
        }
        else
        {
            ui->bB_Create->setEnabled(true);
        }
}

void Create_Network::on_bB_Create_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton stdButton = ui->bB_Create->standardButton(button);
    switch (stdButton)
    {
    case QDialogButtonBox::Ok:
    {
       ~Create_Network();
    }
    case QDialogButtonBox::Cancel:
    {
        this->network->ClearAllNeuronsNumber();
        this->network->SetLayersNumber(NULL);
        ~Create_Network();
    }
    case QDialogButtonBox::Reset:
    {
        this->network->ClearAllNeuronsNumber();
        this->network->SetLayersNumber(NULL);
        ui->lE_LiczbaWarstw->setEnabled(true);
        ui->sB_NrWarstwy->setValue(1);
        ui->sB_NrWarstwy->setEnabled(false);
        ui->lE_LiczbaNeuronow->setText();
        ui->lE_LiczbaNeuronow->setEnabled(false);
        ui->bB_Create->setEnabled(false);
    }
}
