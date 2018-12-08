#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("/home/zzh/图片/cat.jpg");
    if (src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);
    vector<Mat> channels_bgr;
    split(src, channels_bgr);
    Mat gray_src, gray_src_b, gray_src_g, gray_src_r;
    Mat dst, gray_dst, gray_dst_b, gray_dst_g, gray_dst_r;
    cvtColor(src, gray_src, COLOR_BGR2GRAY);
    gray_src_b = channels_bgr[0];
    gray_src_g = channels_bgr[1];
    gray_src_r = channels_bgr[2];
    // 利用通道分离对每个通道直方图均衡化，再合并通道来达成对3通道图像的直方图均衡化，从而增加对比度
    equalizeHist(gray_src, gray_dst);
    equalizeHist(gray_src_b, gray_dst_b);
    equalizeHist(gray_src_g, gray_dst_g);
    equalizeHist(gray_src_r, gray_dst_r);
    vector<Mat> equalize_channels_bgr;
    equalize_channels_bgr.emplace_back(gray_dst_b);
    equalize_channels_bgr.emplace_back(gray_dst_g);
    equalize_channels_bgr.emplace_back(gray_dst_r);
    merge(equalize_channels_bgr, dst);
    imshow("gray_dst", gray_dst);
    imshow("gray_dst_b", gray_dst_b);
    imshow("gray_dst_g", gray_dst_g);
    imshow("gray_dst_r", gray_dst_r);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}

