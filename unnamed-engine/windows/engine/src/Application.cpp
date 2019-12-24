#include "Application.hpp"


Application::Application(string title) : window(sf::VideoMode::getDesktopMode(), title)
{
	window.setFramerateLimit(0);
	GlobalInfo(this, &dt, &window);
	trace("Application creation");
}

Application::Application(int width, int height, string title) : window(sf::VideoMode(width, height), title)
{
	window.setFramerateLimit(0);
	GlobalInfo(this, &dt, &window);
	trace("Application creation");
}

Application::~Application()
{
	trace("Application destruction");
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
	load();
	GlobalInfo::offset = this;
	while(window.isOpen())
	{
		dt = dtClock.restart().asSeconds();
		if(getDynamicState()) eventLoop();
		_update();
		_view(window);
		tick++;
	}
}

bool Application::runNoWait()
{
	if(window.isOpen())
	{
		dt = dtClock.restart().asSeconds();
		if(getDynamicState()) eventLoop();
		_update();
		_view(window);
		tick++;
		return 1;
	}
	return 0;
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

bool Application::isRunning() const
{
	return window.isOpen();
}

