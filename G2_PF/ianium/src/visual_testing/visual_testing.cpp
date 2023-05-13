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
	int match_method;
	int max_Trackbar = 5;

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
	const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
	cv::createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar, &VisualTesting::matchingMethod, this);
	matchingMethod(0, 0);
	cv::waitKey(0);

	return true;
}

/// <summary>
/// Function internally used by openCV in template_matching to obtain the matching occurrences
/// </summary>
void VisualTesting::matchingMethod(int, void* obj) {
	VisualTesting* instance = static_cast<VisualTesting*>(obj);

	instance->a = 10;
	std::cout << instance->a << std::endl;
}