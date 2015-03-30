#ifndef LAYER_H
#define LAYER_H
#include "neuron.h"
#include "bias.h"
#include <stdint.h>
class Layer
{
private:
    uint8_t index;
    vector<Neuron> neuron;
    Bias biasNeuron;
public:

    Layer();
    ~Layer();
    void SetLayerIndex();
    void GetLayerIndex();
    Neuron* GetNeuronAt(uint8_t layer, uint16_t neuron);
    void ConnectNeuronsBetweenLayers();

};

#endif // LAYER_H
