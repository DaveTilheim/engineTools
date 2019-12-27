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
#include <LambdaDynamic.hpp>
#include <Timer.hpp>

using namespace std;


class App : public SmartApplication
{
public:
	using SmartApplication::SmartApplication;
	
	LRectEntity *c;

	virtual void load() override
	{
		app << "mini-mush.png";
		c = new LRectEntity();
		duplicateTexture("mini-mush.png", c);
		c->setSize(sf::Vector2f(300, 300));
		c->setSideOrigin();
		c->setPosition(getCenter());

		c->setUpdate([this](RectEntity& r)
		{
			cout << r.getTLPosition() << endl;
			cout << r.getSidePosition(TOP_LEFT) << endl;
			Image img = r.getTexture();
			img.light(
				app["mini-mush.png"]->copyToImage(),
				r.getTLPosition(),
				getMpf(),
				r.getSize(),
				r.getRotation(),
				r.getSidePosition());
			r.updateTexture(img);
			r.rotate(1);
		});
		app << c;
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
