#include "Utilities.hpp"

using namespace se;

sf::RenderWindow *Utilities::window = nullptr;

sf::Vector2i Utilities::getMousePosition()
{
	return sf::Mouse::getPosition(*Utilities::window);
}

bool Utilities::isKeyPressed(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

bool isButtonPressed(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}
