#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void videoControl(int, void*);

int waitTime = 33;
int maxTime = 300;
VideoCapture capture("/home/zzh/视频/1.mp4");
Mat frame;

int main() {
    namedWindow("mp4", CV_WINDOW_AUTOSIZE);
    capture >> frame;
    imshow("mp4", frame);
    createTrackbar("waitTime", "mp4", &waitTime, maxTime, videoControl);
    videoControl(waitTime, 0);
    return 0;
}

void videoControl(int, void*) {

    while (1) {
        if (frame.empty())
            break;
        imshow("mp4", frame);
        capture >> frame;
        char c = waitKey(waitTime);
        if(c == 27)
            break;
    }
}
