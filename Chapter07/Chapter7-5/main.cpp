#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define IMAGE_DIR "/Users/zhangxiaomin/Works/A02-PrivateThings/Learning/OpenCV/OpenCV3-Learning/opencv3-learning/images/"

int main()
{
    QString fileName="binaryGroup.bmp";
    QString filePath=IMAGE_DIR+fileName;

    cv::Mat image = cv::imread (filePath.toStdString (),0);

    //用于存储轮廓的向量
    std::vector<std::vector<cv::Point>> contours;

    cv::findContours (image,
                      contours,                 // 储存轮廓的向量
                      cv::RETR_EXTERNAL,        // 检索外部轮廓
                      cv::CHAIN_APPROX_NONE);   // 每个轮廓的全部像素

    // 删除太短或太长的轮廓
    int cmin=50;    //最小轮廓长度
    int cmax=1000;  //最大轮廓长度

    std::vector<std::vector<cv::Point>>::iterator itc=contours.begin ();

    // 针对所有轮廓
    while (itc!=contours.end())
    {
        // 验证轮廓大小
        if(itc->size ()<cmin || itc->size ()>cmax)
        {
            itc=contours.erase (itc);
        }
        else
        {
            ++itc;
        }
    }

    // 在白色图像上黑色轮廓
    cv::Mat result(image.size(), CV_8U, cv::Scalar(255));
    cv::drawContours (result,contours,
                      -1,   // 画全部轮廓
                      0,    // 用黑色画
                      2);   // 宽度为2

    cv::imshow ("image",image);
    cv::imshow ("result",result);

    cv::waitKey (0);
    return 0;
}
