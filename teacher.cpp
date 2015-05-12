#include "teacher.h"
#include <cmath>
#include "neuron.h"
#include "layer.h"
#include "network.h"
Teacher::Teacher()
{
    //  Create the expectedOutput vector
    this->expectedOutput.resize(this->network->GetLayerAt(network->GetLayersNumber()-1)->GetNeuronsNumber());

}

Teacher::~Teacher()
{
    this->expectedOutput.clear();
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

void Teacher::CalculateEntireNetworkError()
{
    double sumOfErrors = 0;
   for(uint16_t i=0; i<network->GetNeuronsNumber(network->GetLayersNumber()-1); i++)
   {
       //   Get the neuron in the last layer
       sumOfErrors += pow((network->GetLayerAt(network->GetLayersNumber()-1)->GetNeuronAt(i)->GetOutput()) - expectedOutput[i], 2);
   }
   entireNetworkError = 0.5*sumOfErrors;
}
