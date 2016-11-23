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
    Mat src, dst;
    const char* name = argc==2 ? argv[1] : "img/p4.jpg";
    
    
    src = imread(name, 1);
    
    
    
    int width=src.cols;
    int height=src.rows;
    
    dst=Mat::zeros(tar,tar,CV_8UC(3));    
    
    namedWindow("a", CV_WINDOW_AUTOSIZE);
    imshow("a", dst2);
    waitKey(0);
    
    
    
    return 0; 
}
