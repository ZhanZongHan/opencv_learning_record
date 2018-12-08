#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

// https://blog.csdn.net/linqianbi/article/details/78631889 掩膜知识参考
int main(int argc, char** argv) {
    Mat src, dst;
    src = imread("../images/lijiaxin.png");
    if(!src.data) {
        printf("can not load image!");
        return -1;
    }
    namedWindow("src", CV_WINDOW_AUTOSIZE);
    imshow("src", src);

    /*
    dst = Mat::zeros(src.size(), src.type());
    int rows = src.rows;
    int cols = (src.cols - 1) * src.channels();   // https://blog.csdn.net/mao_hui_fei/article/details/78217049 通道知识参考
    int offset = src.channels();

    for(int i = 1; i < rows - 1; i++) {
        const uchar* previous = src.ptr<uchar>(i - 1);  // 获取行的指针
        const uchar* current = src.ptr<uchar>(i);
        const uchar* next = src.ptr<uchar>(i + 1);
        uchar* output = dst.ptr<uchar>(i);
        for(int j = offset; j < cols; j++) {    // 根据通道顺序表示得此循环
            output[j] = saturate_cast<uchar>(5*current[j] - (previous[j] + next[j] + current[j-offset] + current[j+offset]));    // 该函数保证数值在0-255之间， 设置的掩膜矩阵数值数学关系式
        }
    }*/

    Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    filter2D(src, dst, -1, kernel);

    namedWindow("dst", CV_WINDOW_AUTOSIZE);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}