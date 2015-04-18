#ifndef BIAS_H
#define BIAS_H
#include "neuron.h"
#include <stdint.h>

class Bias:public Neuron
{
private:
    uint8_t input;
public:
    Bias();
    ~Bias();

};

#endif // BIAS_H
