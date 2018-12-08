#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int size = 0;
int max_size = 21;
Mat src, dst;

void rollback(int, void *);

int main() {
    src = imread("/home/zzh/图片/cat.jpg");
    if(src.empty()) {
        cout << "can not load image!" << endl;
        return -1;
    }
    namedWindow("src", CV_WINDOW_AUTOSIZE);
    imshow("src", src);

    namedWindow("dst", CV_WINDOW_AUTOSIZE);
    createTrackbar("dilate_or_erode", "dst", &size, max_size, rollback);
    rollback(0, 0);
    waitKey(0);
    return 0;
}

void rollback(int, void*) {
    int s = size * 2 + 1;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(s, s)); // Size()参数要为奇数
    //erode(src, dst, kernel, Point(-1, -1), 1);
    dilate(src, dst, kernel);
    imshow("dst", dst);
}