#include "commonneuron.h"

CommonNeuron::CommonNeuron()
{
    this->input = 0;
    this->ClearOutput();
    this->ClearConnections();
}

CommonNeuron::~CommonNeuron()
{
    this->ClearConnections();
}

void CommonNeuron::ConnectNeuronsFromPreviousLayer(Layer* previousLayer)
{

}
/**
 * @brief CommonNeuron::CreateSourceNeuronConnection    -   This function is called in order to add an connection to the end of the sourceConnectionsList
 * @param connection    -   The pointer to the connection to add
 */
void CommonNeuron::CreateSourceNeuronConnection(Connection* connection)
{
    this->sourceNeuronConnection.append(connection);
}
/**
 * @brief CommonNeuron::ClearSourceNeuronConnection -   This function is called in \fn ClearConnections() and it clears the sourceNeuronConnectionList if it is not empty
 */
void CommonNeuron::ClearSourceNeuronConnection()
{
    if(!this->sourceNeuronConnection.empty())
    {
        this->sourceNeuronConnection.clear();
    }
}

/**
 * @brief CommonNeuron::ClearConnections    -   This function clears both target- and sourceConnections lists which the CommonNeuron contains.
 */
void CommonNeuron::ClearConnections()
{
    this->ClearSourceNeuronConnection();
    this->ClearTargetNeuronConnection();
}

/**
 * @brief CommonNeuron::ClearInput  -   This function is called in the \fn LoadInput() method in order to clear(set to zero) the input of the CommonNeuron which called this method
 */
void CommonNeuron::ClearInput()
{
    this->input = 0;
}

/**
 * @brief CommonNeuron::SetIndex    -   This function is called when the CommonNeuron is created in order to set its index
 * @param index -   The value of the index which will be set
 */
void CommonNeuron::SetIndex(uint16_t index)
{
    this->index = index;
}
/**
 * @brief CommonNeuron::GetIndex    -   This function is called in order to get the index value of the required CommonNeuron
 * @return  The index value of the CommonNeuron which called this method
 */
uint16_t CommonNeuron::GetIndex()
{
    return this->index;
}
/**
 * @brief CommonNeuron::SourceConnectionsSize   -   This function is called to get the size of the sourceConnectionList (number of its objects)
 * @return The size of the SourceConnectionList
 */
uint16_t CommonNeuron::SourceConnectionsSize()
{
    return this->sourceNeuronConnection.size();
}
/**
 * @brief CommonNeuron::GetSourceConnectionAt   -   This function is called in order to get the pointer to the required CommonNeuron
 * @param connectionIndex   -   The index of the required CommonNeuron
 * @return The pointer to the demanded CommonNeuron
 */
Connection* CommonNeuron::GetSourceConnectionAt(uint16_t connectionIndex)
{
    return this->sourceNeuronConnection[connectionIndex];
}
/**
 * @brief CommonNeuron::AllocateMemoryForSourceConnectionList   -   This function is called to reserve specified amount of memory for the SourceConnectionList in order not to reallocate it every time a new connection is added.
 * @param connectionsNumber -   The number of the connection the list will contain
 */

void CommonNeuron::AllocateMemoryForSourceConnectionList(uint16_t connectionsNumber)
{
    this->sourceNeuronConnection.reserve(connectionsNumber);
}

/**
 * @brief CommonNeuron::SourceNeuronConnectionEmpty -   This function checks wheter the list of the sourceConnections is empty. The source connection is the pointer in the higher layer's neurons to the connection between the previousLayer neuron and thisLayer neuron
 * @return  true if empty
 */
bool CommonNeuron::SourceNeuronConnectionEmpty()
{
    return this->sourceNeuronConnection.isEmpty();
}

/**
 * @brief CommonNeuron::LoadInput   -   This function sets the input's value to zero, calculates the combinations of weights and output for each neuron from the previous layer, calculates the sum of them and saves it in the input of the neuron, which called this method. If the calling neuron is in the first (input) layer, it loads directly the value to the input
 */
void CommonNeuron::LoadInput()
{
    //  Clear input of the CommonNeuron
    ClearInput();
    //  If it is the first layer
    if(this->sourceNeuronConnection.isEmpty())
    {
        //  TODO:   Implement loading inputs in the first layers
    }
    else    //  If it isn't the first layer
    {
        //  The input is a sum of multiplications of weights and outputs from the biasNeuron (sourceConnectionIndex == 0) and previousLayer neurons
        for(uint16_t sourceConnectionIndex=0; sourceConnectionIndex<SourceConnectionsSize(); sourceConnectionIndex++)
        {
            this->input += (this->sourceNeuronConnection[sourceConnectionIndex]->GetWeight()*this->sourceNeuronConnection[sourceConnectionIndex]->GetConnectedNeuron()->GetOutput());
        }
    }
}


