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
		switch(event.type)
		{
			case sf::Event::Closed:
				closedEventHandler(event);
				break;

			case sf::Event::KeyPressed:
				keyPressedEventHandler(event);
				break;

			case sf::Event::KeyReleased:
				keyReleasedEventHandler(event);
				break;

			case sf::Event::Resized:
				resizedEventHandler(event);
				break;

			case sf::Event::LostFocus:
				lostFocusEventHandler(event);
				break;

			case sf::Event::GainedFocus:
				gainedFocusEventHandler(event);
				break;

			case sf::Event::TextEntered:
				textEnteredEventHandler(event);
				break;

			case sf::Event::MouseWheelMoved:
				mouseWheelMovedEventHandler(event);
				break;

			case sf::Event:: MouseWheelScrolled:
				mouseWheelScrolledEventHandler(event);
				break;

			case sf::Event::MouseButtonPressed:
				mouseButtonPressedEventHandler(event);
				break;

			case sf::Event::MouseButtonReleased:
				mouseButtonReleasedEventHandler(event);
				break;

			case sf::Event::MouseMoved:
				mouseMovedEventHandler(event);
				break;

			case sf::Event::MouseEntered:
				mouseEnteredEventHandler(event);
				break;

			case sf::Event::MouseLeft:
				mouseLeftEventHandler(event);
				break;

			case sf::Event::JoystickButtonReleased:
				joystickButtonReleasedEventHandler(event);
				break;

			case sf::Event::JoystickButtonPressed:
				joystickButtonPressedEventHandler(event);
				break;

			case sf::Event::JoystickMoved:
				joystickMovedEventHandler(event);
				break;

			case sf::Event::JoystickConnected:
				joystickConnectedEventHandler(event);
				break;

			case sf::Event::JoystickDisconnected:
				joystickDisconnectedEventHandler(event);
				break;

			case sf::Event::TouchBegan:
				touchBeganEventHandler(event);
				break;

			case sf::Event::TouchEnded:
				touchEndedEventHandler(event);
				break;

			case sf::Event::TouchMoved:
				touchMovedEventHandler(event);
				break;

			case sf::Event::SensorChanged:
				sensorChangedEventHandler(event);
				break;

			case sf::Event::Count:
				countEventHandler(event);
				break;
		}
	}
}

void Application::closedEventHandler(sf::Event event)
{
	this->window->close();
}

void Application::keyPressedEventHandler(sf::Event event)
{

}

void Application::keyReleasedEventHandler(sf::Event event)
{

}

void Application::resizedEventHandler(sf::Event event)
{

}

void Application::lostFocusEventHandler(sf::Event event)
{

}

void Application::gainedFocusEventHandler(sf::Event event)
{

}

void Application::textEnteredEventHandler(sf::Event event)
{

}

void Application::mouseWheelMovedEventHandler(sf::Event event)
{

}

void Application::mouseWheelScrolledEventHandler(sf::Event event)
{

}

void Application::mouseButtonPressedEventHandler(sf::Event event)
{

}

void Application::mouseButtonReleasedEventHandler(sf::Event event)
{

}

void Application::mouseMovedEventHandler(sf::Event event)
{

}

void Application::mouseEnteredEventHandler(sf::Event event)
{

}

void Application::mouseLeftEventHandler(sf::Event event)
{

}

void Application::joystickButtonReleasedEventHandler(sf::Event event)
{

}

void Application::joystickButtonPressedEventHandler(sf::Event event)
{

}

void Application::joystickMovedEventHandler(sf::Event event)
{

}

void Application::joystickConnectedEventHandler(sf::Event event)
{

}

void Application::joystickDisconnectedEventHandler(sf::Event event)
{

}

void Application::touchBeganEventHandler(sf::Event event)
{

}

void Application::touchEndedEventHandler(sf::Event event)
{

}

void Application::touchMovedEventHandler(sf::Event event)
{

}

void Application::sensorChangedEventHandler(sf::Event event)
{

}

void Application::countEventHandler(sf::Event event)
{

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
	while(this->window->isOpen())
	{
		this->dt = this->dtClock.restart().asSeconds();
		this->totalTime = this->totalClock.getElapsedTime().asSeconds();
		this->eventLoop();
		this->update();
		this->render();
	}
}
