#include "network.h"

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
        this->neuronsNumber.at(layerIndex) = number;
    }
}

/**
 * @brief Network::ClearAllNeuronsNumber
 * This function is called in order to clear the neuronsNumber vector. It contains the numbers of neurons in each of the layers
 */
void Network::ClearAllNeuronsNumber()
{
    this->neuronsNumber.clear();
}

void Network::CreateNetwork()
{
    for(uint8_t index=0; index<layersNumber; index++)
    {
        Layer lay(index, this->neuronsNumber[index]);
        layer.push_back(lay);

        if(index>=1)
        {
            //layer[index].ConnectNeuronsBetweenLayers();
        }
    }
}
