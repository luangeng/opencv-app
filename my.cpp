/*
 * A Demo to learn openCV
 */
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/legacy/compat.hpp"

#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;
static void help()
{
    printf("This is a test function\n");
    return;
}

void resize(IplImage* image)
{
    CvSize size;
    double bb=0.5;
    size.width=image->width * bb;
    size.height=image->height * bb;
    printf("\nbefore:%d, after:%d\n", image->width,size.width);
    
    IplImage* image2 = cvCreateImage(size, image->depth, image->nChannels);
    cvResize(image,image2);
    
    cvNamedWindow("resize", 1);
    cvShowImage("resize", image2 );
    cvWaitKey(0);
    cvDestroyWindow("resize");
    
//    cvSaveImage("love.png", image2);
    cvReleaseImage(&image2);
}
//黑白两色图
void binary(IplImage* image)
{
    //创建并转为单通道灰度图
    IplImage* gray = cvCreateImage(cvGetSize(image), 8, 1);
    cvCvtColor(image,gray, CV_BGR2GRAY);
    
    //转为2色图
    IplImage* binary = cvCreateImage(cvGetSize(image), 8, 1);
    cvThreshold(gray, binary, 200, 255, 2);
    
    cvNamedWindow("1", 1);
    cvShowImage("1", binary);
    cvWaitKey(0);
    cvDestroyWindow("1");
    
//    cvSaveImage("love.png", image2);
    cvReleaseImage(&binary);
    cvReleaseImage(&gray);
}

//灰度直方图
void hist(IplImage* image)
{
    //单通道灰度图
    IplImage* gray = cvCreateImage(cvGetSize(image), 8, 1);
    cvCvtColor(image,gray, CV_BGR2GRAY);
    
    int histSize = 256;
    float range[] = {0,255};
    float *pRange[] = {range};
    CvHistogram *hist = cvCreateHist(1, &histSize, CV_HIST_ARRAY, pRange);
    cvCalcHist(&gray, hist);
    
    int histWidth=255, histHeight=150;
    int scale = 1;
    IplImage* histImage = cvCreateImage(cvSize(histWidth*scale,histHeight), 8, 3);
    cvSet(histImage, CV_RGB(0,0,255));
    
    float maxValue = 0;
    cvGetMinMaxHistValue(hist, NULL, &maxValue,NULL,NULL);
    
    for(int i=0; i<histWidth; i++){
        float value = cvQueryHistValue_1D(hist, i);
        int realHeight = cvRound(value/maxValue*histHeight);
        cvRectangle(histImage, 
            cvPoint(i*scale, histHeight), 
            cvPoint((i+1)*scale-1,histHeight-realHeight),
            CV_RGB(i,i,i), CV_FILLED);
    }
    
    // Show image
    cvNamedWindow("1", CV_WINDOW_AUTOSIZE);
    cvShowImage("1", histImage);
    cvWaitKey(0);
    cvDestroyWindow("1");
    
    cvReleaseImage(&histImage);
    cvReleaseImage(&gray);
}

//均衡化
void equalize(IplImage* image)
{
    //创建并转为单通道灰度图
    IplImage* gray = cvCreateImage(cvGetSize(image), 8, 1);
    cvCvtColor(image,gray, CV_BGR2GRAY);
    
    //转为2色图
    IplImage* equa = cvCreateImage(cvGetSize(image), 8, 1);
    cvEqualizeHist(gray, equa);
    
    cvNamedWindow("1", 1);
    cvShowImage("1", equa);
    cvNamedWindow("2", 1);
    cvShowImage("2", gray);
    cvWaitKey(0);
    cvDestroyWindow("1");
    cvDestroyWindow("2");
    
//    cvSaveImage("love.png", image2);
    cvReleaseImage(&equa);
    cvReleaseImage(&gray);
}

//彩色直方图均衡化
void equalize2(IplImage* image)
{
    IplImage* created = cvCreateImage(cvGetSize(image), 8, 3);
    const int maxChannel = 3;
    IplImage* pImageChannel[maxChannel] = {NULL};
    
    for(int i=0; i< maxChannel; i++){
        pImageChannel[i] = cvCreateImage(cvGetSize(image), 8,1);
    }
    cvSplit(image, pImageChannel[0], pImageChannel[1],
         pImageChannel[2], NULL);
    
    for(int i=0; i< image->nChannels; i++){
        cvEqualizeHist(pImageChannel[i], pImageChannel[i]);
    }
    
    cvMerge(pImageChannel[0], pImageChannel[1],pImageChannel[2],
        NULL, created);
        
    for(int i=0; i< image->nChannels; i++){
        cvReleaseImage(&pImageChannel[i]);
    }
        
    cvNamedWindow("1", 1);
    cvShowImage("1", created);
    cvWaitKey(0);
    cvDestroyWindow("1");
    
    cvSaveImage("shasha.png", created);
    cvReleaseImage(&created);
}

int main(int argc, char** argv)
{
    const char* image_name = argc == 2 ? argv[1] : "love.png";

    cv::initModule_nonfree();
    help();

    IplImage* image = cvLoadImage( image_name, CV_LOAD_IMAGE_UNCHANGED );
    if( !image )
    {
        fprintf( stderr, "Can not load %s .", image_name );
        exit(-1);
    }

    CvMemStorage* storage = cvCreateMemStorage(0);
    
    hist(image);
    //equalize2(image);
    
    
    
    
//    cvNamedWindow("before", 1);
//    cvShowImage("before", image );
//    cvWaitKey(0);
//    cvDestroyWindow("before");
    
    cvReleaseImage(&image);
    
    return 0;
}









