#ifndef HARRISDETECTOR_H
#define HARRISDETECTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class HarrisDetector
{
private:
    // 32位浮点数型的角点强度图像
    cv::Mat cornerStrength;
    // 32位浮点数型的阈值化角点图像
    cv::Mat cornerTh;
    // 局部最大值图像（内部）
    cv::Mat localMax;
    // 平滑导数的邻域尺寸
    int neighborhood;
    // 梯度计算的口径
    int aperture;
    // Harris参数
    double k;
    // 阈值计算的最大强度
    double maxStrength;
    // 计算得到的阈值（内部）
    double threshold;
    // 非最大值抑制的领域尺寸
    int nonMaxSize;
    // 非最大值抑制的内核
    cv::Mat kernel;



public:
    // 构造函数
    HarrisDetector():neighborhood(3),aperture(3),k(0.01),maxStrength(0.0),threshold(0.01),nonMaxSize(3)
    {
        //创建用于非最大值抑制的内核
        setLocalMaxWindowSize(nonMaxSize);
    }

    // 创建非最大值抑制的内核
    void setLocalMaxWindowSize(int size)
    {
        nonMaxSize = size;
        kernel.create (nonMaxSize, nonMaxSize,CV_8U);
    }

    // 计算Harris角点
    void detect(const cv::Mat& image)
    {
        // 计算Harris
        cv::cornerHarris (image, cornerStrength,
                          neighborhood,         // 领域尺寸
                          aperture,             // 口径尺寸
                          k);                   // Harris参数

        // 计算内部阈值
        cv::minMaxLoc (cornerStrength,0,&maxStrength);

        // 检测局部最大值
        cv::Mat dilated;
        cv::dilate (cornerStrength,dilated,cv::Mat());
        cv::compare (cornerStrength,dilated, localMax, cv::CMP_EQ);
    }

    // 用Harris值得到角点分布图
    cv::Mat getCornerMap(double qualityLevel)
    {
        cv::Mat cornerMap;

        // 对角点强度阈值化
        threshold = qualityLevel*maxStrength;
        cv::threshold (cornerStrength,cornerTh,threshold,255,cv::THRESH_BINARY);

        //转换成8位图像
        cornerTh.convertTo (cornerMap,CV_8U);

        //非最大抑制值
        cv::bitwise_and (cornerMap,localMax,cornerMap);

        return cornerMap;
    }

    // 用Harris值得到特征值
    void getCorners(std::vector<cv::Point> &points, double qualityLevel)
    {
        // 获得角点分布图
        cv::Mat cornerMap=getCornerMap (qualityLevel);

        //获得角点
        getCorners (points,cornerMap);
    }

    // 用角点分布图得到特征值
     void getCorners(std::vector<cv::Point> &points, cv::Mat& cornerMap)
     {
         // 迭代遍历元素，得到所有特征
         for(int y=0;y<cornerMap.rows;y++)
         {
             const uchar* rowPtr=cornerMap.ptr<uchar> (y);

             for(int x=0;x<cornerMap.cols;x++)
             {
                 // 如果它是一个特征点
                 if(rowPtr[x])
                 {
                     points.push_back (cv::Point(x,y));
                 }
             }
         }

     }

    // 在特征点的位置画圆形
     void drawOnImage(cv::Mat& image,
                      const std::vector<cv::Point>& points,
                      cv::Scalar color=cv::Scalar(255,255,255),
                      int radius=3,
                      int thickness=1)
     {
        std::vector<cv::Point>::const_iterator it=points.begin ();

        // 针对所有的角点
        while (it != points.end ())
        {
            // 在每个角点位置画一个圆
            cv::circle (image,*it,radius,color,thickness);
            ++it;
        }
     }


};

#endif // HARRISDETECTOR_H
