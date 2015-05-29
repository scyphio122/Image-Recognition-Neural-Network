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
    double input;

    void ClearSourceNeuronConnection();

public:
    CommonNeuron();
    virtual ~CommonNeuron();
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
    double      GetInput();
    void        AddToInput(double value);

};

#endif // COMMONNEURON_H
