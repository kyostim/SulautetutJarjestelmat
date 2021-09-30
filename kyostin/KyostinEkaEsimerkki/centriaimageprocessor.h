#ifndef CENTRIAIMAGEPROCESSOR_H
#define CENTRIAIMAGEPROCESSOR_H

#include <QObject>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

class CentriaImageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit CentriaImageProcessor(QObject *parent = nullptr);
    ~CentriaImageProcessor();

protected:
    void timerEvent(QTimerEvent *event);


private:
    int _timerId = -1;

    cv::VideoCapture _videoCapture;

};

#endif // CENTRIAIMAGEPROCESSOR_H
