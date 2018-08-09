#include "mainwindow.h"
#include <QApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

#define IMAGE_DIR "/Users/zhangxiaomin/Works/A02-PrivateThings/Learning/OpenCV/OpenCV3-Learning/opencv3-learning/images/"

int main()
{
    QString fileName="church01.jpg";
    QString filePath=IMAGE_DIR+fileName;

    cv::Mat image=cv::imread (filePath.toStdString ());

    cv::imshow ("image1",image);

    cv::waitKey (0);

    return 0;
}
