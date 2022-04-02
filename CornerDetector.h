#pragma once
#include "Convolution.h"

class CornerDetector
{
public:
	Mat detectHarrist(Mat sourceImage, float alpha, int thres);
	Mat detectBlob(Mat sourceImage, int thres);
	Mat detectBlob(Mat sourceImage, int thres, vector<KeyPoint>& points);
	Mat detectDOG(Mat sourceImage, int thres);
	CornerDetector();
	~CornerDetector();
private:
	Convolution _conv;
};