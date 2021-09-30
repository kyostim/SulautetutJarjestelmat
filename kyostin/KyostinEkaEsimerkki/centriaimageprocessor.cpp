#include "centriaimageprocessor.h"

CentriaImageProcessor::CentriaImageProcessor(QObject *parent) : QObject(parent)
{
    _timerId = startTimer(100);
}

CentriaImageProcessor::~CentriaImageProcessor()
{
    if(_timerId >= 0)
    {
        killTimer(_timerId);
        _timerId = -1;
    }

    if(_videoCapture.isOpened())
    {
        _videoCapture.release();
    }
}

void CentriaImageProcessor::timerEvent(QTimerEvent *event)
{
    if(!_videoCapture.isOpened())
    {
        _videoCapture.open("/dev/video0");
    }
    else
    {
        cv::Mat image;
        _videoCapture.read(image);
        if(image.cols>0)
        {
        cv::Mat grayImage;
        cv::cvtColor(image,grayImage,cv::COLOR_BGR2GRAY);

        cv::Mat thresholdImage;
        cv::threshold(grayImage, thresholdImage,ThresholdValue,255,1);

        //cv::imshow("image", image);
        //cv::imshow("grayImage", grayImage);
        cv::imshow("thresholdImage", thresholdImage);
        }

    }
}
