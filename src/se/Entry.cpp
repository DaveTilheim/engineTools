#include "Entry.hpp"

using namespace se;

Entry::Entry(float x, float y, std::string text, sf::Font *font, Application *root, sf::Color color)
: Label(x, y, text, font, root, color)
{
	this->onLeftClick([this](Widget *w){
		this->focus = true;
		this->setOutline(this->focusedColor);
	});
	trace("Entry creation");
}

void Entry::update()
{
	this->Widget::update();
	if(this->focus)
	{
		if(util::isButtonPressed(sf::Mouse::Left) and not this->contains(static_cast<sf::Vector2f>(util::getMousePosition())))
		{
			this->focus = false;
			this->setOutline(this->unfocusedColor);
		}
	}
}

void Entry::outOfBounds()
{
	sf::Vector2f size = this->getSize();
	sf::Text& text = this->getText();
	if(size.x - this->padd < text.getGlobalBounds().width)
	{
		this->setTextWithoutChange(this->getString().substr(0, this->getString().size()-1));
	}
	if(size.y - this->padd < text.getGlobalBounds().height)
	{
		while(this->getString().size() and this->getString()[this->getString().size()-1] != '\n')
		{
			this->setTextWithoutChange(this->getString().substr(0, this->getString().size()-1));
		}
		if(this->getString()[this->getString().size()-1] == '\n')
		{
			this->setTextWithoutChange(this->getString().substr(0, this->getString().size()-1));
		}
	}
}

void Entry::keyCodeCatch(const char kcode)
{
	if(this->focus and kcode)
	{
		if(kcode == 10 and not this->allowNewline)
		{
			return;
		}
		if(kcode == 8)
		{
			if(not (this->getString() == this->newlineStr))
			{
				this->setTextWithoutChange(this->getString().substr(0, this->getString().size()-1));
			}
		}
		else
		{
			trace(std::to_string((int)kcode).c_str());
			this->setTextWithoutChange(this->getString() + kcode);
			if(kcode == 10 and this->newlineStr.size())
			{
				this->setTextWithoutChange(this->getString() + this->newlineStr);
			}
			if(this->sizeLocked)
			{
				this->outOfBounds();
			}
		}
	}
}

void Entry::setNewlineStr(std::string nlc)
{
	this->newlineStr = nlc;
}

void Entry::allowNewLine(bool b)
{
	this->allowNewline = b;
}

void Entry::lockSize(bool lock)
{
	this->sizeLocked = lock;
}

void Entry::setFocusedColor(const sf::Color& c)
{
	this->focusedColor = c;
}

void Entry::setUnfocusedColor(const sf::Color& c)
{
	this->unfocusedColor = c;
}
