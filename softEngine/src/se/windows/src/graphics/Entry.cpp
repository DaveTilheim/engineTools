#include <graphics/Entry.hpp>

using namespace se;

Entry::Entry(float x, float y, std::string text, sf::Font *font, Application *root, sf::Color color)
: Label(x, y, text, font, root, color)
{
	this->onLeftClick([this](Widget *w){
		this->focus = true;
		this->cursor = this->getString().size();
		this->setOutline(this->focusedColor);
	});
	this->cursor = text.size();
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
		else
		{
			if(this->cursorKeysRelease)
			{
				if(util::isKeyPressed(sf::Keyboard::Left))
				{
					this->cursor--;
					if(this->cursor < 0)
					{
						this->cursor = 0;
					}
					this->cursorKeysRelease = false;
				}
				else if(util::isKeyPressed(sf::Keyboard::Right))
				{
					this->cursor++;
					if(this->cursor >= this->getString().size())
					{
						this->cursor = this->getString().size();
					}
					this->cursorKeysRelease = false;
				}
			}
			else
			{
				if(not util::isKeyPressed(sf::Keyboard::Right) and not util::isKeyPressed(sf::Keyboard::Left))
				{
					this->cursorKeysRelease = true;
				}
			}
		}
	}
}

void Entry::outOfBounds()
{
	sf::Vector2f size = this->getSize();
	sf::Text& text = this->getText();
	while(size.x - this->padd < text.getGlobalBounds().width)
	{
		this->removeAt(this->cursor);
		text = this->getText();
	}
	while(size.y - this->padd < text.getGlobalBounds().height)
	{
		if(this->newlineStr.size())
		{
			for(int i = 0; i < this->newlineStr.size(); i++)
			{
				this->removeAt(this->cursor);
			}
		}
		this->removeAt(this->cursor);
	}
}

void Entry::insert(std::string s, int pos)
{
	if(pos < 0 or pos > this->getString().size())
	{
		return;
	}
	std::string tmp = this->getString();
	if(pos >= 0)
	{
		tmp.insert(pos, s);
		this->cursor = pos + s.size();
	}
	else
	{
		tmp += s;
		this->cursor = tmp.size();
	}
	this->setTextWithoutChange(tmp);
	if(this->sizeLocked)
	{
		this->outOfBounds();
	}
}

void Entry::insert(char c, int pos)
{
	this->insert(std::string(1, c), pos);
}

void Entry::removeAt(int pos)
{
	if(pos < 1 or pos > this->getString().size())
	{
		return;
	}
	std::string tmp = this->getString();
	if(pos >= 0)
	{
		tmp.erase(tmp.begin() + pos - 1);
		this->cursor--;
	}
	else
	{
		tmp.erase(tmp.size()-1);
		this->cursor--;
	}
	this->setTextWithoutChange(tmp);
}

void Entry::keyCatch(char kcode)
{
	if(this->focus and kcode)
	{
		trace(std::to_string((int)kcode).c_str());
		if(kcode == 10 and not this->allowNewline)
		{
			return;
		}
		if(kcode == 8)
		{
			if(not (this->getString() == this->newlineStr))
			{
				this->removeAt(this->cursor);
			}
		}
		else
		{
			this->insert(kcode, this->cursor);
			if(kcode == 10 and this->newlineStr.size())
			{
				this->insert(this->newlineStr, this->cursor);
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
