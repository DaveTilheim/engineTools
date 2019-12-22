#ifndef SYSTEMENTITY_HPP
#define SYSTEMENTITY_HPP
#include "DynamicVisual.hpp"


class SystemEntity : public DynamicVisual
{
protected:
	virtual void update() override = 0;
	virtual void view(sf::RenderWindow& window) const override = 0;
public:
	using DynamicVisual::DynamicVisual;
	SystemEntity(const SystemEntity& cp);
	virtual ~SystemEntity();
	SystemEntity& operator=(const SystemEntity& cp);
};


#endif
