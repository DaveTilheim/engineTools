#ifndef SYSTEMENTITY_HPP
#define SYSTEMENTITY_HPP
#include "DynamicVisual.hpp"
#include "Debug.hpp"


class SystemEntity : public DynamicVisual
{
protected:
	static int systemEntityCounter;
	virtual void update() override = 0;
	virtual void view(sf::RenderWindow& window) override = 0;
public:
	using DynamicVisual::DynamicVisual;
	SystemEntity();
	SystemEntity(const SystemEntity& cp);
	virtual ~SystemEntity();
	SystemEntity& operator=(const SystemEntity& cp);
	static int getSystemEntityCounter();
};


#endif
