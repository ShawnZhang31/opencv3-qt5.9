#include "mainwindow.h"
#include <QApplication>

#pragma once
#include <harrisdetector.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define IMAGE_DIR "/Users/zhangxiaomin/Works/A02-PrivateThings/Learning/OpenCV/OpenCV3-Learning/opencv3-learning/images/"


int main()
{
    QString fileName="church01.jpg";
    QString filePath=IMAGE_DIR+fileName;

    cv::Mat image=cv::imread (filePath.toStdString (),0);

    //检测角点
    cv::Mat cornerStrength;
    cv::cornerHarris (image,
                      cornerStrength,
                      3,
                      3,
                      0.01);

    //二值化处理
    cv::Mat harrisCorners;
    cv::threshold (cornerStrength,harrisCorners,0.0001,255,cv::THRESH_BINARY_INV);

    cv::imshow ("corners",harrisCorners);

    HarrisDetector harris;
    harris.detect (image);
    std::vector<cv::Point> pts;
    harris.getCorners (pts,0.02);
    harris.drawOnImage (image,pts);

    cv::namedWindow ("Corners");
    cv::imshow ("Corners",image);

    cv::waitKey (0);

    return 0;
}
