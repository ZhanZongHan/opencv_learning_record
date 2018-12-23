#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat move_rect(const Mat &pre, const Mat &now);

int main() {
    VideoCapture capture(0);
    Mat frame;
    Mat pre;
    int count = 1;
    capture >> frame;
    pre = frame;
    while(!frame.empty()) {
        // 若是第一帧，就跳过

        double FPS = capture.get(CAP_PROP_FPS);
        Mat result = move_rect(pre, frame);
        // 绘制矩形
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(result, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        for (int i = 0; i < contours.size(); i++) {
            if (contours[i].size() < 5)
                continue;
            Rect rect = boundingRect(contours[i]);
            rectangle(frame, rect, Scalar(0, 0, 255), 2);
        }
    //    pre = frame;

        imshow("frame", frame);
        pre = frame.clone();
        capture >> frame;
        if(waitKey((int)(1000.0/FPS)) == 'q')
            break;
    }
    capture.release();
    return 0;
}

Mat move_rect(const Mat &pre, const Mat &now) {
    // 转灰度图像
    Mat gray_pre, gray_now;
    cvtColor(pre, gray_pre, COLOR_BGR2GRAY);
    cvtColor(now, gray_now, COLOR_BGR2GRAY);
    Mat diff;
    absdiff(gray_now, gray_pre, diff);
//    normalize(diff, diff, 0, 255, NORM_MINMAX);

    // 二值化
    Mat b_diff;
    threshold(diff, b_diff, 0, 255, THRESH_BINARY|THRESH_OTSU);

    // 膨胀，连通二值图像
    Mat morph_diff;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
    morphologyEx(b_diff, morph_diff, MORPH_OPEN, kernel);
    imshow("morph_diff", morph_diff);
    return morph_diff;

}