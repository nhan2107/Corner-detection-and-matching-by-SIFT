#include "CornerDetector.h"
Mat CornerDetector::detectHarrist(Mat sourceImage, float alpha, int thres)
{
	Mat gray_img;
	Mat dst = sourceImage.clone();
	cvtColor(sourceImage, gray_img, COLOR_BGR2GRAY);
	GaussianBlur(gray_img, gray_img, Size(3, 3), 1.0, 1.0, BORDER_DEFAULT);
	vector<float> kX = { -1.0, 0.0, 1.0, -2.0, 0.0, 2.0, -1.0, 0.0, 1.0 };
	vector<float> kY = { -1.0, -2.0, -1.0, 0.0, 0.0, 0.0, 1.0, 2.0, 1.0 };

	// Find gradient X, gradient Y
	Mat gx, gy;
	int w = gray_img.cols;
	int h = gray_img.rows;
	_conv.SetKernel(kX, 3, 3);
	_conv.DoConvolution(gray_img, gx);
	_conv.SetKernel(kY, 3, 3);
	_conv.DoConvolution(gray_img, gy);

	Mat Ix2, Iy2, Ixy;
	pow(gx, 2.0, Ix2);
	pow(gy, 2.0, Iy2);
	multiply(gx, gy, Ixy);

	// Gaussian blur 
	Mat Ix2_blur, Iy2_blur, Ixy_blur;
	GaussianBlur(Ix2, Ix2_blur, Size(7, 7), 2.0, 0.0, BORDER_DEFAULT);
	GaussianBlur(Iy2, Iy2_blur, Size(7, 7), 0.0, 2.0, BORDER_DEFAULT);
	GaussianBlur(Ixy, Ixy_blur, Size(7, 7), 2.0, 2.0, BORDER_DEFAULT);

	// Compute R = det(M) − k(trace(M))2
	Mat Ix2Iy2, IxyIxy;
	multiply(Ix2_blur, Iy2_blur, Ix2Iy2);
	multiply(Ixy_blur, Ixy_blur, IxyIxy);

	Mat trace;
	pow((Ix2_blur + Iy2_blur), 2.0, trace);
	Mat R = (Ix2Iy2 - IxyIxy) - alpha * trace;

	// Compare with Thresholds
	Mat dst_norm, dst_norm_scaled;
	normalize(R, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled);
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			if ((int)dst_norm.at<float>(y, x) > thres) 
			{
				circle(dst, Point(x, y), 1, Scalar(0, 0, 255), 1, 8, 0);
			}
	return dst;
}
Mat CornerDetector::detectBlob(Mat sourceImage, int thres) 
{
	Mat gray_img;
	Mat dst = sourceImage.clone();;
	cvtColor(sourceImage, gray_img, COLOR_BGR2GRAY);
	GaussianBlur(gray_img, gray_img, Size(11, 11), 1.0, 1.0, BORDER_DEFAULT);
	int w = gray_img.cols;
	int h = gray_img.rows;

	// Laplace
	Laplacian(gray_img, gray_img, CV_8UC1, 3, 1, 0, BORDER_DEFAULT);

	// Compare with Thresholds
	Mat dst_norm;
	normalize(gray_img, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			if ((int)dst_norm.at<float>(y, x) > thres) 
			{
				circle(dst, Point(x, y), 1, Scalar(0, 0, 255), 1, 8, 0);
			}
	return dst;
}
Mat CornerDetector::detectBlob(Mat sourceImage, int thres, vector<KeyPoint>& points) {
	Mat gray_img;
	Mat dst = sourceImage.clone();
	cvtColor(sourceImage, gray_img, COLOR_BGR2GRAY);
	GaussianBlur(gray_img, gray_img, Size(5, 5), 1.0, 1.0, BORDER_DEFAULT);
	int w = gray_img.cols;
	int h = gray_img.rows;

	// Laplace
	Laplacian(gray_img, gray_img, CV_8UC1, 3, 1, 0, BORDER_DEFAULT);

	// Compare with Thresholds
	Mat dst_norm;
	normalize(gray_img, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	vector<Point2f> key;
	for (int y = 0; y < h; y++) 
		for (int x = 0; x < w; x++)
			if ((int)dst_norm.at<float>(y, x) > thres) 
			{
				key.push_back(Point2f(x * 1.f, y * 1.f));
			}
	for (int i = 0; i < key.size(); i++) 
	{
		points.push_back(KeyPoint(key[i], 1.f));
	}
	return dst;
}

Mat CornerDetector::detectDOG(Mat sourceImage, int thres) 
{
	Mat gray_img;
	Mat dst = sourceImage.clone();
	cvtColor(sourceImage, gray_img, COLOR_BGR2GRAY);
	int w = gray_img.cols;
	int h = gray_img.rows;

	// Calculate low_sigma Gaussian blur, high_sigma Gaussian blur and DoG
	Mat lsigma, hsigma;
	GaussianBlur(gray_img, lsigma, Size(5, 5), 1.0, 1.0, BORDER_DEFAULT);
	GaussianBlur(gray_img, hsigma, Size(7, 7), 1.0, 1.0, BORDER_DEFAULT);
	Mat DoG = lsigma - hsigma;

	// Compare with Thresholds
	Mat dst_norm;
	normalize(DoG, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			if ((int)dst_norm.at<float>(y, x) > thres) 
			{
				circle(dst, Point(x, y), 1, Scalar(0, 0, 255), 1, 8, 0);
			}
	return dst;
}
CornerDetector::CornerDetector(){};
CornerDetector::~CornerDetector(){};