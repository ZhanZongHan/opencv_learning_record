#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    ifstream ifs("../calibrateCamera/images/calibdata.txt");
    vector<string> filename;
    string filename_temp;
    vector<Mat> boards;
    while (getline(ifs, filename_temp)) {
        string file_path = "../calibrateCamera/images/" + filename_temp;
        Mat chessboard = imread(file_path);
        if (chessboard.empty()) {
            cout << filename_temp << " can not be loaded..." << endl;
            continue;
        }
        filename.emplace_back(filename_temp);
        boards.emplace_back(chessboard);
    }
    Size board_size(9, 6);  // 棋盘内角点行列上的角点数
    vector<vector<Point2f>> image_points;   // 每副图像内角点的坐标
    for (int i = 0; i < boards.size(); i++) {
        vector<Point2f> corners;
        findChessboardCorners(boards[i], board_size, corners);
        Mat gray_board;
        cvtColor(boards[i], gray_board, COLOR_BGR2GRAY);
        find4QuadCornerSubpix(gray_board, corners, Size(5, 5));
        drawChessboardCorners(gray_board, board_size, corners, true);
        image_points.emplace_back(corners);
    }

    vector<vector<Point3f>> object_points;
    Size square_size(10, 10);
    for (int k = 0; k < boards.size(); k++) {
        vector<Point3f> temp_points;
        for (int i = 0; i < board_size.height; i++) {
            for (int j = 0; j < board_size.width; j++) {
                Point3f world_point;
                world_point.x = i * square_size.width;
                world_point.y = j * square_size.height;
                world_point.z = 0;
                temp_points.emplace_back(world_point);
            }
        }
        object_points.emplace_back(temp_points);
    }
    Size image_size; // 图像的宽高
    image_size.width = boards[0].cols;
    image_size.height = boards[0].rows;
    Mat camera_matrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); // 内参矩阵
    Mat dist_coeffs = Mat(1, 5, CV_32FC1, Scalar::all(0)); // 畸变矩阵
    vector<Mat> r_vecs;  // 旋转向量
    vector<Mat> t_vecs; //  位移向量
    calibrateCamera(object_points, image_points, image_size, camera_matrix, dist_coeffs, r_vecs, t_vecs);
    cout << "内参矩阵：" << endl << camera_matrix << endl << endl;
    cout << "畸变矩阵：" << endl << dist_coeffs << endl << endl;
    for (int i = 0; i < boards.size(); ++i) {
        Mat src = imread("../calibrateCamera/images/" + filename[i]);
        Mat dst, src_resize, dst_resize;
/*    undistort(src, dst, camera_matrix, dist_coeffs);
    resize(src, src_resize, Size(src.rows / 8, src.cols / 8));
    resize(dst, dst_resize, Size(dst.rows / 8, dst.cols / 8));
    imshow("src_resize", src_resize);
    imshow("dst_resize", dst_resize);*/
/*    undistort(src, dst, camera_matrix, dist_coeffs);
    imshow("src", src);
    resize(dst, dst_resize, Size(dst.cols / 1, dst.rows / 1));
    imshow("dst_resize", dst_resize);*/
        Mat mapx = Mat(image_size, CV_32FC1);
        Mat mapy = Mat(image_size, CV_32FC1);
        Mat R = Mat::eye(3, 3, CV_32F);
        Mat new_camera_matrix = getOptimalNewCameraMatrix(camera_matrix, dist_coeffs, image_size, 1, image_size, 0);
        initUndistortRectifyMap(camera_matrix, dist_coeffs, R, new_camera_matrix, image_size, CV_32FC1, mapx, mapy);
        dst = Mat::zeros(src.size(), src.type());
        remap(src, dst, mapx, mapy, INTER_LINEAR);
        resize(dst, dst_resize, Size(dst.cols / 2, dst.rows / 2));
        imshow("dst_resize", dst_resize);
        waitKey(200);
    }


    return 0;
}

