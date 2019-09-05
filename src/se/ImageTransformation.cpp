#include "ImageTransformation.hpp"

using namespace se;

void ImageTransformation::negative(sf::Color &c)
{
	c.r = (c.r + 255) % 256;
	c.g = (c.g + 255) % 256;
	c.b = (c.b + 255) % 256;
}

bool ImageTransformation::isTransparent(const sf::Color &c)
{
	return c.a == 0;
}
