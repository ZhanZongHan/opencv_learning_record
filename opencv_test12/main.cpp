#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("/home/zzh/图片/reba.jpeg");
    if(!src.data) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    Mat dst_x, dst_y, dst;
    // 常见算子： Robert算子， Sobel算子， 拉普拉斯算子
    //  Robert_x
    Mat kernel;
    kernel = (Mat_<int>(2, 2) << 1, 0, 0, -1);
    filter2D(src, dst_x, -1, kernel);
    imshow("dst_x", dst_x);
    //Robert_y
    kernel = (Mat_<int>(2, 2) << 0, 1, -1, 0);
    filter2D(src, dst_y, -1, kernel);
    imshow("dst_y", dst_y);

    add(dst_x, dst_y, dst);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}