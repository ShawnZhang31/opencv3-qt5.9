#ifndef LINEFINDER_H
#define LINEFINDER_H
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#define PI 3.1415926
class LineFinder
{
private:
    //原始图像
    cv::Mat img;

    //包含被检测直线的端点的向量
    std::vector<cv::Vec4i> lines;

    //累加器分辨率参数
    double deltaRho;
    double deltaTheta;

    //确认直线之前必须收到的最小投票数
    int minVote;

    //直线的最小长度
    double minLength;

    //直线上允许的最大空隙
    double maxGap;

public:
    //默认累加分辨率是1像素，1度
    //没有空隙，没有最小长度
    LineFinder():deltaRho(1),deltaTheta(PI/180),minVote(10),minLength(0.0),maxGap(0.0)
    {

    }

    // 设置累加器的分辨率
    void setAccResolution(double dRho, double dTheta)
    {
        deltaRho=dRho;
        deltaTheta=dTheta;
    }

    // 设置最小投票数
    void setMinVote(int minv)
    {
        minVote=minv;
    }

    //设置直线长度和空隙
    void setLineLengthAndGap(double length, double gap)
    {
        minLength=length;
        maxGap=gap;
    }

    // 应有概率霍夫变换
    std::vector<cv::Vec4i> findLines(cv::Mat& binary)
    {
        lines.clear ();
        cv::HoughLinesP (binary,lines,
                         deltaRho,deltaTheta,minVote,
                         minLength,maxGap);
        return lines;
    }

    // 在图像上绘制检测到的直线
    void drawDetectedLines(cv::Mat &image,
                           cv::Scalar color=cv::Scalar(255,255,255))
    {
        // 画直线
        std::vector<cv::Vec4i>::const_iterator it2=lines.begin ();

        while (it2!=lines.end ())
        {
            cv::Point pt1((*it2)[0],(*it2)[1]);
            cv::Point pt2((*it2)[2],(*it2)[3]);

            cv::line (image,pt1,pt2,color);

            ++it2;
        }
    }
};
#endif // LINEFINDER_H
