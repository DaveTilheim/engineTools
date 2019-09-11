#include "Widget.hpp"

using namespace se;

void Widget::update()
{
	if(this->onHoveringLambda)
	{
		(*this->onHoveringLambda)();
	}
	if(this->onLeftClickLambda)
	{
		(*this->onLeftClickLambda)();
	}
	if(this->onRightClickLambda)
	{
		(*this->onRightClickLambda)();
	}
}

void Widget::onHovering(std::function<void(Widget *self)> lambda, std::function<void(Widget *self)> passLambda)
{
	if(!this->onHoveringLambda)
	{
		this->onHoveringLambda = new std::function<void()>();
	}
	*this->onHoveringLambda = [=]()
	{
		if(this->contains(static_cast<sf::Vector2f>(util::getMousePosition())))
		{
			this->hoverBool = true;
			lambda(this);
		}
		else
		{
			if(this->hoverBool)
			{
				passLambda(this);
				this->hoverBool = false;
			}
		}
	};
}

bool Widget::isGrabbable()
{
	if(this->grabbAble)
	{
		if(util::isButtonPressed(sf::Mouse::Left) && !this->contains(static_cast<sf::Vector2f>(util::getMousePosition())))
			this->grabbAble = true;
	}
	
	if(!util::isButtonPressed(sf::Mouse::Left) && this->contains(static_cast<sf::Vector2f>(util::getMousePosition())))
	{
		this->grabbAble = true;
	}
	else
	{
		if(!util::isButtonPressed(sf::Mouse::Left) && !this->contains(static_cast<sf::Vector2f>(util::getMousePosition())))
		{
			this->grabbAble = false;
		}
	}
	return this->grabbAble;
}

bool Widget::isClickAble(sf::Mouse::Button button)
{
	if(this->clickAble)
	{
		this->clickAble = !(util::isButtonPressed(button) && !this->contains(static_cast<sf::Vector2f>(util::getMousePosition())));
	}
	if(!util::isButtonPressed(button) && this->contains(static_cast<sf::Vector2f>(util::getMousePosition())))
	{
		this->clickAble = true;
	}
	return this->clickAble;
}

void Widget::onLeftClick(std::function<void(Widget *self)> lambda, std::function<void(Widget *self)> passLambda)
{
	if(!this->onLeftClickLambda)
	{
		this->onLeftClickLambda = new std::function<void()>();
	}
	*this->onLeftClickLambda = [=]()
	{
		if(this->isClickAble(sf::Mouse::Left) && this->contains(static_cast<sf::Vector2f>(util::getMousePosition())))
		{
			if(util::isButtonPressed(sf::Mouse::Left))
			{
				lambda(this);
				this->leftClickBool = true;
			}
			else
			{
				if(this->leftClickBool)
				{
					passLambda(this);
					this->leftClickBool = false;
				}
			}
		}
		else
		{
			this->leftClickBool = false;
		}
	};
}


void Widget::onRightClick(std::function<void(Widget *self)> lambda, std::function<void(Widget *self)> passLambda)
{
	if(!this->onRightClickLambda)
	{
		this->onRightClickLambda = new std::function<void()>();
	}
	*this->onRightClickLambda = [=]()
	{
		if(this->isClickAble(sf::Mouse::Right) && this->contains(static_cast<sf::Vector2f>(util::getMousePosition())))
		{
			if(util::isButtonPressed(sf::Mouse::Right))
			{
				lambda(this);
				this->rightClickBool = true;
			}
			else
			{
				if(this->rightClickBool)
				{
					passLambda(this);
					this->rightClickBool = false;
				}
			}
		}
		else
		{
			this->rightClickBool = false;
		}
	};
}

Widget::~Widget()
{
	if(this->onHoveringLambda)
	{
		delete this->onHoveringLambda;
	}
	if(this->onLeftClickLambda)
	{
		delete this->onLeftClickLambda;
	}
	std::cout << "Widget destroyed" << std::endl;
}
