#ifndef BIAS_H
#define BIAS_H
#include "neuron.h"
#include <stdint.h>

class Bias:public Neuron
{
private:
    static const double input = 1;
public:
    double      GetInput();
    Bias();
    virtual ~Bias();

};

#endif // BIAS_H
