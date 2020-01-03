#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "DynamicVisual.hpp"
#include "Debug.hpp"
#include "EventHandler.hpp"
#include "GlobalInfo.hpp"

using namespace std;

class Application : public DynamicVisual, public EventHandler
{
private:
	double dt = 0;
	sf::Clock dtClock;
	sf::Color backgroundColor;
	unsigned long tick = 0;
	void closedEventHandler(const sf::Event& event) override;
protected:
	mutable sf::RenderWindow window;
	static int applicationCounter;
	virtual void update() override = 0;
	virtual void view(sf::RenderWindow& win) override = 0;
	virtual void close();
	void eventLoop();
public:
	Application(string title="Application");
	Application(int width, int height, string title="Application");
	virtual ~Application();
	virtual void load() = 0;
	void run();
	bool runNoWait();
	double getDt() const;
	unsigned long getTick() const;
	sf::RenderWindow& getWindow();
	const sf::Color& getBackgroundColor() const;
	sf::Vector2f getCenter() const;
	void setBackgroundColor(const sf::Color& color);
	bool isRunning() const;
	int getApplicationCounter();
	inline void fill() const;
	inline void fill(const sf::Color& c) const;
	inline void refresh() const;
};

inline void Application::fill() const
{
	window.clear(backgroundColor);
}

inline void Application::fill(const sf::Color& color) const
{
	window.clear(color);
}

inline void Application::refresh() const
{
	window.display();
}

#endif
