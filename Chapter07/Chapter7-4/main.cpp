#include "mainwindow.h"
#include <QApplication>

#include <linefinder.h>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define IMAGE_DIR "/Users/zhangxiaomin/Works/A02-PrivateThings/Learning/OpenCV/OpenCV3-Learning/opencv3-learning/images/"
int main()
{
    QString fileName="road.jpg";
    QString filePath=IMAGE_DIR+fileName;
    cv::Mat image=cv::imread (filePath.toStdString ());

    cv::Mat contours;
    cv::Canny (image,contours,
               100,
               350);

    LineFinder finder;
    finder.setLineLengthAndGap (100,20);
    finder.setMinVote (60);

    std::vector<cv::Vec4i> lines=finder.findLines (contours);
    std::vector<cv::Vec4i>::const_iterator it=lines.begin ();

    while (it != lines.end ())
    {
        std::cout<<"x0="<<(*it)[0]<<";y0="<<(*it)[1]<<std::endl;
        std::cout<<"x1="<<(*it)[2]<<";y2="<<(*it)[3]<<std::endl;

        cv::line (image,cv::Point((*it)[0],(*it)[1]),cv::Point((*it)[2],(*it)[2]),cv::Scalar(255,0,0),1);

        ++it;
    }

    int n=2;    //选用直线
    // 黑色图像
    cv::Mat oneline(contours.size(),CV_8U,cv::Scalar(0));

    // 白色直线
    cv::line (oneline,cv::Point(lines[n][0],lines[n][1]),
                      cv::Point(lines[n][2],lines[n][2]),
                      cv::Scalar(255),
                      3);

    cv::bitwise_and (contours,oneline,oneline);

    std::vector<cv::Point> points;

    //迭代遍历像素，得到所有点的位置
    for(int y=0;y<oneline.rows;y++)
    {
        uchar* rowPtr = oneline.ptr<uchar>(y);

        for(int x=0;x<oneline.cols;x++)
        {
            if(rowPtr[x])
            {
                points.push_back (cv::Point(x,y));
            }
        }
    }

    cv::Vec4f line;
    cv::fitLine (points,line,
                 cv::DIST_L2,
                 0,
                 0.01,0.01);

    int x0=line[2];
    int y0=line[3];
    int x1=x0+100*line[0];
    int y1=y0+100*line[1];

    cv::line (image,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar(0,0,255),3);

    cv::imshow ("image",image);
    cv::imshow ("oneline",oneline);

    cv::waitKey (0);
    return 0;
}
