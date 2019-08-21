#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Updater.hpp"

namespace se
{
	class Application : public Updater
	{
	private:
		void initWindow(sf::VideoMode &vm, std::string &title);
		void initRandomSeed();
		void eventLoop();
	protected:
		sf::RenderWindow *window;
		double totalTime;
		double dt;
		sf::Clock dtClock;
		sf::Clock totalClock;
		virtual void update() abstract;
		virtual void render() abstract;
	public:
		Application(double width, double height, std::string &title);
		Application(std::string &title);
		void run();
		~Application();
		double getDt() const;
		double getTotalTime() const;
		sf::RenderWindow *getWindow() const;
		void setFrameRate(int fps);
		void fill(sf::Color color=sf::Color::Black);
		void display();
		virtual void closedEventHandler(sf::Event event);
		virtual void keyPressedEventHandler(sf::Event event);
		virtual void keyReleasedEventHandler(sf::Event event);
		virtual void resizedEventHandler(sf::Event event);
		virtual void lostFocusEventHandler(sf::Event event);
		virtual void gainedFocusEventHandler(sf::Event event);
		virtual void textEnteredEventHandler(sf::Event event);
		virtual void mouseWheelMovedEventHandler(sf::Event event);
		virtual void mouseWheelScrolledEventHandler(sf::Event event);
		virtual void mouseButtonPressedEventHandler(sf::Event event);
		virtual void mouseButtonReleasedEventHandler(sf::Event event);
		virtual void mouseMovedEventHandler(sf::Event event);
		virtual void mouseEnteredEventHandler(sf::Event event);
		virtual void mouseLeftEventHandler(sf::Event event);
		virtual void joystickButtonReleasedEventHandler(sf::Event event);
		virtual void joystickButtonPressedEventHandler(sf::Event event);
		virtual void joystickMovedEventHandler(sf::Event event);
		virtual void joystickConnectedEventHandler(sf::Event event);
		virtual void joystickDisconnectedEventHandler(sf::Event event);
		virtual void touchBeganEventHandler(sf::Event event);
		virtual void touchEndedEventHandler(sf::Event event);
		virtual void touchMovedEventHandler(sf::Event event);
		virtual void sensorChangedEventHandler(sf::Event event);
		virtual void countEventHandler(sf::Event event);
	};
}

#endif
