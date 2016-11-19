/*
绘制灰度直方图
*/
#include <cv.h>
#include <highgui.h>
#include <math.h>

using namespace cv;
using namespace std;

int hist(Mat image)
{
    const int channels[1]={0};
    const int histSize[1]={256};
    float hranges[2]={0,255};
    const float* ranges[1]={hranges};
    MatND hist;
    calcHist(&image,1,channels,Mat(),hist,1,histSize,ranges);
    
    double maxVal=0;
    double minVal=0;

    //找到直方图中的最大值和最小值
    minMaxLoc(hist,&minVal,&maxVal,0,0);
    printf("%f,%f", maxVal, minVal);
    int histSizer=hist.rows;
    Mat histImg(histSizer+20,histSizer+20,CV_8UC3,Scalar(180,180,180));
    rectangle(histImg, Rect(Point(10,10),Point(histSizer+10,histSizer+10)),Scalar(255,255,255),-1,8);

    for(int h=0;h<histSizer;h++)
    {
        float histVal=hist.at<float>(h);
        int length=static_cast<int>(histVal*histSizer/maxVal);
        line(histImg,Point(h+10,histSizer+10),Point(h+10,histSizer-length+10),Scalar(h,h,h));
    }
    
    namedWindow("hist", CV_WINDOW_AUTOSIZE);
    imshow("hist", histImg);
    waitKey(0);
    waitKey(0);
    
}

int main(int argc, char **argv)
{
    Mat src, gray, dst;
    const char* name = argc==2 ? argv[1] : "img/p4.jpg";
    
    src = imread(name, 1);
    cvtColor(src, gray, CV_BGR2GRAY);
    namedWindow("gray", CV_WINDOW_AUTOSIZE);
    imshow("gray", gray);
    waitKey(0);
    
    hist(gray);
    
    return 0; 
}
