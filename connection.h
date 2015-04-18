#ifndef CONNECTION_H
#define CONNECTION_H
#include "neuron.h"
#include "filehandler.h"

#define MIN_WEIGHT (double)(-50)
#define MAX_WEIGHT (double)(50)

class Neuron;
class CommonNeuron;

class Connection:FileHandler
{
private:
    double weight;
    Neuron* targetNeuron;
public:
    Connection();
    ~Connection();
    void RandomizeWeight();
    void SetWeight(double weightToSet);
    void SetNeuronAddress(Neuron *targetNeuron);


};

#endif // CONNECTION_H
