#include "MultiColorPicker.hpp"

using namespace se;


MultiColorPicker::MultiColorPicker(float x, float y, float w, float h, Application *root, const sf::Color&color, sf::Font *font) 
: ColorPicker(x, y, w, h,root, color, font), redValue(color.r), greenValue(color.g), blueValue(color.b), alphaValue(color.a)
{
	Slider *rSelector = new Slider(x, getPosition().y+h/2+20, w, 15, root, 255);
	Slider *gSelector = new Slider(x, getPosition().y+h/2+40, w, 15, root, 255);
	Slider *bSelector = new Slider(x, getPosition().y+h/2+60, w, 15, root, 255);
	Slider *aSelector = new Slider(x, getPosition().y+h/2+80, w, 15, root, 255);
	rSelector->getCursor().setSize(sf::Vector2f(5, rSelector->getCursor().getSize().y));
	rSelector->getCursor().setMiddleOrigin();
	rSelector->getCursor().setFillColor(sf::Color(255, 0, 0, 150));
	rSelector->getCursor().setOutline(sf::Color(0,0,0,150), 1);
	rSelector->setOutline(sf::Color::Black, 1);
	rSelector->setValue(color.r);
	gSelector->getCursor().setSize(sf::Vector2f(5, gSelector->getCursor().getSize().y));
	gSelector->getCursor().setMiddleOrigin();
	gSelector->getCursor().setFillColor(sf::Color(0, 255, 0, 150));
	gSelector->getCursor().setOutline(sf::Color(0,0,0,150), 1);
	gSelector->setValue(color.g);
	gSelector->setOutline(sf::Color::Black, 1);
	bSelector->getCursor().setSize(sf::Vector2f(5, bSelector->getCursor().getSize().y));
	bSelector->getCursor().setMiddleOrigin();
	bSelector->getCursor().setFillColor(sf::Color(0, 0, 255, 150));
	bSelector->getCursor().setOutline(sf::Color(0,0,0,150), 1);
	bSelector->setValue(color.b);
	bSelector->setOutline(sf::Color::Black, 1);
	aSelector->getCursor().setSize(sf::Vector2f(5, aSelector->getCursor().getSize().y));
	aSelector->getCursor().setMiddleOrigin();
	aSelector->getCursor().setFillColor(sf::Color(0, 0, 0, 150));
	aSelector->getCursor().setOutline(sf::Color(0,0,0,150), 1);
	aSelector->setValue(color.a);
	aSelector->setOutline(sf::Color::Black, 1);
	rSelector->setAtChange([this](Slider *s)
	{
		setRedValue(s->getValue());
		updateColor();
	});
	gSelector->setAtChange([this](Slider *s)
	{
		setGreenValue(s->getValue());
		updateColor();
	});
	bSelector->setAtChange([this](Slider *s)
	{
		setBlueValue(s->getValue());
		updateColor();
	});
	aSelector->setAtChange([this](Slider *s)
	{
		setAlphaValue(s->getValue());
		updateColor();
	});
	link("rSelector", *rSelector, true, true);
	link("gSelector", *gSelector, true, true);
	link("bSelector", *bSelector, true, true);
	link("aSelector", *aSelector, true, true);
	sf::Texture *rtxtr = new sf::Texture();
	sf::Texture *gtxtr = new sf::Texture();
	sf::Texture *btxtr = new sf::Texture();
	sf::Texture *atxtr = new sf::Texture();
	rtxtr->create(256, 15);
	gtxtr->create(256, 15);
	btxtr->create(256, 15);
	atxtr->create(256, 15);
	sf::Image rimg = rtxtr->copyToImage();
	sf::Image gimg = gtxtr->copyToImage();
	sf::Image bimg = btxtr->copyToImage();
	sf::Image aimg = atxtr->copyToImage();
	unsigned char r = 0, g = 0, b = 0, a = 0;
	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 256; j++)
		{
			rimg.setPixel(j, i, sf::Color(r, 0, 0));
			gimg.setPixel(j, i, sf::Color(0, g, 0));
			bimg.setPixel(j, i, sf::Color(0, 0, b));
			aimg.setPixel(j, i, sf::Color(0, 0, 0, a));
			r++, g++, b++, a++;
		}
	}
	rtxtr->update(rimg);
	rSelector->addTexture("_multi_color_picker0x0", rtxtr);
	rSelector->setTexture("_multi_color_picker0x0");
	gtxtr->update(gimg);
	gSelector->addTexture("_multi_color_picker0x0", gtxtr);
	gSelector->setTexture("_multi_color_picker0x0");
	btxtr->update(bimg);
	bSelector->addTexture("_multi_color_picker0x0", btxtr);
	bSelector->setTexture("_multi_color_picker0x0");
	atxtr->update(aimg);
	aSelector->addTexture("_multi_color_picker0x0", atxtr);
	aSelector->setTexture("_multi_color_picker0x0");
}

void MultiColorPicker::updateColor()
{
	setMainColor(sf::Color(getRedValue(), getGreenValue(), getBlueValue(), getAlphaValue()));
}

unsigned char MultiColorPicker::getRedValue() const
{
	return redValue;
}

unsigned char MultiColorPicker::getGreenValue() const
{
	return greenValue;
}

unsigned char MultiColorPicker::getBlueValue() const
{
	return blueValue;
}

unsigned char MultiColorPicker::getAlphaValue() const
{
	return alphaValue;
}

void MultiColorPicker::setRedValue(unsigned char redv)
{
	redValue = redv;
}

void MultiColorPicker::setGreenValue(unsigned char greenv)
{
	greenValue = greenv;
}

void MultiColorPicker::setBlueValue(unsigned char bluev)
{
	blueValue = bluev;
}

void MultiColorPicker::setAlphaValue(unsigned char alphav)
{
	alphaValue = alphav;
}
