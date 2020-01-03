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
#include <TextEntity.hpp>
#include <LambdaDynamic.hpp>
#include <ProgressBar.hpp>
#include <Timer.hpp>

using namespace std;

extern LTextEntity TXT_ref;

class App : public SmartApplication
{
public:
	using SmartApplication::SmartApplication;
	
	LRectEntity *re = nullptr;

	Light light;

	LRectEntity *wall = nullptr;
	
	void load() override
	{
		setBackgroundColor(sf::Color(100, 100, 100));
		getWindow().setFramerateLimit(0);

		app << "mini-mush.png" << "br.jpg" << "wall.jpg";

		light.setRadius(300);
		//light.setJump(10);
		//light.setPixelizedMode(true);

		wall = new LRectEntity(app["wall.jpg"], sf::Vector2f(0,0), TOP_LEFT);
		wall->setSize(static_cast<sf::Vector2f>(getWindow().getSize()));

		
		
		setDynamicViewMode(true);
		setDynamicTraitement([this](DynamicView& d)
		{
			d.image.light(d.reference, getMpf(), light);
		});

		re = new LRectEntity(app["mini-mush.png"], getCenter(), MIDDLE_CENTER);

		duplicateTexture("mini-mush.png", "mini-mush-ref.png");
	

		re->setUpdate([this](RectEntity& e)
		{
			e.moveTowardInerty(getMpf(), sf::Vector2f(1,1));
		});

		app << wall<< re;

	}

	void keyPressedEventHandler(const sf::Event& event) override
	{
		LRectEntity *e = new LRectEntity(*re);
		e->setPosition(rand()%1400, rand()%800);
		app << e;
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
