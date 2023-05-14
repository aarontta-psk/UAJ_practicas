#include "visual_testing.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <SDL2/SDL.h>


void VisualTesting::testOPENCV(const char* path)
{
	cv::Mat image = cv::imread(path);
	if (!image.empty()) {
		cv::imshow("testImage", image);
		cv::waitKey(0);
	}
	else std::cout << "Failed to read, " << path << "not found" << std::endl;
}

VisualTesting::VisualTesting() {
	initPrivate();
}

VisualTesting::~VisualTesting() {
	releasePrivate();
}

bool VisualTesting::isImageOnScreen(const char* imagePath)
{
	return template_matching("TODO", imagePath).size() != 0;
}

void VisualTesting::takeScreenshot()
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);


	int width, height;
	SDL_GetRendererOutputSize(renderer, &width, &height);
	SDL_Surface* sshot = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
	SDL_SaveBMP(sshot, "screenshot.bmp");
	SDL_FreeSurface(sshot);
}

bool VisualTesting::initPrivate()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return false;

	window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_HIDDEN);
	if (!window)
		return false;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
		return false;
	return true;
}

void VisualTesting::releasePrivate()
{
	//instance.get()->closePlatform();
	SDL_Quit();
}

std::vector<std::pair<double, double>> VisualTesting::template_matching(const char* gameScreenshotImagePath, const char* templateImagePath, const char* maskPath)
{

	cv::Mat img; cv::Mat templateImg; cv::Mat maskImg; cv::Mat result;
	std::vector<std::pair<double, double>> resultVector;

	// Image, template and mask (if used) are loaded
	img = cv::imread(gameScreenshotImagePath, cv::IMREAD_COLOR);
	templateImg = cv::imread(templateImagePath, cv::IMREAD_COLOR);
	if(maskPath) maskImg = cv::imread(maskPath, cv::IMREAD_COLOR);

	if (img.empty() || templateImg.empty() || (maskPath && maskImg.empty()))
	{
		std::cout << "Can't read one of the images" << std::endl;
		return resultVector;
	}

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
	
	// label connected components in binary mask
	cv::Mat labels, stats, centroids;
	int num_groups = cv::connectedComponentsWithStats(mask, labels, stats, centroids);
	// the background group isn't counted
	std::cout << num_groups - 1 << std::endl;

	// loop over connected components and get center positions
	for (int i = 1; i < num_groups; i++) {
		int x = centroids.at<double>(i, 0);
		int y = centroids.at<double>(i, 1);
		resultVector.push_back(std::make_pair(x,y));
	}

	imshow("Labeled_image", img_display);
	imshow("Black and White mask", result);
	cv::waitKey(0);

	return resultVector;
}