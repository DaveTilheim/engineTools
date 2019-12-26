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
#include <Timer.hpp>

using namespace std;


class App : public SmartApplication
{
public:
	using SmartApplication::SmartApplication;
	
	CER_Timer *timer;
	LCircleEntity *c;

	virtual void load() override
	{
		c = new LCircleEntity(getCenter(), 50, MIDDLE_CENTER);
		timer = new CER_Timer(3e3,
		[this]()
		{
			cout << *timer << endl;
		},
		[this]()
		{
			c->setFillColor(sf::Color(rand()%256, rand()%256, rand()%256));
		});
		app << c << timer;
	}

	void keyPressedEventHandler(const sf::Event& event) override
	{

	}

	void mouseButtonPressedEventHandler(const sf::Event& event) override
	{
		
	}

	~App()
	{
		
	}
};


int main(int argc, char const *argv[])
{
	App app;
	app.run();

	return 0;
}
