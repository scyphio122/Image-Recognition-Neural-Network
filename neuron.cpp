#include "neuron.h"

Neuron::Neuron()
{

}

Neuron::~Neuron()
{

}
void Neuron::ClearConnection()
{
    this->ClearTargetNeuronConnection();
}


void Neuron::ClearOutput()
{
     this->output = 0;
}

void Neuron::CreateTargetNeuronConnection(Connection *connection)
{
    this->targetNeuronConnection.push_back(*connection);
}

void Neuron::ClearTargetNeuronConnection()
{
    if(!this-targetNeuronConnection.empty())
    {
        this->targetNeuronConnection.clear();
    }
}
uint16_t Neuron::ConnectionsSize()
{
    return this->targetNeuronConnection.size();
}

Connection* Neuron::GetConnectionAt(uint16_t index)
{
    return &(this->targetNeuronConnection[index]);
}

/*void Neuron::ConnectNeuron(CommonNeuron *neuronToConnect, bool connectionWeightRandom_Or_FromFile)
{
    Connection con;
    if(connectionWeightRandom_Or_FromFile == CONNECTION_WEIGHT_RANDOM)
        con.RandomizeWeight();
    else
        //  TODO: LOAD WEIGHT FROM FILE


    //  Set the address of the connection to the output neuron in next layer
    con.SetNeuronAddress(neuronToConnect);
    //  Create the forward connection
    this->CreateTargetNeuronConnection(&con);
    //  Set the soutrce neuron address in the connection
    con.SetNeuronAddress(this);
    //  Create the backward connection
    neuronToConnect->CreateSourceNeuronConnection(&con);

}*/
