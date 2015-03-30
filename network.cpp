#include "network.h"

Network::Network()
{
    layersNumber = 0;

}

Network::~Network()
{

}

void Network::SetLayersNumber(uint8_t number)
{
    this->layersNumber = number;
}

/**
 * @brief Network::SetNeuronsNumber
 *           This function is used to set the @param number of neurons in a specified  @param layer
 * @param layer     -   index of the layer we put neurons number. The input layer has index 0
 * @param number    -   specified amount of neurons
 */
void Network::SetNeuronsNumber(uint8_t layerIndex, uint16_t number)
{
    if(layerIndex < neuronsNumber.size())
    {
        this->neuronsNumber.push_back(number);
    }
    else
    {
        this->neuronsNumber.at(layerIndex) = number;
    }
}
