#include "image.h"
#include <QVector>
#include <cv.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <stdint-gcc.h>
#include <QPixmap>
#include <cmath>

Image::Image()
{

}

Image::~Image()
{

}

void Image::SetDirectory(string directory)
{
    this->directory = directory;
}

string Image::GetDirectory()
{
    return this->directory;
}

/**
 * @brief Image::LoadImage   -   This function is called in order to load an image in directory held in Image::direcory. If the image's size is bigger than 640x480 pixels, this function resizes it to this size.
 * @return  false - if picture does not exist, true if loading ok
 */
bool Image::LoadImage()
{
    if(directory.empty())
        return false;
    this->image = imread(this->directory, 1);

    if(this->image.empty())
        return false;
    else
        return true;
}

void Image::ResizeImage()
{
    if(!this->image.empty())
    {
        if(this->image.rows > 240)
            resize(this->image, this->image, Size(0, 0), 1, ((double)240/this->image.rows));
        if(this->image.cols > 320)
            resize(this->image, this->image, Size(0, 0), ((double)320/this->image.cols), 1);
    }
}

void Image::SetImage(Mat image)
{
    this->image = image;
}

Mat Image::GetImage()
{
    return this->image;
}

void Image::SetImageName(string name)
{
    this-> imageName = name;
}

string Image::GetImageName()
{
    return this->imageName;
}

/**
 * @brief Image::GetHSV -   This function is called in order to get the 3 channels: H, S and V from RGB image
 * @return              -   Vector with channels in order: H, S, V
 *
 */
void Image::Convert2HSV()
{
    Mat convertedImage;

    cvtColor(this->image, convertedImage, CV_RGB2HSV);
    split(convertedImage, this->hsv);
}
/**
 * @brief Image::GetHSV -   This function is called in order to get the specific channel from hsv vector
 * @param channel       -   The index of the channel. It may be H, S, or V
 * @return              -   the specified channel
 */
Mat Image::GetHSV(uint8_t channel)
{
    return this->hsv[channel];
}

/**
 * @brief Image::AutomaticThreshold -   This function is called in order to get the automatically generated binary picture of specified image
 * @param image                     -   The image that will be thresholded. By default it will be H, S or V channel
 * @return                          -   The image after thresholding
 */
Mat Image::AutomaticThreshold(Mat inputImage)
{
    Mat thresholdedImage;
    //  Get rid of the smaller "holes" in image
    morphologyEx(inputImage, inputImage, MORPH_OPEN, 5);
    //  Get thresholded image
    adaptiveThreshold(inputImage,this->contourImage, 255, CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 21, 1);

    return thresholdedImage;
}

/**
 * @brief HandMadeThreshold         -   This function is called to binarize the image by hand. The caller is the input image
 * @param inputImage                -   The input image
 * @param outputImage               -   The output image
 * @param value                     -   The threshold value
 */
void Image::HandMadeThreshold(Mat inputImage, int value)
{

    //  Get rid of the smaller "holes" in image
    morphologyEx(inputImage, this->contourImage, MORPH_OPEN, 5);
    threshold(this->contourImage, this->contourImage, value, 255, THRESH_BINARY);
}


/**
 * @brief Image::FindContours   -   This function is called to find the contours in the caller image and draw the biggest on in the outputImage. The list(vector) of the found contours is saved in the caller object
 * @param outputImage           -   The image where to draw the biggest contour found
 *
 */

void Image::FindContours()
{
    Mat temp;    //  temp Mat

    //  Copy the image to the created Mat contour because findContour changes the image
    this->contourImage.copyTo(temp);

    vector<Vec4i> hierarchy;

     bitwise_not(temp, temp);


    /// Find contours
    findContours( temp, this->contoursFound, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    //  Fill the contour image with zeroes
    this->contourImage = Mat::zeros( temp.size(), CV_8UC3 );


    //  Set the contour color to white
    Scalar color = Scalar( 255, 255, 255 );
    /*for( unsigned int i = 0; i< contours.size(); i++ )
        drawContours( outputImage, contours, i, color, 1, 8, hierarchy, 0, Point() );*/
    //  draw the biggest contour found
    drawContours( this->contourImage, this->contoursFound, this->GetMaxContourIndex() , color, 1, 8, hierarchy, 0, Point() );
    return;
}


/**
 * @brief Image::GetCountoursFound  -   This function is called to return the vector of all contours found by FindCounturs method
 * @return  vector< vector <Point> > contoursFound
 */
vector< vector <Point> > Image::GetContoursFound()
{
    return this->contoursFound;
}


/**
 * @brief Image::GetMaxCountourIndex    -   This function returns index of the max contour found
 * @return  -   index of the maximal contour foun
 */
int Image::GetMaxContourIndex()
{
    int max=0;           //  The maximum surface found in the set of the contours
    int maxIndex=0;     //  The index of the biggest contour
    //  Find the biggest contour
    for( unsigned int i = 0; i< this->contoursFound.size(); i++ )
       {
        if(abs(contourArea(this->contoursFound[i]) > max))
        {
            max = abs(contourArea(this->contoursFound[i]));
            maxIndex = i;

        }
       }
    return maxIndex;
}

/**
 * @brief Image::GetMaxContour  -   This function is called in order to return the array with the biggest contour found in the binarized image. It mus be called after the FindContours method.
 * @return  The biggest contours
 */
vector <Point> Image::GetMaxContour()
{
    return this->contoursFound[this->GetMaxContourIndex()];
}

/**
 * @brief Image::CalculateMalinowskaCoefficient -   This function is called in order to calculate the Malinowska coefficient of the biggest contour in the binarized image
 */
double Image::CalculateMalinowskaCoefficient()
{
    vector <Point> biggestContour = GetMaxContour();
    this->malinowskaCoefficient = (arcLength(biggestContour, true))/(2*sqrt(M_PI*contourArea(biggestContour))) - 1;
    //  Return this value for teaching algoritm - to put it in array of teaching examples
    return this->malinowskaCoefficient;
}

/**
 * @brief Image::CalculateHuMoments -   This function calculates the values of Hu moments of the conotur. They are both saved in the this->huMoments and returned.
 * @return              -   The calculater vector<double> of HuMoments
 */
std::vector<double> Image::CalculateHuMoments()
{
    HuMoments(moments(this->GetMaxContour(), false), this->huMoments);
    return this->huMoments;
}


Mat Image::GetContourImage()
{
    return this->contourImage;
}

