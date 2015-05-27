#ifndef CLASSIFIEDOBJECT_H
#define CLASSIFIEDOBJECT_H

#include "string"
using namespace std;

class ClassifiedObject
{
private:
    string name;
    double expectedOutput;
public:
    ClassifiedObject();
    ~ClassifiedObject();

    string  GetName();
    void    SetName(string name);
    double  GetExpectedOutput();
    void    SetExpectedOutput(double value);
};

#endif // CLASSIFIEDOBJECT_H
