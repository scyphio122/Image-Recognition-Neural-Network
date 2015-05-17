#include "connection.h"
#include <cstdlib>
#include <QList>
#include "neuron.h"
Connection::Connection()
{
    //RandomizeWeight();
    this->weight = 0;
    this->previousWeight = 0;
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
double Connection::GetPreviousWeight()
{
    return this->previousWeight;
}

void Connection::SetWeight(double weightToSet)
{
    this->previousWeight = this->weight;
    this->weight = weightToSet;
}

Neuron* Connection::GetConnectedNeuron()
{
    return (this->targetNeuron);
}
