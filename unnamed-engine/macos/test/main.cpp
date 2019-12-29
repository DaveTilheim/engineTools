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
	
	LSpriteEntity *c;


	Light light;
	virtual void load() override
	{
		setBackgroundColor(sf::Color(100, 100, 100));
		getWindow().setFramerateLimit(0);
		app << "mini-mush.png" << "rainbow.jpg" << "fonts/Symtext.ttf" << "filter.png" << "magic.jpg" << "fonts/prompt.ttf" << "txtr.jpg";
		
		c = new LSpriteEntity();
		
		c->setPosition(getCenter());
		duplicateTexture("mini-mush.png", c);
		Image i(c->getTexture());

		//i << app["txtr.jpg"] << app["txtr.jpg"] << app["rainbow.jpg"] << app["mini-mush.png"];
		i = (i + 50 - ~Image(app["txtr.jpg"]) & i & i) ;
		c->updateTexture(i);
		c->setSideOrigin();
		c->setUpdate([this](SpriteEntity& e)
		{
			Image i(e.getTexture());

			//i.gravity();
			
			e.updateTexture(i);
		});

		app << c;
		
	}

	void keyPressedEventHandler(const sf::Event& event) override
	{
		c->setDynamicState(not c->getDynamicState());
	}

	void mouseButtonPressedEventHandler(const sf::Event& event) override
	{
		Image i(c->getTexture());

		i.luminus(100);
		
		c->updateTexture(i);
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
