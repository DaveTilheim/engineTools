#include "Utilities.hpp"

using namespace se;

sf::RenderWindow *Utilities::window = nullptr;
bool Utilities::appOpen = true;

sf::Vector2i Utilities::getMousePosition()
{
	return sf::Mouse::getPosition(*Utilities::window);
}

bool Utilities::isKeyPressed(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

bool Utilities::isButtonPressed(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}