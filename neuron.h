#ifndef NEURON_H
#define NEURON_H

#include <QVector>
#include "connection.h"
#include <stdint-gcc.h>

class Connection;
class CommonNeuron;
class Neuron
{
protected:
    double output;
    QVector<Connection> targetNeuronConnection;

public:
    Neuron();
    ~Neuron();
    void CalculateOutput();
    double GetOutput();
    Connection* GetConnectionAt(uint16_t index);
    void ClearConnection();
    void ClearOutput();
    void CreateTargetNeuronConnection(Connection *connection);
    void ClearTargetNeuronConnection();
    void ConnectNeuron(CommonNeuron *neuronToConnect, bool connectionWeightRandom_Or_FromFile);

    uint16_t ConnectionsSize();
};

#endif // NEURON_H
