#ifndef COMMONNEURON_H
#define COMMONNEURON_H
#include "neuron.h"
#include <vector>
#include <stdint.h>

class CommonNeuron:Neuron
{
private:
    uint16_t index;
    double input;
    vector<Connection> connectionFrom;
public:
    CommonNeuron();
    ~CommonNeuron();
    void SetIndex();
    uint16_t GetIndex();
    void LoadInput();
    void ClearInput();
    void ConnectNeuronsFromPreviousLayer();
};

#endif // COMMONNEURON_H
