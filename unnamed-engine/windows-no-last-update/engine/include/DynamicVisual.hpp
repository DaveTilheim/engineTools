#ifndef DYNAMICVISUAL_HPP
#define DYNAMICVISUAL_HPP
#include <iostream>
#include "Dynamic.hpp"
#include "Visual.hpp"

using namespace std;

class DynamicVisual : public Dynamic, public Visual
{
protected:
	virtual void update() override = 0;
	virtual void view(sf::RenderWindow&) override = 0;
public:
	DynamicVisual(bool dynamicState=true, bool visualState=true);
	DynamicVisual(const DynamicVisual& cp);
	unsigned char getState() const;
	void setState(bool dynamicState, bool visualState);
	void pause();
	void play();
	DynamicVisual& operator=(const DynamicVisual& cp);
	friend ostream& operator<<(ostream& out, const DynamicVisual& obj);
};

#endif
