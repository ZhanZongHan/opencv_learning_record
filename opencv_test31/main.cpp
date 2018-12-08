#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

int main() {
    Mat src = imread("/home/zzh/图片/cat.jpg");
    if(src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    double hessianThreshold = 100;
    vector<KeyPoint> key_points;
    Ptr<SURF> detector = SURF::create(hessianThreshold);
    detector->detect(src, key_points, Mat());

    Mat dst = src.clone();
    drawKeypoints(src, key_points, dst, Scalar::all(-1));
    imshow("dst", dst);

    waitKey(0);
    return 0;
}

