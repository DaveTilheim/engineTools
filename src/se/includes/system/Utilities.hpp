#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <SFML/Graphics.hpp>
#include <cmath>
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
		static float getDistance(int x1, int y1, int x2, int y2);
	};
	typedef Utilities util;
}

#endif
