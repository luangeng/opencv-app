/*
将图像缩小或放大到32*32
*/
#include <cv.h>
#include <highgui.h>
#include <math.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat src, dst, dst2;
    const char* name = argc==2 ? argv[1] : "img/p4.jpg";
    
    int tar = 300;
    
    src = imread(name, 1);
    //cvtColor(src, gray, CV_BGR2GRAY);
    
    dst=Mat::zeros(tar,tar,CV_8UC(3));
    dst2=Mat::zeros(tar,tar,CV_8UC(3));
    
    double fx=0;
    double fy=0;
    
    int width=src.cols;
    int height=src.rows;
    
    
    
    if(width>height){
        fx=tar/(double)width;
    }else{
        fx=tar/(double)height;
    }
    
    fy=fx;
    
    resize(src, dst, Size(), fx, fx);
    //copy(dst,dst2);
    
    
    
    namedWindow("a", CV_WINDOW_AUTOSIZE);
    imshow("a", dst2);
    waitKey(0);
    
    
    
    return 0; 
}
