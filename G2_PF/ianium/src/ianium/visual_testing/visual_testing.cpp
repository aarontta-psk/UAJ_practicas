#include "visual_testing.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <SDL2/SDL.h>

#define TEMP_SCREENSHOT_NAME "tempScreenshot.bmp"

using namespace ianium;

VisualTesting::VisualTesting(SDL_Window* sdl_window, SDL_Renderer* sdl_renderer) {
	window = sdl_window;
	renderer = sdl_renderer;
}

VisualTesting::~VisualTesting() = default;

bool VisualTesting::assertImageOnScreen(std::string imagePath)
{
	takeScreenshot();

	return template_matching(TEMP_SCREENSHOT_NAME, imagePath).size() != 0;
}

void VisualTesting::takeScreenshot()
{
	int width, height;
	SDL_GetRendererOutputSize(renderer, &width, &height);
	SDL_Surface* sshot = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
	SDL_SaveBMP(sshot, TEMP_SCREENSHOT_NAME);
	SDL_FreeSurface(sshot);
}

std::vector<std::pair<double, double>> VisualTesting::template_matching(std::string gameScreenshotImagePath, std::string templateImagePath)
{
	cv::Mat img; cv::Mat templateImg; cv::Mat maskImg; cv::Mat result;
	std::vector<std::pair<double, double>> resultVector;

	// image, template and mask (if used) are loaded
	img = cv::imread(gameScreenshotImagePath, cv::IMREAD_COLOR);
	templateImg = cv::imread(templateImagePath, cv::IMREAD_COLOR);

	if (img.empty() || templateImg.empty()) {
		std::cout << "Can't read one of the images" << std::endl;
		return resultVector;
	}

	// matching method selector
	cv::Mat img_display;
	img.copyTo(img_display);

	int result_cols = img.cols - templateImg.cols + 1;
	int result_rows = img.rows - templateImg.rows + 1;

	result.create(result_rows, result_cols, CV_32FC1);
	
	cv::matchTemplate(img, templateImg, result, cv::TM_CCOEFF_NORMED);

	double thresh = 0.8;				// set threshold value
	cv::Mat mask = (result >= thresh);	// create binary mask

	std::vector<cv::Point> locations;	// store template locations
	cv::findNonZero(mask, locations);	// find non-zero locations in mask

	for (const auto& loc : locations)
		cv::rectangle(img_display, cv::Rect(loc, templateImg.size()), cv::Scalar(0, 0, 255), 2); // draw rectangles around template
	
	// label connected components in binary mask
	cv::Mat labels, stats, centroids;
	// the background group isn't counted
	int num_groups = cv::connectedComponentsWithStats(mask, labels, stats, centroids);

	// loop over connected components and get center positions
	for (int i = 1; i < num_groups; i++) {
		int x = centroids.at<double>(i, 0);
		int y = centroids.at<double>(i, 1);
		resultVector.push_back(std::make_pair(x,y));
	}

	if (DEBUG_TEST) {
		imshow("Labeled_image", img_display);
		imshow("Black and White mask", result);
		cv::waitKey(0);
	}

	return resultVector;
}