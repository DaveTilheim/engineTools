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
