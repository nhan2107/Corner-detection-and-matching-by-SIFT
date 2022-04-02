#include <opencv2/opencv.hpp>
#include "CornerDetector.h";

class Matching 
{
public:
	void matchBySIFT(Mat img1, Mat img2, Mat& dst);
	Matching();
	~Matching();
private:
	CornerDetector _corner;
};
