#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src, dst;
int threshold_value = 127;
int threshold_max_value = 255;
int type_value = 2;
int type_max_value = 4;

void threshold_callback(int, void*);

int main() {
    src = imread("/home/zzh/图片/reba.jpeg", IMREAD_GRAYSCALE);
    if(!src.data) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    namedWindow("threshold_dst", CV_WINDOW_AUTOSIZE);
    createTrackbar("threshold_value", "threshold_dst", &threshold_value, threshold_max_value, threshold_callback);
    createTrackbar("threshold_type_value", "threshold_dst", &type_value, type_max_value, threshold_callback);
    threshold_callback(0, 0);

    waitKey(0);
    return 0;
}

void threshold_callback(int, void*) {
    threshold(src, dst, threshold_value, threshold_max_value, type_value);
    imshow("threshold_dst", dst);
}
