#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void seedPointCallback(int event, int x, int y, int flags, void *param);
Mat src, dst;
int main() {
    src = imread("/home/zzh/图片/building.jpg");
    if(src.empty()) {
        cout << "can not load the image!" << endl;
        return 0;
    }
    dst = src.clone();
    namedWindow("dst", WINDOW_AUTOSIZE);
    imshow("dst", dst);
    setMouseCallback("dst", seedPointCallback);
    waitKey(0);
    return 0;
}

void seedPointCallback(int event, int x, int y, int flags, void *param) {
    if(event != EVENT_LBUTTONDOWN)
        return;
    floodFill(dst, Point(x, y), Scalar(155, 0, 55), 0, Scalar(15, 15, 15), Scalar(15, 15, 15));
    imshow("dst", dst);
    dst = src.clone();
}
