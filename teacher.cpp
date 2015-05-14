#include "teacher.h"
#include <cmath>
#include "neuron.h"
#include "layer.h"
#include "network.h"
extern const double beta;

Teacher::Teacher()
{
    //  Create the expectedOutput vector
    this->expectedOutput.resize(this->network->GetLayerAt(network->GetLayersNumber()-1)->GetNeuronsNumber());

}

Teacher::~Teacher()
{
    this->expectedOutput.clear();
}

/**
 * @brief Teacher::GetEta   -   This function is used to get the value of eta - the coefficient which configures the teaching speed
 * @return eta coefficienr
 */
double Teacher::GetEta()
{
    return this->eta;
}




void Teacher::CalculateLastNeuronError(CommonNeuron *outputNeuron)
{
    double error = (expectedOutput[outputNeuron->GetIndex()] - outputNeuron->GetOutput())*TRANSFER_FUNCTION_DIFFERENTIAL(beta, outputNeuron->GetInput());
    outputNeuron->SetNeuronError(error);
}

void Teacher::CalculateCommonNeuronError(Neuron* thisNeuron)
{
    double sum = 0;
    for(uint16_t i=0; i<thisNeuron->ConnectionsSize(); i++)
    {
        sum += thisNeuron->GetConnectionAt(i)->GetConnectedNeuron()->GetNeuronError()*thisNeuron->GetConnectionAt(i)->GetWeight();
    }
    sum = sum*TRANSFER_FUNCTION_DIFFERENTIAL(beta, thisNeuron->GetInput());
    thisNeuron->SetNeuronError(sum);
}


void Teacher::ChangeWeight(Connection* connection, Neuron* sourceNeuron)
{
    double weightChange =  this->GetEta()*connection->GetConnectedNeuron()->GetNeuronError()*sourceNeuron->GetOutput();
    double connectionWeight = connection->GetWeight();
    connection->SetWeight(connectionWeight+weightChange);
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

/**
 * @brief Teacher::RandomizeTeachingExample -   This function should be called from the teaching algorithm. Its purpose is to randomize the example which will be loaded in the network.
 * @param exampleTable  -   The pointer to the table containing all the known examples to be taught
 * @return  The pointer to the randomized example
 */
QVector <QVector <double> >* Teacher::RandomizeTeachingExample(QVector <QVector<double> > *exampleTable)
{
    return &(exampleTable[rand()%(exampleTable->size())]);
}

void Teacher::BackPropagationAlgorithm()
{
    QVector<QVector <double> > example;
    example.resize(5);
    for(uint8_t i=0; i<5; i++)
    {
       example[i].resize(3);
    }

    teachingCycleCounter = 0;
    qualificationThreshold = 0.05;
    eta = 0.6;
    example[0][0] = 0.95;
    example[0][1] = 0.1;
    example[0][2] = 0.1;
    example[1][0] = 1.05;
    example[1][1] = 0.2;
    example[1][2] = 0;
    example[2][0] = 0.99;
    example[2][1] = 0.01;
    example[2][2] = 0.1;
    example[3][0] = 0.1;
    example[3][1] = 1;
    example[3][2] = 0.1;
    example[4][0] = 0.05;
    example[4][1] = 0.95;
    example[4][2] = 0.1;
    QVector <double> expOutp;
    expOutp.resize(2);

    expOutp[0] = 0.1;
    expOutp[1] = 0.9;

    do
    {
        //  Choose an example
        QVector <QVector<double> >*input;
        input->resize(1);

        *input = this->RandomizeTeachingExample(&example);
        //  Load it in the network
        this->network->LoadNetworkInput(*input[0]);
        this->network->CalculateNetworkAnswer();
        CalculateEntireNetworkError();
        for(uint16_t outputNeuronIndex=0; outputNeuronIndex<this->network->GetNeuronsNumber(this->network->GetLayersNumber()-1); outputNeuronIndex++)
        {
            CalculateLastNeuronError(this->network->GetLayerAt(this->network->GetLayersNumber()-1)->GetNeuronAt(outputNeuronIndex));
        }
        for(int16_t layerIndex=network->GetLayersNumber()-2; layerIndex>=0; layerIndex--)
        {
            //  BIAS
            CalculateCommonNeuronError(network->GetLayerAt(layerIndex)->GetBias());
            for(uint16_t connectionIndex=0; connectionIndex<this->network->GetLayerAt(layerIndex)->GetBias()->ConnectionsSize(); connectionIndex++)
            {
                ChangeWeight(this->network->GetLayerAt(layerIndex)->GetBias()->GetConnectionAt(connectionIndex), this->network->GetLayerAt(layerIndex)->GetBias());

            }

            for(uint16_t neuronIndex=0; neuronIndex< network->GetNeuronsNumber(layerIndex); neuronIndex++)
            {
                CalculateCommonNeuronError(network->GetLayerAt(layerIndex)->GetNeuronAt(neuronIndex));
                for(uint16_t connectionIndex=0; connectionIndex<this->network->GetLayerAt(layerIndex)->GetNeuronAt(neuronIndex)->ConnectionsSize(); connectionIndex++)
                {
                    ChangeWeight(this->network->GetLayerAt(layerIndex)->GetNeuronAt(neuronIndex)->GetConnectionAt(connectionIndex), this->network->GetLayerAt(layerIndex)->GetNeuronAt(neuronIndex));

                }
            }
        }
        teachingCycleCounter++;
    }while(entireNetworkError>qualificationThreshold || teachingCycleCounter <= 2000);
    example.clear();
}

