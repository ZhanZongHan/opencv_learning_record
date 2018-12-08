#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src, dst, gray_src, edge_image;
int t1 = 50;
int max_value = 255;

void canny_demo(int, void*);

int main() {
    src = imread("/home/zzh/图片/reba.jpeg");
    if(!src.data) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);
    namedWindow("dst", CV_WINDOW_AUTOSIZE);
    cvtColor(src, gray_src, CV_RGB2GRAY);
    createTrackbar("canny", "dst", &t1, max_value, canny_demo);
    canny_demo(0, 0);
    waitKey(0);
    return 0;
}

void canny_demo(int, void*) {
    blur(gray_src, gray_src, Size(3, 3));

    Canny(gray_src, edge_image, t1, t1 * 2, 3, false);
//    dst.create(src.size(), src.type());
//    src.copyTo(dst, edge_image);  // 转变彩色

    imshow("dst", edge_image);
}
/**
 * Canny():
 * 高斯模糊降噪
 * 转变为灰度图像
 * 求梯度图像(Sobel/Scharr)
 * 非最大信号抑制
 * 双阈值确定像素值
 * 输出
 * */