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
#include <InputEntity.hpp>
#include <LambdaDynamic.hpp>
#include <ProgressBar.hpp>
#include <Timer.hpp>

using namespace std;



class App : public SmartApplication
{
public:
	using SmartApplication::SmartApplication;

	Light light;

	LInputEntity *t = nullptr;
	LEntityText *txt;
	sf::Texture text;
	
	void load() override
	{
		setBackgroundColor(sf::Color(100, 100, 100));
		//getWindow().setFramerateLimit(0);

		
		/*setDynamicViewMode(true);
		setDynamicTraitement([this](DynamicView& d)
		{
			d.image.light(d.reference, getMpf(), light);
		});*/
		
		app << "fonts/lemon_milk/LemonMilk.otf";
		t = new LInputEntity(getCenter(), "abcdefghi", *app("fonts/lemon_milk/LemonMilk.otf"), 15, MIDDLE_CENTER);
		t->setFillColor(sf::Color::Green);
		t->setUpdate([this](InputEntity& t)
		{
			t.moveTowardInerty(getMp().x, getMp().y, 1,1);
			//t.setPosition((int)getMpf().x, (int)getMpf().y);
			//t.rotate(0.2);
		});
		t->setOutlineThickness(3);
		t->setOutlineColor(sf::Color::Red);
		t->setFocus(true);
		t->setNewLine(true);


		

		app << t;

	}

	
	void keyPressedEventHandler(const sf::Event& event) override
	{
		//t->rotate(30);
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
