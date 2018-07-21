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

    // 创建SURF特征检测器对象
    cv::Ptr<cv::xfeatures2d::SurfFeatureDetector> ptrSURF=cv::xfeatures2d::SurfFeatureDetector::create (2000.0);

    // 关键特征点
    std::vector<cv::KeyPoint> keypoints;

    // 检测关键点
    ptrSURF->detect (image,keypoints);

    cv::drawKeypoints (image,keypoints,image,cv::Scalar(0,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    cv::imshow ("image",image);
    cv::waitKey (0);

    return 0;
}
