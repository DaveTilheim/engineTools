#include "Application.hpp"


using namespace se;


Application::Application(double width, double height, std::string title)
{
	trace("Application creation");
	sf::VideoMode vm(width, height);
	this->initWindow(vm, title);
	this->initRandomSeed();
	this->setFrameRate(60);
}

Application::Application(std::string title)
{
	trace("Application creation");
	sf::VideoMode vm(sf::VideoMode::getDesktopMode());
	this->initWindow(vm, title);
	this->initRandomSeed();
	this->setFrameRate(0);
}

Application::~Application()
{
	delete this->window;
	for(auto it = this->globals.begin(); it != this->globals.end(); it++)
	{
		std::cout << "global freed" << std::endl;
		free(this->globals[it->first]);
	}
	trace("Application destruction");
}

void Application::initRandomSeed()
{
	srand(time(NULL));
}

void Application::initWindow(sf::VideoMode &vm, std::string &title)
{
	this->window = new sf::RenderWindow(vm, title);
	Utilities::window = this->window;
	this->window->setVerticalSyncEnabled(true);
}

void Application::eventLoop()
{
	for(sf::Event event; this->window->pollEvent(event);)
	{
		this->handleEvent(event);
	}
}

void Application::close()
{
	//to override
}

void Application::closedEventHandler(const sf::Event& event)
{
	util::appOpen = false;
	this->close();
	Thread::flush();
	this->window->close();
}


double Application::getDt() const
{
	return this->dt;
}

double Application::getTotalTime() const
{
	return this->totalClock.getElapsedTime().asSeconds();;
}

sf::RenderWindow *Application::getWindow() const
{
	return this->window;
}

void Application::setFrameRate(int fps)
{
	this->window->setFramerateLimit(fps);
}

unsigned Application::getFrameRate() const
{
	return static_cast<unsigned>(1.0 / this->dt);
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
		this->eventLoop();
		if(this->getUpdateState())
		{
			this->update();
		}
		if(this->getRenderState())
		{
			this->render();
		}
		this->tick++;
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
	return this->globals.find(name) != this->globals.end() ? this->globals[name] : nullptr;
}

