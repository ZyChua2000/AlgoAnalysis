
#ifndef VirtualSeamCarving_HPP
#define VirtualSeamCarving_HPP
#include <opencv2/opencv.hpp>
class VirtualSeamCarving
{
public:
	virtual ~VirtualSeamCarving() = default;
	virtual void SeamCarving(cv::Mat& image, int newHeight, int newWidth) = 0;
};


#endif
