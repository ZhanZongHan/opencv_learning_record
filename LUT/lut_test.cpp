#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int TCount = 1;
int tableLevel = 10;
int maxLevel = 255;
Mat src, dst;
Mat lookUpTable(1, 256, CV_8UC1);

void createLUT(Mat &lookUpTable, int level);

void LUTCallBack(int, void *);

int main() {
    src = imread("/home/zzh/图片/cat.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if (src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);
    dst = src.clone();
    namedWindow("dst", WINDOW_AUTOSIZE);
    createTrackbar("level", "dst", &tableLevel, maxLevel, LUTCallBack);
    LUTCallBack(tableLevel, 0);
    waitKey(0);
    return 0;
}

void createLUT(Mat &lookUpTable, int level) {
    for (int i = 0; i < 256; i++) {
        if (level == 0) level++;
        lookUpTable.at<uchar>(0, i) = (i / level) * level;
    }
}

void LUTCallBack(int, void *) {
    double time = static_cast<double>(getTickCount());
    createLUT(lookUpTable, tableLevel);
    LUT(src, lookUpTable, dst);
    time = (static_cast<double>(getTickCount()) - time) / getTickFrequency();
    cout << "第" << TCount++ << "次运算时间为" << time << "秒" << endl;
    imshow("dst", dst);
}
