#include "Convolution.h"

vector<float> Convolution::GetKernel()
{
	return this->_k;
}

void Convolution::SetKernel(vector<float> k, int kWidth, int kHeight)
{
	this->_k = k;
	this->_kHeight = kHeight;
	this->_kWidth = kWidth;
}

int Convolution::DoConvolution(const Mat& sourceImage, Mat& destinationImage)
{
	if (sourceImage.empty())
	{
		return 1;
	}
	int w = sourceImage.cols;
	int h = sourceImage.rows;
	destinationImage = Mat(sourceImage.rows, sourceImage.cols, CV_32FC1, Scalar(0));
	int	xStart = this->_kWidth / 2; 
	int yStart = this->_kHeight / 2;
	int xEnd = w - (this->_kWidth - 1);
	int yEnd = h - (this->_kHeight - 1);
	int step = w;

	uchar* pSrc = sourceImage.data + w * yStart + xStart;
	float* pDst = (float*)(destinationImage.data) + w * yStart + xStart;

	// Create offset table
	vector<int> offsets;
	int wLim = this->_kWidth / 2;
	int hLim = this->_kHeight / 2;
	for (int y = -hLim; y <= hLim; y++)
		for (int x = -wLim; x <= wLim; x++)
		{
			offsets.push_back(y * step + x);
		}
	// Calculate convolution
	int size = this->_kWidth * this->_kHeight;
	for (int y = yStart; y < yEnd; y++) 
	{
		const uchar* pSrcRow = pSrc;
		float* pDstRow = pDst;
		for (int x = xStart; x < xEnd; x++, pSrcRow++, pDstRow++)
		{
			float sum = 0;
			for (int u = -yStart; u <= yStart; u++)
				for (int i = 0; i < size; i++)
					sum += pSrcRow[offsets[i]] * _k[i];
			*pDstRow = sum;
		}
		pSrc += step;
		pDst += step;
	}
	return 0; // if success
}

Convolution::Convolution() {}
Convolution::~Convolution() {}
