#include <opencv2/opencv.hpp>

int main(int argc, char const *argv[])
{
	auto p = cv::imread(argv[1],0);
	cv::imshow("ciao",p);
	cv::imshow("!ciao2",p);
	cv::waitKey(0);
	return 0;
}