
#include <iostream>
#include "Libraries\Headers\opencv2\core\core.hpp"
#include "Libraries\Headers\opencv2\highgui\highgui.hpp"
#include "Libraries\Headers\opencv2\opencv.hpp"
#include <functional>
#include <string>
#include "Transform.h"
#include "Convert.h"
using namespace cv;
using namespace std;
static int __str_cmp__(const char* string_1, const char* string_2)
{
	while (*string_1)
	{
		// if characters differ or end of second string is reached
		if (*string_1 != *string_2)
			break;

		// move to next pair of characters
		string_1++;
		string_2++;
	}
	// return the ASCII difference after converting char* to unsigned char*
	return *(const unsigned char*)string_1 - *(const unsigned char*)string_2 == 0 ? 1 : 0;
}
// Hàm main
int main(int argc, char* argv[]) {
	Transform colorTransfer;
	Convert converter;
	if (__str_cmp__(argv[2], "--rgb2gray")) {
		// --rgb2gray
		 
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[1], cv::IMREAD_ANYCOLOR);
		if (!inputImage.data || inputImage.channels() != 3) {
			std::cout << "[EXCEPTION] Error occurs.\n";
			return 0;
		}

		// Khởi tạo ảnh đầu ra
		cv::Mat outputImage = cv::Mat(inputImage.rows, inputImage.cols, CV_8UC1);

		// Chuyển đổi
		converter.Converter(inputImage, outputImage, 0);

		// Dispay ảnh ra màn hình
		cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image", inputImage);

		cv::namedWindow("Show result image RGB to GrayScale", cv::WINDOW_AUTOSIZE);
		cv::imshow("Show result image RGB to GrayScale", outputImage);
		cv::waitKey(0);

		cv::destroyWindow("Input image");
		cv::destroyWindow("Show result image RGB to GrayScale");
	}
	else if (__str_cmp__(argv[2], "--gray2rgb")) {
		// --gray2rgb
		 
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[1], cv::IMREAD_ANYCOLOR);
		if (!inputImage.data || inputImage.channels() != 1) {
			std::cout << "[EXCEPTION] Error occurs.\n";
			return 0;
		}

	

		// Khởi tạo ảnh đầu ra
		cv::Mat outputImage = cv::Mat(inputImage.rows, inputImage.cols, CV_8UC3);

		// Chuyển đổi
		converter.Converter(inputImage, outputImage, 1);


		// Dispay ảnh ra màn hình
		cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image", inputImage);
		cv::namedWindow("Show result image GrayScale to RGB", cv::WINDOW_AUTOSIZE);
		cv::imshow("Show result image GrayScale to RGB", outputImage);

		cv::waitKey(0);

		cv::destroyWindow("Input image");
		cv::destroyWindow("Show result image GrayScale to RGB");
	}
	else if (__str_cmp__(argv[2], "--openimg")) {
		// --gray2rgb
		 
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[1], cv::IMREAD_ANYCOLOR);
		if (!inputImage.data) {
			std::cout << "[EXCEPTION] Error occurs.\n";
			return 0;
		}

		// Dispay ảnh ra màn hình
		cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image", inputImage);
		

		cv::waitKey(0);

		cv::destroyWindow("Input image");
		
	}
	else if (__str_cmp__(argv[2], "--bright")) {
		// --bright
		 
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[1], cv::IMREAD_ANYCOLOR);
		if (!inputImage.data || (inputImage.channels() != 3 && inputImage.channels() != 1)) {
			std::cout << "[EXCEPTION] Error occurs.\n";
		}

		// Khởi tạo ảnh đầu ra
		cv::Mat outputImage = inputImage.clone();

		// Thay đổi độ sáng
		if (argv[3] == nullptr) {
			std::cout << "Exception: No brightness input.\n";
			return 0;
		}
		else {
			colorTransfer.ChangeBrighness(inputImage, outputImage, atoi(argv[3]));
			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result after change birghtness", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result after change birghtness", outputImage);
			cv::waitKey(0);
			cv::destroyWindow("Input image");
			cv::destroyWindow("Show result after change birghtness");
		}
	}
	else if (__str_cmp__(argv[2], "--contrast")) {
		// --contrast
		// code
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[1], cv::IMREAD_ANYCOLOR);
		if (!inputImage.data || (inputImage.channels() != 3 && inputImage.channels() != 1)) {
			std::cout << "[EXCEPTION] Error occurs.\n";
			return 0;
		}

		// Khởi tạo ảnh đầu ra
		cv::Mat outputImage = inputImage.clone();

		// Thay đổi độ sáng
		if (argv[3] == nullptr) {
			std::cout << "Exception: No contrast input.\n";
			return 0;
		}
		else {
			colorTransfer.ChangeContrast(inputImage, outputImage, (float)atof(argv[3]));

			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result after change contrast", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result after change contrast", outputImage);
			cv::waitKey(0);

			cv::destroyWindow("Input image");
			cv::destroyWindow("Show result after change contrast");
		}
	}
	else if ((__str_cmp__(argv[1], "--help")) || (__str_cmp__(argv[1], "--h"))) {
		std::cout << "Usage:  ColorTranform.exe [command] [input path] [command arguments]\n\n"
			<< "Options command & command arguments:\n"
			"--rgb2gray\t[no command arguments]\t\t Convert the image's color space from RGB to GrayScale.\n"
			"--gray2rgb\t[no command arguments]\t\t Convert the image's color space from GrayScale to RGB.\n"
			"--bright\t[b]\t\t\t\t Change image's brightness with intensity equal to [b] argument.\n"
			"--contrast\t[c]\t\t\t\t Change image's contrast with intensity equal to [c] argument.\n"
			
			"\n\nDepartment of Computer Science, University of Science\nAuthor: Hoang-Duc Nguyen"
			;
	}
	else {
		std::cout << "[Exception] Error arguments.\n";
	}
	//std::cin.get();
	return 0;
}


