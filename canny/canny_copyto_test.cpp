#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src = imread("/home/zzh/图片/cat.jpg");
Mat gray_src, canny_src, dst;
int th = 100, maxTh = 255;

void canny_callback(int, void*);

int main() {
    if(src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);
    cvtColor(src, gray_src, COLOR_BGR2BGRA);
    GaussianBlur(gray_src, gray_src, Size(3, 3), 0, 0);
    namedWindow("edge_src", WINDOW_AUTOSIZE);
    createTrackbar("thresholdVal", "edge_src", &th, maxTh, canny_callback);
    canny_callback(th, 0);
    waitKey(0);
    return 0;
}

void canny_callback(int, void*) {
    dst = Mat::zeros(src.size(), src.type());
    Canny(gray_src, canny_src, th, th*2);
    src.copyTo(dst, canny_src);
    imshow("edge_src", dst);
}