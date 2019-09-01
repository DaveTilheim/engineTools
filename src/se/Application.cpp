#include "Application.hpp"
#include <string>
#include <ctime>
#include <cstdlib>

using namespace se;


Application::Application(double width, double height, std::string &title)
{
	sf::VideoMode vm(width, height);
	this->initWindow(vm, title);
	this->initRandomSeed();
}

Application::Application(std::string &title)
{
	sf::VideoMode vm(sf::VideoMode::getDesktopMode());
	this->initWindow(vm, title);
	this->initRandomSeed();
}

Application::~Application()
{
	delete this->window;
	for(std::map<std::string, void *>::iterator it = this->globals.begin(); it != this->globals.end(); it++)
	{
		std::cout << "global freed" << std::endl;
		free(this->globals[it->first]); // can not delete void * expression
	}
	std::cout << "Application closed" << std::endl;
}

void Application::initRandomSeed()
{
	srand(time(NULL));
}

void Application::initWindow(sf::VideoMode &vm, std::string &title)
{
	this->window = new sf::RenderWindow(vm, title);
}

void Application::eventLoop()
{
	for(sf::Event event; this->window->pollEvent(event); )
	{
		this->handleEvent(event);
	}
}

void Application::closedEventHandler(sf::Event& event)
{
	this->window->close();
}


double Application::getDt() const
{
	return this->dt;
}

double Application::getTotalTime() const
{
	return this->totalTime;
}

sf::RenderWindow *Application::getWindow() const
{
	return this->window;
}

void Application::setFrameRate(int fps)
{
	this->window->setFramerateLimit(fps);
}

void Application::fill(sf::Color color)
{
	this->window->clear(color);
}

void Application::display()
{
	this->window->display();
}

void Application::run()
{
	this->load();
	while(this->window->isOpen())
	{
		this->dt = this->dtClock.restart().asSeconds();
		this->totalTime = this->totalClock.getElapsedTime().asSeconds();
		this->eventLoop();
		this->update();
		this->render();
	}
}

void Application::global(std::string name, void *data)
{
	if(data)
	{
		this->globals[name] = data;
	}
	else
	{
		free(this->globals[name]);
		this->globals.erase(name);
	}
}

void *Application::operator()(std::string name)
{
	return this->globals[name];
}

