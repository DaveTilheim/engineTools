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

		light.setRadius(350);
		
		light.setLux(50,1,0);
		light.setBasic(0.2,0,0,0.03);
	
		//setDynamicViewMode(true);
		setDynamicTraitement([this](DynamicView& view)
		{
			//view.image.light(view.reference, view.sprite, getMpf(), light);
			view.image.negative();
		});
		
		
		app["br.jpg"]->copyToImage().saveToFile("ez.jpg");

		setFilterMode(true);
		
		setFilter(sf::Color(20,20,168,200));


		setFilter(app["br.jpg"]);
		

		re = new LRectEntity(getCenter(), sf::Vector2f(100, 100), MIDDLE_CENTER);
		duplicateTexture("mini.png", re);


		re->setUpdate([this](RectEntity& e)
		{
			if(e.collision(getMpf()))
			{
				e.setPosition(rand()%1400, rand()%800);
			}
			Image image = e.getTexture();
			image.light(Image(app["mini.png"]), e, getMpf(), light);
			app["mini.png-"+e.addrStr()]->update(image);
			e.moveTowardInerty(getMpf(), sf::Vector2f(1,1));
		});

		for(int i = 0; i < 30; i++)
		{
			LRectEntity *e = new LRectEntity(*re);
			e->setPosition(rand()%1400, rand()%800);
			duplicateTexture("mini.png", e);
			app << e;
		}

		e.setPosition(300, 100);
		
		app << re;
	}

	void keyPressedEventHandler(const sf::Event& event) override
	{
		setFilterMode(false);
	}

	void mouseButtonPressedEventHandler(const sf::Event& event) override
	{
		setFilterMode(true);
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
