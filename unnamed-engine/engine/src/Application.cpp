#include "Application.hpp"


Application::Application(string title) : window(sf::VideoMode::getDesktopMode(), title)
{
	window.setFramerateLimit(0);
}

Application::Application(int width, int height, string title) : window(sf::VideoMode(width, height), title)
{
	window.setFramerateLimit(0);
}

Application::~Application()
{
	window.setFramerateLimit(0);
}

void Application::eventLoop()
{
	sf::Event event;
	while(window.pollEvent(event))
	{
		handleEvent(event);
	}
}

void Application::run()
{
	setGlobalDeltaTime(&dt);
	load();
	while(window.isOpen())
	{
		dt = dtClock.restart().asSeconds();
		if(getDynamicState()) eventLoop();
		_update();
		_view(window);
		tick++;
	}
}

double Application::getDt() const
{
	return dt;
}

unsigned long Application::getTick() const
{
	return tick;
}

void Application::close()
{

}

void Application::closedEventHandler(const sf::Event& event) 
{
	close();
	window.close();
}

sf::RenderWindow& Application::getWindow()
{
	return window;
}

const sf::Color& Application::getBackgroundColor() const
{
	return backgroundColor;
}

void Application::setBackgroundColor(const sf::Color& color)
{
	backgroundColor = color;
}

