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
		
	}
public:
	using Entity<sf::RectangleShape>::Entity;
	~TEntity()
	{
	
	}
};

class CEntity : public Entity<sf::CircleShape>
{
protected:
	void update() override
	{
		getWindow().setPosition(getMpD());
	}
public:
	using Entity<sf::CircleShape>::Entity;
	~CEntity()
	{
	
	}
};

class App : public SmartApplication
{
public:
	using SmartApplication::SmartApplication;
	TEntity *e1;
	//A subApp = A(300, 300, "sub app");
	//App2 *sa;
	void load() override
	{
		setBackgroundColor(sf::Color(0, 0, 255));
		e1 = new TEntity();
		e1->setSize(sf::Vector2f(50, 50));
		e1->setFillColor(sf::Color::Red);
		e1->setSideOrigin();
		e1->setPosition(150, 150);
		
		
		app << e1;
	}

	void keyPressedEventHandler(const sf::Event& e) override
	{
		cout << "push" << endl;
	}
};





int main(int argc, char const *argv[])
{
	App app(300, 300);
	app.run();

	return 0;
}
