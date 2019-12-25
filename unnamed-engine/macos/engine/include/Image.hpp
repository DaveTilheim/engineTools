#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

class Image final : public sf::Image
{
public:
	using sf::Image::Image;
	Image(const sf::Image& cp);
	Image(const sf::Texture& txtr);
	Image(const sf::Texture* txtr);
	void negative();
};

#endif
