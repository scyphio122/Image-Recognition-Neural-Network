#include "commonneuron.h"

CommonNeuron::CommonNeuron()
{
    this->input = 0;
    this->ClearOutput();
    this->ClearConnections();
}

CommonNeuron::~CommonNeuron()
{
    this->ClearConnections();
}

void CommonNeuron::ConnectNeuronsFromPreviousLayer(Layer* previousLayer)
{

}

void CommonNeuron::CreateSourceNeuronConnection(Connection* connection)
{
    this->sourceNeuronConnection.push_back(connection);

}
void CommonNeuron::ClearSourceNeuronConnection()
{
    if(!this->sourceNeuronConnection.empty())
    {
        this->sourceNeuronConnection.clear();
    }
}

void CommonNeuron::ClearConnections()
{
    this->ClearSourceNeuronConnection();
    this->ClearTargetNeuronConnection();
}
void CommonNeuron::SetIndex(uint16_t index)
{
    this->index = index;
}

uint16_t CommonNeuron::GetIndex()
{
    return this->index;
}
