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

    cv::Mat image1=cv::imread (filePath.toStdString ());
    cv::Mat image2=image1.clone ();

    // 定义特征检测器
    cv::Ptr<cv::FeatureDetector> ptrDetector;       //泛型检测器指针
    ptrDetector=cv::FastFeatureDetector::create (80);       // 这里选用FAST检测器

    // 检测关键点
    std::vector<cv::KeyPoint> keypoints1;
    std::vector<cv::KeyPoint> keypoints2;

    ptrDetector->detect (image1,keypoints1);
    ptrDetector->detect (image2,keypoints2);

    // 定义一个11x11的矩形，用于表示每个关键点周围的图像块
    // 定义正方形的领域
    const int nsize(11);
    cv::Rect neighborhood(0,0,nsize,nsize);         // 领域的尺寸
    cv::Mat patch1;
    cv::Mat patch2;

    /* 将一幅图像的关键点与另一幅图像的全部关键点进行比较。
     * 在第二幅图像中找出与第一幅图像中的关键点最相似的图像块。
     */
    // 在第二幅图像上找出与第一幅图像中的每个关键点最匹配的
    cv::Mat result;
    std::vector<cv::DMatch> matches;

    // 针对图像1的全部关键点
    for(int i=0;i<keypoints1.size ();i++)
    {
        // 定义图像块
        neighborhood.x=keypoints1[i].pt.x-nsize/2;
        neighborhood.y=keypoints1[i].pt.y-nsize/2;

        // 如果领域超出图像范围，就继续处理下一个点
        if(neighborhood.x<0 || neighborhood.y<0 ||
           neighborhood.x+nsize >=image1.cols ||
           neighborhood.y+nsize >=image1.rows)
            continue;

        // 第一幅图像的块
        patch1=image1(neighborhood);

        // 存放最匹配的值
        cv::DMatch bestMatch;

        // 针对第二幅图像的全部关键点
        for(int j=0;j<keypoints2.size ();j++)
        {
            // 定义图像块
            neighborhood.x = keypoints2[j].pt.x-nsize/2;
            neighborhood.y = keypoints2[j].pt.y-nsize/2;

            // 如果领域超出图像范围，就处理下一点
            if(neighborhood.x<0 || neighborhood.y<0 ||
               neighborhood.x + nsize >=image2.cols ||
               neighborhood.y + nsize >=image2.rows)
                continue;

            // 第二幅图像的块
            patch2=image2(neighborhood);

            // 匹配两个图像块
            cv::matchTemplate (patch1,patch2,result,cv::TM_SQDIFF);

            // 检查是否为最佳匹配
            if(result.at<float>(0,0)<bestMatch.distance)
            {
                bestMatch.distance=result.at<float>(0,0);
                bestMatch.queryIdx=i;
                bestMatch.trainIdx=j;
            }
        }

        // 添加最佳匹配
        matches.push_back (bestMatch);
    }


    /*
     * 两个图像块越相似，他们对应着同一个场景点的可能性就越大，因此需要根据相似度对匹配结果进行排序
     */
    //提取25个最佳匹配项
//    std::nth_element(matches.begin (),matches.begin ()+25,matches.end ());
//    matches.erase (matches.begin ()+25,matches.end ());

    // 画出匹配结果
    cv::Mat matchImage;
    cv::drawMatches (image1,keypoints1,
                     image2,keypoints2,
                     matches,matchImage,
                     cv::Scalar(255,255,255),
                     cv::Scalar(255,255,255));


    cv::imshow ("Matches",matchImage);



    cv::waitKey (0);

    return 0;
}
