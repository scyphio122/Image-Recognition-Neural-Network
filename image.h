#ifndef IMAGE_H
#define IMAGE_H

#include <cv.hpp>
#include <imgproc/imgproc.hpp>
#include <QImage>
#include <vector>
#include "imageparameters.h"

#define     H_channel   0
#define     S_chennel   1
#define     V_channel   2

using namespace std;
using namespace cv;

class Image : public ImageParameters
{
private:
    string          directory;
    Mat             image;
    Mat             contourImage;
    string          imageName;
    vector<Mat>     hsv;
    vector <vector <Point> > contoursFound;

public:


    Image();
    ~Image();

    void                    SetDirectory(string directory);
    string                  GetDirectory();
    bool                    LoadImage();
    void                    SetImage(Mat image);
    Mat                     GetImage();
    Mat                     GetContourImage();
    void                    SetImageName(string name);
    string                  GetImageName();
    void                    Convert2HSV();
    Mat                     GetHSV(uint8_t channel);
    void                    ResizeImage();
    void                    FindContours();
    vector<vector<Point> >  GetContoursFound();
    vector<Point>           GetMaxContour();
    int                     GetMaxContourIndex();
    void                    HandMadeThreshold(Mat inputImage, int value);

    Mat                         AutomaticThreshold(Mat inputImage);
    virtual double              CalculateMalinowskaCoefficient();
    virtual std::vector<double> CalculateHuMoments();


};


#endif // IMAGE_H
