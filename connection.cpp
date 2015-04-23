#include "connection.h"
#include <cstdlib>

Connection::Connection()
{
    RandomizeWeight();
}

Connection::~Connection()
{

}

void Connection::RandomizeWeight()
{
    this->weight = double(rand()/RAND_MAX)*(MAX_WEIGHT - MIN_WEIGHT) + MIN_WEIGHT;
}

void Connection::SetNeuronAddress(CommonNeuron *targetNeuron)
{
    this->targetNeuron = targetNeuron;
}
