#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("/home/zzh/图片/circle.jpg");
    if(!src.data) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    Mat gray_src, dst;
    cvtColor(src, gray_src, CV_BGR2GRAY);
    medianBlur(gray_src, dst, 3);

    vector<Vec3f> circles;
    HoughCircles(dst, circles, CV_HOUGH_GRADIENT, 1, 20, 100, 30, 5, 100);
    for(int i = 0; i < circles.size(); i++) {
        Vec3f c = circles[i];
        circle(src, Point(c[0], c[1]), c[2], Scalar(255, 0, 0), 3, LINE_8);
        circle(src, Point(c[0], c[1]), 2, Scalar(255, 0, 0), 3, LINE_8);
    }
    imshow("dst", dst);
    imshow("src_after", src);
    waitKey(0);
    return 0;
}