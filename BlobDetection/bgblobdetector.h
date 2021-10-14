#ifndef BGBLOBDETECTOR_H
#define BGBLOBDETECTOR_H

#include <QObject>
#include <QtMath>

#include <string>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>


class BGBlobDetector : public QObject
{
    Q_OBJECT
public:
    uchar MinThreshold = 10;
    uchar MaxThreshold = 200;

    bool FilterbyArea = true;
    int MinArea = 300;
    int MaxArea = 2500;

    bool FilterByCircularity = true;
    float MinCircularity = 0.0;
    float MaxCircularity = 1.0;

    bool FilterByInertia = true;
    float MinInertia = 0.0;
    float MaxInertia = 1.0;

    explicit BGBlobDetector(QObject *parent = nullptr);
    ~BGBlobDetector();

    void Start();
    void Stop();

protected:
    void timerEvent(QTimerEvent *event);

private:
    int _timerId = -1;

    cv::VideoCapture _videoCapture;
    cv::Ptr<cv::SimpleBlobDetector> _detector;

    void static MouseCallBack(int event, int x, int y, int flags, void* userdata);

};

#endif // BGBLOBDETECTOR_H