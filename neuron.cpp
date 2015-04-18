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
