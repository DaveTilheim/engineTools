#include <graphics/ImageTransformation.hpp>

using namespace se;

void ImageTransformation::negative(sf::Color &c)
{
	c.r = (c.r + 255) % 256;
	c.g = (c.g + 255) % 256;
	c.b = (c.b + 255) % 256;
}

void ImageTransformation::reverse(sf::Image &img)
{
	sf::Vector2u size = img.getSize();
	for(int i = 0; i < size.x/2; i++)
	{
		for(int j = 0; j < size.y/2; j++)
		{
			sf::Color c(img.getPixel(i, j));
			img.setPixel(i, j, img.getPixel(size.x-1-i, size.y-1-j));
			img.setPixel(size.x-1-i, size.y-1-j, c);
		}
	}
}

bool ImageTransformation::isTransparent(const sf::Color &c)
{
	return c.a == 0;
}
