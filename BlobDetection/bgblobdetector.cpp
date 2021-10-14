#include "bgblobdetector.h"

BGBlobDetector::BGBlobDetector(QObject *parent) : QObject(parent)
{

}

BGBlobDetector::~BGBlobDetector()
{
    Stop();
    if(_videoCapture.isOpened())
    {
        _videoCapture.release();
    }
}

void BGBlobDetector::Start()
{
    if(_timerId == -1)
    {
        cv::namedWindow("image");
        cv::setMouseCallback("image", &MouseCallBack,this);

        _timerId = startTimer(100);
    }
}

void BGBlobDetector::Stop()
{
    if(_timerId >= 0)
    {
        killTimer(_timerId);
        _timerId = -1;
    }
}

void BGBlobDetector::timerEvent(QTimerEvent *event)
{
    if(!_videoCapture.isOpened())
    {
        //_videoCapture.open("/dev/video0");
        _videoCapture.open(0);
    }
    else
    {
        cv::Mat image;
        _videoCapture.read(image);

        if(image.cols > 0)
        {
            cv::Mat grayImage;
            cv::cvtColor(image,grayImage, cv::COLOR_BGR2GRAY);


            cv::SimpleBlobDetector::Params params;
            params.minThreshold = MinThreshold;
            params.maxThreshold = MaxThreshold;
            params.filterByArea = FilterbyArea;
            params.minArea = MinArea;
            params.maxArea = MaxArea;
            params.filterByCircularity = FilterByCircularity;
            params.minCircularity = MinCircularity;
            params.maxCircularity = MaxCircularity;
            params.filterByInertia = FilterByInertia;
            params.minInertiaRatio = MinInertia;
            params.maxInertiaRatio = MaxInertia;


            _detector = cv::SimpleBlobDetector::create(params);



            std::vector<cv::KeyPoint> keypoints;
            _detector->detect(grayImage, keypoints);

            cv::Mat im_with_keypoints;
            if(keypoints.size() > 0)
            {
                cv::Mat keypointsImage(grayImage.rows,grayImage.cols, CV_8UC3, cv::Scalar(255,0,255));

                foreach(cv::KeyPoint keypoint, keypoints)
                {
                    int radian = keypoint.size / 2;
                    QString sizetext = QString("Size:%1").arg(3.14 * radian *radian);
                    cv::circle(keypointsImage,keypoint.pt,radian,cv::Scalar(255,0,0));
                    cv::circle(image,keypoint.pt,radian,cv::Scalar(255,0,0));
                    //cv::putText(keypointsImage,sizetext.toUtf8().constData(),keypoint.pt,1,1,cv::Scalar(255,0,0));

                }

                if(keypoints.size() == 4)
                {
//                    float x1 = keypoints[0].pt.x;
//                    float x2 = keypoints[1].pt.x;
//                    float x3 = keypoints[2].pt.x;
//                    float y1 = keypoints[0].pt.y;
//                    float y2 = keypoints[1].pt.y;
//                    float y3 = keypoints[2].pt.y;

//                    float distance1 = qSqrt(((x1-x2) *(x1-x2)) + ((y1-y2)* (y1-y2)));
//                    float distance2 = qSqrt(((x1-x3) *(x1-x3)) + ((y1-y3)* (y1-y3)));
//                    float distance3 = qSqrt(((x3-x2) *(x3-x2)) + ((y3-y2)* (y3-y2)));
//                    cv::Point distance1Point = cv::Point((x1+x2)/2, (y1+y2)/2);
//                    cv::Point distance2Point = cv::Point((x1+x3)/2, (y1+y3)/2);
//                    cv::Point distance3Point = cv::Point((x3+x2)/2, (y3+y2)/2);
//                    cv::putText(keypointsImage,std::to_string(distance1),distance1Point,1,1,cv::Scalar(255,0,0));
//                    cv::putText(keypointsImage,std::to_string(distance2),distance2Point,1,1,cv::Scalar(255,0,0));
//                    cv::putText(keypointsImage,std::to_string(distance3),distance3Point,1,1,cv::Scalar(255,0,0));


                    //Perspective correction
//                    cv::Mat contentAreaImage = cv::Mat(100,200, CV_8UC1, cv::Scalar(255,255,255));
//                    std::vector<cv::Point2f> inputPoints, outputPoints;

                    //find the biggest and smallest points
                    int biggestPointIndex = 0;
                    int smallestPointIndex = 0;

                    for(int i = 1; i < 4; i++)
                    {
                        if(keypoints[i].size > keypoints[biggestPointIndex].size)
                        {
                            biggestPointIndex = i;
                        }

                        if(keypoints[i].size < keypoints[smallestPointIndex].size)
                        {
                            smallestPointIndex = i;
                        }
                    }

                    int topLeftPointIndex = 0;
                    int bottomRightIndex = 0;
                    int leftDistance = 9999999;
                    int rightDistance = 999999;
                    for(int i = 0; i < 4; i++)
                    {
                        if(i != biggestPointIndex && i != smallestPointIndex)
                        {
                            int bigDistance = cv::norm(keypoints[biggestPointIndex].pt - keypoints[i].pt);
                            int smallDistance = cv::norm(keypoints[smallestPointIndex].pt - keypoints[i].pt);
                            if(bigDistance < leftDistance)
                            {
                                topLeftPointIndex = i;
                                leftDistance = bigDistance;
                            }
                            if(smallDistance < rightDistance)
                            {
                                bottomRightIndex = i;
                                rightDistance = smallDistance;
                            }
                        }
                    }

                    cv::putText(keypointsImage,"TL",keypoints[topLeftPointIndex].pt,1,1,cv::Scalar(255,0,0));
                    cv::putText(keypointsImage,"TR",keypoints[smallestPointIndex].pt,1,1,cv::Scalar(255,0,0));
                    cv::putText(keypointsImage,"BL",keypoints[biggestPointIndex].pt,1,1,cv::Scalar(255,0,0));
                    cv::putText(keypointsImage,"BR",keypoints[bottomRightIndex].pt,1,1,cv::Scalar(255,0,0));


                    cv::Mat contentAreaImage = cv::Mat(200,400, CV_8UC1, cv::Scalar(255,255,255));
                    std::vector<cv::Point2f> inputPoints, outputPoints;

                    inputPoints.push_back(keypoints[topLeftPointIndex].pt);
                    inputPoints.push_back(keypoints[smallestPointIndex].pt);
                    inputPoints.push_back(keypoints[bottomRightIndex].pt);
                    inputPoints.push_back(keypoints[biggestPointIndex].pt);

                    outputPoints.push_back(cv::Point2f(0,0));
                    outputPoints.push_back(cv::Point2f(contentAreaImage.cols - 1,0));
                    outputPoints.push_back(cv::Point2f(contentAreaImage.cols - 1, contentAreaImage.rows -1));
                    outputPoints.push_back(cv::Point2f(0,contentAreaImage.rows -1));


                    cv::Mat lamda = cv::getPerspectiveTransform(inputPoints, outputPoints);
                    cv::warpPerspective(image,contentAreaImage,lamda,contentAreaImage.size());
                    cv::imshow("contentAreaImage",contentAreaImage);

                    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
                    ocr->Init(nullptr, "eng", tesseract::OEM_LSTM_ONLY);
                    ocr->SetImage(contentAreaImage.data, contentAreaImage.cols, contentAreaImage.rows,3,image.step);
                    QString contentText = QString(ocr->GetUTF8Text());
                    ocr->End();
                    delete ocr;
                    int t = 0;
                }

                cv::imshow("keypointsImage", keypointsImage);
            }
            cv::drawKeypoints( grayImage, keypoints, im_with_keypoints, cv::Scalar(0,0,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

            // Show blobs
            //cv::imshow("keypoints", im_with_keypoints );


            cv::imshow("image",image);
            //cv::imshow("grayImage",grayImage);
            _detector->clear();
        }
    }
}

void BGBlobDetector::MouseCallBack(int event, int x, int y, int flags, void *userdata)
{

}
