#ifndef WIDGET_HPP
#define WIDGET_HPP
#include <functional>
#include "Utilities.hpp"
#include "RectEntity.hpp"

namespace se
{
	class Widget : public RectEntity
	{
	private:
		bool isClickAble(sf::Mouse::Button button=sf::Mouse::Left);
		bool isGrabbable();
	protected:
		std::function<void()> *onHoveringLambda = nullptr;
		std::function<void()> *onLeftClickLambda = nullptr;
		std::function<void()> *onRightClickLambda = nullptr;
		bool hoverBool = false;
		bool leftClickBool = false;
		bool rightClickBool = false;
		bool clickAble = false;
		bool grabbAble = false;
	public:
		using RectEntity::RectEntity;
		~Widget();
		virtual void update() override;
		virtual void onHovering(std::function<void(Widget *self)> lambda, std::function<void(Widget *self)> passLambda=[](Widget *self){});
		virtual void onLeftClick(std::function<void(Widget *self)> lambda, std::function<void(Widget *self)> passLambda=[](Widget *self){});
		virtual void onRightClick(std::function<void(Widget *self)> lambda, std::function<void(Widget *self)> passLambda=[](Widget *self){});
		template <class T> void grabbing(bool pixelCol=false);
	};

	template <class T>
	void Widget::grabbing(bool pixelCol)
	{
		if(this->isGrabbable() && (this->contains(static_cast<sf::Vector2f>(util::getMousePosition())) || this->leftClickBool))
		{
			if(util::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i nmp = util::getMousePosition();
				if(pixelCol && !this->leftClickBool)
				{
					if(!this->pixelContains(static_cast<sf::Vector2f>(nmp)))
					{
						return;
					}
				}
				sf::Vector2i bmp = this->getRoot<T>()->mp;
				this->move(nmp.x - bmp.x, nmp.y - bmp.y, 1.0/this->getRoot<T>()->getFrameRate());
				this->leftClickBool = true;
			}
			else
			{
				this->leftClickBool = false;
			}
		}
		else
		{
			this->leftClickBool = false;
		}
	}
}

#endif
