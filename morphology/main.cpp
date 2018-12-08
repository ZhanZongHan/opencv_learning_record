#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat src, dst, dst1, dst2;
    src = imread("/home/zzh/图片/cat.jpg");
    if (src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

//    Mat kernel = getStructuringElement(MORPH_RECT, Size(23,23));
//    erode(src, dst, kernel);
//    dilate(dst, dst, kernel);
//    morphologyEx(src, dst, CV_MOP_OPEN, kernel);

//    dilate(src, dst, kernel);
//    erode(dst, dst, kernel);
//    morphologyEx(src, dst, CV_MOP_CLOSE, kernel);
    dst = src.clone();
    Mat kernel;
    kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
//    cvtColor(src, dst, CV_RGB2GRAY);

    //   adaptiveThreshold(~dst, dst, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 15, -2);// 二值化，输入图必须是单通道的
//    morphologyEx(dst, dst, CV_MOP_OPEN, kernel);



    erode(dst, dst1, kernel);
    dilate(dst, dst2, kernel);
    Mat dst3 = dst2 - dst1; //梯度

//    bitwise_not(dst, dst);
/*  黑帽 闭图像-原图像; 顶帽：原图像-开图像
    morphologyEx(dst, dst1, MORPH_CLOSE, kernel);
    Mat dst3 = dst1 - dst;

    */
//    imshow("dst1", dst1);
//    imshow("dst2", dst2);
    imshow("dst3", dst3);
    waitKey(0);
    return 0;
}