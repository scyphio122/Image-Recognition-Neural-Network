#ifndef TEACHER_H
#define TEACHER_H

#include <stdint-gcc.h>
#include <QVector>


class Network;
class Neuron;
class Connection;
class Bias;
class CommonNeuron;
class Layer;
class FileHandler;
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

    QVector <double>      expectedOutput;
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
    void        SetAlpha(double alpha);
    void        SetEta(double eta);
    void        SetTeachingCycleCounter(uint32_t    teachingCycleCounterToSet);
    void        SetQualificationError(double qualificationThhresholdToSet);
    void        SetOutputError(Neuron *outputNeuron);
    void        CalculateLastNeuronError(CommonNeuron *outputNeuron);
    void        CalculateCommonNeuronError(Neuron* thisNeuron);
    void        CalculateEntireNetworkError();
    void        ChangeWeight(Connection* connection, Neuron* sourceNeuron);
    uint32_t    GetTeachingCycleCounter();
    QVector <QVector<double>  >*RandomizeTeachingExample(QVector<QVector<double> > *exampleTable);
    void        BackPropagationAlgorithm();


};

#endif // TEACHER_H
