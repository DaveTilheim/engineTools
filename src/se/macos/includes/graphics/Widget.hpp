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
		bool leftClickGrabbableBool = false;
		bool rightClickBool = false;
		bool clickAble = false;
		bool grabbAble = false;
	public:
		using RectEntity::RectEntity;
		virtual ~Widget();
		virtual void update() override;
		virtual void onHovering(std::function<void(Widget *self)> lambda, std::function<void(Widget *self)> passLambda=[](Widget *self){});
		virtual void onLeftClick(std::function<void(Widget *self)> lambda, bool one=false, std::function<void(Widget *self)> passLambda=[](Widget *self){});
		virtual void onRightClick(std::function<void(Widget *self)> lambda, bool one=false, std::function<void(Widget *self)> passLambda=[](Widget *self){});
		virtual void onLeftHoldClick(std::function<void(Widget *self)> lambda, std::function<void(Widget *self)> passLambda=[](Widget *self){});
		virtual void onRightHoldClick(std::function<void(Widget *self)> lambda, std::function<void(Widget *self)> passLambda=[](Widget *self){});
		template <class T> void grabbing(bool pixelCol=false);
	};

	template <class T>
	void Widget::grabbing(bool pixelCol)
	{
		if(this->isGrabbable() and (this->contains(static_cast<sf::Vector2f>(util::getMousePosition())) or this->leftClickGrabbableBool))
		{
			if(util::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i nmp = util::getMousePosition();
				if(pixelCol and !this->leftClickGrabbableBool)
				{
					if(!this->pixelContains(static_cast<sf::Vector2f>(nmp)))
					{
						return;
					}
				}
				sf::Vector2i bmp = this->getRoot<T>()->mp;
				this->move(nmp.x - bmp.x, nmp.y - bmp.y, 1.0/this->getRoot<T>()->getFrameRate());
				this->leftClickGrabbableBool = true;
			}
			else
			{
				this->leftClickGrabbableBool = false;
			}
		}
		else
		{
			this->leftClickGrabbableBool = false;
		}
	}
}

#endif
