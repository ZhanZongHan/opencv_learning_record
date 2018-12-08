#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;

int main() {
    Mat src = imread("../images/picture.jpeg");
    if(!src.data) {
        cout << "image doesn't exist!" << endl;
        return -1;
    }
    imshow("src", src);


    Mat dst = src.clone();
//    dst.create(src.size(), src.type());
    cvtColor(src, dst, CV_BGR2GRAY);
    imshow("dst", dst);
    int height = src.rows;
    int width = src.cols;
    int channels = src.channels();
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(channels == 1) {
                int gray = dst.at<uchar>(i, j);
                dst.at<uchar>(i, j) = 255 - gray;
            } else if (channels == 3) {
                int b = src.at<Vec3b>(i, j)[0];
                int g = src.at<Vec3b>(i, j)[1];
                int r = src.at<Vec3b>(i, j)[2];
                src.at<Vec3b>(i , j)[0] = 255 - b;  // 对每个像素值进行改变操作
                src.at<Vec3b>(i , j)[1] = 255 - g;
                src.at<Vec3b>(i , j)[2] = 255 - r;

                dst.at<uchar>(i,j) = max(b, max(g, r));
            }
        }
    }
    imshow("dst_after", dst);
//    Mat dst1;
//    bitwise_not(dst, dst1); // 对每个像素值取非
    imshow("src_after", src);
    waitKey(0);
    return 0;
}