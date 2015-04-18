#ifndef COMMONNEURON_H
#define COMMONNEURON_H
#include "neuron.h"
#include <vector>
#include <stdint.h>
#include "layer.h"

class Layer;

class CommonNeuron:public Neuron
{
private:
    double input;
    vector<Connection*> sourceNeuronConnection;

    void ClearSourceNeuronConnection();
public:
    CommonNeuron();
    ~CommonNeuron();
    void SetIndex();
    uint16_t GetIndex();
    void LoadInput();
    void ClearInput();
    void ConnectNeuronsFromPreviousLayer(Layer* previousLayer);
    void CreateSourceNeuronConnection(Connection* connection);
    void ClearConnections();
};

#endif // COMMONNEURON_H
