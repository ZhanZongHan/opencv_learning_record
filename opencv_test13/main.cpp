#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src;
    src = imread("/home/zzh/图片/cat.jpg");
    if(src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    int top = (int)(0.05 * src.cols);
    int bottom = (int)(0.05 * src.cols);
    int left = (int)(0.05 * src.rows);
    int right = (int)(0.05 * src.rows);
    int type = BORDER_DEFAULT;
    int c = 0;
    Mat dst;
    RNG rng(12345);

    while(true) {
        c = waitKey(500);
        if(c == 27)
            break;

        if((char)c == 'c')
            type = BORDER_CONSTANT;
        else if((char)c == 'w')
            type = BORDER_WRAP;
        else if((char)c == 'r')
            type = BORDER_REPLICATE;

        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        copyMakeBorder(src, dst, top, bottom, left, right, type, color);
        imshow("dst", dst);
    }

    return 0;
}