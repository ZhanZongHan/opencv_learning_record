#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    string xml_path = "../ex5/haarcascade_xml/haarcascade_frontalface_alt.xml";
    CascadeClassifier face_cascade;
    if (!face_cascade.load(xml_path)) {
        cout << "xml file load unsuccessfully!" << endl;
        return -1;
    }
    VideoCapture capture(0);
    Mat frame;
    namedWindow("face", WINDOW_AUTOSIZE);
    int count = 1;
    while (capture.read(frame)) {
        vector<Rect> faces;
        face_cascade.detectMultiScale(frame, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(400, 400), Size(400, 400));
        for (int i = 0; i < faces.size(); i++) {
            rectangle(frame, faces[i], Scalar(0, 0, 255), 2);
            Mat dst;
            resize(frame(faces[i]), dst, Size(150, 150));
            if (count % 5 == 0)
                imwrite(format("../ex5/faces/face_%d.jpg", count/5), dst);
        }
        count++;
        imshow("face", frame);
        char c = waitKey(10);
        if (c == 'q' || count == 200)
            break;
    }
    capture.release();
    return 0;
}

