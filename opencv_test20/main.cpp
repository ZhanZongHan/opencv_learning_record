#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src, hsv, hue;
int bins = 12;
int max_bins = 255;

void back_pro_demo(int, void *);

int main() {
    src = imread("/home/zzh/图片/hand.jpeg");
    if(!src.data) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);

    cvtColor(src, hsv, CV_BGR2HSV);
    int n_channels[] = {0, 0};
    hue.create(hsv.size(), hsv.depth());
    mixChannels(&hsv, 1, &hue, 1, n_channels, 1);

    namedWindow("dst", CV_WINDOW_AUTOSIZE);
    namedWindow("hist_image", CV_WINDOW_AUTOSIZE);
    createTrackbar("back_pro", "src", &bins, max_bins, back_pro_demo);
    back_pro_demo(0, 0);
    waitKey(0);
    return 0;
}

void back_pro_demo(int, void *) {
    Mat hist;
    float range[] = {0, 180};
    const float *ranges[] = {range};
    calcHist(&hue, 1, 0, Mat(), hist, 1, &bins, ranges, true, false);
    normalize(hist, hist, 0, 255, NORM_MINMAX);

    Mat dst;
    calcBackProject(&hue, 1, 0, hist, dst, ranges, 1, true);
    imshow("dst", dst);

    int hist_w = 400;
    int hist_h = 400;
    int bin_w = hist_w / bins;
    Mat hist_image(Size(hist_w, hist_h), CV_8UC3, Scalar(0, 0, 0));
    for(int i = 1; i < bins; i++) {
        rectangle(hist_image, Point((i-1)*bin_w, 400),
                Point(i*bin_w, hist_h-cvRound(hist.at<float>(i))), Scalar(0, 0, 255), -1);
    }
    imshow("hist_image", hist_image);
    return;
}