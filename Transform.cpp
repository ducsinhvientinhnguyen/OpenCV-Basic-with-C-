#include "Transform.h"

int Transform::ChangeBrighness(const cv::Mat& sourceImage, cv::Mat& destinationImage, short b)
{
	// Kiểm trả ảnh đầu vào
	if (!sourceImage.data) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 1; // Trả về 1
	}
	// Chiều rộng của ảnh source
	int width = sourceImage.cols;

	// Chiều cao của ảnh source
	int heigth = sourceImage.rows;

	// Số channels của ảnh source
	int sourceChannels = sourceImage.channels();

	// Mode
	int mode;

	// Check the source image is RGB type?
	if (sourceImage.type() == CV_8UC3) {
		mode = 3;
		// Khởi tạo ảnh destination là ảnh grayscale với thông số height, width
		destinationImage = cv::Mat(heigth, width, CV_8UC3, cv::Scalar(0));
	}
	else if (sourceImage.type() == CV_8UC1) {
		mode = 1;
		// Khởi tạo ảnh destination là ảnh grayscale với thông số height, width
		destinationImage = cv::Mat(heigth, width, CV_8UC1, cv::Scalar(0));
	}

	// Số channels của ảnh destination
	int destinationChannels = destinationImage.channels();

	// Widthstep của ảnh source
	size_t sourceWidthStep = sourceImage.step[0];

	// Widthstep của ảnh destination
	size_t destinationWidthStep = destinationImage.step[0];

	// Con trỏ quản lý vùng nhớ data ảnh source
	uchar* ptrSourceData = sourceImage.data;

	// Con trỏ quản lý vùng nhớ data ảnh destination
	uchar* ptrDestinationData = destinationImage.data;

	for (int y = 0; y < heigth; y++, ptrSourceData += sourceWidthStep, ptrDestinationData += destinationWidthStep) {
		uchar* ptrSourceRow = ptrSourceData;
		uchar* ptrDestinationRow = ptrDestinationData;

		for (int x = 0; x < width; x++, ptrSourceRow += sourceChannels, ptrDestinationRow += destinationChannels) {
			if (mode == 3) {
				// Lấy giá trị kênh màu Blue của ảnh source
				uchar blue = ptrSourceRow[0];

				// Lấy giá trị kênh màu Green của ảnh source
				uchar green = ptrSourceRow[1];

				// Lấy giá trị kênh màu Red của ảnh source
				uchar red = ptrSourceRow[2];

				blue = blue + b > 255 ? 255 : blue + b;
				green = green + b > 255 ? 255 : green + b;
				red = red + b > 255 ? 255 : red + b;

				// Gán giá trị độ xám vừa lấy được vào kênh màu Blue của ảnh destination
				ptrDestinationRow[0] = blue;
				// Gán giá trị độ xám vừa lấy được vào kênh màu Green của ảnh destination
				ptrDestinationRow[1] = green;
				// Gán giá trị độ xám vừa lấy được vào kênh màu Red của ảnh destination
				ptrDestinationRow[2] = red;
			}
			else if (mode == 1) {
				// Lấy giá trị kênh màu gray của ảnh source
				uchar gray = ptrSourceRow[0];

				gray = gray + b > 255 ? 255 : gray + b;

				// Gán giá trị độ xám vừa tính được vào kênh vào của ảnh destination
				ptrDestinationRow[0] = gray;
			}

		}
	}

	// Lưu ảnh xuống đĩa
	cv::imwrite("result_brightness.jpg", destinationImage);


	// Chuyển đổi ảnh thành công: in ra màn hình console tin nhắn
	std::cout << "Sucess: change brightness of image.\n";
	return 0;
}

int Transform::ChangeContrast(const cv::Mat& sourceImage, cv::Mat& destinationImage, float c)
{
	if (!sourceImage.data) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 0; // Trả về 1
	}
	// Tính số cột, số dòng của sourceImage
	int width = sourceImage.cols, height = sourceImage.rows;
	//tạo destinationImage là 1 bản sao của sourceImage
	destinationImage = sourceImage.clone();
	//Tính số channels
	int srcChannels = sourceImage.channels();
	int desChannels = destinationImage.channels();
	//Kiểm tra số channels của sourceImage
	if (srcChannels == 1) {
		for (int y = 0; y < height; y++)
		{
			//con trỏ quản lý dòng
			const uchar* pSrcRow = sourceImage.ptr<uchar>(y);
			uchar* pDstRow = destinationImage.ptr<uchar>(y);

			for (int x = 0; x < width; x++, pSrcRow += srcChannels, pDstRow += desChannels)
			{
				//lấy giá trị kênh màu nhân với c, sau đó gán qua destinationImage
				pDstRow[0] = cv::saturate_cast<uchar>(pSrcRow[0] * c);
			}


		}

	}
	else if (srcChannels == 3) {
		// Con trỏ quản lý vùng nhớ data ảnh sourceimage
		uchar* ptrSourceData = sourceImage.data;
		// Con trỏ quản lý vùng nhớ data ảnh destinationImage
		uchar* ptrdestinationData = destinationImage.data;
		//Tính widthstep
		int sourceWidthStep = sourceImage.step[0];
		int desWidthStep = destinationImage.step[0];


		for (int y = 0; y < height; y++, ptrSourceData += sourceWidthStep, ptrdestinationData += desWidthStep) {
			uchar* ptrSourceRow = ptrSourceData;
			uchar* ptrDesRow = ptrdestinationData;

			for (int x = 0; x < width; x++, ptrSourceRow += srcChannels, ptrDesRow += desChannels) {

				// lấy giá trị kênh màu nhân với c, sau đó gán qua destinationImage

				ptrDesRow[0] = cv::saturate_cast<uchar>(ptrSourceRow[0] * c);

				ptrDesRow[1] = cv::saturate_cast<uchar>(ptrSourceRow[1] * c);

				ptrDesRow[2] = cv::saturate_cast<uchar>(ptrSourceRow[2] * c);


			}
		}

	}
	//Lưu ảnh destinationImage
	cv::imwrite("result_contrast.jpg", destinationImage);
	std::cout << "Sucess: change contrast of image.\n";
	return 1;
}

Transform::Transform() = default;

Transform::~Transform() = default;

