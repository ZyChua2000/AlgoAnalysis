
#ifndef DPSeamCarving_HPP
#define DPSeamCarving_HPP
#include <VirtualSeamCarving.hpp>

class DPSeamCarving : public VirtualSeamCarving
{
public:

	void SeamCarving(cv::Mat& image, int newHeight, int newWidth) override;
};


#endif
