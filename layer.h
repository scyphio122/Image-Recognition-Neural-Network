#ifndef LAYER_H
#define LAYER_H
#include "neuron.h"
#include "bias.h"
#include "commonneuron.h"
#include <stdint.h>



//class CommonNeuron;

class Layer
{
private:
    uint8_t index;
    QVector<CommonNeuron> neuron;
    Bias biasNeuron;
public:
    Layer();
    Layer(uint8_t index, uint16_t neuronsNumber);
    ~Layer();
    void SetLayerIndex(uint8_t number);
    void GetLayerIndex();
    CommonNeuron *GetNeuronAt(uint16_t neuronIndex);
    void ConnectNeuronsBetweenLayers(Layer *thisLayer, Layer *nextLayer, bool connectionWeightRandom_Or_FromFile);
    uint16_t GetNeuronsNumber();
};

#endif // LAYER_H
