#include "bgvideoprocessor.h"

BGVideoProcessor::BGVideoProcessor(QObject *parent) : QObject(parent)
{

}

BGVideoProcessor::~BGVideoProcessor()
{
    Stop();
    if(_videoCapture.isOpened())
    {
        _videoCapture.release();
    }
}

void BGVideoProcessor::Start()
{
    if(_timerId == -1)
    {
        cv::namedWindow("image");
        cv::setMouseCallback("image", &MouseCallBack,this);

        _timerId = startTimer(100);
    }
}

void BGVideoProcessor::Stop()
{
    if(_timerId >= 0)
    {
        killTimer(_timerId);
        _timerId = -1;
    }
}

void BGVideoProcessor::timerEvent(QTimerEvent *event)
{
    if(!_videoCapture.isOpened())
    {
        _videoCapture.open("/dev/video0");
    }
    else
    {
        cv::Mat image;
        _videoCapture.read(image);

        if(image.cols > 0)
        {
            cv::Mat hsvImage, grayImage;
            cv::cvtColor(image,hsvImage, cv::COLOR_BGR2HSV);
            cv::cvtColor(image,grayImage, cv::COLOR_BGR2GRAY);

            if(_clickedX >= 0 && _clickedY >= 0)
            {
                cv::circle(image,cv::Point(_clickedX,_clickedY),2,cv::Scalar(255,255,0),2);
                QString coordinatesText = QString("(%1,%2)").arg(_clickedX).arg(_clickedY);
                cv::putText(image,coordinatesText.toUtf8().constData(),cv::Point(_clickedX + 5,_clickedY),1,1,cv::Scalar(255,255,255));

                if(hsvImage.size > 0)
                {
                    int offset = ((hsvImage.cols * _clickedY) + _clickedX) * hsvImage.channels();
                    uchar hue = hsvImage.data[offset];
                    uchar saturation = hsvImage.data[offset + 1];
                    uchar value = hsvImage.data[offset + 2];
                    QString hsvValuesText = QString("Hue=%1, Saturation=%2, Value=%3").arg(hue).arg(saturation).arg(value);
                    cv::putText(image,hsvValuesText.toUtf8().constData(),cv::Point(_clickedX + 5,_clickedY + 10),1,1,cv::Scalar(255,255,255));

                    if(AutoCalibration)
                    {
                        LowerHue = hue > 5 ? hue -5 : 0;
                        LowerSaturation = saturation > 5 ? saturation -5 : 0;
                        LowerValue = value > 5 ? value -5 : 0;

                        UpperHue = hue < 250 ? hue + 5 : 255;
                        UpperSaturation = saturation < 250 ? saturation + 5 : 255;
                        UpperValue = value < 250 ? value + 5 : 255;
                        AutoCalibration = false;
                    }
                }

            }

            cv::Mat inRangeImage;
            cv::inRange(hsvImage,cv::Scalar(LowerHue, LowerSaturation, LowerValue), cv::Scalar(UpperHue, UpperSaturation,UpperValue),inRangeImage);

            cv::Mat thresholdImage;
            if(AdaptiveThreshold)
            {
                cv::adaptiveThreshold(grayImage,thresholdImage,255,cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY,ThresholdBlockSize,2);
            }
            else
            {
                cv::threshold(grayImage,thresholdImage,ThresholdMin,255,cv::THRESH_BINARY);
            }


            //cv::Mat blueChannel = image;
            //blueChannel -= cv::Scalar(255,255,0);

//            cv::Mat ownTestImage(image.rows, image.cols,0);
//            int index = 0;
//            int rowOffset = 0;
//            for(int row = 0; row < image.rows; row++)
//            {
//                int colOffset = 0;
//                for(int col = 0; col < image.cols; col++)
//                {
//                    int sourceIndex = rowOffset + colOffset + col;
//                    uchar blueColor = image.data[sourceIndex];
//                    uchar greenColor = image.data[sourceIndex + 1];
//                    uchar redColor = image.data[sourceIndex + 2];
//                    ownTestImage.data[index] = blueColor;// -((greenColor + redColor)/2);
//                    index++;
//                    colOffset = colOffset + (image.channels() - 1);
//                }
//                rowOffset = rowOffset + (image.channels() * grayImage.cols);
//            }

//            if(_clickText.size() > 0)
//            {
//                QString testi(_clickText);
//                std::string clickText = testi.toUtf8().constData();
//                cv::putText(image,testi.toUtf8().constData(),cv::Point(_clickedX,_clickedY),1,1,cv::Scalar(255,255,255));
//            }



            cv::imshow("image",image);
            //cv::imshow("hsvImage",hsvImage);
            cv::imshow("inRangeImage", inRangeImage);
            //cv::imshow("greenImage",greenImage);
            //cv::imshow("ownTestImage",ownTestImage);
            cv::imshow("thresholdImage", thresholdImage);

        }
    }
}

void BGVideoProcessor::MouseCallBack(int event, int x, int y, int flags, void *userdata)
{
    if(flags == cv::EVENT_FLAG_LBUTTON)
    {
        BGVideoProcessor* bgVideoProcessor = (BGVideoProcessor*)userdata;
        bgVideoProcessor->_clickText = QString("Mouse left button clicked at(%1, %2)").arg(x).arg(y);
        bgVideoProcessor->_clickedX = x;
        bgVideoProcessor->_clickedY = y;
    }
}
