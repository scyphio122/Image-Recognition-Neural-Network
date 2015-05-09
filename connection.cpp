#include "connection.h"
#include <cstdlib>
#include <QList>
#include "neuron.h"
Connection::Connection()
{
    RandomizeWeight();
}

Connection::~Connection()
{

}

void Connection::RandomizeWeight()
{
    this->weight = (double(rand())/RAND_MAX)*(MAX_WEIGHT - MIN_WEIGHT) + MIN_WEIGHT;
}

void Connection::SetNeuronAddress(Neuron *targetNeuron)
{
    this->targetNeuron = targetNeuron;
}
double Connection::GetWeight()
{
    return this->weight;
}

void Connection::SetWeight(double weightToSet)
{
    this->weight = weightToSet;
}

Neuron* Connection::GetConnectedNeuron()
{
    return (this->targetNeuron);
}


