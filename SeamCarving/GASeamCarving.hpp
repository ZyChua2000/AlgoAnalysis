
#include <DPSeamCarving.hpp>
#ifndef GASeamCarving_HPP
#define GASeamCarving_HPP


class GASeamCarving : public DPSeamCarving
{
public:

	void SeamCarving(cv::Mat& image, int newHeight, int newWidth) override;
};

#endif
