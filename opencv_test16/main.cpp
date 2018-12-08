#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("/home/zzh/图片/cat.jpg");
    if(!src.data) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    Mat gray_src, dst;
    GaussianBlur(src, gray_src, Size(3,3), 0, 0);
//    cvtColor(gray_src, gray_src, CV_RGB2GRAY);
 //   Laplacian(gray_src, dst, CV_16S, 3);
    Laplacian(src, dst, CV_8U, 3);
    Mat dst2 = src - dst;   // 源图像减去Laplacian算子可以增强对比度
//    convertScaleAbs(dst, dst);
//    threshold(dst, dst, 0, 255, THRESH_OTSU | THRESH_BINARY);

    imshow("dst", dst2);

    waitKey(0);
    return 0;
}