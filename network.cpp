#include "network.h"
#include <iostream>

using namespace std;
Network::Network()
{
    layersNumber = 0;

}

Network::~Network()
{

}

/**
 * @brief Network::SetLayersNumber
 * This function is called in order to set the number of layers in the network
 *
 * @param number - the number of the layers to set
 */
void Network::SetLayersNumber(uint8_t number)
{
    this->layersNumber = number;
}

/**
 * @brief Network::GetLayersNumber
 * This function is called in order to get the current number of layers in the network
 *
 * @return The number of layers
 */
uint8_t Network::GetLayersNumber()
{
    return this->layersNumber;
}

/**
 * @brief Network::SetNeuronsNumber
 *           This function is used to set the @param number of neurons in a specified  @param layer
 * @param layer     -   index of the layer we put neurons number. The input layer has index 0
 * @param number    -   specified amount of neurons
 */
void Network::SetNeuronsNumber(uint8_t layerIndex, uint16_t number)
{
    if(layerIndex >= neuronsNumber.size())
    {
        this->neuronsNumber.push_back(number);
    }
    else
    {
        this->neuronsNumber.replace(layerIndex, number);
    }
}

/**
 * @brief Network::ClearAllNeuronsNumber
 * This function is called in order to clear the neuronsNumber QVector. It contains the numbers of neurons in each of the layers
 */
void Network::ClearAllNeuronsNumber()
{
    this->neuronsNumber.clear();
}

/**
 *@brief Network::CreateNetwork     -   This function is called in order to create the network, based on the loaded parameters
 */
void Network::CreateNetwork()
{
    //  Go from first to the last but one layer
    for(uint8_t index=0; index<layersNumber; index++)
    {
        Layer lay(index, this->neuronsNumber[index]);
        //  Create layer and it's neurons
        layer.push_back(lay);
        //  Set indexes of neurons
        for(uint16_t neuronIndex=0; neuronIndex<neuronsNumber[index]; neuronIndex++)
        {
            //  Enumerate the neurons in layer
            layer[index].GetNeuronAt(neuronIndex)->SetIndex(neuronIndex);
        }

    }
    //  Go through all of the layers but last one...
    for(uint8_t index = 0; index<(layersNumber-1); index++)
    {
        // ...and connect neurons between the adjascent two layers
        layer[index].ConnectNeuronsBetweenLayers(&layer[index], &layer[index+1], CONNECTION_WEIGHT_RANDOM);
    }
}

/**
 * @brief Network::SaveNetwork  -   This function saves all the parameters needed to build a neural network in the file in specified directry.
 * @param directory             -   Directory of the file where we want to save the network.
 */
void Network::SaveNetwork(string directory)
{
    string dataToSave;
    this->saveToFile = new ofstream;

    //  Open the file
    SetOfstream(directory, this->saveToFile);

    //  Save layers number
    dataToSave = layersNumber;
    SaveData(dataToSave);
    //  Insert a new line for easier reading
    SaveData("\n;");
    //  Save neurons numbers
    for(uint8_t i=0; i<neuronsNumber.size(); i++)
    {
        dataToSave = neuronsNumber[i];
        SaveData(dataToSave);
    }
    //  Insert a new line for easier reading
    SaveData("\n;");
    //  Save connection's weights
    for(uint8_t layerIndex=0; layerIndex<(layer.size()-1); layerIndex++)
    {
        for(uint16_t neuronIndex=0; neuronIndex<layer[layerIndex].GetNeuronsNumber(); neuronIndex++)
        {
            for(uint16_t connectionIndex=0; connectionIndex<layer[layerIndex].GetNeuronAt(neuronIndex)->ConnectionsSize(); connectionIndex++)
            {
                //  Get weight from specified connection
                dataToSave = layer[layerIndex].GetNeuronAt(neuronIndex)->GetConnectionAt(connectionIndex)->GetWeight();
                //  Save connection's weight
                SaveData(dataToSave);
            }
            //  Insert a new line for easier reading
            SaveData("\n;");
        }
    }
}



void Network::TestNetwork()
{
    cout<<"Liczba warstw: "<<layersNumber<<endl;
    cout<<"########################################"<<endl;
    for(uint8_t i=0; i<layersNumber; i++)
    {
        cout<<"Liczba neuronów w "<<i<<". warstwie wynosi: "<<layer[i].GetNeuronsNumber()<<endl;
    }
    cout<<"#######################################"<<endl;

    for(uint8_t i=0; i<layersNumber-1; i++)
    {
        cout<<"\nWarstwa    "<<i<<"     :"<<endl<<endl;
        for(uint16_t k=0; k<layer[i+1].GetNeuronsNumber(); k++)
        {
            cout<<"Bias połączony z       "<<layer[i+1].GetNeuronAt(k)->GetIndex()<<endl<<endl;
        }


        for(uint16_t j=0; j<layer[i].GetNeuronsNumber(); j++)
        {
            for(uint16_t k=0; k<layer[i+1].GetNeuronsNumber(); k++)
            {
                cout<<"Neuron   "<<layer[i].GetNeuronAt(j)->GetIndex()<<"     polączony z:        "<<layer[i+1].GetNeuronAt(k)->GetIndex()<<endl<<endl;
            }
            cout<<"#######################################"<<endl;

        }
    }

}
