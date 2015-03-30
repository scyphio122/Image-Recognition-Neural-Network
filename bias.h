#ifndef BIAS_H
#define BIAS_H
#include "neuron.h"

class Bias:Neuron
{
private:
    const uint8_t input = 1;
public:
    Bias();
    ~Bias();
};

#endif // BIAS_H
