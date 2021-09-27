#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/utils/logger.hpp>
#include "fuction.h"

using namespace std;

int main() {
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
	cv::namedWindow("Image1");
	int base = 0;
	int height = 720;
	int width = 1080;
	cv::Mat image1(height+1, width+1, CV_8U,base);
	Bresenham(image1, 0, -(height >> 1), 0, (height >> 1), 50);
	Bresenham(image1, -(width >> 1), 0, (width >> 1), 0, 50);
	LineDDA(image1, 0, 0, 300, 300);
	LineMid(image1, 100,300, 300, 100);
	Bresenham(image1, -400, -200, -100, 300);
	CircleDDA(image1, 50, 50, 50);
	CircleMid(image1, -30, -50, 30);
	EllipeMid(image1, -100, -50, 100, 200);
	cv::imshow("Image1", image1);
	cv::imshow("Image1", image1);
	cv::waitKey(0);
	return 0;
}
