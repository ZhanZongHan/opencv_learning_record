#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat src;
    src = imread("/home/zzh/图片/wangzuxian.jpeg");
    if(src.empty()) {
        cout << "can not load image!" << endl;
        return -1;
    }
    imshow("src", src);

    int height = src.rows;
    int width = src.cols;
    int channels = src.channels();
    Mat dst;
    dst = Mat::zeros(src.size(), src.type());

    // g(x, y) = alpha*f(x, y) + beta;
    double alpha = 1.2;
    double beta = 10;
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(channels == 3) {
                float b = src.at<Vec3b>(i, j)[0];
                float g = src.at<Vec3b>(i, j)[1];
                float r = src.at<Vec3b>(i, j)[2];
                dst.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(alpha*b + beta);
                dst.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(alpha*g + beta);
                dst.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(alpha*r + beta);

                imshow("dst", dst);
            }
        }
    }
    waitKey(0);
    return 0;
}