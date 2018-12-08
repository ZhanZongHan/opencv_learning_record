#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src, template_src, dst;
    src = imread("/home/zzh/图片/cat.jpg");
    template_src = imread("/home/zzh/图片/template_cat.jpg");
    if(src.empty() || template_src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }

    matchTemplate(src, template_src, dst, TM_CCOEFF_NORMED, Mat());
    normalize(dst, dst, 0, 1, NORM_MINMAX);
    Point minLoc, maxLoc;
    double minValue, maxValue;
    minMaxLoc(dst, &minValue, &maxValue, &minLoc, &maxLoc, Mat());
    Point tempLoc = maxLoc;
    rectangle(src, Rect(tempLoc.x, tempLoc.y, template_src.cols, template_src.rows), Scalar(0, 0, 255), 2, LINE_AA);
    imshow("src", src);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}