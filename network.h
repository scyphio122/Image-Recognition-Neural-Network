#ifndef NETWORK_H
#define NETWORK_H

#include "layer.h"
#include <QVector>


class Network
{
private:
    uint8_t layersNumber;
    QVector<uint16_t> neuronsNumber;
    QVector<Layer> layer;
public:
    Network();
    ~Network();
    void SetLayersNumber(uint8_t number);
    void SetNeuronsNumber(uint8_t layerIndex, uint16_t number);
    uint8_t GetLayersNumber();
    void ClearAllNeuronsNumber();
    void CreateNetwork();

    void TestNetwork();
};

#endif // NETWORK_H
