#include "classifier.h"
#include <cmath>
#include <stdint-gcc.h>
#include <fstream>

Classifier::Classifier()
{
    this->minimalDistance = 0xFFFFFFFF;
    this->classifiedObjectIndex = 0;
}

Classifier::~Classifier()
{

}

void Classifier::CalculateMinimalDistance(double networkOutput)
{
    this->minimalDistance = 0xFFFFFFFF;
    double  temp;
    for(uint16_t i=0; i<taughtObjects.size(); i++)
    {
        temp = fabs(networkOutput-this->taughtObjects[i].GetExpectedOutput());
        if(temp < this->minimalDistance)
        {
            minimalDistance = temp;
            this->classifiedObjectIndex = i;
        }
    }
    return;
}

string Classifier::GetClassifiedObjectName()
{
    if(taughtObjects.size() != 0)
        return this->taughtObjects[classifiedObjectIndex].GetName();
}

void    Classifier::AddTaughtObject(ClassifiedObject example)
{
    if(!taughtObjects.empty())
    {
        for(uint16_t i=0; i<taughtObjects.size(); i++)
        {
            if(example.GetName() == taughtObjects[i].GetName())
               return;
        }
    }
    this->taughtObjects.append(example);


    return;
}
