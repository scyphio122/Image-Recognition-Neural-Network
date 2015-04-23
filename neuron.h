#ifndef NEURON_H
#define NEURON_H

#include <QVector>
#include "connection.h"


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
    void ClearConnection();
    void ClearOutput();
    void CreateTargetNeuronConnection(Connection *connection);
    void ClearTargetNeuronConnection();
    void ConnectNeuron(CommonNeuron *neuronToConnect, bool connectionWeightRandom_Or_FromFile);
};

#endif // NEURON_H
