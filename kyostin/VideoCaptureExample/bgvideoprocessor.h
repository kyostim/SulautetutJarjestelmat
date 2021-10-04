#ifndef BGVIDEOPROCESSOR_H
#define BGVIDEOPROCESSOR_H

#include <QObject>

#include <string>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class BGVideoProcessor : public QObject
{
    Q_OBJECT
public:
    uchar LowerHue = 36;
    uchar LowerSaturation = 25;
    uchar LowerValue = 25;
    uchar UpperHue = 70;
    uchar UpperSaturation = 255;
    uchar UpperValue = 255;
    bool AutoCalibration = false;

    explicit BGVideoProcessor(QObject *parent = nullptr);
    ~BGVideoProcessor();

    void Start();
    void Stop();

protected:
    void timerEvent(QTimerEvent *event);

private:
    int _timerId = -1;

    cv::VideoCapture _videoCapture;
    QString _clickText = "";
    int _clickedX = -1;
    int _clickedY = -1;

    void static MouseCallBack(int event, int x, int y, int flags, void* userdata);
};

#endif // BGVIDEOPROCESSOR_H
