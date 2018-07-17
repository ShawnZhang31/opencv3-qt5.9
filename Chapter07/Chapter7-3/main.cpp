#include "mainwindow.h"
#include <QApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <linefinder.h>
#include<math.h>
#include <iostream>

#define IMAGE_DIR "/Users/zhangxiaomin/Works/A02-PrivateThings/Learning/OpenCV/OpenCV3-Learning/opencv3-learning/images/"
//#define PI 3.1415926
int main()
{
    QString fileName="road.jpg";
    QString filePath=IMAGE_DIR+fileName;

    cv::Mat image=cv::imread (filePath.toStdString ());

    //应用Canny算法
    cv::Mat contours;
    cv::Canny (image,       //灰度图像
               contours,    //输出轮廓
               125,         //低阈值
               350);        //高阈值


    // 创建LineFinder类的实例
    LineFinder finder;

    // 设置概率霍夫变换的参数
    finder.setLineLengthAndGap (20,0);
    finder.setMinVote (60);

    // 检测直线并画线
    std::vector<cv::Vec4i> lines=finder.findLines (contours);
    finder.drawDetectedLines (image);

    cv::imshow ("image",image);

    QString fileName2="chariot.jpg";
    QString filePath2=IMAGE_DIR+fileName2;
    cv::Mat chariot=cv::imread (filePath2.toStdString (),0);

    cv::GaussianBlur (chariot,chariot,cv::Size(5,5),1.5);

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles (chariot,circles,cv::HOUGH_GRADIENT,
                      2,    // 累加器分辨率
                      50,   // 两个圆之间的最小距离
                      200,  // Canny算子的高阈值
                      100,  // 最小投票数
                      25,   //最小半径
                      100); //最大半径

    std::vector<cv::Vec3f>::const_iterator itc=circles.begin ();
    while (itc!=circles.end ())
    {
        std::cout<<"x="<<(*itc)[0]<<";y="<<(*itc)[1]<<";r="<<(*itc)[2]<<std::endl;

        cv::circle (chariot,
                    cv::Point((*itc)[0],(*itc)[1]),
                    (int)(*itc)[2],
                    cv::Scalar(255,255,255),
                    2);


        ++itc;
    }

    cv::imshow ("circle",chariot);

    cv::waitKey (0);
    return 0;
}
