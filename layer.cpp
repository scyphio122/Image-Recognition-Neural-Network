#include "layer.h"

Layer::Layer(uint8_t index, uint16_t neuronsNumber)
{
    CommonNeuron neuron;
    this->SetLayerIndex(index);
    this->neuron.assign(neuronsNumber, neuron);

}

Layer::~Layer()
{

}

void Layer::SetLayerIndex(uint8_t number)
{
    this->index = number;
}

void Layer::ConnectNeuronsBetweenLayers(Layer *thisLayer, Layer *nextLayer)
{
    Connection con;
    //  Go through the neurons in the previous layer
    for(uint16_t i=0; i<thisLayer->neuron.size(); i++)
    {

        for(uint16_t j=0; j<nextLayer->neuron.size(); j++)
        {
            con.RandomizeWeight();
            //  Set the address of the connection to the output neuron
            con.SetNeuronAddress(nextLayer->GetNeuronAt(j));
            //  Create the forward connection
            thisLayer->neuron[i].CreateTargetNeuronConnection(&con);
            //  Set the soutrce neuron address in the connection
            con.SetNeuronAddress(thisLayer->GetNeuronAt(i));
            //  Create the backward connection
            nextLayer->neuron[j].CreateSourceNeuronConnection(&con);
        }
    }
}

CommonNeuron* Layer::GetNeuronAt(uint16_t neuronIndex)
{
    if(neuronIndex < this->neuron.size())
        return &(this->neuron[neuronIndex]);
    else
        return NULL;
}
