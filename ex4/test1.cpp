#include <math.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    string part_path = "../ex4/images/";
    ifstream inImgPath(part_path + "image_name.txt");    //标定所用图像文件的路径
    vector<string> imgList;
    string temp;
    if (!inImgPath.is_open()) {
        cout << "没有找到文件" << endl;
    }
    //读取文件中保存的图片文件路径，并存放在数组中
    while (getline(inImgPath, temp)) {
        imgList.push_back(temp);
    }

    for (int i = 0; i < imgList.size(); i++) {
        Mat src = imread(part_path + imgList[i]);
        if (src.empty()) {
            printf("could not load image...\n");
            return -1;
        }
        namedWindow("input image", WINDOW_AUTOSIZE);
        imshow("input image", src);
        Mat gray, binary;
        cvtColor(src, gray, COLOR_BGR2GRAY);
        blur(gray, gray, Size(5, 5));
        threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        imshow("binary", binary);
        // 检测轮廓
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        Moments moments;
        findContours(binary.clone(), contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
        Mat result = Mat::zeros(src.size(), CV_8UC3);
        for (size_t t = 0; t < contours.size(); t++) {
            double area = contourArea(contours[t]);
            if (area < 100) continue;
            RotatedRect rect = minAreaRect(contours[t]);
            // 根据矩形特征进行几何分析
            float w = rect.size.width;
            float h = rect.size.height;
            float rate = min(w, h) / max(w, h);

            if (rate > 0.90) {
                if (hierarchy[t][2] == -1)
                    continue;
                Point2f pts[4];
                rect.points(pts);
                // 绘画矩形
                Point point0 = pts[3], point1;
                for (int i = 0; i < 4; i++) {
                    point1 = pts[i];
                    line(src, point0, point1, Scalar(255, 0, 0), 2);
                    point0 = point1;
                }
                circle(src, rect.center, 2, Scalar(255, 255, 0), -1);
                char angle[10];
                sprintf(angle, "%f", rect.angle);
                putText(src, string(angle), rect.center, FONT_HERSHEY_COMPLEX, 0.5, Scalar(0, 255, 255));
            }
        }
        imshow(imgList[i], src);
        waitKey(0);
        destroyWindow(imgList[i]);
    }
    return 0;
}
