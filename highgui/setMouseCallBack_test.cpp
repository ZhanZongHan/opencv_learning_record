#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

bool drawFlag = false;
Rect rect = Rect(-1, -1, 0, 0);
RNG rng(12345);

void drawRect(int event, int x, int y, int flags, void *param);

int main() {
    Mat src = Mat::zeros(500, 500, CV_8UC3), temp;
    namedWindow("temp", CV_WINDOW_AUTOSIZE);
    setMouseCallback("temp", drawRect, (void *) &src);
    while (1) {
        src.copyTo(temp);

        if (drawFlag)
            rectangle(src, rect, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));

        imshow("temp", temp);
       if (waitKey(10) == 27) break;
    }

    return 0;
}

void drawRect(int event, int x, int y, int flags, void *param) {
    Mat &src = *(Mat *) param;
    switch (event) {
        case CV_EVENT_LBUTTONDOWN :
            drawFlag = true;
            rect.x = x;
            rect.y = y;
            break;
        case CV_EVENT_MOUSEMOVE :
            if (drawFlag) {
                rect.width = x - rect.x;
                rect.height = y - rect.y;
            }
            break;
        case CV_EVENT_LBUTTONUP :
            drawFlag = false;
            if (rect.width < 0) {
                rect.x += rect.width;
                rect.width *= -1;
            }
            if (rect.height < 0) {
                rect.y += rect.height;
                rect.height *= -1;
            }
            rectangle(src, rect, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
            rect = Rect(-1, -1, 0, 0);

            break;
        default :
            break;
    }

}

