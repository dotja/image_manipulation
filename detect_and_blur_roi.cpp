#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char* argv[])
{

	//reading images as command-line args
	cv::Mat img, img_roi;

	img = cv::imread(argv[1], cv::IMREAD_COLOR);
	img_roi = cv::imread(argv[2], cv::IMREAD_COLOR);

	if ( img.empty() || img_roi.empty() )
	{
		std::cout << "can not read image.." << std::endl;
		return 1;
	}

	//create the result matrix which will be used during matching
	//it takes rows, columns and image type
	cv::Mat result;

	int result_cols = img.cols - img_roi.cols;
	int result_rows = img.rows - img_roi.rows;

	int img_type = img.type();
	result.create(result_rows, result_cols, img_type);


	//match method used during the matching process
	int match_method = 0;

	//each method uses a specific equation
	std::cout << cv::TM_SQDIFF << std::endl;
	std::cout << cv::TM_SQDIFF_NORMED << std::endl;
	std::cout << cv::TM_CCORR << std::endl;
	std::cout << cv::TM_CCORR_NORMED << std::endl;
	std::cout << cv::TM_CCOEFF << std::endl;
	std::cout << cv::TM_CCOEFF_NORMED << std::endl;

	//run the matchTemplate function
	matchTemplate(img, img_roi, result, match_method);
	//img is the image where the search occurs (W x H)
	//img_roi is the template that we are looing for (w x h)
	//result is where the resutl is stored (W-w+1 x H-h+1)

	//prepare variables
	double minVal, maxVal;
	cv::Point minLoc, maxLoc, matchLoc;

	//find the global min and max in the array
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

	//determine which location to use accoring to matching method used
	if (match_method == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else {
		matchLoc = maxLoc;
	}

	//determine the region to blur programatically
	cv::Rect img_blur = cv::Rect( minLoc, cv::Point(matchLoc.x + img_roi.cols, matchLoc.y + img_roi.rows) );

	//OR: determine the region to blur interactively (uncomment below)
	//cv::Rect img_blur = selectROI(img);


	//blur using a Gaussian filter
	//it takes src image, destination image, kernel size
	// you can think of the kernel as the coefficients used on the pixels of interest
	// if the kernel is (0,0) then the filter will be calculated using the sigma argument
	cv::GaussianBlur( img(img_blur), img(img_blur), cv::Size(51, 51), 0 );

	cv::imshow("Result", img);

	//save the result (optional)
	cv::imwrite("result.png", img);

	cv::waitKey(0);
	return 0;
}



