#ifndef NEURON_H
#define NEURON_H

#include <vector>

class Neuron
{
private:
    double output;
    vector<Connection> connection;
public:
    Neuron();
    ~Neuron();
    void SetIndex();
    void ClearInput();
    void CalculateOutput();
    double GetOutput();
};

#endif // NEURON_H
