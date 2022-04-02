#include "Matching.h"
void Matching::matchBySIFT(Mat img1, Mat img2, Mat& dst) 
{
	Ptr<SiftFeatureDetector> detect = SiftFeatureDetector::create();
	vector<KeyPoint> key1, key2;
	Mat descript1, descript2;
	_corner.detectBlob(img1, 30, key1);
	_corner.detectBlob(img2, 30, key2);
	detect->compute(img1, key1, descript1);
	detect->compute(img2, key2, descript2);

	//Step 2: Matching descriptor vectors with a FLANN based matcher
	// Since SURF is a floating-point descriptor NORM_L2 is used
	Ptr<DescriptorMatcher> match = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
	vector<vector<DMatch>> knn_match;
	match->knnMatch(descript1, descript2, knn_match, 2);

	//Filter matches using the Lowe's ratio test
	const float ratio = 0.5f;
	vector<DMatch> good_match;
	for (size_t i = 0; i < knn_match.size(); i++)
	{
		if (knn_match[i][0].distance < ratio * knn_match[i][1].distance)
		{
			good_match.push_back(knn_match[i][0]);
		}
	}

	//Draw matches
	Mat match_img;
	drawMatches(img1, key1, img2, key2, good_match, match_img, Scalar::all(-1),
		Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//Show detected matches
	namedWindow("SIFT Matches", WINDOW_FREERATIO);
	imshow("SIFT Matches", match_img);
	waitKey(0);
	dst = match_img;
}
Matching::Matching(){};
Matching::~Matching(){};