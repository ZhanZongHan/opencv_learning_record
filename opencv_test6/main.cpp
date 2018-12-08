#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    // line(), rectangle(), circle(), ellipse(), polygon(), putText() 各种图形函数
    Mat src = Mat(600, 600, CV_8UC3);
    RNG rng(12345);
    Point p1, p2;
    for(int i = 0; i< 10000; i++) {
        p1.x = rng.uniform(0, src.cols);
        p1.y = rng.uniform(0, src.rows);

        p2.x = rng.uniform(0, src.cols);
        p2.y = rng.uniform(0, src.rows);

        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        line(src, p1, p2, color);
        imshow("src", src);
        if(waitKey(50) > 0)
            break;
    }

    return 0;
}