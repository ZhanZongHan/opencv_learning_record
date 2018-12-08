#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("/home/zzh/图片/lines.png");
    if(src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    Mat gray_src, edge_image, dst;
    cvtColor(src, gray_src, CV_BGR2GRAY);
    Canny(gray_src, edge_image, 100, 230);
    imshow("edge_image", edge_image);
    dst = Mat::zeros(src.size(), src.type());
    vector<Vec4d> p_lines;
    HoughLinesP(edge_image, p_lines, 1, CV_PI/180.0, 10, 0, 10);
    Scalar color = Scalar(0, 255, 0);
    for(size_t i = 0; i < p_lines.size(); i++) {
        Vec4d points = p_lines[i];
        line(dst, Point(points[0], points[1]), Point(points[2], points[3]), color, 3, LINE_8);
    }
    imshow("dst", dst);
    waitKey(0);
    return 0;
}