#ifndef TEACHER_H
#define TEACHER_H

#include <stdint-gcc.h>
#include <QVector>
#include "image.h"

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
    double      momentum;                      //  Momentum coefficient
    double      eta;                        //  The Learning speed coefficient
    uint32_t    teachingCycleCounter;
    uint32_t    maxTeachingCycleCounter;
    double      connectionError;
    double      entireNetworkError;
    Network*    network;
    uint8_t     progress;

    QVector<double>      expectedOutput;
    vector< vector<double> > teachingExamples;
    Image*      image;

    double        CalculateNeuronsError(Neuron*   neuron);
    double        CalculateWeight(Connection* connection);



public:
    Teacher();
    ~Teacher();

    void        AppendTeachingExampleFromTheLoadedImage(double expectedOutput);
    uint16_t    GetExpectedOutputSize();
    double      GetAlpha();
    double      GetEta();
    double      GetEntireNetworkError();
    double      GetQualificationThreshold();
    void        SetMomentum(double momentum);
    void        SetEta(double eta);
    void        SetNetwork(Network* networkToSet);
    void        SetMaxTeachingCycleCounter(uint32_t    maxTeachingCycleCounterToSet);
    void        SetQualificationError(double qualificationThhresholdToSet);
    void        SetOutputError(Neuron *outputNeuron);
    void        SetImage(Image* image);
    void        CalculateLastNeuronError(CommonNeuron *outputNeuron, double expectedOutput);
    void        CalculateCommonNeuronError(Neuron* thisNeuron);
    void        CalculateEntireNetworkErrorForCurrentExample(double expectedOutput);
    void        ChangeWeight(Connection* connection, Neuron* sourceNeuron);
    uint32_t    GetTeachingCycleCounter();
    uint8_t     RandomizeTeachingExample(vector<vector<double> > *exampleTable);
    void        BackPropagationAlgorithm();
    void        CalculateProgress(unsigned long long teachingCounter);
    uint8_t     GetProgress();


};

#endif // TEACHER_H
