#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("/home/zzh/图片/cat.jpg");
    if (!src.data) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);
    Mat gray_src, edge_image;
    cvtColor(src, gray_src, CV_BGR2GRAY);
    GaussianBlur(gray_src, gray_src, Size(3, 3), 0, 0);
    Canny(gray_src, edge_image, 100, 200, 3, false);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(edge_image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

    int len = contours.size();
    Mat dst(src.size(), src.type(), Scalar(0, 0, 0));
    vector<vector<Point>> convexes(contours.size());
    for (int i = 0; i < len; i++) {
        convexHull(contours[i], convexes[i], false, true);
    }
    for (int i = 0; i < len; i++) {
        drawContours(dst, contours, i, Scalar(0, 0, 255), 2, LINE_8, hierarchy);
        drawContours(dst, convexes, i, Scalar(0, 255, 255), 2, LINE_8, hierarchy);
    }
    imshow("dst", dst);
    waitKey(0);
    return 0;
}