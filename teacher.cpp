#include "teacher.h"
#include <cmath>
#include "neuron.h"
#include "layer.h"
#include "network.h"
#include <iostream>
extern const double beta;
using namespace std;
Teacher::Teacher()
{
    //  Create the expectedOutput vector
   // this->expectedOutput.resize(this->network->GetLayerAt(network->GetLayersNumber()-1)->GetNeuronsNumber());

}

Teacher::~Teacher()
{
    //this->expectedOutput.clear();
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
    double error = (expectedOutput/*[outputNeuron->GetIndex()]*/ - outputNeuron->GetOutput())*TRANSFER_FUNCTION_DIFFERENTIAL(beta, outputNeuron->GetInput());
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
    connection->SetWeight(connectionWeight+weightChange + this->alpha*(connection->GetWeight()-connection->GetPreviousWeight()));
}



void Teacher::CalculateEntireNetworkErrorForCurrentExample()
{
    double sumOfErrors = 0;
   for(uint16_t i=0; i<network->GetNeuronsNumber(network->GetLayersNumber()-1); i++)
   {
       //   Get the neuron in the last layer
       sumOfErrors += pow((network->GetLayerAt(network->GetLayersNumber()-1)->GetNeuronAt(i)->GetOutput()) - expectedOutput/*[i]*/, 2);
   }
   entireNetworkError = 0.5*sumOfErrors;
}

/**
 * @brief Teacher::RandomizeTeachingExample -   This function should be called from the teaching algorithm. Its purpose is to randomize the example which will be loaded in the network.
 * @param exampleTable  -   The pointer to the table containing all the known examples to be taught
 * @return  The pointer to the randomized example
 */
uint8_t Teacher::RandomizeTeachingExample(QVector <QVector<double> > *exampleTable)
{
    return (rand()*871+71)%(exampleTable->size());
}

void Teacher::BackPropagationAlgorithm()
{
    QVector<QVector <double> > example;
    example.resize(5);
    for(uint8_t i=0; i<5; i++)
    {
       example[i].resize(4);
    }

    double entireNetworkErrorForAllExamples;
    teachingCycleCounter = 0;
    qualificationThreshold = 0.000005;
    eta = 0.6;
    alpha = 0.5;

    example[0][0] = 0.95;
    example[0][1] = 0.1;
    example[0][2] = 0.1;
    example[0][3] = 0.1;
    example[1][0] = 1.05;
    example[1][1] = 0.2;
    example[1][2] = 0;
    example[1][3] = 0.1;
    example[2][0] = 0.99;
    example[2][1] = 0.01;
    example[2][2] = 0.1;
    example[2][3] = 0.1;
    example[3][0] = 0.1;
    example[3][1] = 1;
    example[3][2] = 0.1;
    example[3][3] = 0.9;
    example[4][0] = 0.05;
    example[4][1] = 0.95;
    example[4][2] = 0.1;
    example[4][3] = 0.9;

    QVector<double> input;
    input.resize(4);
    //  Get number of teaching examples
    uint16_t exampleSize = example.size();
    do
    {
        entireNetworkErrorForAllExamples = 0;
        do
        {
            //  Choose an example

            uint8_t exampleNumber = this->RandomizeTeachingExample(&example);
            input = example[exampleNumber];
            this->expectedOutput = input.at(3);
            //  Load it in the network
            this->network->LoadNetworkInput(input);
            this->network->CalculateNetworkAnswer();
            CalculateEntireNetworkErrorForCurrentExample();

            //  If an error for the specified example is bigger then qualification threshold then change weights, otherwise skip changes
            if(this->entireNetworkError > qualificationThreshold)
            {
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
                //  Calculate an error after changes of weights
                this->network->CalculateNetworkAnswer();
                CalculateEntireNetworkErrorForCurrentExample();
            }
            else
                continue; // Error when entireNetworkErrorForAllExamples > qualificationThreshold == 4

            cout<< teachingCycleCounter+0<<"  Blad: "<<this->entireNetworkError+0<<" przyklad: "<<exampleNumber+0<<endl;
            entireNetworkErrorForAllExamples += this->entireNetworkError;
            teachingCycleCounter++;

        }while(teachingCycleCounter%(exampleSize) < (uint16_t)(exampleSize-1));

        entireNetworkErrorForAllExamples = entireNetworkErrorForAllExamples/(exampleSize);
        cout<<"\nCalkowity blad sieci dla wszystkich przykladow: "<<entireNetworkErrorForAllExamples+0<<endl;
    }while(entireNetworkErrorForAllExamples > qualificationThreshold && teachingCycleCounter <= 100000);

    cout<<"Koncowa liczba cykli: "<<teachingCycleCounter+0<<endl;
    example.clear();

}

void Teacher::SetNetwork(Network *networkToSet)
{
    this->network = networkToSet;
}
