#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>

namespace se
{
	class Utilities final
	{
	public:
		static sf::RenderWindow *window;
		static bool appOpen;
		static sf::Vector2i getMousePosition();
		static bool isKeyPressed(sf::Keyboard::Key key);
		static bool isButtonPressed(sf::Mouse::Button button);
		static std::vector<std::string> split(std::string, char);
		static void removeChar(std::string&, char);
	};
	typedef Utilities util;
}

#endif
