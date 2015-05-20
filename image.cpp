#include "image.h"
#include <QVector>
#include <cv.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <stdint-gcc.h>
#include <QPixmap>

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
    {

        if(this->image.rows > 480)
            resize(this->image, this->image, Size(0, 0), 1, (this->image.rows/480));
        if(this->image.cols > 640)
            resize(this->image, this->image, Size(0, 0), (this->image.cols/640), 1);
        return true;
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
Mat Image::AutomaticThreshold(Mat image)
{
    Mat thresholdedImage;
    //  Get rid of the smaller "holes" in image
    morphologyEx(image, image, MORPH_OPEN, 5);
    //  Get thresholded image
    adaptiveThreshold(image,thresholdedImage, 255, CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 21, 1);

    return thresholdedImage;
}

/**
 * @brief Image::HandMadeThreshold  -   This function is called to binarize the image by hand.
 * @param image                     -   The input image
 * @param value                     -   The threshold image
 * @return  The output image, after thresholding
 */
Mat Image::HandMadeThreshold(Mat image, int value)
{
    Mat thresholdedImage;
    threshold(image, thresholdedImage, value, 255, THRESH_BINARY);
    return thresholdedImage;
}


/**
 * @brief Image::FindContours   -   This function is called to find the contours in the caller image and draw the biggest on in the outputImage
 * @param outputImage           -   The image where to draw the biggest contour found
 * @return  The vector containing all found contours
 */

vector< vector <Point> > Image::FindContours(Mat &outputImage)
{
    Mat contour;    //  temp Mat
    int max=0;      //  The maximum surface found in the set of the contours
    int maxIndex;   //  The index of the biggest contour

    //  Copy the image to the created Mat contour because findContour changes the image
    this->image.copyTo(contour);
    vector<vector<Point> > contours;

    vector<Vec4i> hierarchy;
    if((this->image.at<uint8_t>(0,0) == 255) && (this->image.at<uint8_t>(0,this->image.cols-1) == 255) && (this->image.at<uint8_t>(this->image.rows-1,0) == 255) && (this->image.at<uint8_t>(this->image.rows-1,this->image.cols-1) == 255))
    {
        bitwise_not(contour, contour);
    }

    /// Find contours
    findContours( contour, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    //  Fill the contour image with zeroes
    outputImage = Mat::zeros( contour.size(), CV_8UC3 );

    //  Find the biggest contour
    for( unsigned int i = 0; i< contours.size(); i++ )
       {
        if(abs(contourArea(contours[i]) > max))
        {
            max = abs(contourArea(contours[i]));
            maxIndex = i;

        }
       }
    //  Set the contour color to white
    Scalar color = Scalar( 255, 255, 255 );
    //  draw the biggest contour found
    drawContours( outputImage, contours, maxIndex, color, 1, 8, hierarchy, 0, Point() );
    return contours;
}




/**
 * @brief Image::ConvertMat2QPixmap -   This function is called in order to convert the Mat image to Pixmap
 * @param image                     -   The image to convert (input)
 * @param pixmap                    -   The pixmap where the image will be stored (output)
 */
void Image::ConvertMat2QPixmap(Mat image, QPixmap &pixmap)
{
     QImage imageqt;
     imageqt.fill(qRgba(0,0,0,0));
    //  If the image is colourer (?)
    if(image.channels() == 3)
    {
         imageqt = QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
         imageqt = imageqt.convertToFormat(QImage::Format_RGBA8888);
    }
    else    //  If the image is gray-scaled
            imageqt = QImage(image.data, image.cols, image.rows, image.step, QImage::Format_Mono);

    pixmap = QPixmap::fromImage(imageqt);
}
