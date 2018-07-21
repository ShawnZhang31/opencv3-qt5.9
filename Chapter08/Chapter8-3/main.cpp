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

    // 关键点的向量
    std::vector<cv::KeyPoint> keypoints;

    // FAST特征检测器，阈值为40
    cv::Ptr<cv::FastFeatureDetector> ptrFAST=cv::FastFeatureDetector::create (40);

    // 检测关键点
    ptrFAST->detect (image,keypoints);

    cv::drawKeypoints (image,keypoints,image,cv::Scalar(0,255,0),cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);

    cv::imshow ("image",image);
    cv::waitKey (0);

    return 0;
}
