#ifndef IMAGE_TRANSFORMATION_HPP
#define IMAGE_TRANSFORMATION_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>

namespace se
{
	class ImageTransformation final
	{
	public:
		static void negative(sf::Color &c);
		static void reverse(sf::Image &img);
		template <const unsigned char r=0, const unsigned char g=0, const unsigned char b=0>
		static void border(sf::Image &img);
		template <const unsigned N=2>
		static void degrading(sf::Color &c);
		static bool isTransparent(const sf::Color &c);
	};

	template <const unsigned N>
	void ImageTransformation::degrading(sf::Color &c)
	{
		if(rand()%N == 0)
		{
			c.a = 0;
		}
	}

	template <const unsigned char r, const unsigned char g, const unsigned char b>
	void ImageTransformation::border(sf::Image &img)
	{
		auto size = img.getSize();
		auto cpImg = img;
		for(int i = 0; i < size.x; i++)
		{
			for(int j = 0; j < size.y; j++)
			{
				auto px = cpImg.getPixel(i, j);
				if(px.a == 0)
				{
					if(i-1 >= 0 and cpImg.getPixel(i-1, j).a)
					{
						img.setPixel(i, j, sf::Color(r, g, b));
					}
					else if(i+1 < size.x and cpImg.getPixel(i+1, j).a)
					{
						img.setPixel(i, j, sf::Color(r, g, b));
					}
					else if(j-1 >= 0 and cpImg.getPixel(i, j-1).a)
					{
						img.setPixel(i, j, sf::Color(r, g, b));
					}
					else if(j+1 < size.y and cpImg.getPixel(i, j+1).a)
					{
						img.setPixel(i, j, sf::Color(r, g, b));
					}
				}
				else
				{
					if(i-1 < 0 or i+1 >= size.x or j-1 < 0 or j+1 >= size.y)
					{
						img.setPixel(i, j, sf::Color(r, g, b));
					}
				}
			}
		}
	}
}

#endif
