#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src, gray_src;
int t1 = 80;
int t_max = 255;
RNG rng(12345);

void demo(int, void *);

int main() {
    src = imread("/home/zzh/图片/balloon.png");
    if (src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    cvtColor(src, gray_src, CV_BGR2GRAY);
    GaussianBlur(gray_src, gray_src, Size(3, 3), 0, 0);
    imshow("gray_src", gray_src);

    namedWindow("canny_src", CV_WINDOW_AUTOSIZE);
    createTrackbar("canny_value", "canny_src", &t1, t_max, demo);
    demo(0, 0);

    waitKey(0);
    return 0;
}

void demo(int, void *) {
    Mat canny_src;
    Canny(gray_src, canny_src, t1, t1 * 2, 3);
    imshow("canny_src", canny_src);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(canny_src, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    vector<vector<Point>> contour_poly(contours.size());
    vector<Moments> mos(contours.size());
    vector<Point2f> centers(contours.size());
    Mat draw_image;
    src.copyTo(draw_image);
    for (int i = 0; i < contours.size(); i++) {
        approxPolyDP(contours[i], contour_poly[i], 5, true);
        mos[i] = moments(contour_poly[i]);
        centers[i] = Point2f(static_cast<float>(mos[i].m10 / mos[i].m00), static_cast<float>(mos[i].m01 / mos[i].m00));
    }

    for (int i = 0; i < contour_poly.size(); i++) {
        if (contour_poly[i].size() < 10)
            continue;
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(draw_image, contour_poly, i, color, 2, LINE_AA, hierarchy);
        circle(draw_image, centers[i], 1, color, 1);
        cout << "x: " << centers[i].x << " y: " << centers[i].y << " area: " << contourArea(contour_poly[i]) << endl;
    }
    imshow("draw_image", draw_image);
}