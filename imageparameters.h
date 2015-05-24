#ifndef IMAGEPARAMETERS_H
#define IMAGEPARAMETERS_H

#include <vector>
#include <stdint-gcc.h>

class ImageParameters
{
protected:
    double malinowskaCoefficient;
    std::vector <double> huMoments;

public:
    ImageParameters();
    ~ImageParameters();

    virtual double                  CalculateMalinowskaCoefficient()=0;
    virtual std::vector<double>     CalculateHuMoments()=0;

    double                          GetMalinowskaCoefficient();
    std::vector<double>             GetHuMoments();
    double                          GetHuMoment(uint16_t index);
};

#endif // IMAGEPARAMETERS_H
