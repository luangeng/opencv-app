/*
diffusion 扩散

*/
#include <cv.h>
#include <highgui.h>
#include <math.h>

using namespace cv;
using namespace std;

uchar Max(uchar a,uchar b)
{
    return a>b?a:b;
}
int Abs(int a)
{
    return a>0?a:-a;
}

void shrink(Mat img)
{
    ///
}

void spread(Mat img, int thick)
{
    uchar *p;
    int x=img.rows;
    int y=img.cols;
    int threshold = 230; 
    for(long i=0; i< x; i++){
        p = img.ptr<uchar>(i);
        for(long j = 0; j< y; j++){
            if(p[j]==255){
                int aa = thick;
                for(int k=0-thick; k<=thick; k++){
                    if(j+k>=0 && j+k<y){
                        p[j+k]=Max(p[j+k],255-(Abs(aa)*25));
                    }
                    if(i+k>=0 && i+k<x){
                        img.ptr<uchar>(i+k)[j]=Max(img.ptr<uchar>(i+k)[j], 255-(Abs(aa)*25));
                    }
                    aa--;
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    Mat src,gray, dst;
    const char* name = argc==2 ? argv[1] : "img/sha.png";
    
    src = imread(name, 1);
    //cvtColor(src, gray, CV_BGR2GRAY);
    
    /****************************************/
    int x = 32;
    int y = 32;
    int threshold = 100;
    Mat o = Mat::zeros(x,y,CV_8UC(1));
    
    
    int thick = 1;
    int type = 8;
    ellipse(o,
            Point(x/2,x/2),
            Size(x/4,x/3),
            0,
            0,
            360,
            Scalar(255,255,255),
            thick,
            type);
            
        spread(o, 7);
    /****************************************/
    
    int rows=100;
    int cols=100;
    
    Mat sub=Mat::zeros(rows,cols,CV_8UC(1));
   // sub.create(cvSize(rows,cols), CV_8UC(1));
    
    uchar* w;
    for(long i=0; i< rows; i++){
        w=sub.ptr<uchar>(i);
        for(long j=0; j< cols; j++){
            long value = (i-50)*(i-50)+(j-50)*(j-50);
          
            if(value>30*30 && value<31*31){
                w[j]=(uchar)255;
            }
        }
    }
   
    /*
    Mat out2;
    out2.create(img.size(), img.type());
    row = out2.rows;
    col = out2.cols * out2.channels();
    p=out2.data;
    for(long i=0; i<row*col;i++){
        *(p+i) = (uchar)(255*0.5*((double)img.data[i]/255)+30);
    }
    
    */
    namedWindow("a", CV_WINDOW_AUTOSIZE);
    imshow("a", o);
    waitKey(30000);
    
    return 0; 
}
