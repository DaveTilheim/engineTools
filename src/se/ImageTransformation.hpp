#ifndef __IMAGE_TRANSFORMATION_HPP__
#define __IMAGE_TRANSFORMATION_HPP__

#include <SFML/Graphics.hpp>
#include <cstdlib>

namespace se
{
	class ImageTransformation final
	{
	public:
		static void negative(sf::Color &c);
		template <const unsigned N=2> static void degrading(sf::Color &c);
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
}

#endif
