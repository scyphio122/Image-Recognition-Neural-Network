#ifndef TEACHER_H
#define TEACHER_H

#include <stdint-gcc.h>

#define DIFFERENTIAL

class Network;
class Neuron;
class Connection;
class Bias;
class CommonNeuron;
class Layer;

class Teacher
{
private:
    double      qualificationThreshold;
    double      alpha;
    double      eta;
    uint32_t    teachingCycleCounter;
    double      connectionError;
    double      entireNetworkError;
    Network*    network;

    double      expectedOutput;
    //Image*      image;

    double        CalculateNeuronsError(Neuron*   neuron);
    double        CalculateWeight(Connection* connection);


public:
    Teacher();
    ~Teacher();

    double      GetAlpha();
    double      GetEta();
    double      GetEntireNetworkError();
    double      GetQualificationThreshold();
    double      CalculateWeightDifferential(Neuron* neuron);
    void        SetAlpha(double alpha);
    void        SetEta(double eta);
    void        SetTeachingCycleCounter(uint32_t    teachingCycleCounterToSet);
    void        SetQualificationError(double qualificationThhresholdToSet);
    void        SetOutputError(Neuron *outputNeuron);
    void        CalculateLastNeuronError(CommonNeuron *outputNeuron);
    void        CalculateOutputDifferential(Neuron* thisNeuron, Layer* nextLayer);
    uint32_t    GetTeachingCycleCounter();

};

#endif // TEACHER_H
