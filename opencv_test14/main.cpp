#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src, gray_src;
    src = imread("/home/zzh/图片/reba.jpeg");
    if(src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    GaussianBlur(src, gray_src, Size(3, 3), 0, 0);
    cvtColor(gray_src, gray_src, CV_RGB2GRAY);
    imshow("gray_src", gray_src);
    Mat x_grad, y_grad, xy_grad;
//    Sobel(gray_src, x_grad, CV_16S, 1, 0);
//    Sobel(gray_src, y_grad, CV_16S, 0, 1);
    Scharr(gray_src, x_grad, CV_16S, 1, 0);
    Scharr(gray_src, y_grad, CV_16S, 0, 1);

    convertScaleAbs(x_grad, x_grad);
    convertScaleAbs(y_grad, y_grad);
    addWeighted(x_grad, 0.5, y_grad, 0.5, 0, xy_grad);
    imshow("x_grad", x_grad);
    imshow("y_grad", y_grad);
    imshow("xy_grad", xy_grad);
    waitKey(0);
    return 0;
}