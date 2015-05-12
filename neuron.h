#ifndef NEURON_H
#define NEURON_H

#include <QList>
#include "connection.h"
#include <stdint-gcc.h>

class Connection;
class CommonNeuron;
class Neuron
{
protected:
    double input;
    double output;
    double outputDifferential;
    QList<Connection> targetNeuronConnection;



public:
    Neuron();
    ~Neuron();
    void        CalculateOutput();
    double      GetOutput();
    Connection* GetConnectionAt(uint16_t index);
    void        ClearConnection();
    void        ClearOutput();
    void        CreateTargetNeuronConnection(Connection connection);
    void        ClearTargetNeuronConnection();
    void        ConnectNeuron(CommonNeuron *neuronToConnect, bool connectionWeightRandom_Or_FromFile);
    void        AllocateMemoryForTargetConnectionsList(uint16_t connectionsNumber);
    double      GetOutputDifferential();
    void        SetOutputDifferential(double value);
    double      GetInput();
    uint16_t    ConnectionsSize();

};

#endif // NEURON_H
