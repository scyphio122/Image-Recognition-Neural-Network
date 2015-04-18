#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include "connection.h"

using std::vector;

class Connection;

class Neuron
{
protected:
    double output;
    vector<Connection> targetNeuronConnection;

public:
    Neuron();
    ~Neuron();
    void CalculateOutput();
    double GetOutput();
    void ClearConnection();
    void ClearOutput();
    void CreateTargetNeuronConnection(Connection *connection);
    void ClearTargetNeuronConnection();
};

#endif // NEURON_H
