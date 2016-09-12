// CannyStill.cpp

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           // may have to modify this line if not using Windows

// function prototypes ////////////////////////////////////////////////////////////////////////////
double calculateSharpness(const cv::Mat& src);

///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	cv::Mat imgOrigGrayscale;
	cv::Mat imgBlurred;

    imgOrigGrayscale = cv::imread("image.png", CV_LOAD_IMAGE_GRAYSCALE);          // open image

	if (imgOrigGrayscale.empty()) {                                  // if unable to open image
		std::cout << "error: image not read from file\n\n";     // show error message on command line
		_getch();                                               // may have to modify this line if not using Windows
		return(0);                                              // and exit program
	}

    cv::blur(imgOrigGrayscale, imgBlurred, cv::Size(7, 7));
    //cv::blur(imgBlurred, imgBlurred, cv::Size(7, 7));             // comment these lines out (or not) to test with more or less blurring
    //cv::blur(imgBlurred, imgBlurred, cv::Size(7, 7));

	cv::imshow("imgOrigGrayscale", imgOrigGrayscale);     // show windows
	cv::imshow("imgBlurred", imgBlurred);
    
    double origImageSharpness = calculateSharpness(imgOrigGrayscale);
    double blurredImageSharpness = calculateSharpness(imgBlurred);

    std::cout << "origImageSharpness = " << origImageSharpness << "\n";
    std::cout << "blurredImageSharpness = " << blurredImageSharpness << "\n";

	cv::waitKey(0);                 // hold windows open until user presses a key

	return(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// check image sharpness using the Sobel-Tenengrad method
// the higher the return value, the sharper the image
double calculateSharpness(const cv::Mat& imgInput) {
    cv::Mat imgGradientX, imgGradientY;
    cv::Sobel(imgInput, imgGradientX, CV_64F, 1, 0);
    cv::Sobel(imgInput, imgGradientY, CV_64F, 0, 1);

    cv::Mat sumOfSquares = imgGradientX.mul(imgGradientX) + imgGradientY.mul(imgGradientY);

    double sharpness = cv::mean(sumOfSquares).val[0];
    return sharpness;
}


