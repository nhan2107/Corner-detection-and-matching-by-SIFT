#define _CRT_SECURE_NO_WARNINGS
#include "Matching.h"
int main(int argc, char* argv[])
{
	if ((argc < 4)||(strcmp(argv[0],"19127230_Lab03.exe") != 0))
	{
		cout << "Wrong arguments";
		return 0;
	}
	char* c = argv[2];
	Mat Des_img;
	CornerDetector corner;
	if (strcmp(c, "1") == 0)
	{
		int thre = atoi(argv[3]);
		char* input = argv[1];
		Mat img = imread(input, IMREAD_COLOR);
		if (img.empty())
		{
			cout << "Could not find the image";
			return 1;
		}
		Des_img = corner.detectHarrist(img, 1, thre);
		imshow("image", Des_img);
		waitKey(0);
		return 0;
	}
	if (strcmp(c, "2") == 0) 
	{
		int thre = atoi(argv[3]);
		char* input = argv[1];
		Mat img = imread(input, IMREAD_COLOR);
		if (img.empty())
		{
			cout << "Could not find the image";
			return 1;
		}
		Des_img = corner.detectBlob(img, thre);
		imshow("image", Des_img);
		waitKey(0);
		return 0;
	}
	if (strcmp(c, "3") == 0) 
	{
		int thre = atoi(argv[3]);
		char* input = argv[1];
		Mat img = imread(input, IMREAD_COLOR);
		if (img.empty())
		{
			cout << "Could not find the image";
			return 1;
		}
		Des_img = corner.detectDOG(img, thre);
		imshow("image", Des_img);
		waitKey(0);
		return 0;
	}
	else 
	{
		char* c = argv[3];
		if (strcmp(c, "4") == 0)
		{
			char* input1 = argv[1];
			char* input2 = argv[2];		
			Mat img1 = imread(input1, IMREAD_COLOR);
			Mat img2 = imread(input2, IMREAD_COLOR);
			if (img1.empty())
			{
				cout << "Could not find the image 1";
				return 1;
			}
			if (img2.empty())
			{
				cout << "Could not find the image 2";
				return 1;
			}
			Matching match;
			match.matchBySIFT(img1, img2, Des_img);
			waitKey(0);
			return 0;
		}
		else
		{
			cout << "Wrong arguments";
			return 1;
		}
	}
	cout << "Not found any commands!";
	waitKey(0);
	return 0;
}