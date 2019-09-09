#ifndef __WIDGET_HPP__
#define __WIDGET_HPP__
#include <functional>
#include "Utilities.hpp"
#include "RectEntity.hpp"

namespace se
{
	class Widget : public RectEntity
	{
	protected:
		std::function<void()> *onHoveringLambda = nullptr;
		std::function<void()> *onLeftClickLambda = nullptr;
		bool hoverBool = false;
		bool leftClickBool = false;
	public:
		using RectEntity::RectEntity;
		~Widget();
		virtual void update() override;
		virtual void onHovering(std::function<void(Widget *self)> lambda, std::function<void(Widget *self)> passLambda=[](Widget *self){});
		virtual void onLeftClick(std::function<void(Widget *self)> lambda, std::function<void(Widget *self)> passLambda=[](Widget *self){});
	};
}

#endif
