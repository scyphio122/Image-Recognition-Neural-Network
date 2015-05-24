#include "imageparameters.h"
#include <stdint-gcc.h>
ImageParameters::ImageParameters()
{

}

ImageParameters::~ImageParameters()
{

}

double ImageParameters::GetMalinowskaCoefficient()
{
    return this->malinowskaCoefficient;
}

std::vector <double> ImageParameters::GetHuMoments()
{
    return this->huMoments;
}

double ImageParameters::GetHuMoment(uint16_t index)
{
    return this->huMoments[index];
}
