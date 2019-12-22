#include <SmartApplication.hpp>
#include <iostream>
#include <DynamicVisual.hpp>
#include <SystemEntity.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <Entity.hpp>

using namespace std;


class TEntity : public Entity<sf::RectangleShape>
{
protected:
	void update() override
	{
		movePhySec();
	}
public:
	using Entity<sf::RectangleShape>::Entity;
	~TEntity()
	{
		cout << "Entity deleted" << endl;
	}
};

class CEntity : public Entity<sf::CircleShape>
{
protected:
	void update() override
	{
		//setRotation(getRotation()+0.1);
	}
public:
	using Entity<sf::CircleShape>::Entity;
	~CEntity()
	{
		cout << "Entity deleted" << endl;
	}
};


class App : public SmartApplication
{
public:
	TEntity *e1;
	void load() override
	{
		setBackgroundColor(sf::Color(0, 0, 255));
		e1 = new TEntity();
		e1->setSize(sf::Vector2f(50, 50));
		e1->setFillColor(sf::Color::Red);
		e1->setSideOrigin();
		e1->setPosition(0, 400);
		e1->setSpeed(200, 0);
		//e1->setAcceleration(200, 0);
		
		app << e1;
	}

	void keyPressedEventHandler(const sf::Event& e) override
	{
		cout << "push" << endl;
	}
};

class A : public Application
{
private:
	sf::CircleShape c1;
	sf::CircleShape c2;
public:
	void load() override
	{
		c1 = sf::CircleShape(30);
		c2 = sf::CircleShape(20);
		c2.setPosition(680, 380);
		c1.setFillColor(sf::Color::Red);
		c2.setFillColor(sf::Color::Yellow);
	}

	void update() override
	{
		auto mp = sf::Mouse::getPosition(getWindow());
		c1.setPosition(mp.x - 30, mp.y - 30);
		auto p1 = c1.getPosition() + sf::Vector2f(30,30);
		auto p2 = c2.getPosition() + sf::Vector2f(20,20);
		if(sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y)) < 30 + 20)
		{
			c1.setFillColor(sf::Color::Green);
		}
		else
		{
			c1.setFillColor(sf::Color::Red);
		}
	}

	void view(sf::RenderWindow& win) const override
	{
		win.clear(sf::Color::White);
		win.draw(c1);
		win.draw(c2);
		win.display();
	}
};



int main(int argc, char const *argv[])
{
	App app;
	app.run();

	
	return 0;
}
