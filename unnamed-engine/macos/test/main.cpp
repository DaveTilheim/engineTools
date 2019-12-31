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
#include <Timer.hpp>

using namespace std;


class App : public SmartApplication
{
public:
	using SmartApplication::SmartApplication;
	
	LSpriteEntity *se;


	Light light;
	virtual void load() override
	{
		setBackgroundColor(sf::Color(100, 100, 100));
		getWindow().setFramerateLimit(0);
		app << "fonts/font.ttf";
		Image i(Image::convert(LTextEntity(getCenter(), "Hello world!", *app("fonts/font.ttf"), 50)), "label.png");
		app << i;
		i.setName("label-ref.png");
		app << i;
		se = new LSpriteEntity(app["label.png"], getCenter(), MIDDLE_CENTER);
		/*Image i(Image::convert(*c), "label");
		i.saveToFile("label.png");
		app << i;*/
		
		se->setUpdate([this](SpriteEntity& e)
		{
			Image i = e.getTexture();
			i.light(app["label-ref.png"]->copyToImage(), e, getMpf(), light);
			e.updateTexture(i);
			e.rotate(1);
		});
		
		
		
		app << se;
		
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
