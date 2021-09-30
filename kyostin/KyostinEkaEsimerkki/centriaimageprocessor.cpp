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
        cv::imshow("image", image);
    }
}
