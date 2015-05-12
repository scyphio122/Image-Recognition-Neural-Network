#include "teacher.h"
#include <cmath>
#include "neuron.h"
#include "layer.h"

Teacher::Teacher()
{

}

Teacher::~Teacher()
{

}



/*double Teacher::CalculateWeight(Connection *connection)
{
    return (connection->GetWeight() - alpha*DIFFERENTIAL);
}*/

void Teacher::CalculateLastNeuronError(CommonNeuron *outputNeuron)
{
    outputNeuron->SetOutputDifferential(outputNeuron->GetOutput() - expectedOutput);
}

void Teacher::CalculateOutputDifferential(Neuron* thisNeuron, Layer* nextLayer)
{
    double sum = 0;
    CommonNeuron *neuron;
    for(uint16_t i=0; i<nextLayer->GetNeuronsNumber(); i++)
    {
        neuron = nextLayer->GetNeuronAt(i);
        sum += neuron->GetOutputDifferential()*neuron->GetOutput()*(1-neuron->GetOutput())*thisNeuron->GetConnectionAt(i)->GetWeight();
    }
    thisNeuron->SetOutputDifferential(sum);
}


double Teacher::CalculateWeightDifferential(Neuron* neuron)
{
    return neuron->GetOutput()*(1-neuron->GetOutput())*neuron->GetInput();
}

double Teacher::CalculateWeight(Connection *connection)
{
    //return  connection->GetWeight() - this->alpha*
}
