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

std::vector<std::string> Utilities::split(std::string txt, char splitc)
{
	std::stringstream stream(txt);
	std::string token;
	std::vector<std::string> out;
	while(std::getline(stream, token, splitc))
	{
		out.push_back(token);
	}
	return out;
}

void Utilities::removeChar(std::string& s, char c)
{
	int size = s.size();
	for(int i = 0; i < size; i++)
	{
		if(s[i] == c)
		{
			s.erase(s.begin() + i);
			size--;
			i--;
		}
	}
}
