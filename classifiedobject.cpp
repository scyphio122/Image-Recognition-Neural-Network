#include "classifiedobject.h"

ClassifiedObject::ClassifiedObject()
{

}

ClassifiedObject::~ClassifiedObject()
{

}


string ClassifiedObject::GetName()
{
    return this->name;
}

double ClassifiedObject::GetExpectedOutput()
{
    return this->expectedOutput;
}
void ClassifiedObject::SetExpectedOutput(double value)
{
    this->expectedOutput = value;
}

void ClassifiedObject::SetName(string name)
{
    this->name = name;
}
