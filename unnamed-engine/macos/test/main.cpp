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
	
	LTextProgressBar *pb;
	PR_Timer *timer;

	Light light;
	virtual void load() override
	{
		
		setBackgroundColor(sf::Color(100, 100, 100));
		getWindow().setFramerateLimit(0);
		app << "fonts/font.ttf";
		
		timer = new PR_Timer(ms(3.0), 3);
	
		
		pb = new LTextProgressBar(
		3, 0, 300, 50,
		new LTextEntity("...", *app("fonts/font.ttf"), 40, sf::Color::Black, 1, sf::Color::Yellow),
		MIDDLE_CENTER);
		pb->setFillColor(sf::Color::Black);
		pb->setPosition(getCenter());
		pb->setOutlineThickness(3);
		pb->setOutlineColor(sf::Color::Black);
		
		
		pb->setUpdate([this](TextProgressBar& pB)
		{

			pB.setCurrentValue(timer->getCurrent() / 1000.0);
			if(timer->isFinished())
			{
				removeLater(pb);
			}

		});

		timer->restart();
		app << pb << timer;
		
		
	}

	void keyPressedEventHandler(const sf::Event& event) override
	{
		//capture().copyToImage();
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
