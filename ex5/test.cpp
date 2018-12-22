#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    /* -------------------------	【0】加载图像	----------------------------------------------- */
    VideoCapture vc(0);
    Mat frame_src;
    Mat frame_gray;
    while (1) {
        vc >> frame_src;
        imshow("src", frame_src);
        if(waitKey(10) == 'q') {
            break;
        }
    }
    cvtColor(frame_src, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    /* -------------------------	【1】加载模型	----------------------------------------------- */
    CascadeClassifier face_cascade;
    CascadeClassifier eye_cascade;

    String face_cascade_name = "../ex5/haarcascade_xml/haarcascade_frontalface_alt.xml";
    String eye_cascade_name = "../ex5/haarcascade_xml/haarcascade_eye_tree_eyeglasses.xml";

    if (!face_cascade.load(face_cascade_name))
    {
        printf("can not load the haar_face_Cascader file \n");
        return -1;
    }
    if (!eye_cascade.load(eye_cascade_name))
    {
        printf("can not load the haar_eye_Cascader file \n");
        return -1;
    }


    /* -------------------------	【2】Detect faces	----------------------------------------------- */
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30), Size(300, 300));
    for (int i = 0; i < faces.size(); i++)
    {
        rectangle(frame_src, faces[i], Scalar(0, 255, 0), 2, 8, 0);

        Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        ellipse(frame_src, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
    }


    /* -------------------------	【3】In each face, detect eyes	----------------------------------------------- */
    std::vector<Rect> eyes;
    for (size_t i = 0; i < faces.size(); i++)
    {
        Mat faceROI = frame_gray(faces[i]);

        eye_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
        for (size_t j = 0; j < eyes.size(); j++)
        {
            Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
            int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
            circle(frame_src, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
        }
    }


    imshow("result", frame_src);
    waitKey();

    return 0;
}

