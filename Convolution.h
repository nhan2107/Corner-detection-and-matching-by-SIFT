#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
class Convolution
{
public: 
	vector<float> GetKernel(); //trả về kernel
	void SetKernel(vector<float> k, int kWidth, int kHeight); //set kernel
	int DoConvolution(const Mat& sourceImage, Mat& destinationImage);
	/*
	Hàm tính convolution của 1 ảnh xám với kernel được xác định trước
	sourceImage: ảnh input
	destinationImage: ảnh output
	Hàm trả về
		0: nếu tính thành công
		1: nếu tính thất bại (không đọc được ảnh input,...)
	*/
	Convolution();
	~Convolution();
private:
	vector<float> _k;// lưu giá trị của ma trận kernel dùng để tích chập
	int _kWidth;//chiều rộng kernel
	int _kHeight;//chiều dài kernel
};

