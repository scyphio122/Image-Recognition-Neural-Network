#include "layer.h"
Layer::Layer()
{

}

Layer::Layer(uint8_t index, uint16_t neuronsNumber)
{
    CommonNeuron neuron;
    this->SetLayerIndex(index);
    this->neuron.resize(neuronsNumber);
}

Layer::~Layer()
{

}

void Layer::SetLayerIndex(uint8_t number)
{
    this->index = number;
}

void Layer::ConnectNeuronsBetweenLayers(Layer *thisLayer, Layer *nextLayer, bool connectionWeightRandom_Or_FromFile)
{
    Connection con;

    //  Connect bias
    for(uint16_t j=0; j<nextLayer->neuron.size(); j++)
    {
        if(connectionWeightRandom_Or_FromFile == CONNECTION_WEIGHT_RANDOM)
            con.RandomizeWeight();
        else
            //  TODO: LOAD WEIGHT FROM FILE


        //  Set the address of the connection to the output neuron in next layer
        con.SetNeuronAddress(nextLayer->GetNeuronAt(j));
        //  Create the forward connection
        thisLayer->biasNeuron.CreateTargetNeuronConnection(&con);
        //  Set the soutrce neuron address in the connection
        con.SetNeuronAddress(&thisLayer->biasNeuron);
        //  Create the backward connection
        nextLayer->neuron[j].CreateSourceNeuronConnection(&con);
    }

    //  Go through the neurons in this layer
    for(uint16_t i=0; i<thisLayer->neuron.size(); i++)
    {
        //  And for each neuron in this layer go through neurons in the next layer
        for(uint16_t j=0; j<nextLayer->neuron.size(); j++)
        {
            if(connectionWeightRandom_Or_FromFile == CONNECTION_WEIGHT_RANDOM)
                con.RandomizeWeight();
            else
                //  TODO: LOAD WEIGHT FROM FILE


            //  Set the address of the connection to the output neuron in next layer
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

uint16_t Layer::GetNeuronsNumber()
{
    return this->neuron.size();
}
