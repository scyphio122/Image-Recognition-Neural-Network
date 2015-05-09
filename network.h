#ifndef NETWORK_H
#define NETWORK_H

#include "layer.h"
#include <QVector>

class FileHandler;

class Network:  public FileHandler
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
    bool CreateNetwork(bool weightsFromFileOrRandom);
    void SaveNetwork(string directory);
    bool LoadNetwork(string directory);
    void TestNetwork();
    void TestConnections();
    void DeleteNetwork();
};

#endif // NETWORK_H
