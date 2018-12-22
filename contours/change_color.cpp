#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int value = 50;
int max_value = 255;
Mat src;
Mat temp;
Mat b_temp;
Mat b_c;
Mat result;
void demo(int, void*);

int main() {
    src = imread("/home/zzh/下载/me1.jpeg");
    if (src.empty()) {
        cout << "can not load the image!!";
        return -1;
    }

    cvtColor(src, temp, COLOR_BGR2GRAY);
    GaussianBlur(temp, temp, Size(3, 3), 0);
    namedWindow("temp", WINDOW_AUTOSIZE);
    createTrackbar("value", "temp", &value, max_value, demo);
    demo(0, 0);
    waitKey(0);
    return 0;
}

void demo(int, void*) {

    threshold(temp, b_temp, value, max_value, THRESH_BINARY);
    imshow("temp", b_temp);
/*    Mat kernel = getStructuringElement(MORPH_RECT, Size(11, 11));
    morphologyEx(b_temp, b_temp, MORPH_OPEN, kernel);
    imshow("b_temp", b_temp);*/
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    result = Mat::zeros(temp.size(), temp.type());
    findContours(b_temp, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    drawContours(result, contours, -1, Scalar(255, 255, 255), 1, LINE_8, hierarchy);
    imshow("result", result);

 /*   Mat mask = b_temp;

    b_c = Mat(src.size(), src.type(), Scalar(0, 0, 255));
    src.copyTo(b_c, mask);
    imshow("result", b_c);*/
}