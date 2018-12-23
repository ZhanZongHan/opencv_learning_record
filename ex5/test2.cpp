#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>

using namespace std;
using namespace cv;
using namespace face;

int main() {
    string part_path = "../ex5/faces/";
    ifstream inImgPath(part_path + "labels.txt");    //标定所用图像文件的路径
    vector<string> imgList;
    vector<Mat> images;
    vector<int> labels;
    char separator = ';';
    string label;
    string temp;
    if (!inImgPath.is_open()) {
        cout << "没有找到文件" << endl;
    }
    //读取文件中保存的图片文件路径，并存放在数组中, label为每个人的识别标记
    while (getline(inImgPath, temp)) {
        string image_name;
        stringstream line(temp);
        // 由分割符将照图片名与标记分隔开
        getline(line, image_name, separator);
        getline(line, label);

        images.push_back(imread(part_path + image_name, 0));
        labels.push_back(atoi(label.c_str()));
    }
    Size face_size = images[0].size();

    // *****************************************
    // 开启图像识别
    string xml_path = "../ex5/haarcascade_xml/haarcascade_frontalface_alt.xml";
    CascadeClassifier face_cascade;
    if (!face_cascade.load(xml_path)) {
        cout << "xml file load unsuccessfully!" << endl;
        return -1;
    }
    vector<Rect> faces;
    VideoCapture capture(0);
    Mat frame;

    //训练数据集
    Ptr<LBPHFaceRecognizer> modle = LBPHFaceRecognizer::create();
    modle->train(images, labels);
    Mat gray;
    // 开启摄像头
    while (capture.read(frame)) {
        face_cascade.detectMultiScale(frame, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(400, 400), Size(400, 400));
        for (int i = 0; i < faces.size(); i++) {
            Mat roi = frame(faces[i]);
            cvtColor(roi, gray, COLOR_BGR2GRAY);
            Mat dst;
            resize(gray, dst, face_size);
            rectangle(frame, faces[i], Scalar(0, 0, 255), 2);
            int label = modle->predict(dst);
            // 如果检测出来的结果得到匹配
            putText(frame, label == 0 ? "zzh" : "unknown", Point(faces[i].x, faces[i].y),
                    FONT_HERSHEY_COMPLEX_SMALL, 2,
                    Scalar(255, 255, 0), 2);
        }
        imshow("face", frame);
        if (waitKey(10) == 'q')
            break;
    }
    capture.release();
    return 0;
}
