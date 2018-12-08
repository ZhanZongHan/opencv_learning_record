#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;

int main(int argc, char** argv) {
    Mat src = imread("../images/captain.jpeg"); // 第二个参数，默认为 IMREAD_COLOR，此时为灰度图，另外一个IMREAD_UNCHANGED不可变
    if(src.empty())
    {
        printf("empty path!");
        return -1;
    }
    namedWindow("test", CV_WINDOW_AUTOSIZE);
    imshow("test",  src);

    namedWindow("output", CV_WINDOW_AUTOSIZE);
    Mat output_image;
    cvtColor(src, output_image, CV_RGB2HLS);    // 将src经过参数三的转换到output_image中
    imshow("output", output_image);

    imwrite("../images/captain_after.png", output_image);   // 将修改过后的output_image保存到新的图片中，格式可根据后缀名改变

    waitKey(0);
    return 0;
}