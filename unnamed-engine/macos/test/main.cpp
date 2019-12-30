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
	
	LRectEntity *c;


	Light light;
	virtual void load() override
	{
		setBackgroundColor(sf::Color(100, 100, 100));
		getWindow().setFramerateLimit(0);
		app << "mush.png" << "rainbow.jpg" << "fonts/Symtext.ttf" << "filter.png" << "magic.jpg" << "fonts/prompt.ttf" << "txtr.jpg";
		app << "test.jpg" << "dark-mush.png" << "animated.png" << "sprite.png";
		c = new LRectEntity();
		//faire une méthode qui découpe une partie des sprites d'un planche
		duplicateTexture("sprite.png", c);
		

		c->setAnimationOptions(0.20, 24, 0);
		c->setSpriteSize(8, 3);
		c->updateSprite(c->getBeginSprite());


		c->setPosition(getCenter());
		c->setSize(sf::Vector2f(300, 450));
		
		c->setSideOrigin();


		//c->updateSprite(2);
		c->setUpdate([this](RectEntity& e)
		{
			//e.animate();
			//Image i(e.getTexture());
			//i.light(Image(app["sprite.png"]), e, getMpf(), light);
			//e.updateTexture(i);
			//e.rotate(0.3);
			
		});

		app << c;
		
	}

	void keyPressedEventHandler(const sf::Event& event) override
	{
		c->updateSprite();
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
