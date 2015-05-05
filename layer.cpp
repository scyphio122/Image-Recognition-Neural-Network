#include "layer.h"
#include <QString>
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
/**
 * @brief Layer::SetLayerIndex  -   This function is called in the Layer constructor. It is used to set the layers index.   The layers are numbered from zero. The max layer index is 255.
 *
 * @param number
 */
void Layer::SetLayerIndex(uint8_t number)
{
    this->index = number;
}

/**
 * @brief Layer::ConnectNeuronsBetweenLayers    - This function is called to create connections between neurons in specified, adjuscent layers. It should be called inside the CreateNetwork function, after creating all the layers and neurons
 * @param thisLayer     -   The pointer to the "source" layer
 * @param nextLayer     -   The pointer to the "target" layer
 * @param connectionWeightRandom_Or_FromFile    -   The value which informs whether we want to randomize weights or load them from file
 * @param loadToFile    - the pointer to the ifstream which contains the handler to the file where the network parameters are saved. If we randomize the weights, it should be NULL
 */
void Layer::ConnectNeuronsBetweenLayers(Layer *thisLayer, Layer *nextLayer, bool connectionWeightRandom_Or_FromFile, ifstream* loadToFile)
{
    Connection con;

    //  Connect bias
    for(uint16_t j=0; j<nextLayer->neuron.size(); j++)
    {
        if(connectionWeightRandom_Or_FromFile == CONNECTION_WEIGHT_RANDOM)
            con.RandomizeWeight();
        else
        {
            string data;
            con.SetIfstream(" ", loadToFile);
            con.LoadData(data);
            QString qdata = QString::fromStdString(data);
            con.SetWeight(qdata.toDouble());
        }


        //  Set the address of the connection to the output neuron in next layer
        con.SetNeuronAddress(nextLayer->GetNeuronAt(j));
        //  Create the forward connection
        thisLayer->biasNeuron.CreateTargetNeuronConnection(&con);
        //  Create the backward connection
        nextLayer->neuron[j].CreateSourceNeuronConnection(thisLayer->biasNeuron.GetConnectionAt(j));
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
            {
                string data;
                con.SetIfstream(" ", loadToFile);
                con.LoadData(data);
                QString qdata = QString::fromStdString(data);
                con.SetWeight(qdata.toDouble());
            }


            //  Set the address of the connection to the output neuron in next layer
            con.SetNeuronAddress(nextLayer->GetNeuronAt(j));
            //  Create the forward connection
            thisLayer->neuron[i].CreateTargetNeuronConnection(&con);
            //  Create the backward connection
            nextLayer->neuron[j].CreateSourceNeuronConnection(thisLayer->neuron[i].GetConnectionAt(j));
        }
    }
}

/**
 * @brief Layer::GetNeuronAt    -   This function is called to get a pointer to the specified neuron in the layer
 * @param neuronIndex           -   The required neuron index
 * @return Pointer to the required neuron
 */
CommonNeuron* Layer::GetNeuronAt(uint16_t neuronIndex)
{
    if(neuronIndex < this->neuron.size())
        return &(this->neuron[neuronIndex]);
    else
        return NULL;
}
/**
 * @brief Layer::GetBias        -   This function is caller to get the pointer to the bias neuron in the layer
 * @return  The pointer to the bias neuron
 */

Bias* Layer::GetBias()
{
    return &this->biasNeuron;
}

/**
 * @brief Layer::GetNeuronsNumber   -  This function is called to get the number of the commonNeuron's in the layer
 * @return The number of neurons in the layer
 */
uint16_t Layer::GetNeuronsNumber()
{
    return this->neuron.size();
}
