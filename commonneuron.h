#ifndef COMMONNEURON_H
#define COMMONNEURON_H
#include "neuron.h"
#include <QList>
#include <stdint.h>
#include "layer.h"

class Layer;

class CommonNeuron : public Neuron
{
private:
    QList<Connection*> sourceNeuronConnection;
    uint16_t index;

    void ClearSourceNeuronConnection();

public:
    CommonNeuron();
    ~CommonNeuron();
    void SetIndex(uint16_t index);
    uint16_t GetIndex();   
    void LoadInput_InputLayer(double input);
    void ClearInput();
    void ConnectNeuronsFromPreviousLayer(Layer* previousLayer);
    void CreateSourceNeuronConnection(Connection* connection);
    void ClearConnections();
    uint16_t SourceConnectionsSize();
    Connection* GetSourceConnectionAt(uint16_t connectionIndex);
    void AllocateMemoryForSourceConnectionList(uint16_t connectionsNumber);
    bool SourceNeuronConnectionEmpty();


};

#endif // COMMONNEURON_H
