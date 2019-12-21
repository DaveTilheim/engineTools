#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <iostream>
#include <string>
#include "DynamicVisual.hpp"
#include "EventHandler.hpp"

using namespace std;

class Application : public DynamicVisual, public EventHandler
{
private:
	mutable sf::RenderWindow window;
	double dt = 0;
	sf::Clock dtClock;
	sf::Color backgroundColor;
	unsigned long tick = 0;
	void eventLoop();
	void closedEventHandler(const sf::Event& event) override;
protected:
	virtual void update() override = 0;
	virtual void draw(sf::RenderWindow& win) const override = 0;
	virtual void load() = 0;
	virtual void close();
public:
	Application(string title="Application");
	Application(int width, int height, string title="Application");
	virtual ~Application();
	void run();
	double getDt() const;
	unsigned long getTick() const;
	sf::RenderWindow& getWindow();
	const sf::Color& getBackgroundColor() const;
	void setBackgroundColor(const sf::Color& color);
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
