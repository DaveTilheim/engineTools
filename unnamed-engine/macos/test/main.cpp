#include <SmartApplication.hpp>
#include <iostream>
#include <DynamicVisual.hpp>
#include <SystemEntity.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <RectEntity.hpp>
#include <Image.hpp>
#include <CircleEntity.hpp>
#include <LambdaDynamic.hpp>

using namespace std;


class TEntity : public RectEntity
{

protected:
	void update() override
	{
		
	}
public:
	using RectEntity::RectEntity;
	~TEntity()
	{
	
	}
};

class CEntity : public CircleEntity
{

protected:
	void update() override
	{
		
	}
public:
	using CircleEntity::CircleEntity;
	~CEntity()
	{
	
	}
};
class CEntity1 : public CircleEntity
{
	CEntity *target;
protected:
	void update() override
	{
		setPosition(getMpf());
		if(collision(*target))
		{
			setFillColor(sf::Color::Red);
		}
		else
		{
			setFillColor(sf::Color::Green);
		}
	}
public:
	CEntity1(CEntity *t) : CircleEntity()
	{
		target = t;
	}
	~CEntity1()
	{
	
	}
};


class App : public SmartApplication
{
public:
	using SmartApplication::SmartApplication;
	CEntity *e1;
	CEntity1 *e2;

	virtual void load() override
	{
		app << "mush.png";
		auto e = new LRectEntity(getCenter(), RectEntity::DEFAULT_SIZE, MIDDLE_CENTER);
		e->setUpdate([e](RectEntity& r)
		{
			e->moveToward(getMpf(), sf::Vector2f(300, 300));
		});
		app << e;
	}

	void keyPressedEventHandler(const sf::Event& e) override
	{
		cout << "push" << endl;
	}

	void mouseButtonPressedEventHandler(const sf::Event& event) override
	{
		
	}
};


int main(int argc, char const *argv[])
{
	App app;
	app.run();

	return 0;
}
