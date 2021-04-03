#include "Convert.h"

/*
Hàm chuyển đổi không gian màu của ảnh từ RGB sang GrayScale
	sourceImage: ảnh input
	destinationImage: ảnh output
Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input,...)
*/
int Convert::RGB2GrayScale(const cv::Mat& sourceImage, cv::Mat& destinationImage)
{
	// Kiểm tra ảnh đầu vào
	if (sourceImage.data == NULL) {
		return 0;
	}

	// Khai báo các hệ số alpha_1, alpha_2, alpha_3
	float alpha1 = 0.11;
	float alpha2 = 0.59;
	float alpha3 = 0.3;

	// Chiều rộng của ảnh
	int width = sourceImage.cols;
	// Chiều cao của ảnh
	int heigth = sourceImage.rows;
	// Số channels của ảnh source
	int srcChannels = sourceImage.channels();
	// Số channels của ảnh đích
	int dstChannels = destinationImage.channels();

	// Tạo ảnh destination
	destinationImage = cv::Mat(heigth, width, CV_8UC1);

	// Witdth step của ảnh source
	int srcWidthStep = sourceImage.step[0];
	// Witdth step của ảnh destination
	int dstWidthStep = destinationImage.step[0];

	// Con trỏ vùng data ảnh source
	uchar* pSrcData = sourceImage.data;
	// Con trỏ vùng data ảnh destination
	uchar* pDstData = destinationImage.data;

	for (int y = 0; y < heigth; y++, pSrcData += srcWidthStep, pDstData += dstWidthStep) {
		uchar* pSrcRow = pSrcData;
		uchar* pDstRow = pDstData;

		for (int x = 0; x < width; x++, pSrcRow += srcChannels, pDstRow += dstChannels) {
			uchar blue = pSrcRow[0];
			uchar green = pSrcRow[1];
			uchar red = pSrcRow[2];
			uchar gray_value = (uchar)(blue * alpha1 + green * alpha2 + red * alpha3);
			pDstRow[0] = gray_value;
		}
	}
	return 1;
}

/*
Hàm chuyển đổi không gian màu của ảnh từ GrayScale sang RGB
	sourceImage: ảnh input
	destinationImage: ảnh output
Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input,...)
*/
int Convert::GrayScale2RGB(const cv::Mat& sourceImage, cv::Mat& destinationImage)
{
	if (sourceImage.data == NULL) {
		return 0;
	}


	int width = sourceImage.cols;
	int heigth = sourceImage.rows;

	destinationImage = cv::Mat(heigth, width, CV_8UC3);
	int srcChannels = sourceImage.channels();
	int dstChannels = destinationImage.channels();

	int srcWidthStep = sourceImage.step[0];
	int dstWidthStep = destinationImage.step[0];

	uchar* pSrcData = sourceImage.data;
	uchar* pDstData = destinationImage.data;

	for (int y = 0; y < heigth; y++, pSrcData += srcWidthStep, pDstData += dstWidthStep) {
		uchar* pSrcRow = pSrcData;
		uchar* pDstRow = pDstData;

		for (int x = 0; x < width; x++, pSrcRow += srcChannels, pDstRow += dstChannels) {
			uchar gray_value = pSrcRow[0];
			pDstRow[0] = gray_value;
			pDstRow[1] = gray_value;
			pDstRow[2] = gray_value;
		}
	}

	return 1;
}
int Convert::Converter(cv::Mat& sourceImage, cv::Mat& destinationImage, int type)
{
	// Kiểm trả ảnh đầu vào
	if (!sourceImage.data) {
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 1;
	}

	// Switch để chọn lựa type chuyển đổi
	switch (type)
	{
	case 0: return this->RGB2GrayScale(sourceImage, destinationImage);

	case 1: return this->GrayScale2RGB(sourceImage, destinationImage);

	

	default:
		// Exception: Type không hỗ trợ
		std::cerr << "[EXCEPTION] Type is not supported.\n";
		return 1;
	}

	// Chuyển đổi ảnh thành công
	return 0;
}


int Convert::Converter(IplImage* sourceImage, IplImage* destinationImage, int type)
{
	cv::Mat matSourceImage = cv::cvarrToMat(sourceImage);
	cv::Mat matDestinationImage = cv::cvarrToMat(destinationImage);

	/*
	Mat cvarrToMat(const CvArr* arr, bool copyData=false, bool allowND=true, int coiMode=0 )
	Parameters:
	•arr — input CvMat, IplImage , or CvMatND.
	•copyData — when false (default value), no data is copied and only the new header is created, in this case, the original array should not be deallocated while the new matrix header is used; if the parameter is true, all the data is copied and you may deallocate the original array right after the conversion.
	•allowND — when true (default value), CvMatND is converted to 2-dimensional Mat, if it is possible (see the discussion below); if it is not possible, or when the parameter is false, the function will report an error.
	•coiMode — parameter specifying how the IplImage COI (when set) is handled.
	◦If coiMode=0 and COI is set, the function reports an error.
	◦If coiMode=1 , the function never reports an error. Instead, it returns the header to the whole original image and you will have to check and process COI manually. See extractImageCOI() .
	Normally, the function is used to convert an old-style 2D array ( CvMat or IplImage ) to Mat.
	However, the function can also take CvMatND as an input and create Mat() for it, if it is possible.
	And, for CvMatND A , it is possible if and only if A.dim[i].size*A.dim.step[i] == A.dim.step[i-1] for all or for all but one i, 0 < i < A.dims .
	That is, the matrix data should be continuous or it should be representable as a sequence of continuous matrices. By using this function in this way, you can process CvMatND using an arbitrary element-wise function.
	The last parameter, coiMode , specifies how to deal with an image with COI set. By default, it is 0 and the function reports an error when an image with COI comes in. And coiMode=1 means that no error is signalled.
	You have to check COI presence and handle it manually. The modern structures, such as Mat and MatND do not support COI natively.
	To process an individual channel of a new-style array, you need either to organize a loop over the array (for example, using matrix iterators) where the channel of interest will be processed, or extract the COI using mixChannels() (for new-style arrays) or extractImageCOI() (for old-style arrays), process this individual channel, and insert it back to the output array if needed (using mixChannels() or insertImageCOI() , respectively).
	*/

	// Kiểm trả ảnh đầu vào
	if (!matSourceImage.data) {
		std::cout << "Exception: Error with input image.\n";
		return 1;
	}

	// Switch để chọn lựa type chuyển đổi
	switch (type)
	{
	case 0: return this->RGB2GrayScale(matSourceImage, matDestinationImage);

	case 1: return this->GrayScale2RGB(matSourceImage, matDestinationImage);


	default:
		// Exception: Type không hỗ trợ
		std::cerr << "[EXCEPTION] Type is not supported.\n";
		return 1;
	}

	// Chuyển đổi ảnh thành công
	return 0;
}

// Constructor
Convert::Convert() = default;

// Destructor
Convert::~Convert() = default;

