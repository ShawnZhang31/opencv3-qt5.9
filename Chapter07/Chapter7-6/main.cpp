#include "mainwindow.h"
#include <QApplication>

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

    // 测试边框
    cv::Rect r0=cv::boundingRect (contours[0]);
    //画矩形
    cv::rectangle (result,r0,cv::Scalar(120),2);

    //测试覆盖圆
    float radius;
    cv::Point2f center;
    cv::minEnclosingCircle (contours[1], center, radius);
    //画圆形
    cv::circle (result,center,static_cast<int>(radius),0,2);

    // 测试多边形逼近
    std::vector<cv::Point> poly;
    cv::approxPolyDP (contours[2], poly, 5, true);
    // 画多边形
    cv::polylines (result,poly,true,0,2);

    //测试凸包
    std::vector<cv::Point> hull;
    cv::convexHull (contours[3],hull);
    //画多边形
    cv::polylines (result,hull,true,0,2);

    //画重心
    itc=contours.begin ();
    while (itc!=contours.begin ())
    {
        //计算所有轮廓
        cv::Moments mom=cv::moments (cv::Mat(*itc++));
        //画重心
        cv::circle (result,
                    cv::Point(mom.m10/mom.m00, mom.m01/mom.m00),
                    2, cv::Scalar(0),2);
    }


    cv::imshow ("image",image);
    cv::imshow ("result",result);

    cv::waitKey (0);
    return 0;
}
