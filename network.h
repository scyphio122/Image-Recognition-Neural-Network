#ifndef NETWORK_H
#define NETWORK_H

#include "layer.h"
#include <vector>
using namespace std;

class FileHandler;
enum  TransportFunction_e  {UNIPOLAR_SIGMOID_FUNCTION, BIPOLAR_SIGMOID_FUNCTION};
extern TransportFunction_e transportFunction;

class Network:  public FileHandler
{
private:
    uint8_t layersNumber;
    QVector<uint16_t> neuronsNumber;
    QVector<Layer> layer;
public:
    Network();
    ~Network();
    void        SetLayersNumber(uint8_t number);
    void        SetNeuronsNumber(uint8_t layerIndex, uint16_t number);
    uint8_t     GetLayersNumber();
    void        ClearAllNeuronsNumber();
    bool        CreateNetwork(bool weightsFromFileOrRandom);
    void        SaveNetwork(string directory);
    bool        LoadNetwork(string directory);
    bool        LoadNetworkInput(vector<double> inputExample);
    void        TestNetwork();
    void        TestConnections();
    void        DeleteNetwork();
    Layer*      GetLayerAt(uint8_t layerIndex);
    uint16_t    GetNeuronsNumber(uint8_t layerIndex);
    void        CalculateNetworkAnswer();
    double      GetNetworkAnswer();
};

#endif // NETWORK_H
