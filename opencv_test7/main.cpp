#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat src = imread("/home/zzh/图片/jiaoyan.png");
    if(src.empty()) {
        cout << "can not load image!" << endl;
        return -1;
    }
    imshow("src", src);

//    Mat dst;
//    blur(src, dst, Size(21, 21));
//    imshow("dst", dst);

//    Mat dst_Gaussian;
//    GaussianBlur(src, dst_Gaussian, Size(21, 21), 10);  //Size()参数均为奇数，为取中心点
//    imshow("dst_Gaussian", dst_Gaussian);

    Mat dst_median;
    medianBlur(src, dst_median, 11);
    imshow("dst_median", dst_median);

//    Mat dst_bilateral;
//    bilateralFilter(src, dst_bilateral, 15, 100, 3);
//    imshow("dst_bilateral", dst_bilateral);
//
//    Mat result;
//    Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
//    filter2D(dst_bilateral, result, -1, kernel);    // 在双边模糊的基础上再锐化d
//    imshow("result", result);

    waitKey(0);
    return 0;
}