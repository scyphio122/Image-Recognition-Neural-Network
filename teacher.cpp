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

void Teacher::CalculateLastNeuronError(CommonNeuron *outputNeuron, double expectedOutput)
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
    connection->SetWeight(connectionWeight+weightChange + this->momentum*(connection->GetWeight()-connection->GetPreviousWeight()));
}



void Teacher::CalculateEntireNetworkErrorForCurrentExample(double expectedOutput)
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
uint8_t Teacher::RandomizeTeachingExample(vector <vector<double> > *exampleTable)
{
    return (rand()*871+71)%(exampleTable->size());
}

void Teacher::BackPropagationAlgorithm()
{

    double entireNetworkErrorForAllExamples;
    teachingCycleCounter = 0;


    vector<double> input;
    input.resize(this->teachingExamples[0].size());
    //  Get number of teaching examples
    uint16_t examplesNumber = this->teachingExamples.size();
    uint16_t notRejectedExampleCounter = 0;
    do
    {
        entireNetworkErrorForAllExamples = 0;
        do
        {
            //  Choose an example

            uint8_t exampleNumber = this->RandomizeTeachingExample(&this->teachingExamples);
            input = this->teachingExamples[exampleNumber];
            //  Load it in the network
            this->network->LoadNetworkInput(input);
            this->network->CalculateNetworkAnswer();
            CalculateEntireNetworkErrorForCurrentExample(expectedOutput[exampleNumber]);

            //  If an error for the specified example is bigger then qualification threshold then change weights, otherwise skip changes
            if(this->entireNetworkError > qualificationThreshold)
            {
                for(uint16_t outputNeuronIndex=0; outputNeuronIndex<this->network->GetNeuronsNumber(this->network->GetLayersNumber()-1); outputNeuronIndex++)
                {
                    CalculateLastNeuronError(this->network->GetLayerAt(this->network->GetLayersNumber()-1)->GetNeuronAt(outputNeuronIndex), this->expectedOutput[exampleNumber]);
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
                CalculateEntireNetworkErrorForCurrentExample(expectedOutput[exampleNumber]);
            }
            else
                continue;


            entireNetworkErrorForAllExamples += this->entireNetworkError;
            teachingCycleCounter++;
            notRejectedExampleCounter++;
            cout<< teachingCycleCounter+0<<"  Blad: "<<this->entireNetworkError+0<<" przyklad: "<<exampleNumber+0<<endl;
        }while(notRejectedExampleCounter < examplesNumber);

        notRejectedExampleCounter = 0;
        entireNetworkErrorForAllExamples = entireNetworkErrorForAllExamples/(examplesNumber);
        cout<<"\nCalkowity blad sieci dla wszystkich przykladow: "<<entireNetworkErrorForAllExamples+0<<endl;
    }while(entireNetworkErrorForAllExamples > qualificationThreshold && teachingCycleCounter < maxTeachingCycleCounter);


}

void Teacher::SetNetwork(Network *networkToSet)
{
    this->network = networkToSet;
}

void Teacher::SetImage(Image *image)
{
    this->image = image;
}

/**
 * @brief Teacher::AppendTeachingExampleFromTheLoadedImage  -   This function adds the parameters from the image saved in the Teacher::image* field to the teachingExamples vector
 * @param - the value of the expectedValue from MainWindow
 */
void Teacher::AppendTeachingExampleFromTheLoadedImage(double expectedOutput)
{
    //  Create a single vector with input parameters from the image
    vector <double> inputParameters = vector<double>(this->image->GetHuMoments().size()+1);
    //  Load hu moments
    for(unsigned int i=0; i<inputParameters.size()-1; i++)
    {
        inputParameters[i] = this->image->GetHuMoment(i);
    }
    //  Load the Malinowska coefficient
    inputParameters[inputParameters.size()-1] = this->image->GetMalinowskaCoefficient();

    //  Load the input parameters
    this->teachingExamples.push_back(inputParameters);

    //  Set the expected output for the loaded example
    this->expectedOutput.push_back(expectedOutput);


}

uint16_t    Teacher::GetExpectedOutputSize()
{
    return this->expectedOutput.size();
}


void Teacher::SetMaxTeachingCycleCounter(uint32_t    maxTeachingCycleCounterToSet)
{
    this->maxTeachingCycleCounter = maxTeachingCycleCounterToSet;
}

void Teacher::SetMomentum(double momentum)
{
    this->momentum = momentum;
}
void Teacher::SetEta(double eta)
{
    this->eta = eta;
}

void Teacher::SetQualificationError(double qualificationThhresholdToSet)
{
    this->qualificationThreshold = qualificationThhresholdToSet;
}

void Teacher::CalculateProgress(unsigned long long int teachingCounter)
{
    this->progress = (uint8_t)((teachingCounter/this->maxTeachingCycleCounter)*100);
}

uint8_t Teacher::GetProgress()
{
    return this->progress;
}
