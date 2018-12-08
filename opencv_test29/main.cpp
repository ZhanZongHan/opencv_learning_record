#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

Mat src, gray_src;
Mat harris_rsp, harris_src;
Mat shiTomasi_src;
Mat harris_result_img, shiTomasi_result_img;
const char *HARRIS_WINDOW = "harris_window";
const char *SHITOMASI_WINDOW = "shiTomasi_window";
int harris_quality_level = 30;
int shiTomasi_quality_level = 30;
int max_quality_level = 100;
double harris_min_rsp, harris_max_rsp;
double shiTomasi_min_rsp, shiTomasi_max_rsp;

void harris_demo(int, void *);
void shiTomasi_demo(int, void *);

int main() {
    src = imread("/home/zzh/图片/building.jpg");
    if (!src.data) {
        cout << "can not load the image!" << endl;
    }
    namedWindow("src", CV_WINDOW_AUTOSIZE);
    imshow("src", src);

    namedWindow(HARRIS_WINDOW, CV_WINDOW_AUTOSIZE);
    namedWindow(SHITOMASI_WINDOW, CV_WINDOW_AUTOSIZE);
    cvtColor(src, gray_src, CV_BGR2GRAY);
    int block_size = 3;
    int k_size = 3;
    double k = 0.04;
    // 计算harris特征值
    harris_rsp = Mat::zeros(gray_src.size(), CV_32FC(6));
    harris_src = Mat::zeros(gray_src.size(), CV_32FC1);
    cornerEigenValsAndVecs(gray_src, harris_rsp, block_size, k_size, 4);
    for (int i = 0; i < gray_src.rows; i++) {
        for (int j = 0; j < gray_src.cols; j++) {
            double lambda_1 = harris_rsp.at<Vec6f>(i, j)[0];
            double lambda_2 = harris_rsp.at<Vec6f>(i, j)[1];
            harris_src.at<float>(i, j) = lambda_1 * lambda_2 - k * pow((lambda_1 + lambda_2), 2);
        }
    }
    minMaxLoc(harris_src, &harris_min_rsp, &harris_max_rsp, 0, 0, Mat());
    createTrackbar("harris_rsp:", HARRIS_WINDOW, &harris_quality_level, max_quality_level, harris_demo);
    harris_demo(0, 0);

    // 计算最小特征值
    shiTomasi_src = Mat::zeros(gray_src.size(), CV_32FC1);
    cornerMinEigenVal(gray_src, shiTomasi_src, block_size, k_size, 4);
    minMaxLoc(shiTomasi_src, &shiTomasi_min_rsp, &shiTomasi_max_rsp, 0, 0, Mat());
    createTrackbar("shiTomasi_rsp:", SHITOMASI_WINDOW, &shiTomasi_quality_level, max_quality_level, shiTomasi_demo);
    shiTomasi_demo(0, 0);

    waitKey(0);
}

void harris_demo(int, void *) {
    if (harris_quality_level < 10)
        harris_quality_level = 10;
    double t = harris_min_rsp + (double(harris_quality_level) / max_quality_level) * (harris_max_rsp - harris_min_rsp);

    harris_result_img = src.clone();
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            double v = harris_src.at<float>(i, j);
            if (v > t) {
                circle(harris_result_img, Point(j, i), 2, Scalar(0, 0, 255), -1);
            }
        }
    }
    imshow(HARRIS_WINDOW, harris_result_img);
}

void shiTomasi_demo(int, void *) {
    if (shiTomasi_quality_level < 10)
        shiTomasi_quality_level = 10;
    double t = shiTomasi_min_rsp +
               (double(shiTomasi_quality_level) / max_quality_level) * (shiTomasi_max_rsp - shiTomasi_min_rsp);

    shiTomasi_result_img = src.clone();
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            double v = shiTomasi_src.at<float>(i, j);
            if (v > t) {
                circle(shiTomasi_result_img, Point(j, i), 2, Scalar(0, 0, 255), -1);
            }
        }
    }
    imshow(SHITOMASI_WINDOW, shiTomasi_result_img);
}