#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("/home/zzh/图片/cat.jpg");
    if(src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    Mat dst;
//    pyrUp(src, dst, Size(src.cols * 2, src.rows * 2));  // 上采样
//    imshow("dst_up", dst);
//
//    pyrDown(src, dst, Size(src.cols / 2, src.rows / 2));    // 降采样
//    imshow("dst_down", dst);

    // 高斯不同 DOG
    Mat g1, g2;
    cvtColor(src, src, CV_RGB2GRAY);
    GaussianBlur(src, g1, Size(5, 5), 0, 0);
    GaussianBlur(g1, g2, Size(5, 5), 0, 0);
    subtract(g1, g2, dst, Mat());
    normalize(dst, dst, 255, 0, NORM_MINMAX);   // 归一化
 //   threshold(dst, dst, 0, 255, THRESH_OTSU);
    imshow("dst_dog", dst);
    waitKey(0);
    return 0;
}