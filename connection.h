#ifndef CONNECTION_H
#define CONNECTION_H
#include "neuron.h"
#include "filehandler.h"

class Neuron;

class Connection:FileHandler
{
private:
    double weight;
    Neuron* targetNeuron;
    Neuron* sourceNeuron;
public:
    Connection();
    ~Connection();
    void RandomizeWeight();
    void SetWeight(double weightToSet);
    void SetNeuronAddress(Neuron* neuronToConnect);


};

#endif // CONNECTION_H
