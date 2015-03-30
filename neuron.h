#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include "connection.h"

using std::vector;

class Connection;

class Neuron
{
private:
    double output;
    vector<Connection> connection;
public:
    Neuron();
    ~Neuron();
    void CalculateOutput();
    double GetOutput();
};

#endif // NEURON_H
