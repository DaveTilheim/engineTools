#include <SFML/Graphics.hpp>

namespace se
{
	class Utilities final
	{
	public:
		static sf::RenderWindow *window;
		static sf::Vector2i getMousePosition();
		static bool isKeyPressed(sf::Keyboard::Key key);
		static bool isButtonPressed(sf::Mouse::Button button);
	};
	typedef Utilities util;
}
