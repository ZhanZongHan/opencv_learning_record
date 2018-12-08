#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    int r = 400;
    Mat src = Mat::zeros(Size(r, r), CV_8UC1);
    vector<Point2f> points(6);
    points[0] = Point(r/2-60, r/2-60);
    points[1] = Point(r/2+60, r/2-60);
    points[2] = Point(r/2+116, r/2);
    points[3] = Point(r/2+60, r/2+60);
    points[4] = Point(r/2-60, r/2+60);
    points[5] = Point(r/2-116, r/2);

    for(int i = 0; i < 6; i++) {
        line(src, points[i], points[(i+1)%6], Scalar(255, 255, 255));
    }
    imshow("src", src);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(src, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    Mat dists = Mat(src.size(), CV_32FC1);
    for(int i = 0; i < src.rows; i++) {
        for(int j = 0; j < src.cols; j++) {
            double dist = pointPolygonTest(contours[0], Point2f(static_cast<float>(i), static_cast<float>(j)), true);
            dists.at<float>(i, j) = static_cast<float >(dist);
        }
    }//https://hk.saowen.com/a/caf48aafeb82aa8f2a506fcaf42a1c2c5285888f7d6c1e48244911759da4a138，需要自行result查找资料，采用c++实现其功能

    double minValue, maxValue;
    minMaxLoc(dists, &minValue, &maxValue, 0, 0, Mat());
    Mat dst = Mat::zeros(src.size(), CV_8UC3);
    for(int i = 0; i < dst.rows; i++) {
        for(int j = 0; j < dst.cols; j++) {
            float dist = dists.at<float>(i, j);
            if(dist > 0) {
                dst.at<Vec3b>(i ,j)[0] = static_cast<uchar>((1-abs(dist/maxValue)) * 255);
            } else if (dist < 0) {
                dst.at<Vec3b>(i ,j)[2] = static_cast<uchar>((1-abs(dist/minValue)) * 255);
            } else {
                dst.at<Vec3b>(i ,j)[0] = 255;
                dst.at<Vec3b>(i ,j)[1] = 255;
                dst.at<Vec3b>(i ,j)[2] = 255;
            }
        }
    }

    imshow("dst", dst);
    waitKey(0);
    return 0;
}