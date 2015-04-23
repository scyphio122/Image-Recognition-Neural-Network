#ifndef CONNECTION_H
#define CONNECTION_H
#include "neuron.h"
#include "filehandler.h"

#define MIN_WEIGHT (double)(-50)
#define MAX_WEIGHT (double)(50)
#define CONNECTION_WEIGHT_RANDOM    true
#define CONNECTION_WEIGHT_FROM_FILE false


//class Neuron;
class CommonNeuron;
class Connection:FileHandler
{
private:
    double weight;
    CommonNeuron* targetNeuron;
public:
    Connection();
    ~Connection();
    void RandomizeWeight();
    void SetWeight(double weightToSet);
    void SetNeuronAddress(CommonNeuron *targetNeuron);


};

#endif // CONNECTION_H
