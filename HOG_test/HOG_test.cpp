#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("/home/zzh/图片/passer-by.jpg");
    if(src.empty()) {
        cout << "can not load the image!" << endl;
        return -1;
    }
    imshow("src", src);
    HOGDescriptor descriptor = HOGDescriptor();
    descriptor.setSVMDetector(descriptor.getDefaultPeopleDetector());
    vector<Rect> people;
    descriptor.detectMultiScale(src, people, 0, Size(3, 3), Size(0, 0));
    for(int i = 0; i < people.size(); i++) {
        rectangle(src, people[i], Scalar(0, 0, 255));
    }
    imshow("src_HOG", src);
    waitKey(0);
}

