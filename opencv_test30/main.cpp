#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src, gray_src, result_img1, result_img2;
int corner_num = 50;
int max_corners = 200;

void sub_pixel_demo(int, void *);

int main() {
    src = imread("/home/zzh/图片/checkerboard.jpg");
    if (!src.data) {
        cout << "can not load the image!" << endl;
    }
    namedWindow("src", CV_WINDOW_AUTOSIZE);
    imshow("src", src);

    cvtColor(src, gray_src, CV_BGR2GRAY);
    createTrackbar("corners_num:", "src", &corner_num, max_corners, sub_pixel_demo);
    sub_pixel_demo(0, 0);

    waitKey(0);
    return 0;
}

void sub_pixel_demo(int, void *) {
    vector<Point2f> corners;
    if (corner_num < 10)
        corner_num = 10;
    result_img1 = src.clone();
    goodFeaturesToTrack(gray_src, corners, corner_num, 0.01, 10);
    for (int i = 0; i < corners.size(); i++) {
        circle(result_img1, corners[i], 5, Scalar(0, 0, 255), 2);
    }
    imshow("result_img1", result_img1);

    TermCriteria tc = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.01);
    result_img2 = src.clone();
    cornerSubPix(gray_src, corners, Size(5, 5), Size(-1, -1), tc);
    for (int i = 0; i < corners.size(); i++) {
        circle(result_img2, corners[i], 5, Scalar(0, 255, 255), 2);
    }
    imshow("result_img2", result_img2);
}