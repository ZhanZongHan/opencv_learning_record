#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("/home/zzh/图片/paper.jpg");
    if (src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    // 去背景
    Mat gray_src;
    src.copyTo(gray_src);
    for (int i = 0; i < gray_src.rows; i++) {
        for (int j = 0; j < gray_src.cols; j++) {
            int b = gray_src.at<Vec3b>(i, j)[0];
            int g = gray_src.at<Vec3b>(i, j)[1];
            int r = gray_src.at<Vec3b>(i, j)[2];
            if (b >= 253 && g >= 253 && r >= 253) {
                gray_src.at<Vec3b>(i, j)[0] = 0;
                gray_src.at<Vec3b>(i, j)[1] = 0;
                gray_src.at<Vec3b>(i, j)[2] = 0;
            }
        }
    }

    // 锐化
    Mat shape_src;
    Mat kernel_Laplace = (Mat_<int>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
    filter2D(gray_src, shape_src, -1, kernel_Laplace);
    shape_src = gray_src - shape_src;
    imshow("shape_src", shape_src);

    // 二值化
    cvtColor(shape_src, gray_src, CV_BGR2GRAY);
    Mat binary_src;
    threshold(gray_src, binary_src, 10, 255, THRESH_BINARY | THRESH_OTSU);

    // 距离变换
    Mat dist_trans_src;
    distanceTransform(binary_src, dist_trans_src, CV_DIST_L2, 3);
    normalize(dist_trans_src, dist_trans_src, 0, 1, NORM_MINMAX);
    imshow("dist_trans_src", dist_trans_src);

    threshold(dist_trans_src, dist_trans_src, 0.4, 1, THRESH_BINARY);
    Mat k1 = Mat::ones(3, 3, CV_8UC1);
    erode(dist_trans_src, dist_trans_src, k1);
    imshow("erode", dist_trans_src);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    dist_trans_src.convertTo(dist_trans_src, CV_8UC1);
    findContours(dist_trans_src, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

    Mat contour_src = src;
    Mat markers = Mat::zeros(dist_trans_src.size(), CV_32SC1);
    vector<Vec3b> colors;
    for (int i = 0; i < contours.size(); i++) {
        drawContours(markers, contours, i, Scalar::all(i + 1), -1);

        int b = theRNG().uniform(0, 255);
        int g = theRNG().uniform(0, 255);
        int r = theRNG().uniform(0, 255);
        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }
    imshow("markers", markers*1000);

    contour_src.convertTo(contour_src, CV_8UC3);
    watershed(contour_src, markers);    // 第一个参数是一个未被修改过的CV_8UC3图像

    //bitwise_not(markers, markers);

    // 上色
    Mat result = Mat::zeros(markers.size(), CV_8UC3);
    for(int i = 0; i < markers.rows; i++) {
        for(int j = 0; j < markers.cols; j++) {
            int temp = markers.at<int>(i, j);
            if(temp > 0 && temp < contours.size()) {
                result.at<Vec3b>(i, j) = colors[temp - 1];
            }
        }
    }//cout << result;
    imshow("watershed", result);

    waitKey(0);
    return 0;
}