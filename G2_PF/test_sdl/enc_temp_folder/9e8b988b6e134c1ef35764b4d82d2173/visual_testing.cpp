#include "visual_testing/visual_testing.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

void VisualTesting::testOPENCV(const char* path)
{
	cv::Mat image = cv::imread(path);
	if (!image.empty()) {
		cv::imshow("testImage", image);
		cv::waitKey(0);
	}
	else std::cout << "Failed to read, " << path << "not found" << std::endl;
}

bool VisualTesting::template_matching(const char* gameScreenshotImagePath, const char* templateImagePath, const char* maskPath)
{
	cv::Mat img; cv::Mat templateImg; cv::Mat maskImg; cv::Mat result;
	const char* image_window = "Source Image";
	const char* result_window = "Result window";

	// Image, template and mask (if used) are loaded
	img = cv::imread(gameScreenshotImagePath, cv::IMREAD_COLOR);
	templateImg = cv::imread(templateImagePath, cv::IMREAD_COLOR);
	if(maskPath) maskImg = cv::imread(maskPath, cv::IMREAD_COLOR);

	if (img.empty() || templateImg.empty() || (maskPath && maskImg.empty()))
	{
		std::cout << "Can't read one of the images" << std::endl;
		return false;
	}

	cv::namedWindow(image_window, cv::WINDOW_AUTOSIZE);
	cv::namedWindow(result_window, cv::WINDOW_AUTOSIZE);

	// Matching method selector
	cv::Mat img_display;
	img.copyTo(img_display);
	int result_cols = img.cols - templateImg.cols + 1;
	int result_rows = img.rows - templateImg.rows + 1;

	result.create(result_rows, result_cols, CV_32FC1);
	/*bool method_accepts_mask = cv::TM_SQDIFF
	if (use_mask && method_accepts_mask)
	{
		matchTemplate(img, templ, result, match_method, mask);
	}*/
	/*else*/
	
	cv::matchTemplate(img, templateImg, result, cv::TM_CCOEFF_NORMED);

	//cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

	double thresh = 0.8; // set threshold value
	cv::Mat mask = (result >= thresh); // create binary mask

	std::vector<cv::Point> locations; // store template locations
	cv::findNonZero(mask, locations); // find non-zero locations in mask

	for (const auto& loc : locations) {
		cv::rectangle(img_display, cv::Rect(loc, templateImg.size()), cv::Scalar(0, 0, 255), 2); // draw rectangles around template
	}
	std::cout << locations.size() << std::endl;

	imshow(image_window, img_display);
	imshow(result_window, result);
	cv::waitKey(0);

	return true;
}