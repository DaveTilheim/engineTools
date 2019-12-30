#ifndef ANIMATED_HPP
#define ANIMATED_HPP
#include "Image.hpp"
#include <SFML/Graphics.hpp>

class Animated
{
private:
	float animationSpeed = 1.0f; // per second
	int nbSprites = 0;
	int beginSprite = 0;
protected:
	sf::Clock animationClock;
public:
	virtual void updateTexture(const Image& img);
	virtual void replaceTexture(const Image& img);
	virtual void animate();
	virtual void updateSprite();
	virtual void updateSprite(int index);
	float getAnimationSpeed() const;
	int getNbSprites() const;
	int getBeginSprite() const;
	void setAnimationSpeed(float aspd=1.0f);
	void setNbSprites(int nb);
	void setBeginSprite(int bs);
	void setAnimationOptions(float as, int nbs, int bs);
	void setSpriteSize(int w, int h);
};


#endif
