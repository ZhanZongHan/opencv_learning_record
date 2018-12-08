#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
/*
 *   void calcHist(const Mat* arrays, int narrays, const int* channels, InputArray mask, SparseMat&
hist, int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=
false )；
 */
int main() {
    Mat src = imread("/home/zzh/图片/lines.png");
    if(!src.data) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);
    Mat *bgr_c = new Mat[3];    // 用指针记得要申请空间
    // vector<Mat> bgr_c;
    split(src, bgr_c);
    Mat b_hist, g_hist, r_hist;
    int histSize = 256; // 要显示在直方图上的条形个数
    float range[] = {0, 256};
    const float *ranges[] = {range};
    calcHist(&bgr_c[0], 1, 0, Mat(), b_hist, 1, &histSize, ranges, true, false);
    calcHist(&bgr_c[1], 1, 0, Mat(), g_hist, 1, &histSize, ranges, true, false);
    calcHist(&bgr_c[2], 1, 0, Mat(), r_hist, 1, &histSize, ranges, true, false);
    // 由于直方图里的频数可能过大，所以限制范围，归一化
    int hist_w = 512;
    int hist_h = 400;
    int bin_w = hist_w / histSize;  // 每个小条形的范围长度
    normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX);
    normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX);
    normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX);

    // 绘制直方图
    Mat hist_image(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));
    for(int i = 1; i < histSize; i++) {
        // y轴是向下为正方向
        line(hist_image, Point((i-1)*bin_w, hist_h-cvRound(b_hist.at<float>(i-1))),
                Point((i)*bin_w, hist_h-cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2);

        line(hist_image, Point((i-1)*bin_w, hist_h-cvRound(g_hist.at<float>(i-1))),
                Point((i)*bin_w, hist_h-cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2);

        line(hist_image, Point((i-1)*bin_w, hist_h-cvRound(r_hist.at<float>(i-1))),
                Point((i)*bin_w, hist_h-cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2);
    }
    imshow("hist_image", hist_image);
    waitKey(0);
    return 0;
}
