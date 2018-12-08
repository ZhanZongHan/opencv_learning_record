#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src, gray_src, dst;
int threshold_value = 170;
int threshold_max_value = 255;
RNG rng(12345);

void demo(int, void*);

int main() {
    src = imread("/home/zzh/图片/balloon.png");
    if(src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    namedWindow("src", CV_WINDOW_AUTOSIZE);

    cvtColor(src, gray_src, CV_BGR2GRAY);
    blur(gray_src, gray_src, Size(3, 3));

    createTrackbar("threshold_value", "src", &threshold_value, threshold_max_value, demo);
    demo(0,0);

    waitKey(0);
    return 0;
}

void demo(int, void*) {
    Mat draw_image;
    threshold(gray_src, dst, threshold_value, threshold_max_value, THRESH_BINARY);
    imshow("dst", dst);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    vector<vector<Point>> contours_poly(contours.size());
    vector<Rect> rectangles(contours.size());
    vector<Point2f> centers(contours.size());
    vector<float> radius(contours.size());
    vector<RotatedRect> ellipses(contours.size());
    vector<RotatedRect> minRects(contours.size());

    for (int i = 0; i < contours.size(); ++i) {
        approxPolyDP(contours[i], contours_poly[i], 3, true);
        rectangles[i] = boundingRect(contours_poly[i]);
        minEnclosingCircle(contours_poly[i], centers[i], radius[i]);
        if(contours_poly[i].size() > 5){
            ellipses[i] = fitEllipse(contours_poly[i]);
            minRects[i] = minAreaRect(contours_poly[i]);
        }
    }

    draw_image.create(src.size(), src.type());
    Point2f pts[4];
    for(int i = 0; i < contours_poly.size(); ++i) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        rectangle(draw_image, rectangles[i], color, 1, LINE_AA);
        circle(draw_image, centers[i], radius[i], color, 1, LINE_AA);
        if(contours_poly[i].size() > 5) {
            ellipse(draw_image, ellipses[i], color, 1, LINE_AA);
            minRects[i].points(pts);
            for(int j = 0; j < 4; ++j) {
                line(draw_image, pts[j], pts[(j+1)%4], color, 1, LINE_AA);
            }
        }
    }

    imshow("draw_image", draw_image);
}