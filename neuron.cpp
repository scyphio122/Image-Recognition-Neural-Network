#include "neuron.h"
#include "network.h"
#include <cmath>
extern enum TransportFunction_e transportFunction;

const double beta = 0.6;

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

void Neuron::CreateTargetNeuronConnection(Connection connection)
{
    this->targetNeuronConnection.append(connection);
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

double  Neuron::GetOutput()
{
    return this->output;
}

void Neuron::AllocateMemoryForTargetConnectionsList(uint16_t connectionsNumber)
{
    this->targetNeuronConnection.reserve(connectionsNumber);
}

/**
 * @brief Neuron::CalculateOutput   This function calculates an output of the neuron based on the chosen in MainWindow transport function type
 */
void Neuron::CalculateOutput()
{
    static double x = this->input;

#ifdef    BIPOLAR_SIGMOID_FUNCTION
        this->output = 2/(1 + exp(-beta*x)) - 1;
 #endif
#ifdef  UNIPOLAR_SIGMOID_FUNCTION
        this->output = 1/(1 + exp(-beta*x));
#endif

    return;
}

double Neuron::GetInput()
{
    return this->input;
}
double Neuron::GetOutputDifferential()
{
    return this->outputDifferential;
}

void Neuron::SetOutputDifferential(double value)
{
    this->outputDifferential = value;
}

