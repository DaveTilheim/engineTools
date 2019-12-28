#include <SmartApplication.hpp>
#include <iostream>
#include <DynamicVisual.hpp>
#include <SystemEntity.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <RectEntity.hpp>
#include <Image.hpp>
#include <CircleEntity.hpp>
#include <ConvexEntity.hpp>
#include <SpriteEntity.hpp>
#include <LambdaDynamic.hpp>
#include <Timer.hpp>

using namespace std;


class App : public SmartApplication
{
public:
	using SmartApplication::SmartApplication;
	
	LConvexEntity *c;
	Light light;
	virtual void load() override
	{
		setBackgroundColor(sf::Color(100, 100, 100));
		
		app << "mini-mush.png";
		//light.setLux(2, 0, 0.5);
		c = new LConvexEntity();
		
		c->setPosition(getCenter());
		duplicateTexture("mini-mush.png", c);
		c->setPoints(3, -100, 100, 100, 200, 200, -100);
		c->setSideOrigin(BOTTOM_RIGHT);
		//c->setScale(2, 0.45);
		c->setUpdate([this](ConvexEntity& e)
		{
			Image i = e.getTexture();
			auto s = e.getScale();
			i.light(app["mini-mush.png"]->copyToImage(), e, getMpf(), light);
			e.updateTexture(i);
			//e.scale(1.001, 1.001);
			e.rotate(0.5);
			cout << e.getTLPosition() << " " << e.getSidePosition(TOP_LEFT) << endl;
		});


		app << c;
		
	}

	void keyPressedEventHandler(const sf::Event& event) override
	{
		c->setDynamicState(not c->getDynamicState());
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
