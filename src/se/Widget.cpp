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

void Widget::onLeftClick(std::function<void(Widget *self)> lambda, std::function<void(Widget *self)> passLambda)
{
	if(!this->onLeftClickLambda)
	{
		this->onLeftClickLambda = new std::function<void()>();
	}
	*this->onLeftClickLambda = [=]()
	{
		if(this->contains(static_cast<sf::Vector2f>(util::getMousePosition())))
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
