#include <SmartApplication.hpp>
#include <iostream>
#include <DynamicVisual.hpp>
#include <SystemEntity.hpp>

using namespace std;


class Entity : public SystemEntity
{
protected:
	void update() override
	{

	}

	void draw(sf::RenderWindow& win) const override
	{

	}
public:
	using SystemEntity::SystemEntity;
	~Entity()
	{
		cout << "Entity deleted" << endl;
	}
};


class App : public SmartApplication
{
public:
	Entity e1;
	Entity e2;
	void load() override
	{
		setBackgroundColor(sf::Color(0, 0, 255));
		e2 = e1;
		cout << e2 << endl;
		app << e2 << e1 ;

	}

	void keyPressedEventHandler(const sf::Event& e) override
	{
		cout << "push" << endl;
	}
};



int main(int argc, char const *argv[])
{
	App app;
	app.run();

	
	return 0;
}
