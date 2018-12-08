#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src, gray_src;
int num_corners = 50;
int max_corners = 220;

void Shi_Tomasi(int, void*);

int main() {
    src = imread("/home/zzh/图片/building.jpg");
    if(src.empty()) {
        cout << "can not load the image!";
        return -1;
    }
    namedWindow("src", CV_WINDOW_AUTOSIZE);
    imshow("src", src);

    createTrackbar("corners_num:", "src", &num_corners, max_corners, Shi_Tomasi);
    Shi_Tomasi(0, 0);

    waitKey(0);
    return 0;
}

void Shi_Tomasi(int, void*) {
    vector<Point2f> corners;
    cvtColor(src, gray_src, CV_BGR2GRAY);
    goodFeaturesToTrack(gray_src, corners, num_corners, 0.02, 10, Mat());
    cout << "corners num : " << corners.size() << endl;
    cvtColor(gray_src, gray_src, CV_GRAY2BGR);
    for(int i = 0; i < corners.size(); i++) {
        circle(gray_src, corners[i], 2, Scalar(0, 0, 255), -1);
    }
    imshow("gray_src", gray_src);
}

