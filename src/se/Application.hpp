#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Updater.hpp"
#include "EventHandler.hpp"

namespace se
{
	class Application : public Updater, public EventHandler
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
		virtual void load() abstract;
		virtual void update() abstract;
		virtual void render() abstract;
		virtual void closedEventHandler(sf::Event& event);
	public:
		Application(double width, double height, std::string &title);
		Application(std::string &title);
		~Application();
		void run();
		double getDt() const;
		double getTotalTime() const;
		sf::RenderWindow *getWindow() const;
		void setFrameRate(int fps);
		void fill(sf::Color color=sf::Color::Black);
		void display();
	};
}

#endif
