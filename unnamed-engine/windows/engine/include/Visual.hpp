#ifndef VISUAL_HPP
#define VISUAL_HPP
#include <SFML/Graphics/RenderWindow.hpp>


class Visual
{
private:
	bool visualState;
protected:
	virtual void view(sf::RenderWindow& window) const = 0;
public:
	Visual(bool state=true);
	Visual(const Visual& cp);
	bool getVisualState() const;
	void setVisualState(bool state);
	void _view(sf::RenderWindow& window) const;
	Visual& operator=(const Visual& cp);
};

#endif
