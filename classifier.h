#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <string>
#include <QVector>
#include <stdint-gcc.h>
#include "classifiedobject.h"
using namespace std;
/*struct object
{
    double expectedOutputValue;
    string name;
};
*/
class Classifier
{
protected:
    QVector <ClassifiedObject>    taughtObjects;
    double              minimalDistance;
    uint16_t            classifiedObjectIndex;
public:
    void    AddTaughtObject(ClassifiedObject example);
    string  GetClassifiedObjectName();
    void    CalculateMinimalDistance(double networkOutput);

    Classifier();
    ~Classifier();
};

#endif // CLASSIFIER_H
