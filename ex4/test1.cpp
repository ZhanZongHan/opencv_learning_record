#include <math.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void scanAndDetectQRCode(Mat &image, int index);

bool isXCorner(Mat &image);

bool isYCorner(Mat &image);

Mat transformCorner(Mat &image, RotatedRect &rect);

int main(int argc, char **argv) {
    /*for (int i = 1; i < 25; i++) {
        Mat qrcode_image = imread(format("D:/gloomyfish/qrcode/%d.jpg", i));
        scanAndDetectQRCode(qrcode_image, i);
    }
    return 0;
    */
    Mat src = imread("../ex4/images/sample4.png");
    if (src.empty()) {
        printf("could not load image...\n");
        return -1;
    }
    namedWindow("input image", WINDOW_AUTOSIZE);
    imshow("input image", src);
    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
 //   morphologyEx(binary, binary, MORPH_OPEN, kernel);
    imshow("binary", binary);
    // detect rectangle now
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Moments moments;
    findContours(binary.clone(), contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE, Point());
    Mat result = Mat::zeros(src.size(), CV_8UC3);
    for (size_t t = 0; t < contours.size(); t++) {
        double area = contourArea(contours[t]);
        if (area < 100) continue;
        RotatedRect rect = minAreaRect(contours[t]);
        // 根据矩形特征进行几何分析
        float w = rect.size.width;
        float h = rect.size.height;
        float rate = min(w, h) / max(w, h);
        /*     if (rate > 0.85 && w < src.cols / 4 && h < src.rows / 4) {
                 printf("angle : %.2f\n", rect.angle);
     //            Mat qr_roi = transformCorner(src, rect);
                 //if (isXCorner(qr_roi) && isYCorner(qr_roi))
                 {
                     drawContours(src, contours, static_cast<int>(t), Scalar(0, 0, 255), 2, 8);
                     drawContours(result, contours, static_cast<int>(t), Scalar(255, 0, 0), 2, 8);
                 }*/
        if(rate > 0.80){

      /*      vector<int> hull;
            convexHull(contours[t], hull);
            Point point0 = contours[t][hull[hull.size()-1]], point1;
            for(int i = 0; i < hull.size(); i++) {
                point1 = contours[t][hull[i]];
                line(src, point0, point1, Scalar(255,0,0), 2);
                point0 = point1;
            }*/
            Point2f pts[4];
            rect.points(pts);
            Point point0 = pts[3], point1;
            for(int i = 0; i < 4; i++) {
                point1 = pts[i];
                line(src, point0, point1, Scalar(255,0,0), 2);
                point0 = point1;
            }
            circle(src, rect.center, 2, Scalar(255,255,0), -1);
            char angle[10];
            sprintf(angle, "%f", rect.angle);
            putText(src, string(angle), rect.center, FONT_HERSHEY_COMPLEX, 0.3, Scalar(0,255,255));
        }
    }
    imshow("result", src);
    waitKey(0);
    return 0;
}