#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
    Mat img (600, 600, CV_8UC3);
    RNG rng(12345);
    while (1) {
        vector<Point> points;
        int counts = rand()%45 + 5;
        img = Scalar::all(0);
        for(int i = 0; i < counts; i++) {
            Point point;
            point.x = static_cast<int>(rng.uniform(img.cols*0.15, img.cols*0.85));
            point.y = static_cast<int>(rng.uniform(img.rows*0.15, img.rows*0.85));
            circle(img, point, 2, Scalar(rng.uniform(0, 255),rng.uniform(0, 255),rng.uniform(0, 255)), -1);
            points.emplace_back(point);
        }
        vector<int> hull;
        // 检测凸包点，hull存储每个凸点在points里的索引下标
        convexHull(points, hull);
        //  最后一个凸点
        Point point0 = points[hull[hull.size()-1]];
        for(int i = 0; i < hull.size(); i++) {
            Point point = points[hull[i]];
            line(img, point0, point, Scalar(rng.uniform(0, 255),rng.uniform(0, 255),rng.uniform(0, 255)));
            point0 = point;
        }
        imshow("img", img);
        if (waitKey(0) == 27)
            break;
    }
    return 0;
}

