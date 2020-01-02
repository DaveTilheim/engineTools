#ifndef GLOBALINFO_HPP
#define GLOBALINFO_HPP
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <map>

class Application;
class SmartApplication;


struct GlobalInfo
{
	static Application *offset;
	static std::map<Application *, GlobalInfo> globalInfo;
	Application *root = nullptr;
	double *dt = nullptr;
	sf::RenderWindow *window = nullptr;
	GlobalInfo(){}
	GlobalInfo(Application *root, double *dt, sf::RenderWindow *window) : root(root), dt(dt), window(window)
	{
		GlobalInfo::globalInfo[root] = *this;
	}
};

inline double getDt()
{
	return *GlobalInfo::globalInfo[GlobalInfo::offset].dt;
}

inline Application *getRoot()
{
	return GlobalInfo::globalInfo[GlobalInfo::offset].root;
}

inline SmartApplication *getSRoot()
{
	return (SmartApplication *)GlobalInfo::globalInfo[GlobalInfo::offset].root;
}

inline sf::RenderWindow& getWindow()
{
	return *GlobalInfo::globalInfo[GlobalInfo::offset].window;
}

inline sf::Vector2i getMp()
{
	return sf::Mouse::getPosition(getWindow());
}

inline sf::Vector2f getMpf()
{
	return static_cast<sf::Vector2f>(sf::Mouse::getPosition(getWindow()));
}

inline sf::Vector2i getMpD()
{
	return sf::Mouse::getPosition();
}

inline bool pressed(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}

inline bool pressed(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

#endif
