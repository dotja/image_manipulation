#include <iostream>
#include <opencv2/core.hpp> // basic building blocks
#include <opencv2/imgcodecs.hpp> // capabilities for reading and writing images 
#include <opencv2/highgui.hpp> // view an image in a window
#include <opencv2/imgproc.hpp> // for cvtColor

using namespace std;
using namespace cv;


int main (int argc, char* argv[])
{
	cout << "name of the input image: " << argv[1] << endl;
	cout << "name of the output image: " << argv[2] << endl;

	Mat img;
	img = imread(argv[1], IMREAD_COLOR);

	if (img.empty())
	{
		cout << "can not read image.." << endl;
		return 1;
	}

	Mat gray_img;
	cvtColor(img, gray_img, COLOR_BGR2GRAY);

	imwrite(argv[2], gray_img);
	imshow("color image", img);
	imshow("gray image", gray_img);
	waitKey(0);

	return 0;
}
