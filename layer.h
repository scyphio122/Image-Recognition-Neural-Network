#ifndef LAYER_H
#define LAYER_H
#include "neuron.h"
#include "bias.h"
#include "commonneuron.h"
#include <stdint.h>
#include <string>


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
    CommonNeuron* GetNeuronAt(uint16_t neuronIndex);
    Bias* GetBias();
    void ConnectNeuronsBetweenLayers(Layer *thisLayer, Layer *nextLayer, bool connectionWeightRandom_Or_FromFile, std::ifstream *loadToFile);
    uint16_t GetNeuronsNumber();
    bool TestLayersConnections(Layer* thisLayer, Layer* previousLayer);
};

#endif // LAYER_H
