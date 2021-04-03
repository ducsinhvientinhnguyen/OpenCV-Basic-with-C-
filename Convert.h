﻿#pragma once
#ifndef CONVERTER_H
#define CONVERTER_H

#include "CV_Include.h"

class Convert
{
	/*
	Hàm chuyển đổi không gian màu của ảnh từ RGB sang GrayScale
	sourceImage: ảnh input
	destinationImage: ảnh output
	Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input,...)
	*/
	int RGB2GrayScale(const cv::Mat& sourceImage, cv::Mat& destinationImage);

	/*
	Hàm chuyển đổi không gian màu của ảnh từ GrayScale sang RGB
	sourceImage: ảnh input
	destinationImage: ảnh output
	Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input,...)
	*/
	int GrayScale2RGB(const cv::Mat& sourceImage, cv::Mat& destinationImage);


public:
	/*
	Hàm chuyển đổi không gian màu của ảnh
	sourceImage: ảnh input
	destinationImage: ảnh output cùng kích thước, cùng loại với ảnh input
	type: loại chuyển đổi
		0,1: chuyển từ RGB sang GrayScale và ngược lại
	Hàm trả về
		0: nếu chuyển thành công
		1: nếu chuyển thất bại (không đọc được ảnh input hay type không chính xác,...)
	*/
	int Converter(cv::Mat& sourceImage, cv::Mat& destinationImage, int type);
	int Converter(IplImage* sourceImage, IplImage* destinationImage, int type);
	Convert();
	~Convert();
};

#endif // CONVERTER_H