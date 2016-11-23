/*
绘图
*/
#include <cv.h>
#include <highgui.h>
#include <math.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat canvas(400,400,CV_8UC3,Scalar(255,255,255));
    
    line(canvas, Point(10,10),Point(100,10),Scalar(0), 1, 8);
    line(canvas, Point(10,20),Point(200,20),Scalar(50), 2, 4);
    line(canvas, Point(10,40),Point(300,30),Scalar(100,200,255), 3, 2);
    line(canvas, Point(10,80),Point(400,40),Scalar(200), 4, 1);
    
    rectangle(canvas, Rect(Point(0,200),Point(40,280)),Scalar(0,0,255),-1,8);
    rectangle(canvas, Rect(Point(40,200),Point(80,280)),Scalar(0,255,0),4,8);
    rectangle(canvas, Rect(Point(80,200),Point(120,280)),Scalar(255,255,0),8,8);
    
    circle(canvas, Point(50,50),10, Scalar(0,0,255),2);
    circle(canvas, Point(300,100),5, Scalar(0,255,0),3);
    circle(canvas, Point(250,350),15, Scalar(255,0,0),4);        
    ellipse(canvas, Point(50,300),Size(20,10),0,0,300,Scalar(255,0,255),5);
    
    putText(canvas,"(50,50)",Point(50,50),1,1,Scalar(0));
    putText(canvas,"(300,100)",Point(300,100),1,1,Scalar(0));
    putText(canvas,"(250,350)",Point(250,350),1,1,Scalar(0));
    putText(canvas,"(50,300)",Point(50,300),1,1,Scalar(0));
    
    Point ps[1][5];
    ps[0][0] = Point(50,50);
    ps[0][1] = Point(300,100);
    ps[0][2] = Point(250,350);
    ps[0][3] = Point(50,300);            
    const Point* pts[1]={ps[0]};
    int pn[1]={4};
    polylines(canvas,pts,pn,1,true,Scalar(0));
    
    namedWindow("canvas", CV_WINDOW_AUTOSIZE);
    imshow("canvas", canvas);
    waitKey(0);
    
    return 0; 
}
