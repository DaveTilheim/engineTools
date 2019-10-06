#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Updater.hpp"
#include "EventHandler.hpp"
#include "Utilities.hpp"
#include "Thread.hpp"
#include <string>
#include <ctime>
#include <cstdlib>


namespace se
{
	class Application : public Updater, public EventHandler
	{
	private:
		void initWindow(sf::VideoMode &vm, std::string &title);
		void initRandomSeed();
		void eventLoop();
		unsigned frameRate = 60;
	protected:
		sf::RenderWindow *window;
		double dt;
		sf::Clock dtClock;
		sf::Clock totalClock;
		unsigned long tick = 0;
		std::map<std::string, void *> globals;
		virtual void load() abstract;
		virtual void update() override abstract;
		virtual void render() override abstract;
		virtual void close();
		virtual void closedEventHandler(sf::Event& event) override final;
	public:
		Application(double width, double height, std::string title);
		Application(std::string title);
		virtual ~Application();
		void run();
		double getDt() const;
		double getTotalTime() const;
		unsigned getFrameRate() const;
		sf::RenderWindow *getWindow() const;
		void setFrameRate(int fps);
		void fill(sf::Color color=sf::Color::Black);
		void display();
		void global(std::string name, void *data);
		template <typename T>
		void global(std::string name, T data);
		template <typename T>
		T *global(std::string name);
		void *operator()(std::string name);
	};
	typedef Application A;

	template <typename T> void Application::global(std::string name, T data)
	{
		this->globals[name] = new T(data);
	}

	template <typename T> T *Application::global(std::string name)
	{
		void *data = this->globals[name];
		return data ? reinterpret_cast<T *>(this->globals[name]) : nullptr;
	}
}

#endif
