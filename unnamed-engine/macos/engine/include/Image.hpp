#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <math.h>
#include "Utils.hpp"

class Image final : public sf::Image
{
public:
	using sf::Image::Image;
	Image(const sf::Image& cp);
	Image(const sf::Texture& txtr);
	Image(const sf::Texture* txtr);
	void negative();
	void fade(int filterSize=3);
	void gravity();
	void light(const sf::Image& reference, const sf::Vector2f& pos, sf::Vector2f lightPos, const sf::Vector2f& scale, float angle, const sf::Vector2f& normPos);
};

#endif
