#include "neuron.h"
#include "network.h"
#include <cmath>
//extern enum TransportFunction_e transportFunction;

extern const double beta;

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
 * @brief CommonNeuron::LoadInput_MiddleLayer   -   This function adds the calculated neuron output multiplied by the connection weight, to the inputs of the neurons pointed by the targetNeuron connections.
 */
void Neuron::LoadSignalInNextNeurons(double signal)
{
    CommonNeuron* connectedNeuron;
    //  The input is a sum of each neuron is multiplication of weight and outputs from the biasNeuron (sourceConnectionIndex == 0) and previousLayer neurons
    for(uint16_t targetConnectionIndex=0; targetConnectionIndex<this->ConnectionsSize(); targetConnectionIndex++)
    {
        connectedNeuron = dynamic_cast<CommonNeuron*>(this->targetNeuronConnection[targetConnectionIndex].GetConnectedNeuron());
        if(connectedNeuron != NULL)
            connectedNeuron->AddToInput(this->targetNeuronConnection[targetConnectionIndex].GetWeight()*signal);
    }
}

/**
 * @brief Neuron::CalculateOutput   This function calculates an output of the neuron based on the chosen in MainWindow transport function type
 */
void Neuron::CalculateOutput()
{
    CommonNeuron* neuron = NULL;
    double x;
    Bias* bias = dynamic_cast<Bias*>(this);
    if(bias == NULL)
    {
        neuron = dynamic_cast<CommonNeuron*>(this);
        x = neuron->GetInput();
    }
    else
        x = bias->GetInput();


#ifdef    BIPOLAR_SIGMOID_FUNCTION
        this->output = 2/(1 + exp(-beta*x)) - 1;
 #endif
#ifdef  UNIPOLAR_SIGMOID_FUNCTION
        this->output = 1/(1 + exp(-beta*x));
#endif
    this->LoadSignalInNextNeurons(this->output);
    return;
}


double Neuron::GetNeuronError()
{
    return this->neuronError;
}

void Neuron::SetNeuronError(double value)
{
    this->neuronError = value;
}

