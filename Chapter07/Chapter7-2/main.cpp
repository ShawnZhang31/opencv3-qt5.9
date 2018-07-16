#include "mainwindow.h"
#include <QApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define IMAGE_DIR "/Users/zhangxiaomin/Works/A02-PrivateThings/Learning/OpenCV/OpenCV3-Learning/opencv3-learning/images/"

int main()
{
    QString fileName="road.jpg";
    QString filePath=IMAGE_DIR+fileName;

    cv::Mat image=cv::imread (filePath.toStdString (),0);

    //应用Canny算法
    cv::Mat contours;
    cv::Canny (image,       //灰度图像
               contours,    //输出轮廓
               125,         //低阈值
               350);        //高阈值

    cv::imshow ("image",image);
    cv::threshold (contours,contours,1,255,cv::THRESH_BINARY_INV);
    cv::imshow ("contours",contours);
    cv::waitKey (0);

    return 0;
}
