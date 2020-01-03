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
	LRectEntity e;

	Light light;
	virtual void load() override
	{
		setBackgroundColor(sf::Color(100, 100, 100));
		getWindow().setFramerateLimit(0);
		app << "mini.png" << "br.jpg";

		//light.setRadius(350);
		
		

		re = new LRectEntity(getCenter(), sf::Vector2f(1,1), MIDDLE_CENTER);
		//duplicateTexture("mini.png", re);

		re->setFillColor(sf::Color(rand()%256, rand()%256, rand()%256));
		re->setUpdate([this](RectEntity& e)
		{
			if(e.collision(getMpf()))
			{
				e.setPosition(rand()%1400, rand()%800);
			}
			
			e.moveTowardInerty(getMpf(), sf::Vector2f(1,1));
		});

		for(int i = 0; i < 100000; i++)
		{
			LRectEntity *e = new LRectEntity(*re);
			e->setFillColor(sf::Color(rand()%256, rand()%256, rand()%256));
			e->setPosition(rand()%1400, rand()%800);
			app << e;
		}

		e.setPosition(300, 100);
		
		app << re;
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
