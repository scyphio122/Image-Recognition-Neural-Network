#ifndef NETWORK_H
#define NETWORK_H

#include "layer.h"
#include <vector>

using std::vector;

class Network
{
private:
    uint8_t layersNumber;
    vector<uint16_t> neuronsNumber;
    vector<Layer> layer;
public:
    Network();
    ~Network();
    void SetLayersNumber(uint8_t number);
    void SetNeuronsNumber(uint8_t layerIndex, uint16_t number);
    uint8_t GetLayersNumber();
    void ClearAllNeuronsNumber();
    void CreateNetwork();
};

#endif // NETWORK_H
