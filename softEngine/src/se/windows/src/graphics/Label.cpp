#include <graphics/Label.hpp>

using namespace se;

Label::Label(float x, float y, std::string text, sf::Font *font, Application *root, sf::Color color)
: Widget(0,0, 0,0, root)
{
	this->text = new sf::Text();
	if(font)
	{
		this->text->setFont(*font);
	}
	this->text->setFillColor(color);
	this->text->setString(text);
	this->text->setOrigin(this->text->getLocalBounds().left, this->text->getLocalBounds().top);
	this->Widget::setSize(sf::Vector2f(this->text->getGlobalBounds().width, this->text->getGlobalBounds().height));
	this->setPosition(x, y);
	this->setMiddleOrigin();
	trace("Label creation");
}

Label::~Label()
{
	delete this->text;
	trace("Label deleted");
}

sf::Text &Label::getText()
{
	return *this->text;
}

std::string Label::getString()
{
	return this->text->getString();
}

void Label::setText(std::string text)
{
	this->text->setString(text);
	this->updatePadding();
}

std::vector<std::string> Label::getLines()
{
	std::string txt = this->getString();
	std::stringstream stream(txt);
	std::string token;
	std::vector<std::string> out;
	while(std::getline(stream, token, '\n'))
	{
		out.push_back(token);
	}
	return out;
}

std::string Label::getLastLine()
{
	std::vector<std::string> v = this->getLines();
	return v[v.size()-1];
}

std::string Label::getFirstLine()
{
	return this->getLines()[0];
}

std::vector<std::string> Label::getWords(unsigned lineid)
{
	std::string txt = this->getLines()[lineid];
	std::stringstream stream(txt);
	std::string token;
	std::vector<std::string> out;
	while(std::getline(stream, token, ' '))
	{
		util::removeChar(token, ' ');
		out.push_back(token);
	}
	return out;
}

std::vector<std::string> Label::getWords(std::string txt)
{
	std::stringstream stream(txt);
	std::string token;
	std::vector<std::string> out;
	while(std::getline(stream, token, ' '))
	{
		out.push_back(token);
	}
	return out;
}

void Label::setTextWithoutChange(std::string text)
{
	this->text->setString(text);
}

void Label::render()
{
	this->Widget::render();
	this->root->getWindow()->draw(*this->text);
}

void Label::setPosition(float x, float y)
{
	this->text->setPosition(x + this->padd, y + this->padd);
	this->Widget::setPosition(x, y);
}

void Label::setTLPosition(float x, float y)
{
	auto size = getSize();
	this->setPosition(size.x / 2 + x, size.y / 2 + y);
}

void Label::setRotation(float angle)
{
	this->Widget::setRotation(angle);
	this->text->setRotation(angle);
}

void Label::move(float x, float y)
{
	this->Widget::move(x, y);
	this->text->setPosition(this->getPosition().x + this->padd, this->getPosition().y + this->padd);
}

void Label::setOrigin(float x, float y)
{
	this->Widget::setOrigin(x, y);
	this->text->setOrigin(x+this->text->getLocalBounds().left, y+this->text->getLocalBounds().top);
}

void Label::updatePadding()
{
	this->Widget::setSize(sf::Vector2f(this->text->getGlobalBounds().width + this->padd*2, this->text->getGlobalBounds().height+this->padd*2));
	this->center();
}

void Label::padding(unsigned pdg)
{
	this->padd = pdg;
}

void Label::setSize(sf::Vector2f v)
{
	this->Widget::setSize(v);
	this->text->setPosition(getPosition().x + this->padd, getPosition().y + this->padd);
	this->setMiddleOrigin();
}

void Label::setCharSize(unsigned s)
{
	this->text->setCharacterSize(s);
}

void Label::setSize(unsigned size, unsigned padd)
{
	if(not padd)
		padd = this->padd;
	this->text->setCharacterSize(size);
	this->Widget::setSize(sf::Vector2f(this->text->getGlobalBounds().width + this->padd*2, this->text->getGlobalBounds().height+this->padd*2));
	this->setMiddleOrigin();
}

void Label::setScale(float sx, float sy)
{
	this->Widget::setScale(sx, sy);
	this->setMiddleOrigin();
}

void Label::setScale(float sx)
{
	this->setSize(this->text->getCharacterSize()*sx);
	this->setMiddleOrigin();
}

void Label::center()
{
	this->setMiddleOrigin();
	sf::Rect<float> bounds = this->text->getLocalBounds();
	sf::Vector2f size = this->getSize();
	sf::Vector2f origin = this->text->getOrigin();
	this->text->setOrigin(bounds.width/2-size.x/2+origin.x, bounds.height/2-size.y/2+origin.y);
}

void Label::left()
{
	this->setMiddleOrigin();
	sf::Rect<float> bounds = this->text->getLocalBounds();
	sf::Vector2f size = this->getSize();
	sf::Vector2f origin = this->text->getOrigin();
	this->text->setOrigin(origin.x, bounds.height/2-size.y/2+origin.y);
}

void Label::right()
{
	this->setMiddleOrigin();
	sf::Rect<float> bounds = this->text->getLocalBounds();
	sf::Vector2f size = this->getSize();
	sf::Vector2f origin = this->text->getOrigin();
	this->text->setOrigin(-origin.x+bounds.width, bounds.height/2-size.y/2+origin.y);
}

void Label::top()
{
	this->setMiddleOrigin();
	sf::Rect<float> bounds = this->text->getLocalBounds();
	sf::Vector2f size = this->getSize();
	sf::Vector2f origin = this->text->getOrigin();
	this->text->setOrigin(bounds.width/2-size.x/2+origin.x, origin.y);
}

void Label::bottom()
{
	this->setMiddleOrigin();
	sf::Rect<float> bounds = this->text->getLocalBounds();
	sf::Vector2f size = this->getSize();
	sf::Vector2f origin = this->text->getOrigin();
	this->text->setOrigin(bounds.width/2-size.x/2+origin.x, origin.y-size.y+bounds.height);
}

void Label::rotate(float angle)
{
	this->Widget::rotate(angle);
	angle *= this->root->getDt();
	this->text->rotate(angle);
}

void Label::setTextFillColor(const sf::Color &c)
{
	this->text->setFillColor(c);
}
