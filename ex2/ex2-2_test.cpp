#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define SIZE 3

vector<Point2f> points;
int click_counts = 0;
Rect r;
Mat src1, src2, dst, dst2, dst3;

void rect(int event, int x, int y, int flags, void *);

int main() {
    src1 = imread("/home/zzh/桌面/图片1.png");
    src2 = imread("/home/zzh/桌面/图片2.png");
    if (src1.empty() || src2.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    dst = src2.clone();
    dst2 = Mat::zeros(src1.rows * 2, src1.cols * 2, src1.type());

    namedWindow("dst", CV_WINDOW_AUTOSIZE);
    imshow("dst", dst);
    setMouseCallback("dst", rect);


    waitKey(0);
    return 0;

}

void rect(int event, int x, int y, int flags, void *) {
    if (click_counts == SIZE) {
        points[1].x = abs((points[1].x - points[0].x) / src1.cols);
        points[1].y = abs((points[1].y - points[0].y) / src1.rows);
        points[2].x = abs((points[2].x - points[0].x) / src1.cols);
        points[2].y = abs((points[2].y - points[0].y) / src1.rows);
        cout << points[1].x << " " << points[1].y << " " << points[2].x << " " << points[2].y << endl;
        for (int i = 0; i < src1.rows; i++) {
            for (int j = 0; j < src1.cols; j++) {
                uchar b = src1.at<Vec3b>(i, j)[0];
                uchar g = src1.at<Vec3b>(i, j)[1];
                uchar r = src1.at<Vec3b>(i, j)[2];
                int x0 = (int) (j * points[1].x + i * points[2].x);
                int y0 = (int) (j * points[1].y + i * points[2].y);
                cout << x0 << " " << y0 << " " << j << " " << i << endl;
                dst2.at<Vec3b>(y0, x0)[0] = b;
                dst2.at<Vec3b>(y0, x0)[1] = g;
                dst2.at<Vec3b>(y0, x0)[2] = r;
            }
        }
        imshow("dst2", dst2);
    }
    if (event == CV_EVENT_LBUTTONDOWN) {
        points.emplace_back(Point(x, y));
        click_counts++;
        circle(dst, Point(x, y), 2, Scalar(0, 0, 255), -1);
        imshow("dst", dst);

    }
}

