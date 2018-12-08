#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src, gray_src;
int thresh = 130;
int thresh_max = 255;

void harris_demo(int, void *);

int main() {
    src = imread("/home/zzh/图片/building.jpg");
    if (src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }


    cvtColor(src, gray_src, CV_BGR2GRAY);
    namedWindow("harris_src", CV_WINDOW_AUTOSIZE);
    createTrackbar("thresh:", "harris_src", &thresh, thresh_max, harris_demo);
    imshow("harris_src", src);
    harris_demo(0, 0);

    waitKey(0);
    return 0;
}

void harris_demo(int, void *) {
    Mat dst = Mat::zeros(gray_src.size(), CV_32FC1);
    Mat norm, norm_scale;

    int blockSize = 2;
    int kSize = 3;
    double k = 0.04;
    cornerHarris(gray_src, dst, blockSize, kSize, k, BORDER_DEFAULT);
    normalize(dst, norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(norm, norm_scale);  // 此时norm_sacle已转变为uchar 值  应at<uchar>(), 其他类型会导致数据乱

    Mat result = src.clone();
//    for (int i = 0; i < norm.rows; i++) {
//        for (int j = 0; j < norm.cols; j++) {
//            if ((int) norm.at<float>(i, j) > thresh) {
//                circle(result, Point(j, i), 5, Scalar(0, 0, 255), -1);
//            }
//        }
//    }
    for (int i = 0; i < norm_scale.rows; i++) {
        for (int j = 0; j < norm_scale.cols; j++) {
            if ((int) norm_scale.at<uchar>(i, j) > thresh) {
                circle(result, Point(j, i), 5, Scalar(0, 0, 255), -1);
            }
        }
    }

    namedWindow("norm_src", CV_WINDOW_AUTOSIZE);
    imshow("norm_src", result);
}

