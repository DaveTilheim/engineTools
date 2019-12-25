#include "Image.hpp"

Image::Image(const sf::Image& cp) : sf::Image(cp)
{

}

Image::Image(const sf::Texture& txtr) : sf::Image(txtr.copyToImage())
{

}

Image::Image(const sf::Texture* txtr) : sf::Image(txtr->copyToImage())
{

}

void Image::negative()
{
	auto s = getSize();
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = getPixel(x, y);
			px.r = 255 - px.r;
			px.g = 255 - px.g;
			px.b = 255 - px.b;
			setPixel(x, y, px);
		}
	}
}
