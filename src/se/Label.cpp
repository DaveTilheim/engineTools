#include "Label.hpp"

using namespace se;

Label::Label(float x, float y, std::string text, sf::Font *font, Application *root, sf::Color color)
: Widget(0,0, 0,0, root)
{
	if(font)
	{
		this->text.setFont(*font);
	}
	this->text.setFillColor(color);
	this->text.setString(text);
	this->text.setOrigin(this->text.getLocalBounds().left, this->text.getLocalBounds().top);
	this->Widget::setSize(sf::Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height));
	this->setPosition(x, y);
	this->setMiddleOrigin();
	trace("Label creation");
}

sf::Text &Label::getText()
{
	return this->text;
}

void Label::render()
{
	this->Widget::render();
	this->root->getWindow()->draw(this->text);
}

void Label::setPosition(float x, float y)
{
	this->text.setPosition(x, y);
	this->Widget::setPosition(x, y);
}

void Label::setRotation(float angle)
{
	this->Widget::setRotation(angle);
	this->text.setRotation(angle);
}

void Label::move(float x, float y)
{
	this->Widget::move(x, y);
	this->text.setPosition(this->getPosition());
}

void Label::setOrigin(float x, float y)
{
	this->Widget::setOrigin(x, y);
	this->text.setOrigin(x+this->text.getLocalBounds().left, y+this->text.getLocalBounds().top);
}

void Label::setSize(sf::Vector2f v)
{
	this->Widget::setSize(v);
	this->setMiddleOrigin();
}

void Label::setSize(unsigned size, unsigned padding)
{
	this->text.setCharacterSize(size);
	this->Widget::setSize(sf::Vector2f(this->text.getGlobalBounds().width + padding*2, this->text.getGlobalBounds().height+padding*2));
	this->setMiddleOrigin();
}

void Label::setScale(float sx, float sy)
{
	this->Widget::setScale(sx, sy);
	this->setMiddleOrigin();
}

void Label::setScale(float sx)
{
	this->setSize(this->text.getCharacterSize()*sx);
	this->setMiddleOrigin();
}

void Label::center()
{
	this->setMiddleOrigin();
	sf::Rect<float> bounds = this->text.getLocalBounds();
	sf::Vector2f size = this->getSize();
	sf::Vector2f origin = this->text.getOrigin();
	this->text.setOrigin(bounds.width/2-size.x/2+origin.x, bounds.height/2-size.y/2+origin.y);
}

void Label::left()
{
	this->setMiddleOrigin();
	sf::Rect<float> bounds = this->text.getLocalBounds();
	sf::Vector2f size = this->getSize();
	sf::Vector2f origin = this->text.getOrigin();
	this->text.setOrigin(origin.x, bounds.height/2-size.y/2+origin.y);
}

void Label::right()
{
	this->setMiddleOrigin();
	sf::Rect<float> bounds = this->text.getLocalBounds();
	sf::Vector2f size = this->getSize();
	sf::Vector2f origin = this->text.getOrigin();
	this->text.setOrigin(-origin.x+bounds.width, bounds.height/2-size.y/2+origin.y);
}

void Label::top()
{
	this->setMiddleOrigin();
	sf::Rect<float> bounds = this->text.getLocalBounds();
	sf::Vector2f size = this->getSize();
	sf::Vector2f origin = this->text.getOrigin();
	this->text.setOrigin(bounds.width/2-size.x/2+origin.x, origin.y);
}

void Label::bottom()
{
	this->setMiddleOrigin();
	sf::Rect<float> bounds = this->text.getLocalBounds();
	sf::Vector2f size = this->getSize();
	sf::Vector2f origin = this->text.getOrigin();
	this->text.setOrigin(bounds.width/2-size.x/2+origin.x, origin.y-size.y+bounds.height);
}

void Label::rotate(float angle)
{
	this->Widget::rotate(angle);
	angle *= this->root->getDt();
	this->text.rotate(angle);
}

void Label::setTextFillColor(sf::Color &c)
{
	this->text.setFillColor(c);
}
