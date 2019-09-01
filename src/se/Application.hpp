#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <map>
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
		std::map<std::string, void *> globals;
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
		void global(std::string name, void *data);
		template <typename T>
		T *global(std::string name);
		void *operator()(std::string name);
	};
	typedef Application A;

	template <typename T>
	T *Application::global(std::string name)
	{
		void *data = this->globals[name];
		return data ? reinterpret_cast<T *>(this->globals[name]) : nullptr;
	}
}

#endif
