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

    Mat trans_m = (Mat_<uchar>(2, 2) << 2, 0, 0, 2);
    Mat dst = Mat::zeros(src.size()*2, src.type());

    for(int i = 0; i < src.rows; i++) {
        for(int j = -0; j < src.cols; j++) {
            int x = trans_m.at<uchar>(0)*j + trans_m.at<uchar>(1)*i;
            int y = trans_m.at<uchar>(2)*j + trans_m.at<uchar>(3)*i;
            if(x < 0 || x >= dst.cols || y < 0 || y >= dst.rows )
                continue;
            dst.at<Vec3b>(y, x) = src.at<Vec3b>(i, j);
        }
    }
    imshow("src", src);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}


