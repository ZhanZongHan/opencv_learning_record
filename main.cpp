#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    Mat src = imread("//home/zzh/图片/cat.jpg");
    imshow("src", src);
    Mat dst;
    blur(src, dst, Size(15, 15));
    imshow("dst", dst);
    imwrite("blur_cat.jpg", dst);
    waitKey(0);
    return 0;
}