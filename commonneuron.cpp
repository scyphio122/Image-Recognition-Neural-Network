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
    this->sourceNeuronConnection.append(connection);

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

uint16_t CommonNeuron::SourceConnectionsSize()
{
    return this->sourceNeuronConnection.size();
}

Connection* CommonNeuron::GetSourceConnectionAt(uint16_t connectionIndex)
{
    return this->sourceNeuronConnection[connectionIndex];
}

void CommonNeuron::AllocateMemoryForSourceConnectionList(uint16_t connectionsNumber)
{
    this->sourceNeuronConnection.reserve(connectionsNumber);
}

bool CommonNeuron::SourceNeuronConnectionEmpty()
{
    return this->sourceNeuronConnection.isEmpty();
}
